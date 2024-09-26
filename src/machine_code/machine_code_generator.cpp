#include "machine_code_generator.hpp"

namespace machine_code {
void MachineCodeGenerator::generate(const std::map<std::string, bblocks::BBControlFlowGraph>& cfg) {
  for (const auto& [functionName, controlFlowGraph] : cfg) {
    // enumerate labels of blocks
    enumerateBlockLabels(functionName, controlFlowGraph);

    // calculate live ranges
    liveRanges_.insert({functionName, LiveRangesGenerator{}});
    liveRanges_[functionName].generate(controlFlowGraph, blockBounds_[functionName]);
    liveRanges_[functionName].saveLiveRanges("live_ranges_" + functionName + ".txt");

    // calculate variable addresses
    generateVariableAddresses(functionName, controlFlowGraph, liveRanges_[functionName]);

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

void MachineCodeGenerator::saveMachineCode(const std::string& filename) {
  std::fstream file;
  file.open(filename, std::ios::out);

  for (const auto& [functionName, instructions] : machineCode_) {
    for (const auto& instruction : instructions) {
      file << instruction.toString() << "\n";
    }
  }
}

void MachineCodeGenerator::saveAssembly(const std::string& filename) {
  std::fstream file;
  file.open(filename, std::ios::out);

  for (const auto& [functionName, instructions] : machineCode_) {
    for (const auto& instruction : instructions) {
      if (instruction.getType() == MachineInstruction::Type::LABEL) {
        continue;
      }

      MachineInstruction instructionCopy = instruction;
      for (const auto& [label, value] : labelValues_[functionName]) {
        instructionCopy.replaceOperand(label, getBinary(value));
      }
      file << instructionCopy.toAssembly() << "\n";
    }
  }
}

void MachineCodeGenerator::saveBinary(const std::string& filename) {
  std::fstream file;
  file.open(filename, std::ios::out | std::ios::binary);

  for (const auto& [functionName, instructions] : machineCode_) {
    for (const auto& instruction : instructions) {
      if (instruction.getType() == MachineInstruction::Type::LABEL) {
        continue;
      }

      MachineInstruction instructionCopy = instruction;
      for (const auto& [label, value] : labelValues_[functionName]) {
        instructionCopy.replaceOperand(label, getBinary(value));
      }

      const uint8_t byte = static_cast<uint8_t>(std::stoi(instructionCopy.getBinaryCode(), nullptr, 2));
      file.write(reinterpret_cast<const char*>(&byte), sizeof(byte));

      for (const auto& operand : instructionCopy.getOperands()) {
        const uint16_t word = static_cast<uint16_t>(std::stoi(operand, nullptr, 2));
        file.write(reinterpret_cast<const char*>(&word), sizeof(word));
      }
    }
  }
}

void MachineCodeGenerator::enumerateBlockLabels(const std::string& name, const bblocks::BBControlFlowGraph& cfg) {
  std::map<std::string, std::pair<size_t, size_t>> bounds;
  size_t labelCounter = 0;

  std::queue<std::string> blocksToProcess;
  std::set<std::string> visitedBlocks;

  blocksToProcess.push(cfg.getEntryLabel());
  visitedBlocks.insert(cfg.getEntryLabel());
  while (!blocksToProcess.empty()) {
    const std::string blockLabel = blocksToProcess.front();
    blocksToProcess.pop();

    bounds.insert({blockLabel, {labelCounter, labelCounter + cfg.getBasicBlock(blockLabel).getInstructions().size() - 1}});
    labelCounter += cfg.getBasicBlock(blockLabel).getInstructions().size();

    for (const auto& outLink : cfg.getOutLinks(blockLabel)) {
      if (visitedBlocks.find(outLink) == visitedBlocks.end()) {
        blocksToProcess.push(outLink);
        visitedBlocks.insert(outLink);
      }
    }
  }

  blockBounds_.insert({name, bounds});
}

void MachineCodeGenerator::generateVariableAddresses(const std::string& /*name*/, const bblocks::BBControlFlowGraph& /*cfg*/,
                                                     const LiveRangesGenerator& liveRanges) {
  //  variableAddresses_.insert({name, std::map<std::string, uint16_t>{}});

  constexpr size_t beginningAddress = 1024;
  uint16_t address = beginningAddress;
  for (const auto& [variable, range] : liveRanges.getLiveRanges()) {
    variableAddresses_.insert({variable, address});
    address++;
  }
}

void MachineCodeGenerator::calculateLabelValues(const std::string& name) {
  labelValues_.insert({name, std::map<std::string, uint16_t>{}});

  size_t currentLabelValue = 0;
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {getBinary(variableAddresses_[src])}));
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER:
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {getBinary(variableAddresses_[dest])}));
      break;
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMove(const bblocks::BBMoveVN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src = instruction.getSource();
  const std::string dest = getBinary(instruction.getDestination());

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {getBinary(variableAddresses_[src])}));
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
  const std::string src = getBinary(instruction.getSource());
  const std::string dest = instruction.getDestination();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {src}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {getBinary(variableAddresses_[dest])}));
      break;
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMove(const bblocks::BBMoveNN& instruction) {
  std::vector<MachineInstruction> instructions;

  const std::string src = getBinary(instruction.getSource());
  const std::string dest = getBinary(instruction.getDestination());

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {src}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {getBinary(variableAddresses_[src])}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {getBinary(variableAddresses_[dest])}));
      break;
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperation(const bblocks::BBUnaryOperationVN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src = instruction.getSource();
  const std::string dest = getBinary(instruction.getDestination());

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {getBinary(variableAddresses_[src])}));
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
  const std::string src = getBinary(instruction.getSource());
  const std::string dest = instruction.getDestination();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {src}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {getBinary(variableAddresses_[dest])}));
      break;
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperation(const bblocks::BBUnaryOperationNN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src = getBinary(instruction.getSource());
  const std::string dest = getBinary(instruction.getDestination());

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {src}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {getBinary(variableAddresses_[src1])}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_ABS, {getBinary(variableAddresses_[src2])}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {getBinary(variableAddresses_[dest])}));
      break;
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationVVN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src1 = instruction.getSource1();
  const std::string src2 = instruction.getSource2();
  const std::string dest = getBinary(instruction.getDestination());

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {getBinary(variableAddresses_[src1])}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_ABS, {getBinary(variableAddresses_[src2])}));
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
  const std::string src2 = getBinary(instruction.getSource2());
  const std::string dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {getBinary(variableAddresses_[src1])}));
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_IMM, {src2}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {getBinary(variableAddresses_[dest])}));
      break;
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationVNN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src1 = instruction.getSource1();
  const std::string src2 = getBinary(instruction.getSource2());
  const std::string dest = getBinary(instruction.getDestination());

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::runtime_error("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {getBinary(variableAddresses_[src1])}));
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_IMM, {src2}));
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
  const std::string src1 = getBinary(instruction.getSource1());
  const std::string src2 = instruction.getSource2();
  const std::string dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {src1}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_ABS, {getBinary(variableAddresses_[src2])}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {getBinary(variableAddresses_[dest])}));
      break;
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationNVN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src1 = getBinary(instruction.getSource1());
  const std::string src2 = instruction.getSource2();
  const std::string dest = getBinary(instruction.getDestination());

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {src1}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_ABS, {getBinary(variableAddresses_[src2])}));
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
  const std::string src1 = getBinary(instruction.getSource1());
  const std::string src2 = getBinary(instruction.getSource2());
  const std::string dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {src1}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_IMM, {src2}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_AT_ABS_A, {getBinary(variableAddresses_[dest])}));
      break;
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationNNN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src1 = getBinary(instruction.getSource1());
  const std::string src2 = getBinary(instruction.getSource2());
  const std::string dest = getBinary(instruction.getDestination());

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {src1}));
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
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_B_IMM, {src2}));
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
    case bblocks::BBInstruction::SourceType::REGISTER:
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_ABS, {getBinary(variableAddresses_[value])}));
      break;
    case bblocks::BBInstruction::SourceType::MEMORY:
      break;
  }

  instructions.push_back(MachineInstruction(MachineInstruction::CLR_B));
  instructions.push_back(MachineInstruction(MachineInstruction::CMP_A_B));

  switch (instruction.getCondition()) {
    case bblocks::BBBranchCondition::ANY:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {trueLabel}));
      break;
    case bblocks::BBBranchCondition::NEGATIVE:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_S, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::POSITIVE:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_NS, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::ODD:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_P, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::EVEN:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_NP, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::ZERO:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_Z, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::NONZERO:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_NZ, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::CARRY:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_C, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::NOCARRY:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_NC, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::OVERFLOW:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_O, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::NOOVERFLOW:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_NO, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBranch(const bblocks::BBBranchN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string value = getBinary(instruction.getValue());
  const std::string trueLabel = instruction.getTrueLabel();
  const std::string falseLabel = instruction.getFalseLabel();

  switch (instruction.getValueType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT:
      instructions.push_back(MachineInstruction(MachineInstruction::MOV_A_IMM, {value}));
      break;
    case bblocks::BBInstruction::SourceType::REGISTER:
      throw std::runtime_error("Register cannot be number type");
    case bblocks::BBInstruction::SourceType::MEMORY:
      break;
  }

  instructions.push_back(MachineInstruction(MachineInstruction::CLR_B));
  instructions.push_back(MachineInstruction(MachineInstruction::CMP_A_B));

  switch (instruction.getCondition()) {
    case bblocks::BBBranchCondition::ANY:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {trueLabel}));
      break;
    case bblocks::BBBranchCondition::NEGATIVE:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_S, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::POSITIVE:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_NS, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::ODD:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_P, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::EVEN:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_NP, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::ZERO:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_Z, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::NONZERO:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_NZ, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::CARRY:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_C, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::NOCARRY:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_NC, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::OVERFLOW:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_O, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
    case bblocks::BBBranchCondition::NOOVERFLOW:
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL_NO, {trueLabel}));
      instructions.push_back(MachineInstruction(MachineInstruction::JMP_REL, {falseLabel}));
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateCall(const bblocks::BBCall& /*instruction*/) {
  return {MachineInstruction(MachineInstruction::JMP_REL)};
}

std::vector<MachineInstruction> MachineCodeGenerator::generateRet(const bblocks::BBRet& /*instruction*/) {
  return {MachineInstruction(MachineInstruction::JMP_REL_RET)};
}

std::vector<MachineInstruction> MachineCodeGenerator::generateHalt(const bblocks::BBHalt& /*instruction*/) {
  return {MachineInstruction(MachineInstruction::HALT)};
}

std::string MachineCodeGenerator::getBinary(int number) {
  const std::bitset<8> binary(number);
  return "0b" + binary.to_string();
}

}  // namespace machine_code