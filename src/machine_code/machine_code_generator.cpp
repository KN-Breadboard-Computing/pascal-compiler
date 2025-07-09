#include "machine_code_generator.hpp"

namespace machine_code {
int MachineCodeGenerator::registersNumber_{2};

void MachineCodeGenerator::generate(const std::map<std::string, bblocks::BBControlFlowGraph>& cfg, RegisterAllocator allocator,
                                    uint16_t variablesOffset) {
  for (const auto& [functionName, controlFlowGraph] : cfg) {
    currentScope = functionName;
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

    generateVariableAddresses(functionName, variablesOffset);

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

      machineCode_[functionName].emplace_back(MachineInstruction::LABEL, std::vector<std::string>{blockLabel});
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
    for (const auto& [variable, offset] : variableAddresses_.at(functionName)) {
      output << variable << " address " << offset << std::endl;
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

std::vector<uint8_t> MachineCodeGenerator::getBinaryCode() {
  std::vector<uint8_t> binaryCode;
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

      uint8_t byte = static_cast<uint8_t>(std::stoi(instructionCopy.getBinaryCode(), nullptr, 2));
      binaryCode.push_back(byte);

      for (const auto& operand : instructionCopy.getOperands()) {
        byte = static_cast<uint8_t>(std::stoi(operand, nullptr, 2));
        binaryCode.push_back(byte);
      }
    }
  }

  return binaryCode;
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

void MachineCodeGenerator::generateVariableAddresses(const std::string& name, uint16_t variablesOffset) {
  variableAddresses_.insert({name, std::map<std::string, uint16_t>{}});

  std::size_t address = variablesOffset;
  for (const auto& [var, reg] : regAllocators_[name]->getAllocatedRegisters()) {
    if (reg == -1) {
      variableAddresses_[name].insert({var, address});
      address += 1;
    }
  }
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
            case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
              switch (templateArguments[2]) {
                case bblocks::BBInstruction::TemplateArgumentType::STRING:
                  return generateBinaryOperation(*dynamic_cast<bblocks::BBBinaryOperationVNV*>(instruction.get()));
                case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
                  return generateBinaryOperation(*dynamic_cast<bblocks::BBBinaryOperationVNN*>(instruction.get()));
              }
          }
        case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
          switch (templateArguments[1]) {
            case bblocks::BBInstruction::TemplateArgumentType::STRING:
              switch (templateArguments[2]) {
                case bblocks::BBInstruction::TemplateArgumentType::STRING:
                  return generateBinaryOperation(*dynamic_cast<bblocks::BBBinaryOperationNVV*>(instruction.get()));
                case bblocks::BBInstruction::TemplateArgumentType::NUMBER:
                  return generateBinaryOperation(*dynamic_cast<bblocks::BBBinaryOperationNVN*>(instruction.get()));
              }
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
      throw std::invalid_argument("Unspecified instruction type");
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMove(const bblocks::BBMoveVV& instruction) {
  const std::string src = instruction.getSource();
  const int srcReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(src);
  const std::string dest = instruction.getDestination();
  const int destReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(dest);

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          if (srcReg != -1 && destReg != -1) {
            return generateMoveRegReg(srcReg, destReg);
          }
          else if (srcReg != -1) {
            return generateMoveRegMem(srcReg, variableAddresses_[currentScope].at(dest));
          }
          else if (destReg != -1) {
            return generateMoveMemReg(variableAddresses_[currentScope].at(src), destReg);
          }
          else {
            return generateMoveMemMem(variableAddresses_[currentScope].at(src), variableAddresses_[currentScope].at(dest));
          }
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          if (srcReg != -1 && destReg != -1) {
            return generateMoveRegMemImmReg(srcReg, destReg);
          }
          else if (srcReg != -1) {
            return generateMoveRegMemImmMem(srcReg, variableAddresses_[currentScope].at(dest));
          }
          else if (destReg != -1) {
            return generateMoveMemMemImmReg(variableAddresses_[currentScope].at(src), destReg);
          }
          else {
            return generateMoveMemMemImmMem(variableAddresses_[currentScope].at(src), variableAddresses_[currentScope].at(dest));
          }
        }
      }
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          if (srcReg != -1 && destReg != -1) {
            return generateMoveMemImmRegReg(srcReg, destReg);
          }
          else if (srcReg != -1) {
            return generateMoveMemImmRegMem(srcReg, variableAddresses_[currentScope].at(dest));
          }
          else if (destReg != -1) {
            return generateMoveMemImmMemReg(variableAddresses_[currentScope].at(src), destReg);
          }
          else {
            return generateMoveMemImmMemMem(variableAddresses_[currentScope].at(src), variableAddresses_[currentScope].at(dest));
          }
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          if (srcReg != -1 && destReg != -1) {
            return generateMoveMemImmRegMemImmReg(srcReg, destReg);
          }
          else if (srcReg != -1) {
            return generateMoveMemImmRegMemImmMem(srcReg, variableAddresses_[currentScope].at(dest));
          }
          else if (destReg != -1) {
            return generateMoveMemImmMemMemImmReg(variableAddresses_[currentScope].at(src), destReg);
          }
          else {
            return generateMoveMemImmMemMemImmMem(variableAddresses_[currentScope].at(src),
                                                  variableAddresses_[currentScope].at(dest));
          }
        }
      }
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMove(const bblocks::BBMoveVN& instruction) {
  const std::string src = instruction.getSource();
  const int srcReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(src);
  const uint16_t dest = instruction.getDestination();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          if (srcReg != -1) {
            return generateMoveRegMem(srcReg, dest);
          }
          else {
            return generateMoveMemMem(variableAddresses_[currentScope].at(src), dest);
          }
        }
      }
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          if (srcReg != -1) {
            return generateMoveMemImmRegMem(srcReg, dest);
          }
          else {
            return generateMoveMemImmMemMem(variableAddresses_[currentScope].at(src), dest);
          }
        }
      }
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMove(const bblocks::BBMoveNV& instruction) {
  const uint16_t src = instruction.getSource();
  const std::string dest = instruction.getDestination();
  const int destReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(dest);

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          if (destReg != -1) {
            return generateMoveConstReg(static_cast<uint8_t>(src), destReg);
          }
          else {
            return generateMoveConstMem(static_cast<uint8_t>(src), variableAddresses_.at(currentScope).at(dest));
          }
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          if (destReg != -1) {
            return generateMoveConstMemImmReg(static_cast<uint8_t>(src), destReg);
          }
          else {
            return generateMoveConstMemImmMem(static_cast<uint8_t>(src), variableAddresses_.at(currentScope).at(dest));
          }
        }
      }
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          if (destReg != -1) {
            return generateMoveMemReg(src, destReg);
          }
          else {
            return generateMoveMemMem(src, variableAddresses_.at(currentScope).at(dest));
          }
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          if (destReg != -1) {
            return generateMoveMemMemImmReg(src, destReg);
          }
          else {
            return generateMoveMemMemImmMem(src, variableAddresses_.at(currentScope).at(dest));
          }
        }
      }
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMove(const bblocks::BBMoveNN& instruction) {
  const uint16_t src = instruction.getSource();
  const uint16_t dest = instruction.getDestination();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          throw std::runtime_error("Register cannot be number type");
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          return generateMoveConstMem(static_cast<uint8_t>(src), dest);
        }
      }
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          throw std::runtime_error("Register cannot be number type");
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          return generateMoveMemMem(src, dest);
        }
      }
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveRegReg(int src, int dest) {
  std::cout << "mov reg reg" << std::endl;
  std::vector<MachineInstruction> instructions;
  if (src == 1 && dest == 2) {
    instructions.emplace_back(MachineInstruction::MOV_B_A);
  }
  else if (src == 2 && dest == 1) {
    instructions.emplace_back(MachineInstruction::MOV_A_B);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveRegMem(int src, uint16_t dest) {
  std::cout << "mov reg mem" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);
  if (src == 1) {
    if (destAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A,
                                std::vector<std::string>{destAddress.second, destAddress.first.value()});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddress.second});
    }
  }
  else if (src == 2) {
    if (destAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_AT_ABS_B,
                                std::vector<std::string>{destAddress.second, destAddress.first.value()});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_AT_ABS_B_ZP, std::vector<std::string>{destAddress.second});
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveRegMemImmReg(int src, int immDest) {
  std::cout << "mov reg mem imm reg" << std::endl;
  std::vector<MachineInstruction> instructions;
  if (immDest == 1) {
    instructions.emplace_back(MachineInstruction::MOV_TL_A);
  }
  else if (immDest == 2) {
    instructions.emplace_back(MachineInstruction::MOV_TL_B);
  }
  if (src == 1) {
    instructions.emplace_back(MachineInstruction::MOV_AT_B_A);
  }
  else if (src == 2) {
    instructions.emplace_back(MachineInstruction::MOV_AT_TL_B);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveRegMemImmMem(int src, uint16_t immDest) {
  std::cout << "mov reg mem imm mem" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);
  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS,
                              std::vector<std::string>{destAddress.second, destAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{destAddress.second});
  }
  instructions.emplace_back(MachineInstruction::POP_TL);
  if (src == 1) {
    instructions.emplace_back(MachineInstruction::MOV_AT_TL_A);
  }
  else if (src == 2) {
    instructions.emplace_back(MachineInstruction::MOV_AT_TL_B);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemReg(uint16_t src, int dest) {
  std::cout << "mov mem reg" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(src);
  if (dest == 1) {
    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS,
                                std::vector<std::string>{srcAddress.second, srcAddress.first.value()});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }
  }
  else if (dest == 2) {
    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS,
                                std::vector<std::string>{srcAddress.second, srcAddress.first.value()});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmRegReg(int immSrc, int dest) {
  std::cout << "mov mem imm reg reg" << std::endl;
  std::vector<MachineInstruction> instructions;
  if (immSrc == 1) {
    instructions.emplace_back(MachineInstruction::MOV_TL_AT_A);
  }
  else if (immSrc == 2) {
    instructions.emplace_back(MachineInstruction::MOV_TL_AT_B);
  }
  if (dest == 1) {
    instructions.emplace_back(MachineInstruction::MOV_A_TL);
  }
  else if (dest == 2) {
    instructions.emplace_back(MachineInstruction::MOV_B_TL);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmMemReg(uint16_t immSrc, int dest) {
  std::cout << "mov mem imm mem reg" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(immSrc);
  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS,
                              std::vector<std::string>{srcAddress.second, srcAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{srcAddress.second});
  }
  instructions.emplace_back(MachineInstruction::POP_TL);
  if (dest == 1) {
    instructions.emplace_back(MachineInstruction::MOV_A_AT_TL);
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_B_AT_TL);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemMem(uint16_t src, uint16_t dest) {
  std::cout << "mov mem mem" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(src);
  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS,
                              std::vector<std::string>{srcAddress.second, srcAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{srcAddress.second});
  }

  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);
  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::POP_MEM,
                              std::vector<std::string>{destAddress.second, destAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::POP_MEM_ZP, std::vector<std::string>{destAddress.second});
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmRegMem(int immSrc, uint16_t dest) {
  std::cout << "mov mem imm reg mem" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);
  if (immSrc == 1) {
    instructions.emplace_back(MachineInstruction::MOV_TL_AT_A);
  }
  else if (immSrc == 2) {
    instructions.emplace_back(MachineInstruction::MOV_TL_AT_B);
  }
  instructions.emplace_back(MachineInstruction::PUSH_A);
  instructions.emplace_back(MachineInstruction::MOV_A_TL);
  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A,
                              std::vector<std::string>{destAddress.second, destAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddress.second});
  }
  instructions.emplace_back(MachineInstruction::POP_A);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmMemMem(uint16_t immSrc, uint16_t dest) {
  std::cout << "mov mem imm mem mem" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(immSrc);
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);
  instructions.emplace_back(MachineInstruction::PUSH_A);
  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS,
                              std::vector<std::string>{srcAddress.second, srcAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{srcAddress.second});
  }
  instructions.emplace_back(MachineInstruction::MOV_TL_A);
  instructions.emplace_back(MachineInstruction::MOV_A_AT_TL);
  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A,
                              std::vector<std::string>{destAddress.second, destAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddress.second});
  }
  instructions.emplace_back(MachineInstruction::POP_A);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemMemImmReg(uint16_t src, int immDest) {
  std::cout << "mov mem mem imm reg" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(src);
  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS,
                              std::vector<std::string>{srcAddress.second, srcAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{srcAddress.second});
  }
  instructions.emplace_back(MachineInstruction::POP_TL);
  if (immDest == 1) {
    instructions.emplace_back(MachineInstruction::MOV_AT_A_TL);
  }
  else if (immDest == 2) {
    instructions.emplace_back(MachineInstruction::MOV_AT_B_TL);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemMemImmMem(uint16_t src, uint16_t immDest) {
  std::cout << "mov mem mem imm mem" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(src);
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);
  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS,
                              std::vector<std::string>{srcAddress.second, srcAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{srcAddress.second});
  }
  instructions.emplace_back(MachineInstruction::POP_TH);
  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS,
                              std::vector<std::string>{destAddress.second, destAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{destAddress.second});
  }
  instructions.emplace_back(MachineInstruction::POP_TL);
  instructions.emplace_back(MachineInstruction::MOV_AT_TL_TH);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmRegMemImmReg(int immSrc, int immDest) {
  std::cout << "mov mem imm reg mem imm reg" << std::endl;
  std::vector<MachineInstruction> instructions;
  if (immSrc == 1) {
    instructions.emplace_back(MachineInstruction::MOV_TL_AT_A);
  }
  else if (immSrc == 2) {
    instructions.emplace_back(MachineInstruction::MOV_TL_AT_B);
  }
  if (immDest == 1) {
    instructions.emplace_back(MachineInstruction::MOV_AT_A_TL);
  }
  else if (immDest == 2) {
    instructions.emplace_back(MachineInstruction::MOV_AT_B_TL);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmRegMemImmMem(int immSrc, uint16_t immDest) {
  std::cout << "mov mem imm reg mem imm mem" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);
  if (immSrc == 1) {
    instructions.emplace_back(MachineInstruction::MOV_TL_AT_A);
  }
  else if (immSrc == 2) {
    instructions.emplace_back(MachineInstruction::MOV_TL_AT_B);
  }
  instructions.emplace_back(MachineInstruction::PUSH_A);
  instructions.emplace_back(MachineInstruction::MOV_A_TL);
  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A,
                              std::vector<std::string>{destAddress.second, destAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddress.second});
  }
  instructions.emplace_back(MachineInstruction::POP_A);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmMemMemImmReg(uint16_t immSrc, int immDest) {
  std::cout << "mov mem imm mem mem imm reg" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(immSrc);
  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS,
                              std::vector<std::string>{srcAddress.second, srcAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{srcAddress.second});
  }
  instructions.emplace_back(MachineInstruction::POP_TL);
  if (immDest == 1) {
    instructions.emplace_back(MachineInstruction::MOV_AT_A_TL);
  }
  else if (immDest == 2) {
    instructions.emplace_back(MachineInstruction::MOV_AT_B_TL);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmMemMemImmMem(uint16_t immSrc, uint16_t immDest) {
  std::cout << "mov mem imm mem mem imm mem" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(immSrc);
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);
  instructions.emplace_back(MachineInstruction::PUSH_A);
  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS,
                              std::vector<std::string>{srcAddress.second, srcAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{srcAddress.second});
  }
  instructions.emplace_back(MachineInstruction::MOV_TL_A);
  instructions.emplace_back(MachineInstruction::MOV_A_AT_TL);
  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A,
                              std::vector<std::string>{destAddress.second, destAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddress.second});
  }
  instructions.emplace_back(MachineInstruction::POP_A);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveConstReg(uint8_t src, int dest) {
  std::cout << "mov const reg" << std::endl;
  std::vector<MachineInstruction> instructions;
  if (dest == 1) {
    instructions.emplace_back(MachineInstruction::MOV_A_IMM, std::vector<std::string>{getBinaryUint(src)});
  }
  else if (dest == 2) {
    instructions.emplace_back(MachineInstruction::MOV_B_IMM, std::vector<std::string>{getBinaryUint(src)});
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveConstMem(uint8_t src, uint16_t dest) {
  std::cout << "mov const mem" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);
  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_IMM,
                              std::vector<std::string>{destAddress.second, destAddress.first.value(), getBinaryUint(src)});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_IMM_ZP,
                              std::vector<std::string>{destAddress.second, getBinaryUint(src)});
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveConstMemImmReg(uint8_t src, int immDest) {
  std::cout << "mov const mem imm reg" << std::endl;
  std::vector<MachineInstruction> instructions;
  if (immDest == 1) {
    instructions.emplace_back(MachineInstruction::MOV_AT_A_IMM, std::vector<std::string>{getBinaryUint(src)});
  }
  else if (immDest == 2) {
    instructions.emplace_back(MachineInstruction::MOV_AT_B_IMM, std::vector<std::string>{getBinaryUint(src)});
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveConstMemImmMem(uint8_t src, uint16_t immDest) {
  std::cout << "mov const mem imm mem" << std::endl;
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);
  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS,
                              std::vector<std::string>{destAddress.second, destAddress.first.value()});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{destAddress.second});
  }
  instructions.emplace_back(MachineInstruction::POP_TL);
  instructions.emplace_back(MachineInstruction::MOV_AT_TL_IMM, std::vector<std::string>{getBinaryUint(src)});

    return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperation(const bblocks::BBUnaryOperationVV& instruction) {
  const std::string src = instruction.getSource();
  const int srcReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(src);
  const std::string dest = instruction.getDestination();
  const int destReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(dest);
  const bblocks::BBUnaryOperationEnum operation = instruction.getOperation();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          return generateUnaryOperationRegReg(srcReg, destReg, operation);
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          break;
        }
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          break;
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          break;
        }
      }
      break;
    }
  }

}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperation(const bblocks::BBUnaryOperationVN& instruction) {
  const std::string src = instruction.getSource();
  const int srcReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(src);
  const int dest = instruction.getDestination();
  const bblocks::BBUnaryOperationEnum operation = instruction.getOperation();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          return generateUnaryOperationRegMem(srcReg, dest, operation);
        }
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          break;
        }
      }
      break;
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperation(const bblocks::BBUnaryOperationNV& instruction) {
  const int src = instruction.getSource();
  const std::string dest = instruction.getDestination();
  const int destReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(dest);

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          break;
        }
        case bblocks::BBInstruction::DestinationType::MEMORY:
          break;
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          break;
        }
        case bblocks::BBInstruction::DestinationType::MEMORY:
          break;
      }
      break;
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperation(const bblocks::BBUnaryOperationNN& instruction) {
  const int src = instruction.getSource();
  const int dest = instruction.getDestination();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          break;
        }
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          break;
        }
      }
      break;
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperationRegReg(int src, int dest,
                                                                                   bblocks::BBUnaryOperationEnum type) {
  std::vector<MachineInstruction> instructions;
  if (src == 1 && dest == 1) {
    switch (type) {
      case bblocks::BBUnaryOperationEnum::NEG:
        instructions.emplace_back(MachineInstruction::NEG_A_A);
        break;
      case bblocks::BBUnaryOperationEnum::NOT:
        instructions.emplace_back(MachineInstruction::INV_A_A);
        break;
      case bblocks::BBUnaryOperationEnum::INC:
        instructions.emplace_back(MachineInstruction::INC_A);
        break;
      case bblocks::BBUnaryOperationEnum::DEC:
        instructions.emplace_back(MachineInstruction::DEC_A);
        break;
      case bblocks::BBUnaryOperationEnum::SHL:
        instructions.emplace_back(MachineInstruction::SHL_A_A);
        break;
      case bblocks::BBUnaryOperationEnum::SHR:
        instructions.emplace_back(MachineInstruction::SHR_A_A);
        break;
      case bblocks::BBUnaryOperationEnum::SAR:
        instructions.emplace_back(MachineInstruction::DIV2_A_A);
        break;
    }
  }
  else if (src == 1 && dest == 2) {
    switch (type) {
      case bblocks::BBUnaryOperationEnum::NEG:
        instructions.emplace_back(MachineInstruction::NEG_B_A);
        break;
      case bblocks::BBUnaryOperationEnum::NOT:
        instructions.emplace_back(MachineInstruction::INV_B_A);
        break;
      case bblocks::BBUnaryOperationEnum::INC:
        instructions.emplace_back(MachineInstruction::INC_B);
        break;
      case bblocks::BBUnaryOperationEnum::DEC:
        instructions.emplace_back(MachineInstruction::DEC_B);
        break;
      case bblocks::BBUnaryOperationEnum::SHL:
        instructions.emplace_back(MachineInstruction::SHL_B_A);
        break;
      case bblocks::BBUnaryOperationEnum::SHR:
        instructions.emplace_back(MachineInstruction::SHR_B_A);
        break;
      case bblocks::BBUnaryOperationEnum::SAR:
        instructions.emplace_back(MachineInstruction::DIV2_B_A);
        break;
    }
  }
  else if (src == 2 && dest == 1) {
    switch (type) {
      case bblocks::BBUnaryOperationEnum::NEG:
        instructions.emplace_back(MachineInstruction::NEG_A_B);
        break;
      case bblocks::BBUnaryOperationEnum::NOT:
        instructions.emplace_back(MachineInstruction::INV_A_B);
        break;
      case bblocks::BBUnaryOperationEnum::INC:
        instructions.emplace_back(MachineInstruction::INC_A);
        break;
      case bblocks::BBUnaryOperationEnum::DEC:
        instructions.emplace_back(MachineInstruction::DEC_A);
        break;
      case bblocks::BBUnaryOperationEnum::SHL:
        instructions.emplace_back(MachineInstruction::SHL_A_B);
        break;
      case bblocks::BBUnaryOperationEnum::SHR:
        instructions.emplace_back(MachineInstruction::SHR_A_B);
        break;
      case bblocks::BBUnaryOperationEnum::SAR:
        instructions.emplace_back(MachineInstruction::DIV2_A_B);
        break;
    }
  }
  else if (src == 2 && dest == 2) {
    switch (type) {
      case bblocks::BBUnaryOperationEnum::NEG:
        instructions.emplace_back(MachineInstruction::NEG_B_B);
        break;
      case bblocks::BBUnaryOperationEnum::NOT:
        instructions.emplace_back(MachineInstruction::INV_B_B);
        break;
      case bblocks::BBUnaryOperationEnum::INC:
        instructions.emplace_back(MachineInstruction::INC_B);
        break;
      case bblocks::BBUnaryOperationEnum::DEC:
        instructions.emplace_back(MachineInstruction::DEC_B);
        break;
      case bblocks::BBUnaryOperationEnum::SHL:
        instructions.emplace_back(MachineInstruction::SHL_B_B);
        break;
      case bblocks::BBUnaryOperationEnum::SHR:
        instructions.emplace_back(MachineInstruction::SHR_B_B);
        break;
      case bblocks::BBUnaryOperationEnum::SAR:
        instructions.emplace_back(MachineInstruction::DIV2_B_B);
        break;
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperationRegMem(int src, uint16_t dest,
                                                                                   bblocks::BBUnaryOperationEnum type) {
  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);
  if (src == 1) {
    switch (type) {
      case bblocks::BBUnaryOperationEnum::NEG:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::NEG_MEM_A,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::NEG_MEM_A, std::vector<std::string>{destAddress.second});
        }
        break;
      case bblocks::BBUnaryOperationEnum::NOT:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::INV_MEM_A,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::INV_MEM_A, std::vector<std::string>{destAddress.second});
        }
        break;
      case bblocks::BBUnaryOperationEnum::INC:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::INC_A,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::INC_A, std::vector<std::string>{destAddress.second});
        }
        break;
      case bblocks::BBUnaryOperationEnum::DEC:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::DEC_A,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::DEC_A, std::vector<std::string>{destAddress.second});
        }
        break;
      case bblocks::BBUnaryOperationEnum::SHL:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::SHL_MEM_A,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::SHL_MEM_A, std::vector<std::string>{destAddress.second});
        }
        break;
      case bblocks::BBUnaryOperationEnum::SHR:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::SHR_MEM_A,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::SHR_MEM_A, std::vector<std::string>{destAddress.second});
        }
        break;
      case bblocks::BBUnaryOperationEnum::SAR:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::DIV2_MEM_A,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::DIV2_MEM_A, std::vector<std::string>{destAddress.second});
        }
        break;
    }
  }
  else if (src == 2) {
    switch (type) {
      case bblocks::BBUnaryOperationEnum::NEG:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::NEG_MEM_B,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::NEG_MEM_B, std::vector<std::string>{destAddress.second});
        }
        break;
      case bblocks::BBUnaryOperationEnum::NOT:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::INV_MEM_B,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::INV_MEM_B, std::vector<std::string>{destAddress.second});
        }
        break;
      case bblocks::BBUnaryOperationEnum::INC:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::INC_B,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::INC_B, std::vector<std::string>{destAddress.second});
        }
        break;
      case bblocks::BBUnaryOperationEnum::DEC:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::DEC_B,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::DEC_B, std::vector<std::string>{destAddress.second});
        }
        break;
      case bblocks::BBUnaryOperationEnum::SHL:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::SHL_MEM_B,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::SHL_MEM_B, std::vector<std::string>{destAddress.second});
        }
        break;
      case bblocks::BBUnaryOperationEnum::SHR:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::SHR_MEM_B,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::SHR_MEM_B, std::vector<std::string>{destAddress.second});
        }
        break;
      case bblocks::BBUnaryOperationEnum::SAR:
        if (destAddress.first.has_value()) {
          instructions.emplace_back(MachineInstruction::DIV2_MEM_B,
                                    std::vector<std::string>{destAddress.second, destAddress.first.value()});
        }
        else {
          instructions.emplace_back(MachineInstruction::DIV2_MEM_B, std::vector<std::string>{destAddress.second});
        }
        break;
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperationMemReg(uint16_t src, int dest,
                                                                                   bblocks::BBUnaryOperationEnum type) {}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperationMemMem(uint16_t src, uint16_t dest,
                                                                                   bblocks::BBUnaryOperationEnum type) {}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperationConstReg(uint8_t src, int dest,
                                                                                     bblocks::BBUnaryOperationEnum type) {}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperationConstMem(uint8_t src, uint16_t dest,
                                                                                     bblocks::BBUnaryOperationEnum type) {}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationVVV& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src1 = instruction.getSource1();
  const std::string src2 = instruction.getSource2();
  const std::string dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src1Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src1]);
      if (src1Addr.first.has_value()) {
        instructions.emplace_back(MachineInstruction::MOV_A_ABS,
                                  std::vector<std::string>{src1Addr.first.value(), src1Addr.second});
      }
      else {
        instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{src1Addr.second});
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src2Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src2]);
      if (src2Addr.first.has_value()) {
        instructions.emplace_back(MachineInstruction::MOV_B_ABS,
                                  std::vector<std::string>{src2Addr.first.value(), src2Addr.second});
      }
      else {
        instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{src2Addr.second});
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.emplace_back(MachineInstruction::ADD_A);
      break;
    case bblocks::SUB:
      instructions.emplace_back(MachineInstruction::SUB_A_AB);
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::invalid_argument("Unimplemented");
    case bblocks::AND:
      instructions.emplace_back(MachineInstruction::AND_A);
      break;
    case bblocks::OR:
      instructions.emplace_back(MachineInstruction::OR_A);
      break;
    case bblocks::XOR:
      instructions.emplace_back(MachineInstruction::XOR_A);
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER: {
      const auto destAddr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][dest]);
      if (destAddr.first.has_value()) {
        instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A,
                                  std::vector<std::string>{destAddr.first.value(), destAddr.second});
      }
      else {
        instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddr.second});
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
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src1Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src1]);
      if (src1Addr.first.has_value()) {
        instructions.emplace_back(MachineInstruction::MOV_A_ABS,
                                  std::vector<std::string>{src1Addr.first.value(), src1Addr.second});
      }
      else {
        instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{src1Addr.second});
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src2Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src2]);
      if (src2Addr.first.has_value()) {
        instructions.emplace_back(MachineInstruction::MOV_B_ABS,
                                  std::vector<std::string>{src2Addr.first.value(), src2Addr.second});
      }
      else {
        instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{src2Addr.second});
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.emplace_back(MachineInstruction::ADD_A);
      break;
    case bblocks::SUB:
      instructions.emplace_back(MachineInstruction::SUB_A_AB);
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::invalid_argument("Unimplemented");
    case bblocks::AND:
      instructions.emplace_back(MachineInstruction::AND_A);
      break;
    case bblocks::OR:
      instructions.emplace_back(MachineInstruction::OR_A);
      break;
    case bblocks::XOR:
      instructions.emplace_back(MachineInstruction::XOR_A);
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER:
      throw std::invalid_argument("Register cannot be number type");
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
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src1Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src1]);
      if (src1Addr.first.has_value()) {
        instructions.emplace_back(MachineInstruction::MOV_A_ABS,
                                  std::vector<std::string>{src1Addr.first.value(), src1Addr.second});
      }
      else {
        instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{src1Addr.second});
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.emplace_back(MachineInstruction::MOV_B_IMM,
                                std::vector<std::string>{MachineCodeGenerator::getBinaryAnyInt(src2)});
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.emplace_back(MachineInstruction::ADD_A);
      break;
    case bblocks::SUB:
      instructions.emplace_back(MachineInstruction::SUB_A_AB);
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::invalid_argument("Unimplemented");
    case bblocks::AND:
      instructions.emplace_back(MachineInstruction::AND_A);
      break;
    case bblocks::OR:
      instructions.emplace_back(MachineInstruction::OR_A);
      break;
    case bblocks::XOR:
      instructions.emplace_back(MachineInstruction::XOR_A);
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER: {
      const auto destAddr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][dest]);
      if (destAddr.first.has_value()) {
        instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A,
                                  std::vector<std::string>{destAddr.first.value(), destAddr.second});
      }
      else {
        instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddr.second});
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
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src1Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src1]);
      if (src1Addr.first.has_value()) {
        instructions.emplace_back(MachineInstruction::MOV_A_ABS,
                                  std::vector<std::string>{src1Addr.first.value(), src1Addr.second});
      }
      else {
        instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{src1Addr.second});
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.emplace_back(MachineInstruction::MOV_B_IMM,
                                std::vector<std::string>{MachineCodeGenerator::getBinaryAnyInt(src2)});
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.emplace_back(MachineInstruction::ADD_A);
      break;
    case bblocks::SUB:
      instructions.emplace_back(MachineInstruction::SUB_A_AB);
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::invalid_argument("Unimplemented");
    case bblocks::AND:
      instructions.emplace_back(MachineInstruction::AND_A);
      break;
    case bblocks::OR:
      instructions.emplace_back(MachineInstruction::OR_A);
      break;
    case bblocks::XOR:
      instructions.emplace_back(MachineInstruction::XOR_A);
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER:
      throw std::invalid_argument("Register cannot be number type");
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
      instructions.emplace_back(MachineInstruction::MOV_A_IMM,
                                std::vector<std::string>{MachineCodeGenerator::getBinaryAnyInt(src1)});
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src2Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src2]);
      if (src2Addr.first.has_value()) {
        instructions.emplace_back(MachineInstruction::MOV_B_ABS,
                                  std::vector<std::string>{src2Addr.first.value(), src2Addr.second});
      }
      else {
        instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{src2Addr.second});
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.emplace_back(MachineInstruction::ADD_A);
      break;
    case bblocks::SUB:
      instructions.emplace_back(MachineInstruction::SUB_A_AB);
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::invalid_argument("Unimplemented");
    case bblocks::AND:
      instructions.emplace_back(MachineInstruction::AND_A);
      break;
    case bblocks::OR:
      instructions.emplace_back(MachineInstruction::OR_A);
      break;
    case bblocks::XOR:
      instructions.emplace_back(MachineInstruction::XOR_A);
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER: {
      const auto destAddr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][dest]);
      if (destAddr.first.has_value()) {
        instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A,
                                  std::vector<std::string>{destAddr.first.value(), destAddr.second});
      }
      else {
        instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddr.second});
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
      instructions.emplace_back(MachineInstruction::MOV_A_IMM,
                                std::vector<std::string>{MachineCodeGenerator::getBinaryAnyInt(src1)});
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src2Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src2]);
      if (src2Addr.first.has_value()) {
        instructions.emplace_back(MachineInstruction::MOV_B_ABS,
                                  std::vector<std::string>{src2Addr.first.value(), src2Addr.second});
      }
      else {
        instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{src2Addr.second});
      }
      break;
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.emplace_back(MachineInstruction::ADD_A);
      break;
    case bblocks::SUB:
      instructions.emplace_back(MachineInstruction::SUB_A_AB);
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::invalid_argument("Unimplemented");
    case bblocks::AND:
      instructions.emplace_back(MachineInstruction::AND_A);
      break;
    case bblocks::OR:
      instructions.emplace_back(MachineInstruction::OR_A);
      break;
    case bblocks::XOR:
      instructions.emplace_back(MachineInstruction::XOR_A);
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER:
      throw std::invalid_argument("Register cannot be number type");
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
      instructions.emplace_back(MachineInstruction::MOV_A_IMM,
                                std::vector<std::string>{MachineCodeGenerator::getBinaryAnyInt(src1)});
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.emplace_back(MachineInstruction::MOV_B_IMM,
                                std::vector<std::string>{MachineCodeGenerator::getBinaryAnyInt(src2)});
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.emplace_back(MachineInstruction::ADD_A);
      break;
    case bblocks::SUB:
      instructions.emplace_back(MachineInstruction::SUB_A_AB);
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::invalid_argument("Unimplemented");
    case bblocks::AND:
      instructions.emplace_back(MachineInstruction::AND_A);
      break;
    case bblocks::OR:
      instructions.emplace_back(MachineInstruction::OR_A);
      break;
    case bblocks::XOR:
      instructions.emplace_back(MachineInstruction::XOR_A);
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER: {
      const auto destAddr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][dest]);
      if (destAddr.first.has_value()) {
        instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A,
                                  std::vector<std::string>{destAddr.first.value(), destAddr.second});
      }
      else {
        instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddr.second});
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
      instructions.emplace_back(MachineInstruction::MOV_A_IMM,
                                std::vector<std::string>{MachineCodeGenerator::getBinaryAnyInt(src1)});
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getSource2Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      instructions.emplace_back(MachineInstruction::MOV_B_IMM,
                                std::vector<std::string>{MachineCodeGenerator::getBinaryAnyInt(src2)});
      break;
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      break;
    }
  }

  switch (instruction.getOperation()) {
    case bblocks::ADD:
      instructions.emplace_back(MachineInstruction::ADD_A);
      break;
    case bblocks::SUB:
      instructions.emplace_back(MachineInstruction::SUB_A_AB);
      break;
    case bblocks::MUL:
    case bblocks::DIV:
    case bblocks::MOD:
      throw std::invalid_argument("Unimplemented");
    case bblocks::AND:
      instructions.emplace_back(MachineInstruction::AND_A);
      break;
    case bblocks::OR:
      instructions.emplace_back(MachineInstruction::OR_A);
      break;
    case bblocks::XOR:
      instructions.emplace_back(MachineInstruction::XOR_A);
      break;
  }

  switch (instruction.getDestinationType()) {
    case bblocks::BBInstruction::DestinationType::REGISTER:
      throw std::invalid_argument("Register cannot be number type");
    case bblocks::BBInstruction::DestinationType::MEMORY:
      break;
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperationRegRegReg(int src1, int src2, int dest,
                                                                                       bblocks::BBBinaryOperationEnum type) {}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperationRegRegMem(int src1, int src2, uint16_t dest,
                                                                                       bblocks::BBBinaryOperationEnum type) {}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperationRegMemReg(int src1, uint16_t src2, int dest,
                                                                                       bblocks::BBBinaryOperationEnum type) {}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperationRegMemMem(int src1, uint16_t src2, uint16_t dest,
                                                                                       bblocks::BBBinaryOperationEnum type) {}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperationMemRegReg(uint16_t src1, int src2, int dest,
                                                                                       bblocks::BBBinaryOperationEnum type) {}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperationMemRegMem(uint16_t src1, int src2, uint16_t dest,
                                                                                       bblocks::BBBinaryOperationEnum type) {}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperationMemMemReg(uint16_t src1, uint16_t src2, int dest,
                                                                                       bblocks::BBBinaryOperationEnum type) {}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperationMemMemMem(uint16_t src1, uint16_t src2,
                                                                                       uint16_t dest,
                                                                                       bblocks::BBBinaryOperationEnum type) {}

std::vector<MachineInstruction> MachineCodeGenerator::generateBranch(const bblocks::BBBranchV& instruction) {
  const std::string value = instruction.getValue();
  const int valueReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(value);
  const bblocks::BBBranchCondition condition = instruction.getCondition();
  const std::string trueLabel = instruction.getTrueLabel();
  const std::string falseLabel = instruction.getFalseLabel();

  switch (instruction.getValueType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      if (valueReg != -1) {
        return generateBranchReg(valueReg, condition, trueLabel, falseLabel);
      }
      else {
        return generateBranchMem(variableAddresses_.at(currentScope).at(value), condition, trueLabel, falseLabel);
      }
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      if (valueReg != -1) {}
      else {}
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBranch(const bblocks::BBBranchN& instruction) {
  const uint16_t value = instruction.getValue();
  const bblocks::BBBranchCondition condition = instruction.getCondition();
  const std::string trueLabel = instruction.getTrueLabel();
  const std::string falseLabel = instruction.getFalseLabel();

  switch (instruction.getValueType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      return generateBranchConst(static_cast<uint8_t>(value), condition, trueLabel, falseLabel);
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      return generateBranchMem(value, condition, trueLabel, falseLabel);
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBranchReg(int val, bblocks::BBBranchCondition condition,
                                                                        const std::string& trueLabel,
                                                                        const std::string& falseLabel) {
  std::vector<MachineInstruction> instructions;
  if (val == 1) {}
  else if (val == 2) {}

  appendBranchJumps(instructions, condition, trueLabel, falseLabel);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBranchMem(uint16_t val, bblocks::BBBranchCondition condition,
                                                                        const std::string& trueLabel,
                                                                        const std::string& falseLabel) {
  std::vector<MachineInstruction> instructions;

  appendBranchJumps(instructions, condition, trueLabel, falseLabel);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBranchConst(uint8_t val, bblocks::BBBranchCondition condition,
                                                                          const std::string& trueLabel,
                                                                          const std::string& falseLabel) {
  std::vector<MachineInstruction> instructions;

  appendBranchJumps(instructions, condition, trueLabel, falseLabel);

  return instructions;
}

void MachineCodeGenerator::appendBranchJumps(std::vector<MachineInstruction>& instructions, bblocks::BBBranchCondition condition,
                                             const std::string& trueLabel, const std::string& falseLabel) {
  switch (condition) {
    case bblocks::BBBranchCondition::ANY:
      instructions.emplace_back(MachineInstruction::JMP_IMM, std::vector<std::string>{trueLabel});
      break;
    case bblocks::BBBranchCondition::NEGATIVE:
      instructions.emplace_back(MachineInstruction::JMP_IMM, std::vector<std::string>{trueLabel});
      instructions.emplace_back(MachineInstruction::JMP_IMM, std::vector<std::string>{falseLabel});
      break;
    case bblocks::BBBranchCondition::POSITIVE:
      instructions.emplace_back(MachineInstruction::JMP_IMM_NS, std::vector<std::string>{trueLabel});
      instructions.emplace_back(MachineInstruction::JMP_IMM, std::vector<std::string>{falseLabel});
      break;
    case bblocks::BBBranchCondition::ODD:
      instructions.emplace_back(MachineInstruction::JMP_IMM_P, std::vector<std::string>{trueLabel});
      instructions.emplace_back(MachineInstruction::JMP_IMM, std::vector<std::string>{falseLabel});
      break;
    case bblocks::BBBranchCondition::EVEN:
      instructions.emplace_back(MachineInstruction::JMP_IMM_NP, std::vector<std::string>{trueLabel});
      instructions.emplace_back(MachineInstruction::JMP_IMM, std::vector<std::string>{falseLabel});
      break;
    case bblocks::BBBranchCondition::ZERO:
      instructions.emplace_back(MachineInstruction::JMP_IMM_Z, std::vector<std::string>{trueLabel});
      instructions.emplace_back(MachineInstruction::JMP_IMM, std::vector<std::string>{falseLabel});
      break;
    case bblocks::BBBranchCondition::NONZERO:
      instructions.emplace_back(MachineInstruction::JMP_IMM_NZ, std::vector<std::string>{trueLabel});
      instructions.emplace_back(MachineInstruction::JMP_IMM, std::vector<std::string>{falseLabel});
      break;
    case bblocks::BBBranchCondition::CARRY:
      instructions.emplace_back(MachineInstruction::JMP_IMM_C, std::vector<std::string>{trueLabel});
      instructions.emplace_back(MachineInstruction::JMP_IMM, std::vector<std::string>{falseLabel});
      break;
    case bblocks::BBBranchCondition::NOCARRY:
      instructions.emplace_back(MachineInstruction::JMP_IMM_NC, std::vector<std::string>{trueLabel});
      instructions.emplace_back(MachineInstruction::JMP_IMM, std::vector<std::string>{falseLabel});
      break;
    case bblocks::BBBranchCondition::OVERFLOW:
      instructions.emplace_back(MachineInstruction::JMP_IMM_O, std::vector<std::string>{trueLabel});
      instructions.emplace_back(MachineInstruction::JMP_IMM, std::vector<std::string>{falseLabel});
      break;
    case bblocks::BBBranchCondition::NOOVERFLOW:
      instructions.emplace_back(MachineInstruction::JMP_IMM_NO, std::vector<std::string>{trueLabel});
      instructions.emplace_back(MachineInstruction::JMP_IMM, std::vector<std::string>{falseLabel});
      break;
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateCall(const bblocks::BBCall& /*instruction*/) {
  return {MachineInstruction::JMP_FUN};
}

std::vector<MachineInstruction> MachineCodeGenerator::generateRet(const bblocks::BBRet& /*instruction*/) {
  return {MachineInstruction::JMP_RET};
}

std::vector<MachineInstruction> MachineCodeGenerator::generateHalt(const bblocks::BBHalt& /*instruction*/) {
  return {MachineInstruction::HALT};
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