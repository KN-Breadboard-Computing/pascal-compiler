#include "machine_code_generator.hpp"

namespace machine_code {
int MachineCodeGenerator::registersNumber_{2};

void MachineCodeGenerator::generate(const std::map<std::string, bblocks::BBControlFlowGraph>& cfg, RegisterAllocator allocator) {
  for (const auto& [functionName, controlFlowGraph] : cfg) {
    enumerateBlockLabels(functionName, controlFlowGraph);

    liveRanges_.insert({functionName, LiveRangesGenerator{}});
    liveRanges_[functionName].generate(controlFlowGraph, blockBounds_[functionName]);

    switch (allocator) {
      case RegisterAllocator::LINEAR_SCAN:
        regAllocators_[functionName] = std::make_unique<LinearScanRegAlloc>(registersNumber_);
        break;
      case RegisterAllocator::GRAPH_COLORING:
        regAllocators_[functionName] = std::make_unique<InterferenceGraphRegAlloc>(registersNumber_);
        break;
    }
    regAllocators_[functionName]->allocateRegisters(liveRanges_.at(functionName).getLiveRanges());

    generateVariableOffsets(functionName);

    // generate machine code
    machineCode_.insert({functionName, std::vector<MachineInstruction>{}});
    std::queue<std::string> blocksToProcess;
    std::set<std::string> visitedBlocks;
    blocksToProcess.push(controlFlowGraph.getEntryLabel());
    visitedBlocks.insert(controlFlowGraph.getEntryLabel());
    while (!blocksToProcess.empty()) {
      const std::string blockLabel = blocksToProcess.front();
      const auto& block = controlFlowGraph.getBasicBlock(blockLabel);
      blocksToProcess.pop();

      machineCode_[functionName].push_back(MachineInstruction(MachineInstruction::LABEL, {blockLabel}));
      for (const auto& instruction : block.getInstructions()) {
        const std::vector<MachineInstruction> ins = generate(instruction);
        machineCode_[functionName].insert(machineCode_[functionName].end(), ins.begin(), ins.end());
      }

      for (const auto& outLink : controlFlowGraph.getOutLinks(blockLabel)) {
        if (visitedBlocks.find(outLink) == visitedBlocks.end()) {
          blocksToProcess.push(outLink);
          visitedBlocks.insert(outLink);
        }
      }
    }

    calculateLabelValues(functionName);
  }
}

void MachineCodeGenerator::saveLiveRanges(std::ostream& output) const {
  for (const auto& [functionName, liveRanges] : liveRanges_) {
    liveRanges.saveLiveRanges(output);
    output << std::endl;
    regAllocators_.at(functionName)->saveAllocatedRegisters(output);
    output << std::endl;
    for (const auto& [variable, offset] : variableOffsets_.at(functionName)) {
      output << variable << " offset " << offset << std::endl;
    }
  }
}

void MachineCodeGenerator::saveMachineCode(std::ostream& output) {
  for (const auto& [functionName, instructions] : machineCode_) {
    for (const auto& instruction : instructions) {
      output << instruction.toString() << "\n";
    }
  }
}

void MachineCodeGenerator::saveAssembly(std::ostream& output) {
  for (const auto& [functionName, instructions] : machineCode_) {
    for (const auto& instruction : instructions) {
      if (instruction.getType() == MachineInstruction::Type::LABEL) {
        continue;
      }

      MachineInstruction instructionCopy = instruction;
      for (const auto& [label, value] : labelValues_[functionName]) {
        const auto addr = MachineCodeGenerator::getBinaryFullAddress(value);
        instructionCopy.replaceOperand(label, {addr.first, addr.second});
      }
      output << instructionCopy.toAssembly() << "\n";
    }
  }
}

void MachineCodeGenerator::saveBinary(std::ostream& output) {
  for (const auto& [functionName, instructions] : machineCode_) {
    for (const auto& instruction : instructions) {
      if (instruction.getType() == MachineInstruction::Type::LABEL) {
        continue;
      }

      MachineInstruction instructionCopy = instruction;
      for (const auto& [label, value] : labelValues_[functionName]) {
        const auto& addr = MachineCodeGenerator::getBinaryFullAddress(value);
        instructionCopy.replaceOperand(label, {addr.first, addr.second});
      }

      const uint8_t byte = static_cast<uint8_t>(std::stoi(instructionCopy.getBinaryCode(), nullptr, 2));
      output.write(reinterpret_cast<const char*>(&byte), sizeof(byte));

      for (const auto& operand : instructionCopy.getOperands()) {
        const uint8_t word = static_cast<uint8_t>(std::stoi(operand, nullptr, 2));
        output.write(reinterpret_cast<const char*>(&word), sizeof(word));
      }
    }
  }
}

void MachineCodeGenerator::enumerateBlockLabels(const std::string& name, const bblocks::BBControlFlowGraph& cfg) {
  blocksOrder_.insert({name, std::vector<std::string>{}});

  std::map<std::string, std::pair<std::size_t, std::size_t>> bounds;
  std::size_t labelCounter = 0;

  std::stack<std::string> blocksToProcess;
  std::set<std::string> visitedBlocks;

  blocksToProcess.push(cfg.getEntryLabel());
  visitedBlocks.insert(cfg.getEntryLabel());
  while (!blocksToProcess.empty()) {
    const std::string blockLabel = blocksToProcess.top();
    blocksToProcess.pop();
    blocksOrder_[name].push_back(blockLabel);

    bounds.insert({blockLabel, {labelCounter, labelCounter + cfg.getBasicBlock(blockLabel).getInstructions().size() - 1}});
    labelCounter += cfg.getBasicBlock(blockLabel).getInstructions().size();

    if (blockLabel == cfg.getExitLabel()) {
      continue;
    }

    std::vector<std::string> outLinks = cfg.getOutLinks(blockLabel);
    std::sort(outLinks.begin(), outLinks.end(), [](const std::string& a, const std::string& b) {
      return std::atoi(a.substr(2, a.size() - 2).c_str()) > std::atoi(b.substr(2, b.size() - 2).c_str());
    });

    for (const auto& outLink : outLinks) {
      if (visitedBlocks.find(outLink) == visitedBlocks.end()) {
        blocksToProcess.push(outLink);
        visitedBlocks.insert(outLink);
      }
    }
  }

  blockBounds_.insert({name, bounds});
}

void MachineCodeGenerator::generateVariableOffsets(const std::string& name) {
  variableOffsets_.insert({name, std::map<std::string, uint16_t>{}});

  std::size_t offset = 0;
  for (const auto& [var, reg] : regAllocators_[name]->getAllocatedRegisters()) {
    if (reg == -1) {
      variableOffsets_[name].insert({var, offset});
      offset += 1;
    }
  }

  currentFunctionVariableOffsets_ = variableOffsets_[name];
}

void MachineCodeGenerator::calculateLabelValues(const std::string& name) {
  labelValues_.insert({name, std::map<std::string, uint16_t>{}});

  std::size_t currentLabelValue = 0;
  for (const auto& instruction : machineCode_[name]) {
    if (instruction.getType() == MachineInstruction::Type::LABEL) {
      labelValues_[name].insert({instruction.getOperands().front(), currentLabelValue});
    }
    else {
      currentLabelValue++;
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generate(const std::unique_ptr<bblocks::BBInstruction>& instruction) {
  const std::vector<bblocks::BBInstruction::TemplateArgumentType>& templateArguments = instruction->getTemplateTypes();
  switch (instruction->getType()) {
    case bblocks::BBInstruction::Type::MOVE: {
      switch (templateArguments[0]) {
        case bblocks::BBInstruction::TemplateArgumentType::STRING:
          switch (templateArguments[1]) {
            case bblocks::BBInstruction::TemplateArgumentType::STRING:
              return generateMove(*dynamic_cast<bblocks::BBMoveVV*>(instruction.get()));
            case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
              return generateMove(*dynamic_cast<bblocks::BBMoveVN*>(instruction.get()));
          }
          break;
        case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
          switch (templateArguments[1]) {
            case bblocks::BBInstruction::TemplateArgumentType::STRING:
              return generateMove(*dynamic_cast<bblocks::BBMoveNV*>(instruction.get()));
            case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
              return generateMove(*dynamic_cast<bblocks::BBMoveNN*>(instruction.get()));
          }
      }
    }
    case bblocks::BBInstruction::Type::UNARY_OPERATION: {
      switch (templateArguments[0]) {
        case bblocks::BBInstruction::TemplateArgumentType::STRING:
          switch (templateArguments[1]) {
            case bblocks::BBInstruction::TemplateArgumentType::STRING:
              return generateUnaryOperation(*dynamic_cast<bblocks::BBUnaryOperationVV*>(instruction.get()));
            case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
              return generateUnaryOperation(*dynamic_cast<bblocks::BBUnaryOperationVN*>(instruction.get()));
          }
          break;
        case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
          switch (templateArguments[1]) {
            case bblocks::BBInstruction::TemplateArgumentType::STRING:
              return generateUnaryOperation(*dynamic_cast<bblocks::BBUnaryOperationNV*>(instruction.get()));
            case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
              return generateUnaryOperation(*dynamic_cast<bblocks::BBUnaryOperationNN*>(instruction.get()));
          }
      }
    }
    case bblocks::BBInstruction::Type::BINARY_OPERATION: {
      switch (templateArguments[0]) {
        case bblocks::BBInstruction::TemplateArgumentType::STRING:
          switch (templateArguments[1]) {
            case bblocks::BBInstruction::TemplateArgumentType::STRING:
              switch (templateArguments[2]) {
                case bblocks::BBInstruction::TemplateArgumentType::STRING:
                  return generateBinaryOperation(*dynamic_cast<bblocks::BBBinaryOperationVVV*>(instruction.get()));
                case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
                  return generateBinaryOperation(*dynamic_cast<bblocks::BBBinaryOperationVVN*>(instruction.get()));
              }
              break;
            case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
              switch (templateArguments[2]) {
                case bblocks::BBInstruction::TemplateArgumentType::STRING:
                  return generateBinaryOperation(*dynamic_cast<bblocks::BBBinaryOperationVNV*>(instruction.get()));
                case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
                  return generateBinaryOperation(*dynamic_cast<bblocks::BBBinaryOperationVNN*>(instruction.get()));
              }
          }
          break;
        case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
          switch (templateArguments[1]) {
            case bblocks::BBInstruction::TemplateArgumentType::STRING:
              switch (templateArguments[2]) {
                case bblocks::BBInstruction::TemplateArgumentType::STRING:
                  return generateBinaryOperation(*dynamic_cast<bblocks::BBBinaryOperationNVV*>(instruction.get()));
                case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
                  return generateBinaryOperation(*dynamic_cast<bblocks::BBBinaryOperationNVN*>(instruction.get()));
              }
              break;
            case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
              switch (templateArguments[2]) {
                case bblocks::BBInstruction::TemplateArgumentType::STRING:
                  return generateBinaryOperation(*dynamic_cast<bblocks::BBBinaryOperationNNV*>(instruction.get()));
                case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
                  return generateBinaryOperation(*dynamic_cast<bblocks::BBBinaryOperationNNN*>(instruction.get()));
              }
          }
      }
    }
    case bblocks::BBInstruction::Type::BRANCH: {
      switch (templateArguments[0]) {
        case bblocks::BBInstruction::TemplateArgumentType::STRING:
          return generateBranch(*dynamic_cast<bblocks::BBBranchV*>(instruction.get()));
        case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
          return generateBranch(*dynamic_cast<bblocks::BBBranchN*>(instruction.get()));
      }
    }
    case bblocks::BBInstruction::Type::CALL: {
      return generateCall(*dynamic_cast<bblocks::BBCall*>(instruction.get()));
    }
    case bblocks::BBInstruction::Type::RET: {
      return generateRet(*dynamic_cast<bblocks::BBRet*>(instruction.get()));
    }
    case bblocks::BBInstruction::Type::HALT: {
      return generateHalt(*dynamic_cast<bblocks::BBHalt*>(instruction.get()));
    }
    case bblocks::BBInstruction::Type::PHI:
    case bblocks::BBInstruction::Type::UNSPECIFIED: {
      throw std::runtime_error("Unspecified instruction type");
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMove(const bblocks::BBMoveVV& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src = instruction.getSource();
  const std::string dest = instruction.getDestination();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto srcAddr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[src]);
      if (srcAddr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {srcAddr.first.value(), srcAddr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS_ZP, {srcAddr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER: {
      const auto destAddr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[dest]);
      if (destAddr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {destAddr.first.value(), destAddr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A_ZP, {destAddr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMove(const bblocks::BBMoveVN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src = instruction.getSource();
  const int dest = instruction.getDestination();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto srcAddr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[src]);
      if (srcAddr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {srcAddr.first.value(), srcAddr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS_ZP, {srcAddr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER:
      throw std::runtime_error("Register cannot be number type");
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMove(const bblocks::BBMoveNV& instruction) {
  std::vector<MachineInstruction> instructions;
  const int src = instruction.getSource();
  const std::string dest = instruction.getDestination();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {MachineCodeGenerator::getBinaryAnyInt(src)}));
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::runtime_error("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER: {
      const auto destAddr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[dest]);
      if (destAddr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {destAddr.first.value(), destAddr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A_ZP, {destAddr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMove(const bblocks::BBMoveNN& instruction) {
  std::vector<MachineInstruction> instructions;
  const int src = instruction.getSource();
  const int dest = instruction.getDestination();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {MachineCodeGenerator::getBinaryAnyInt(src)}));
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::runtime_error("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER:
      throw std::runtime_error("Register cannot be number type");
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperation(const bblocks::BBUnaryOperationVV& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src = instruction.getSource();
  const std::string dest = instruction.getDestination();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto srcAddr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[src]);
      if (srcAddr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {srcAddr.first.value(), srcAddr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS_ZP, {srcAddr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::BBUnaryOperationEnum::NEG:
      instructions.push_back(MachineInstruction(MachineInstruction::NEG_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::NOT:
      instructions.push_back(MachineInstruction(MachineInstruction::INV_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::INC:
      instructions.push_back(MachineInstruction(MachineInstruction::INC_A));
      break;
    case bblocks::BBUnaryOperationEnum::DEC:
      instructions.push_back(MachineInstruction(MachineInstruction::DEC_A));
      break;
    case bblocks::BBUnaryOperationEnum::SHL:
      instructions.push_back(MachineInstruction(MachineInstruction::SHL_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::SHR:
      instructions.push_back(MachineInstruction(MachineInstruction::SHR_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::SAR:
      instructions.push_back(MachineInstruction(MachineInstruction::DIV2_A_A));
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER: {
      const auto destAddr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[dest]);
      if (destAddr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {destAddr.first.value(), destAddr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A_ZP, {destAddr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperation(const bblocks::BBUnaryOperationVN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src = instruction.getSource();
  const int dest = instruction.getDestination();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto srcAddr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[src]);
      if (srcAddr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {srcAddr.first.value(), srcAddr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS_ZP, {srcAddr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::BBUnaryOperationEnum::NEG:
      instructions.push_back(MachineInstruction(MachineInstruction::NEG_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::NOT:
      instructions.push_back(MachineInstruction(MachineInstruction::INV_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::INC:
      instructions.push_back(MachineInstruction(MachineInstruction::INC_A));
      break;
    case bblocks::BBUnaryOperationEnum::DEC:
      instructions.push_back(MachineInstruction(MachineInstruction::DEC_A));
      break;
    case bblocks::BBUnaryOperationEnum::SHL:
      instructions.push_back(MachineInstruction(MachineInstruction::SHL_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::SHR:
      instructions.push_back(MachineInstruction(MachineInstruction::SHR_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::SAR:
      instructions.push_back(MachineInstruction(MachineInstruction::DIV2_A_A));
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER:
      throw std::runtime_error("Register cannot be number type");
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperation(const bblocks::BBUnaryOperationNV& instruction) {
  std::vector<MachineInstruction> instructions;
  const int src = instruction.getSource();
  const std::string dest = instruction.getDestination();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {MachineCodeGenerator::getBinaryAnyInt(src)}));
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::runtime_error("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::BBUnaryOperationEnum::NEG:
      instructions.push_back(MachineInstruction(MachineInstruction::NEG_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::NOT:
      instructions.push_back(MachineInstruction(MachineInstruction::INV_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::INC:
      instructions.push_back(MachineInstruction(MachineInstruction::INC_A));
      break;
    case bblocks::BBUnaryOperationEnum::DEC:
      instructions.push_back(MachineInstruction(MachineInstruction::DEC_A));
      break;
    case bblocks::BBUnaryOperationEnum::SHL:
      instructions.push_back(MachineInstruction(MachineInstruction::SHL_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::SHR:
      instructions.push_back(MachineInstruction(MachineInstruction::SHR_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::SAR:
      instructions.push_back(MachineInstruction(MachineInstruction::DIV2_A_A));
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER: {
      const auto destAddr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[dest]);
      if (destAddr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {destAddr.first.value(), destAddr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A_ZP, {destAddr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperation(const bblocks::BBUnaryOperationNN& instruction) {
  std::vector<MachineInstruction> instructions;
  const int src = instruction.getSource();
  const int dest = instruction.getDestination();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {MachineCodeGenerator::getBinaryAnyInt(src)}));
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::runtime_error("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::BBUnaryOperationEnum::NEG:
      instructions.push_back(MachineInstruction(MachineInstruction::NEG_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::NOT:
      instructions.push_back(MachineInstruction(MachineInstruction::INV_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::INC:
      instructions.push_back(MachineInstruction(MachineInstruction::INC_A));
      break;
    case bblocks::BBUnaryOperationEnum::DEC:
      instructions.push_back(MachineInstruction(MachineInstruction::DEC_A));
      break;
    case bblocks::BBUnaryOperationEnum::SHL:
      instructions.push_back(MachineInstruction(MachineInstruction::SHL_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::SHR:
      instructions.push_back(MachineInstruction(MachineInstruction::SHR_A_A));
      break;
    case bblocks::BBUnaryOperationEnum::SAR:
      instructions.push_back(MachineInstruction(MachineInstruction::DIV2_A_A));
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER:
      throw std::runtime_error("Register cannot be number type");
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationVVV& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src1 = instruction.getSource1();
  const std::string src2 = instruction.getSource2();
  const std::string dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src1Addr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[src1]);
      if (src1Addr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {src1Addr.first.value(), src1Addr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS_ZP, {src1Addr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src2Addr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[src2]);
      if (src2Addr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_ABS, {src2Addr.first.value(), src2Addr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_ABS_ZP, {src2Addr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.push_back(MachineInstruction(MachineInstruction::ADD_A));
      break;
    case bblocks::SUB:
      instructions.push_back(MachineInstruction(MachineInstruction::SUB_A_AB));
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::runtime_error("Unimplemented");
    case bblocks::AND:
      instructions.push_back(MachineInstruction(MachineInstruction::AND_A));
      break;
    case bblocks::OR:
      instructions.push_back(MachineInstruction(MachineInstruction::OR_A));
      break;
    case bblocks::XOR:
      instructions.push_back(MachineInstruction(MachineInstruction::XOR_A));
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER: {
      const auto destAddr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[dest]);
      if (destAddr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {destAddr.first.value(), destAddr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A_ZP, {destAddr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationVVN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src1 = instruction.getSource1();
  const std::string src2 = instruction.getSource2();
  const int dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src1Addr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[src1]);
      if (src1Addr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {src1Addr.first.value(), src1Addr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS_ZP, {src1Addr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src2Addr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[src2]);
      if (src2Addr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_ABS, {src2Addr.first.value(), src2Addr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_ABS_ZP, {src2Addr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.push_back(MachineInstruction(MachineInstruction::ADD_A));
      break;
    case bblocks::SUB:
      instructions.push_back(MachineInstruction(MachineInstruction::SUB_A_AB));
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::runtime_error("Unimplemented");
    case bblocks::AND:
      instructions.push_back(MachineInstruction(MachineInstruction::AND_A));
      break;
    case bblocks::OR:
      instructions.push_back(MachineInstruction(MachineInstruction::OR_A));
      break;
    case bblocks::XOR:
      instructions.push_back(MachineInstruction(MachineInstruction::XOR_A));
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER:
      throw std::runtime_error("Register cannot be number type");
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationVNV& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src1 = instruction.getSource1();
  const int src2 = instruction.getSource2();
  const std::string dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src1Addr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[src1]);
      if (src1Addr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {src1Addr.first.value(), src1Addr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS_ZP, {src1Addr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_IMM, {MachineCodeGenerator::getBinaryAnyInt(src2)}));
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::runtime_error("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.push_back(MachineInstruction(MachineInstruction::ADD_A));
      break;
    case bblocks::SUB:
      instructions.push_back(MachineInstruction(MachineInstruction::SUB_A_AB));
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::runtime_error("Unimplemented");
    case bblocks::AND:
      instructions.push_back(MachineInstruction(MachineInstruction::AND_A));
      break;
    case bblocks::OR:
      instructions.push_back(MachineInstruction(MachineInstruction::OR_A));
      break;
    case bblocks::XOR:
      instructions.push_back(MachineInstruction(MachineInstruction::XOR_A));
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER: {
      const auto destAddr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[dest]);
      if (destAddr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {destAddr.first.value(), destAddr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A_ZP, {destAddr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationVNN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src1 = instruction.getSource1();
  const int src2 = instruction.getSource2();
  const int dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src1Addr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[src1]);
      if (src1Addr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {src1Addr.first.value(), src1Addr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS_ZP, {src1Addr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_IMM, {MachineCodeGenerator::getBinaryAnyInt(src2)}));
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::runtime_error("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.push_back(MachineInstruction(MachineInstruction::ADD_A));
      break;
    case bblocks::SUB:
      instructions.push_back(MachineInstruction(MachineInstruction::SUB_A_AB));
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::runtime_error("Unimplemented");
    case bblocks::AND:
      instructions.push_back(MachineInstruction(MachineInstruction::AND_A));
      break;
    case bblocks::OR:
      instructions.push_back(MachineInstruction(MachineInstruction::OR_A));
      break;
    case bblocks::XOR:
      instructions.push_back(MachineInstruction(MachineInstruction::XOR_A));
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER:
      throw std::runtime_error("Register cannot be number type");
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationNVV& instruction) {
  std::vector<MachineInstruction> instructions;
  const int src1 = instruction.getSource1();
  const std::string src2 = instruction.getSource2();
  const std::string dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {MachineCodeGenerator::getBinaryAnyInt(src1)}));
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::runtime_error("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src2Addr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[src2]);
      if (src2Addr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_ABS, {src2Addr.first.value(), src2Addr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_ABS_ZP, {src2Addr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.push_back(MachineInstruction(MachineInstruction::ADD_A));
      break;
    case bblocks::SUB:
      instructions.push_back(MachineInstruction(MachineInstruction::SUB_A_AB));
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::runtime_error("Unimplemented");
    case bblocks::AND:
      instructions.push_back(MachineInstruction(MachineInstruction::AND_A));
      break;
    case bblocks::OR:
      instructions.push_back(MachineInstruction(MachineInstruction::OR_A));
      break;
    case bblocks::XOR:
      instructions.push_back(MachineInstruction(MachineInstruction::XOR_A));
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER: {
      const auto destAddr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[dest]);
      if (destAddr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {destAddr.first.value(), destAddr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A_ZP, {destAddr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationNVN& instruction) {
  std::vector<MachineInstruction> instructions;
  const int src1 = instruction.getSource1();
  const std::string src2 = instruction.getSource2();
  const int dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {MachineCodeGenerator::getBinaryAnyInt(src1)}));
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::runtime_error("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src2Addr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[src2]);
      if (src2Addr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_ABS, {src2Addr.first.value(), src2Addr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_ABS_ZP, {src2Addr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.push_back(MachineInstruction(MachineInstruction::ADD_A));
      break;
    case bblocks::SUB:
      instructions.push_back(MachineInstruction(MachineInstruction::SUB_A_AB));
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::runtime_error("Unimplemented");
    case bblocks::AND:
      instructions.push_back(MachineInstruction(MachineInstruction::AND_A));
      break;
    case bblocks::OR:
      instructions.push_back(MachineInstruction(MachineInstruction::OR_A));
      break;
    case bblocks::XOR:
      instructions.push_back(MachineInstruction(MachineInstruction::XOR_A));
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER:
      throw std::runtime_error("Register cannot be number type");
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationNNV& instruction) {
  std::vector<MachineInstruction> instructions;
  const int src1 = instruction.getSource1();
  const int src2 = instruction.getSource2();
  const std::string dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {MachineCodeGenerator::getBinaryAnyInt(src1)}));
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::runtime_error("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_IMM, {MachineCodeGenerator::getBinaryAnyInt(src2)}));
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::runtime_error("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.push_back(MachineInstruction(MachineInstruction::ADD_A));
      break;
    case bblocks::SUB:
      instructions.push_back(MachineInstruction(MachineInstruction::SUB_A_AB));
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::runtime_error("Unimplemented");
    case bblocks::AND:
      instructions.push_back(MachineInstruction(MachineInstruction::AND_A));
      break;
    case bblocks::OR:
      instructions.push_back(MachineInstruction(MachineInstruction::OR_A));
      break;
    case bblocks::XOR:
      instructions.push_back(MachineInstruction(MachineInstruction::XOR_A));
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER: {
      const auto destAddr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[dest]);
      if (destAddr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {destAddr.first.value(), destAddr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A_ZP, {destAddr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationNNN& instruction) {
  std::vector<MachineInstruction> instructions;
  const int src1 = instruction.getSource1();
  const int src2 = instruction.getSource2();
  const int dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {MachineCodeGenerator::getBinaryAnyInt(src1)}));
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::runtime_error("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_IMM, {MachineCodeGenerator::getBinaryAnyInt(src2)}));
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::runtime_error("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.push_back(MachineInstruction(MachineInstruction::ADD_A));
      break;
    case bblocks::SUB:
      instructions.push_back(MachineInstruction(MachineInstruction::SUB_A_AB));
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::runtime_error("Unimplemented");
    case bblocks::AND:
      instructions.push_back(MachineInstruction(MachineInstruction::AND_A));
      break;
    case bblocks::OR:
      instructions.push_back(MachineInstruction(MachineInstruction::OR_A));
      break;
    case bblocks::XOR:
      instructions.push_back(MachineInstruction(MachineInstruction::XOR_A));
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER:
      throw std::runtime_error("Register cannot be number type");
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBranch(const bblocks::BBBranchV& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string value = instruction.getValue();
  const std::string trueLabel = instruction.getTrueLabel();
  const std::string falseLabel = instruction.getFalseLabel();

  switch (instruction.getValueType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT:
      throw std::runtime_error("Constant cannot be string type");
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto valAddr = MachineCodeGenerator::getBinaryAddress(currentFunctionVariableOffsets_[value]);
      if (valAddr.first.has_value()) {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {valAddr.first.value(), valAddr.second}));
      }
      else {
        instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS_ZP, {valAddr.second}));
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY:
      break;
  }

  instructions.push_back(MachineInstruction(MachineInstruction::CLR_B));
  instructions.push_back(MachineInstruction(MachineInstruction::CMP_A_B));

  switch (instruction.getCondition()) {
    case bblocks::BBBranchCondition::ANY:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {trueLabel}));
      break;
    case bblocks::BBBranchCondition::NEGATIVE:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::POSITIVE:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_NS, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::ODD:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_P, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::EVEN:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_NP, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::ZERO:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_Z, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::NONZERO:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_NZ, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::CARRY:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_C, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::NOCARRY:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_NC, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::OVERFLOW:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_O, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::NOOVERFLOW:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_NO, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBranch(const bblocks::BBBranchN& instruction) {
  std::vector<MachineInstruction> instructions;
  const int value = instruction.getValue();
  const std::string trueLabel = instruction.getTrueLabel();
  const std::string falseLabel = instruction.getFalseLabel();

  switch (instruction.getValueType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {MachineCodeGenerator::getBinaryAnyInt(value)}));
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER:
      throw std::runtime_error("Register cannot be number type");
    case bblocks::BBInstruction::SourceType::MEMORY:
      break;
  }

  instructions.push_back(MachineInstruction(MachineInstruction::CLR_B));
  instructions.push_back(MachineInstruction(MachineInstruction::CMP_A_B));

  switch (instruction.getCondition()) {
    case bblocks::BBBranchCondition::ANY:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {trueLabel}));
      break;
    case bblocks::BBBranchCondition::NEGATIVE:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_S, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::POSITIVE:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_NS, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::ODD:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_P, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::EVEN:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_NP, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::ZERO:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_Z, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::NONZERO:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_NZ, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::CARRY:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_C, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::NOCARRY:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_NC, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::OVERFLOW:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_O, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::NOOVERFLOW:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM_NO, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_IMM, {falseLabel}));
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateCall(const bblocks::BBCall& /*instruction*/) {
  return {MachineInstruction(MachineInstruction::JMP_FUN)};
}

std::vector<MachineInstruction> MachineCodeGenerator::generateRet(const bblocks::BBRet& /*instruction*/) {
  return {MachineInstruction(MachineInstruction::JMP_RET)};
}

std::vector<MachineInstruction> MachineCodeGenerator::generateHalt(const bblocks::BBHalt& /*instruction*/) {
  return {MachineInstruction(MachineInstruction::HALT)};
}

std::string MachineCodeGenerator::getBinaryInt(int8_t number) {
  const std::bitset<8> binary(number);
  return "0b" + binary.to_string();
}

std::string MachineCodeGenerator::getBinaryUint(uint8_t number) {
  const std::bitset<8> binary(number);
  return "0b" + binary.to_string();
}

std::string MachineCodeGenerator::getBinaryAnyInt(int number) {
  if (number < 0) {
    return getBinaryInt(static_cast<int8_t>(number));
  }
  return getBinaryUint(static_cast<uint8_t>(number));
}

std::pair<std::optional<std::string>, std::string> MachineCodeGenerator::getBinaryAddress(uint16_t address) {
  constexpr uint16_t lowByteMask = 0xFF;

  if (address < std::numeric_limits<uint8_t>::max()) {
    return {std::nullopt, getBinaryUint(static_cast<uint8_t>(address & lowByteMask))};
  }

  return {getBinaryUint(static_cast<uint8_t>(address >> 8)), getBinaryUint(static_cast<uint8_t>(address & lowByteMask))};
}

std::pair<std::string, std::string> MachineCodeGenerator::getBinaryFullAddress(uint16_t address) {
  constexpr uint16_t lowByteMask = 0xFF;

  return {getBinaryUint(static_cast<uint8_t>(address >> 8)), getBinaryUint(static_cast<uint8_t>(address & lowByteMask))};
}

}  // namespace machine_code