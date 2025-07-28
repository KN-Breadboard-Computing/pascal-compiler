#include "machine_code_generator.hpp"

namespace machine_code {
int MachineCodeGenerator::registersNumber_{2};

void MachineCodeGenerator::generate(const std::map<std::string, bblocks::BBControlFlowGraph>& cfg, RegisterAllocator allocator, uint16_t variablesOffset) {
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

void MachineCodeGenerator::saveMachineCode(std::ostream& output) const {
  for (const auto& [functionName, instructions] : machineCode_) {
    for (const auto& instruction : instructions) {
      output << instruction.toString() << "\n";
    }
  }
}

std::vector<std::string> MachineCodeGenerator::getAssembly() const {
  std::vector<std::string> assemblyCode;
  for (const auto& [functionName, instructions] : machineCode_) {
    for (const auto& instruction : instructions) {
      if (instruction.getType() == MachineInstruction::Type::LABEL) {
        continue;
      }

      MachineInstruction instructionCopy = instruction;
      for (const auto& [label, value] : labelValues_.at(functionName)) {
        const auto addr = MachineCodeGenerator::getBinaryFullAddress(value);
        instructionCopy.replaceOperand(label, {addr.first, addr.second});
      }
      assemblyCode.push_back(instructionCopy.toAssembly());
    }
  }
  return assemblyCode;
}

void MachineCodeGenerator::saveAssembly(std::ostream& output) const {
  for (const auto& [functionName, instructions] : machineCode_) {
    for (const auto& instruction : instructions) {
      if (instruction.getType() == MachineInstruction::Type::LABEL) {
        continue;
      }

      MachineInstruction instructionCopy = instruction;
      for (const auto& [label, value] : labelValues_.at(functionName)) {
        const auto addr = MachineCodeGenerator::getBinaryFullAddress(value);
        instructionCopy.replaceOperand(label, {addr.first, addr.second});
      }
      output << instructionCopy.toAssembly() << "\n";
    }
  }
}

std::vector<uint8_t> MachineCodeGenerator::getBinaryCode() const {
  std::vector<uint8_t> binaryCode;
  for (const auto& [functionName, instructions] : machineCode_) {
    for (const auto& instruction : instructions) {
      if (instruction.getType() == MachineInstruction::Type::LABEL) {
        continue;
      }

      MachineInstruction instructionCopy = instruction;
      for (const auto& [label, value] : labelValues_.at(functionName)) {
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

void MachineCodeGenerator::saveBinary(std::ostream& output) const {
  for (const auto& [functionName, instructions] : machineCode_) {
    for (const auto& instruction : instructions) {
      if (instruction.getType() == MachineInstruction::Type::LABEL) {
        continue;
      }

      MachineInstruction instructionCopy = instruction;
      for (const auto& [label, value] : labelValues_.at(functionName)) {
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
    std::sort(outLinks.begin(), outLinks.end(), [](const std::string& a, const std::string& b) { return std::atoi(a.substr(2, a.size() - 2).c_str()) > std::atoi(b.substr(2, b.size() - 2).c_str()); });

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
            return generateMoveMemImmMemMemImmMem(variableAddresses_[currentScope].at(src), variableAddresses_[currentScope].at(dest));
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
          throw std::invalid_argument("Register cannot be number type");
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
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          return generateMoveMemMem(src, dest);
        }
      }
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveConstReg(uint8_t src, int dest) {
#ifdef MC_DEBUG
  std::cout << "reg := const" << std::endl;
#endif

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
#ifdef MC_DEBUG
  std::cout << "[addr] := const" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);

  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_IMM, std::vector<std::string>{destAddress.first.value(), destAddress.second, getBinaryUint(src)});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_IMM_ZP, std::vector<std::string>{destAddress.second, getBinaryUint(src)});
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveConstMemImmReg(uint8_t src, int immDest) {
#ifdef MC_DEBUG
  std::cout << "[reg] := const" << std::endl;
#endif

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
#ifdef MC_DEBUG
  std::cout << "[[addr]] := const" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);

  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS, std::vector<std::string>{destAddress.first.value(), destAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{destAddress.second});
  }

  instructions.emplace_back(MachineInstruction::POP_TL);
  instructions.emplace_back(MachineInstruction::MOV_AT_TL_IMM, std::vector<std::string>{getBinaryUint(src)});

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveRegReg(int src, int dest) {
#ifdef MC_DEBUG
  std::cout << "reg := reg" << std::endl;
#endif

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
#ifdef MC_DEBUG
  std::cout << "[addr] := reg" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);

  if (src == 1) {
    if (destAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A, std::vector<std::string>{destAddress.first.value(), destAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddress.second});
    }
  }
  else if (src == 2) {
    if (destAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_AT_ABS_B, std::vector<std::string>{destAddress.first.value(), destAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_AT_ABS_B_ZP, std::vector<std::string>{destAddress.second});
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveRegMemImmReg(int src, int immDest) {
#ifdef MC_DEBUG
  std::cout << "[reg] := reg" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;

  if (src == 1) {
    if (immDest == 1) {
      instructions.emplace_back(MachineInstruction::MOV_TL_A);
      instructions.emplace_back(MachineInstruction::MOV_AT_TL_A);
    }
    else if (immDest == 2) {
      instructions.emplace_back(MachineInstruction::MOV_AT_B_A);
    }
  }
  else if (src == 2) {
    if (immDest == 1) {
      instructions.emplace_back(MachineInstruction::MOV_AT_A_B);
    }
    else if (immDest == 2) {
      instructions.emplace_back(MachineInstruction::MOV_TL_B);
      instructions.emplace_back(MachineInstruction::MOV_AT_TL_B);
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveRegMemImmMem(int src, uint16_t immDest) {
#ifdef MC_DEBUG
  std::cout << "[[addr]] := reg" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);

  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS, std::vector<std::string>{destAddress.first.value(), destAddress.second});
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
#ifdef MC_DEBUG
  std::cout << "reg := [addr]" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(src);

  if (dest == 1) {
    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }
  }
  else if (dest == 2) {
    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemMem(uint16_t src, uint16_t dest) {
#ifdef MC_DEBUG
  std::cout << "[addr] := [addr]" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(src);
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);

  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{srcAddress.second});
  }

  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::POP_MEM, std::vector<std::string>{destAddress.first.value(), destAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::POP_MEM_ZP, std::vector<std::string>{destAddress.second});
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemMemImmReg(uint16_t src, int immDest) {
#ifdef MC_DEBUG
  std::cout << "[reg] := [addr]" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(src);

  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
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
#ifdef MC_DEBUG
  std::cout << "[[addr]] := [addr]" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(src);
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);

  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{srcAddress.second});
  }

  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS, std::vector<std::string>{destAddress.first.value(), destAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{destAddress.second});
  }

  instructions.emplace_back(MachineInstruction::POP_TL);
  instructions.emplace_back(MachineInstruction::POP_TH);
  instructions.emplace_back(MachineInstruction::MOV_AT_TL_TH);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmRegReg(int immSrc, int dest) {
#ifdef MC_DEBUG
  std::cout << "reg := [reg]" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;

  if (immSrc == 1) {
    if (dest == 1) {
      instructions.emplace_back(MachineInstruction::MOV_TL_A);
      instructions.emplace_back(MachineInstruction::MOV_A_AT_TL);
    }
    else if (dest == 2) {
      instructions.emplace_back(MachineInstruction::MOV_B_AT_A);
    }
  }
  else if (immSrc == 2) {
    if (dest == 1) {
      instructions.emplace_back(MachineInstruction::MOV_A_AT_B);
    }
    else if (dest == 2) {
      instructions.emplace_back(MachineInstruction::MOV_TL_B);
      instructions.emplace_back(MachineInstruction::MOV_B_AT_TL);
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmRegMem(int immSrc, uint16_t dest) {
#ifdef MC_DEBUG
  std::cout << "[addr] := [reg]" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);

  if (immSrc == 1) {
    instructions.emplace_back(MachineInstruction::PUSH_B);
    instructions.emplace_back(MachineInstruction::MOV_B_AT_A);
    if (destAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_AT_ABS_B, std::vector<std::string>{destAddress.first.value(), destAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_AT_ABS_B_ZP, std::vector<std::string>{destAddress.second});
    }
    instructions.emplace_back(MachineInstruction::POP_B);
  }
  else if (immSrc == 2) {
    instructions.push_back(MachineInstruction::PUSH_A);
    instructions.emplace_back(MachineInstruction::MOV_A_AT_B);
    if (destAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A, std::vector<std::string>{destAddress.first.value(), destAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddress.second});
    }
    instructions.emplace_back(MachineInstruction::POP_A);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmRegMemImmReg(int immSrc, int immDest) {
#ifdef MC_DEBUG
  std::cout << "[reg] := [reg]" << std::endl;
#endif

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
#ifdef MC_DEBUG
  std::cout << "[[addr]] := [reg]" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);

  if (immSrc == 1) {
    instructions.emplace_back(MachineInstruction::PUSH_B);

    if (destAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS, std::vector<std::string>{destAddress.first.value(), destAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{destAddress.second});
    }

    instructions.emplace_back(MachineInstruction::MOV_TH_AT_A);
    instructions.emplace_back(MachineInstruction::MOV_AT_B_TH);
    instructions.emplace_back(MachineInstruction::POP_B);
  }
  else if (immSrc == 2) {
    instructions.emplace_back(MachineInstruction::PUSH_A);

    if (destAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{destAddress.first.value(), destAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{destAddress.second});
    }

    instructions.emplace_back(MachineInstruction::MOV_TH_AT_B);
    instructions.emplace_back(MachineInstruction::MOV_AT_A_TH);
    instructions.emplace_back(MachineInstruction::POP_A);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmMemReg(uint16_t immSrc, int dest) {
#ifdef MC_DEBUG
  std::cout << "reg := [[addr]]" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(immSrc);

  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
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

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmMemMem(uint16_t immSrc, uint16_t dest) {
#ifdef MC_DEBUG
  std::cout << "[addr] := [[addr]]" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(immSrc);
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);

  instructions.emplace_back(MachineInstruction::PUSH_A);
  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{
                                                                 srcAddress.first.value(),
                                                                 srcAddress.second,
                                                             });
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{srcAddress.second});
  }

  instructions.emplace_back(MachineInstruction::MOV_TL_A);
  instructions.emplace_back(MachineInstruction::MOV_A_AT_TL);

  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A, std::vector<std::string>{destAddress.first.value(), destAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddress.second});
  }
  instructions.emplace_back(MachineInstruction::POP_A);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmMemMemImmReg(uint16_t immSrc, int immDest) {
#ifdef MC_DEBUG
  std::cout << "[reg] := [[addr]]" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(immSrc);

  if (immDest == 1) {
    instructions.emplace_back(MachineInstruction::PUSH_B);

    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }

    instructions.emplace_back(MachineInstruction::MOV_TH_AT_B);
    instructions.emplace_back(MachineInstruction::MOV_AT_A_TH);
    instructions.emplace_back(MachineInstruction::POP_B);
  }
  else if (immDest == 2) {
    instructions.emplace_back(MachineInstruction::PUSH_A);

    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }

    instructions.emplace_back(MachineInstruction::MOV_TH_AT_A);
    instructions.emplace_back(MachineInstruction::MOV_AT_B_TH);
    instructions.emplace_back(MachineInstruction::POP_A);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateMoveMemImmMemMemImmMem(uint16_t immSrc, uint16_t immDest) {
#ifdef MC_DEBUG
  std::cout << "[[addr]] := [[addr]]" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(immSrc);
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);

  instructions.emplace_back(MachineInstruction::PUSH_A);
  instructions.emplace_back(MachineInstruction::PUSH_B);

  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{srcAddress.second});
  }

  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_B_ABS, std::vector<std::string>{destAddress.first.value(), destAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{destAddress.second});
  }

  instructions.emplace_back(MachineInstruction::MOV_TH_AT_A);
  instructions.emplace_back(MachineInstruction::MOV_AT_B_TH);
  instructions.emplace_back(MachineInstruction::POP_B);
  instructions.emplace_back(MachineInstruction::POP_A);

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
          if (srcReg != -1 && destReg != -1) {
            return generateUnOpRegReg(srcReg, destReg, operation);
          }
          else if (srcReg != -1) {
            return generateUnOpRegMem(srcReg, variableAddresses_[currentScope].at(dest), operation);
          }
          else if (destReg != -1) {
            return generateUnOpMemReg(variableAddresses_[currentScope].at(src), destReg, operation);
          }
          else {
            return generateUnOpMemMem(variableAddresses_[currentScope].at(src), variableAddresses_[currentScope].at(dest), operation);
          }
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          if (srcReg != -1 && destReg != -1) {
            return generateUnOpRegMemImmReg(srcReg, destReg, operation);
          }
          else if (srcReg != -1) {
            return generateUnOpRegMemImmMem(srcReg, variableAddresses_[currentScope].at(dest), operation);
          }
          else if (destReg != -1) {
            return generateUnOpMemMemImmReg(variableAddresses_[currentScope].at(src), destReg, operation);
          }
          else {
            return generateUnOpMemMemImmMem(variableAddresses_[currentScope].at(src), variableAddresses_[currentScope].at(dest), operation);
          }
        }
      }
      case bblocks::BBInstruction::SourceType::MEMORY: {
        switch (instruction.getDestinationType()) {
          case bblocks::BBInstruction::DestinationType::REGISTER: {
            if (srcReg != -1 && destReg != -1) {
              return generateUnOpMemImmRegReg(srcReg, destReg, operation);
            }
            else if (srcReg != -1) {
              return generateUnOpMemImmRegMem(srcReg, variableAddresses_[currentScope].at(dest), operation);
            }
            else if (destReg != -1) {
              return generateUnOpMemImmMemReg(variableAddresses_[currentScope].at(src), destReg, operation);
            }
            else {
              return generateUnOpMemImmMemMem(variableAddresses_[currentScope].at(src), variableAddresses_[currentScope].at(dest), operation);
            }
          }
          case bblocks::BBInstruction::DestinationType::MEMORY: {
            if (srcReg != -1 && destReg != -1) {
              return generateUnOpMemImmRegMemImmReg(srcReg, destReg, operation);
            }
            else if (srcReg != -1) {
              return generateUnOpMemImmRegMemImmMem(srcReg, variableAddresses_[currentScope].at(dest), operation);
            }
            else if (destReg != -1) {
              return generateUnOpMemImmMemMemImmReg(variableAddresses_[currentScope].at(src), destReg, operation);
            }
            else {
              return generateUnOpMemImmMemMemImmMem(variableAddresses_[currentScope].at(src), variableAddresses_[currentScope].at(dest), operation);
            }
          }
        }
      }
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
          if (srcReg != -1) {
            return generateUnOpRegMem(srcReg, dest, operation);
          }
          else {
            return generateUnOpMemMem(variableAddresses_[currentScope].at(src), dest, operation);
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
            return generateUnOpMemImmRegMem(srcReg, dest, operation);
          }
          else {
            return generateUnOpMemImmMemMem(variableAddresses_[currentScope].at(src), dest, operation);
          }
        }
      }
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperation(const bblocks::BBUnaryOperationNV& instruction) {
  const int src = instruction.getSource();
  const std::string dest = instruction.getDestination();
  const int destReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(dest);
  const bblocks::BBUnaryOperationEnum operation = instruction.getOperation();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          if (destReg != -1) {
            return generateUnOpConstReg(static_cast<uint8_t>(src), destReg, operation);
          }
          else {
            return generateUnOpConstMem(static_cast<uint8_t>(src), variableAddresses_.at(currentScope).at(dest), operation);
          }
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          if (destReg != -1) {
            return generateUnOpConstMemImmReg(static_cast<uint8_t>(src), destReg, operation);
          }
          else {
            return generateUnOpConstMemImmMem(static_cast<uint8_t>(src), variableAddresses_.at(currentScope).at(dest), operation);
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
            return generateUnOpMemReg(src, destReg, operation);
          }
          else {
            return generateUnOpMemMem(src, variableAddresses_.at(currentScope).at(dest), operation);
          }
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          if (destReg != -1) {
            return generateUnOpMemMemImmReg(src, destReg, operation);
          }
          else {
            return generateUnOpMemMemImmMem(src, variableAddresses_.at(currentScope).at(dest), operation);
          }
        }
      }
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnaryOperation(const bblocks::BBUnaryOperationNN& instruction) {
  const int src = instruction.getSource();
  const int dest = instruction.getDestination();
  const bblocks::BBUnaryOperationEnum operation = instruction.getOperation();

  switch (instruction.getSourceType()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      switch (instruction.getDestinationType()) {
        case bblocks::BBInstruction::DestinationType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::DestinationType::MEMORY: {
          return generateUnOpConstMem(static_cast<uint8_t>(src), dest, operation);
        }
      }
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
          return generateUnOpMemMem(src, dest, operation);
        }
      }
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpConstReg(uint8_t src, int dest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "reg := op(const)" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;

  if (dest == 1) {
    instructions.emplace_back(MachineInstruction::MOV_A_IMM, std::vector<std::string>{getBinaryUint(src)});
    generateUnaryOperatorAA(instructions, op);
  }
  else if (dest == 2) {
    instructions.emplace_back(MachineInstruction::MOV_B_IMM, std::vector<std::string>{getBinaryUint(src)});
    generateUnaryOperatorBB(instructions, op);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpConstMem(uint8_t src, uint16_t dest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[addr] := op(const)" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;

  instructions.emplace_back(MachineInstruction::PUSH_A);
  instructions.emplace_back(MachineInstruction::MOV_A_IMM, std::vector<std::string>{getBinaryUint(src)});
  generateUnaryOperatorAMem(instructions, op, dest);
  instructions.emplace_back(MachineInstruction::POP_A);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpConstMemImmReg(uint8_t src, int immDest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[reg] := op(const)" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;

  if (immDest == 1) {
    instructions.emplace_back(MachineInstruction::PUSH_B);
    instructions.emplace_back(MachineInstruction::MOV_B_IMM, std::vector<std::string>{getBinaryUint(src)});
    generateUnaryOperatorBB(instructions, op);
    instructions.emplace_back(MachineInstruction::MOV_AT_A_B);
    instructions.emplace_back(MachineInstruction::POP_B);
  }
  else if (immDest == 2) {
    instructions.emplace_back(MachineInstruction::PUSH_A);
    instructions.emplace_back(MachineInstruction::MOV_A_IMM, std::vector<std::string>{getBinaryUint(src)});
    generateUnaryOperatorAA(instructions, op);
    instructions.emplace_back(MachineInstruction::MOV_AT_B_A);
    instructions.emplace_back(MachineInstruction::POP_A);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpConstMemImmMem(uint8_t src, uint16_t immDest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[[addr]] := op(const)" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);

  instructions.emplace_back(MachineInstruction::PUSH_A);
  instructions.emplace_back(MachineInstruction::MOV_A_IMM, std::vector<std::string>{getBinaryUint(src)});
  generateUnaryOperatorAStc(instructions, op);

  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{destAddress.first.value(), destAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{destAddress.second});
  }

  instructions.emplace_back(MachineInstruction::POP_TH);
  instructions.emplace_back(MachineInstruction::MOV_AT_A_TH);
  instructions.emplace_back(MachineInstruction::POP_A);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpRegReg(int src, int dest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "reg := op(reg)" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  if (src == 1) {
    if (dest == 1) {
      generateUnaryOperatorAA(instructions, op);
    }
    else if (dest == 2) {
      generateUnaryOperatorAB(instructions, op);
    }
  }
  else if (src == 2) {
    if (dest == 1) {
      generateUnaryOperatorBA(instructions, op);
    }
    else if (dest == 2) {
      generateUnaryOperatorBB(instructions, op);
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpRegMem(int src, uint16_t dest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[addr] := op(reg)" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;

  if (src == 1) {
    generateUnaryOperatorAMem(instructions, op, dest);
  }
  else if (src == 2) {
    generateUnaryOperatorBMem(instructions, op, dest);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpRegMemImmReg(int src, int immDest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[reg] := op(reg)" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;

  if (src == 1) {
    generateUnaryOperatorAStc(instructions, op);
  }
  else if (src == 2) {
    generateUnaryOperatorBStc(instructions, op);
  }

  instructions.emplace_back(MachineInstruction::POP_TH);

  if (immDest == 1) {
    instructions.emplace_back(MachineInstruction::MOV_AT_A_TH);
  }
  else if (immDest == 2) {
    instructions.emplace_back(MachineInstruction::MOV_AT_B_TH);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpRegMemImmMem(int src, uint16_t immDest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[[addr]] := op(reg)" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);

  if (src == 1) {
    generateUnaryOperatorAStc(instructions, op);
  }
  else if (src == 2) {
    generateUnaryOperatorBStc(instructions, op);
  }

  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS, std::vector<std::string>{destAddress.first.value(), destAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{destAddress.second});
  }

  instructions.emplace_back(MachineInstruction::POP_TL);
  instructions.emplace_back(MachineInstruction::POP_TH);
  instructions.emplace_back(MachineInstruction::MOV_AT_TL_TH);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpMemReg(uint16_t src, int dest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "reg := op([addr])" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(src);

  if (dest == 1) {
    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }

    generateUnaryOperatorAA(instructions, op);
  }
  else if (dest == 2) {
    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }

    generateUnaryOperatorBB(instructions, op);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpMemMem(uint16_t src, uint16_t dest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[addr] := op([addr])" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(src);

  instructions.emplace_back(MachineInstruction::PUSH_A);

  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{srcAddress.second});
  }

  generateUnaryOperatorAMem(instructions, op, dest);
  instructions.emplace_back(MachineInstruction::POP_A);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpMemMemImmReg(uint16_t src, int immDest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[reg] := op([addr])" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(src);

  if (immDest == 1) {
    instructions.emplace_back(MachineInstruction::PUSH_B);

    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }

    generateUnaryOperatorBB(instructions, op);
    instructions.emplace_back(MachineInstruction::MOV_AT_A_B);
    instructions.emplace_back(MachineInstruction::POP_B);
  }
  else if (immDest == 2) {
    instructions.emplace_back(MachineInstruction::PUSH_A);

    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }

    generateUnaryOperatorAA(instructions, op);
    instructions.emplace_back(MachineInstruction::MOV_AT_B_A);
    instructions.emplace_back(MachineInstruction::POP_A);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpMemMemImmMem(uint16_t src, uint16_t immDest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[[addr]] := op([addr])" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(src);
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);

  instructions.emplace_back(MachineInstruction::PUSH_A);

  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{srcAddress.second});
  }

  generateUnaryOperatorAStc(instructions, op);

  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{destAddress.first.value(), destAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{destAddress.second});
  }

  instructions.emplace_back(MachineInstruction::POP_TH);
  instructions.emplace_back(MachineInstruction::MOV_AT_A_TH);
  instructions.emplace_back(MachineInstruction::POP_A);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpMemImmRegReg(int immSrc, int dest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "reg := op([reg])" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;

  if (immSrc == 1) {
    if (dest == 1) {
      instructions.emplace_back(MachineInstruction::MOV_TH_AT_A);
      instructions.emplace_back(MachineInstruction::MOV_A_TH);
      generateUnaryOperatorAA(instructions, op);
    }
    else if (dest == 2) {
      instructions.emplace_back(MachineInstruction::MOV_B_AT_A);
      generateUnaryOperatorBB(instructions, op);
    }
  }
  else if (immSrc == 2) {
    if (dest == 1) {
      instructions.emplace_back(MachineInstruction::MOV_A_AT_B);
      generateUnaryOperatorAA(instructions, op);
    }
    else if (dest == 2) {
      instructions.emplace_back(MachineInstruction::MOV_TH_AT_B);
      instructions.emplace_back(MachineInstruction::MOV_B_TH);
      generateUnaryOperatorBB(instructions, op);
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpMemImmRegMem(int immSrc, uint16_t dest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[addr] := op([reg])" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;

  if (immSrc == 1) {
    instructions.emplace_back(MachineInstruction::PUSH_B);
    instructions.emplace_back(MachineInstruction::MOV_B_AT_A);
    generateUnaryOperatorBMem(instructions, op, dest);
    instructions.emplace_back(MachineInstruction::POP_B);
  }
  else if (immSrc == 2) {
    instructions.emplace_back(MachineInstruction::PUSH_A);
    instructions.emplace_back(MachineInstruction::MOV_A_AT_B);
    generateUnaryOperatorAMem(instructions, op, dest);
    instructions.emplace_back(MachineInstruction::POP_A);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpMemImmRegMemImmReg(int immSrc, int immDest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[reg] := op([reg])" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  if (immDest == 1) {
    instructions.emplace_back(MachineInstruction::PUSH_B);

    if (immSrc == 1) {
      instructions.emplace_back(MachineInstruction::MOV_B_AT_A);
      generateUnaryOperatorBB(instructions, op);
    }
    else if (immSrc == 2) {
      instructions.emplace_back(MachineInstruction::MOV_TH_AT_B);
      instructions.emplace_back(MachineInstruction::MOV_B_TH);
      generateUnaryOperatorBB(instructions, op);
    }

    instructions.emplace_back(MachineInstruction::MOV_AT_A_B);
    instructions.emplace_back(MachineInstruction::POP_B);
  }
  else if (immDest == 2) {
    instructions.emplace_back(MachineInstruction::PUSH_A);

    if (immSrc == 1) {
      instructions.emplace_back(MachineInstruction::MOV_TH_AT_A);
      instructions.emplace_back(MachineInstruction::MOV_A_TH);
      generateUnaryOperatorAA(instructions, op);
    }
    else if (immSrc == 2) {
      instructions.emplace_back(MachineInstruction::MOV_A_AT_B);
      generateUnaryOperatorAA(instructions, op);
    }

    instructions.emplace_back(MachineInstruction::MOV_AT_B_A);
    instructions.emplace_back(MachineInstruction::POP_A);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpMemImmRegMemImmMem(int immSrc, uint16_t immDest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[[addr]] := op([reg])" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);

  if (immSrc == 1) {
    instructions.emplace_back(MachineInstruction::PUSH_B);
    instructions.emplace_back(MachineInstruction::MOV_B_AT_A);
    generateUnaryOperatorBStc(instructions, op);

    if (destAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS, std::vector<std::string>{destAddress.first.value(), destAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{destAddress.second});
    }

    instructions.emplace_back(MachineInstruction::POP_TH);
    instructions.emplace_back(MachineInstruction::MOV_AT_B_TH);
    instructions.emplace_back(MachineInstruction::POP_B);
  }
  else if (immSrc == 2) {
    instructions.emplace_back(MachineInstruction::PUSH_A);
    instructions.emplace_back(MachineInstruction::MOV_A_AT_B);
    generateUnaryOperatorAStc(instructions, op);

    if (destAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{destAddress.first.value(), destAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{destAddress.second});
    }

    instructions.emplace_back(MachineInstruction::POP_TH);
    instructions.emplace_back(MachineInstruction::MOV_AT_A_TH);
    instructions.emplace_back(MachineInstruction::POP_A);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpMemImmMemReg(uint16_t immSrc, int dest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "reg := op([[addr]])" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(immSrc);

  if (dest == 1) {
    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }

    instructions.emplace_back(MachineInstruction::MOV_TL_A);
    instructions.emplace_back(MachineInstruction::MOV_A_AT_TL);
    generateUnaryOperatorAA(instructions, op);
  }
  else if (dest == 2) {
    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }

    instructions.emplace_back(MachineInstruction::MOV_TL_B);
    instructions.emplace_back(MachineInstruction::MOV_B_AT_TL);
    generateUnaryOperatorBB(instructions, op);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpMemImmMemMem(uint16_t immSrc, uint16_t dest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[addr] := op([[addr]])" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(immSrc);

  instructions.emplace_back(MachineInstruction::PUSH_A);

  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{srcAddress.second});
  }

  instructions.emplace_back(MachineInstruction::MOV_TL_A);
  instructions.emplace_back(MachineInstruction::MOV_A_AT_TL);
  generateUnaryOperatorAMem(instructions, op, dest);
  instructions.emplace_back(MachineInstruction::POP_A);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpMemImmMemMemImmReg(uint16_t immSrc, int immDest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[reg] := op([[addr]])" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(immSrc);

  if (immDest == 1) {
    instructions.emplace_back(MachineInstruction::PUSH_B);

    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_B_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }

    instructions.emplace_back(MachineInstruction::MOV_TL_B);
    instructions.emplace_back(MachineInstruction::MOV_B_AT_TL);
    generateUnaryOperatorBB(instructions, op);
    instructions.emplace_back(MachineInstruction::MOV_AT_A_B);
    instructions.emplace_back(MachineInstruction::POP_B);
  }
  else if (immDest == 2) {
    instructions.emplace_back(MachineInstruction::PUSH_A);

    if (srcAddress.first.has_value()) {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
    }
    else {
      instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{srcAddress.second});
    }

    instructions.emplace_back(MachineInstruction::MOV_TL_A);
    instructions.emplace_back(MachineInstruction::MOV_A_AT_TL);
    generateUnaryOperatorAStc(instructions, op);
    instructions.emplace_back(MachineInstruction::MOV_AT_B_A);
    instructions.emplace_back(MachineInstruction::POP_A);
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateUnOpMemImmMemMemImmMem(uint16_t immSrc, uint16_t immDest, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[[addr]] := op([[addr]])" << std::endl;
#endif

  std::vector<MachineInstruction> instructions;
  std::pair<std::optional<std::string>, std::string> srcAddress = getBinaryAddress(immSrc);
  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(immDest);

  instructions.emplace_back(MachineInstruction::PUSH_A);

  if (destAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::PUSH_ABS, std::vector<std::string>{destAddress.first.value(), destAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::PUSH_ABS_ZP, std::vector<std::string>{destAddress.second});
  }

  if (srcAddress.first.has_value()) {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS, std::vector<std::string>{srcAddress.first.value(), srcAddress.second});
  }
  else {
    instructions.emplace_back(MachineInstruction::MOV_A_ABS_ZP, std::vector<std::string>{srcAddress.second});
  }

  instructions.emplace_back(MachineInstruction::MOV_TL_A);
  instructions.emplace_back(MachineInstruction::MOV_A_AT_TL);
  generateUnaryOperatorAA(instructions, op);

  instructions.emplace_back(MachineInstruction::POP_TL);
  instructions.emplace_back(MachineInstruction::MOV_AT_TL_A);
  instructions.emplace_back(MachineInstruction::POP_A);

  return instructions;
}

void MachineCodeGenerator::generateUnaryOperatorAA(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "spec: regA := op(regA)" << std::endl;
#endif

  switch (op) {
    case bblocks::BBUnaryOperationEnum::NEG: {
      ins.emplace_back(MachineInstruction::NEG_A_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::NOT: {
      ins.emplace_back(MachineInstruction::INV_A_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::INC: {
      ins.emplace_back(MachineInstruction::INC_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::DEC: {
      ins.emplace_back(MachineInstruction::DEC_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHL: {
      ins.emplace_back(MachineInstruction::SHL_A_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHR: {
      ins.emplace_back(MachineInstruction::SHR_A_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SAR: {
      ins.emplace_back(MachineInstruction::DIV2_A_A);
      break;
    }
  }
}

void MachineCodeGenerator::generateUnaryOperatorAB(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "spec: regB := op(regA)" << std::endl;
#endif

  switch (op) {
    case bblocks::BBUnaryOperationEnum::NEG: {
      ins.emplace_back(MachineInstruction::NEG_B_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::NOT: {
      ins.emplace_back(MachineInstruction::INV_B_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::INC: {
      ins.emplace_back(MachineInstruction::INC_A);
      ins.emplace_back(MachineInstruction::MOV_B_A);
      ins.emplace_back(MachineInstruction::DEC_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::DEC: {
      ins.emplace_back(MachineInstruction::DEC_A);
      ins.emplace_back(MachineInstruction::MOV_B_A);
      ins.emplace_back(MachineInstruction::INC_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHL: {
      ins.emplace_back(MachineInstruction::SHL_B_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHR: {
      ins.emplace_back(MachineInstruction::SHR_B_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SAR: {
      ins.emplace_back(MachineInstruction::DIV2_B_A);
      break;
    }
  }
}

void MachineCodeGenerator::generateUnaryOperatorBA(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "spec: regA := op(regB)" << std::endl;
#endif

  switch (op) {
    case bblocks::BBUnaryOperationEnum::NEG: {
      ins.emplace_back(MachineInstruction::NEG_A_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::NOT: {
      ins.emplace_back(MachineInstruction::INV_A_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::INC: {
      ins.emplace_back(MachineInstruction::INC_B);
      ins.emplace_back(MachineInstruction::MOV_A_B);
      ins.emplace_back(MachineInstruction::DEC_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::DEC: {
      ins.emplace_back(MachineInstruction::DEC_B);
      ins.emplace_back(MachineInstruction::MOV_A_B);
      ins.emplace_back(MachineInstruction::INC_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHL: {
      ins.emplace_back(MachineInstruction::SHL_A_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHR: {
      ins.emplace_back(MachineInstruction::SHR_A_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SAR: {
      ins.emplace_back(MachineInstruction::DIV2_A_B);
      break;
    }
  }
}

void MachineCodeGenerator::generateUnaryOperatorBB(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "spec: regB := op(regB)" << std::endl;
#endif

  switch (op) {
    case bblocks::BBUnaryOperationEnum::NEG: {
      ins.emplace_back(MachineInstruction::NEG_B_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::NOT: {
      ins.emplace_back(MachineInstruction::INV_B_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::INC: {
      ins.emplace_back(MachineInstruction::INC_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::DEC: {
      ins.emplace_back(MachineInstruction::DEC_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHL: {
      ins.emplace_back(MachineInstruction::SHL_B_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHR: {
      ins.emplace_back(MachineInstruction::SHR_B_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SAR: {
      ins.emplace_back(MachineInstruction::DIV2_B_B);
      break;
    }
  }
}

void MachineCodeGenerator::generateUnaryOperatorAMem(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op, uint16_t dest) {
#ifdef MC_DEBUG
  std::cout << "spec: [addr] := op(regA)" << std::endl;
#endif

  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);

  switch (op) {
    case bblocks::BBUnaryOperationEnum::NEG: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::NEG_MEM_A, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::NEG_MEM_ZP_A, std::vector<std::string>{destAddress.second});
      }
      break;
    }
    case bblocks::BBUnaryOperationEnum::NOT: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::INV_MEM_A, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::INV_MEM_ZP_A, std::vector<std::string>{destAddress.second});
      }
      break;
    }
    case bblocks::BBUnaryOperationEnum::INC: {
      ins.emplace_back(MachineInstruction::INC_A);
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::MOV_AT_ABS_A, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddress.second});
      }
      ins.emplace_back(MachineInstruction::DEC_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::DEC: {
      ins.emplace_back(MachineInstruction::DEC_A);
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::MOV_AT_ABS_A, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::MOV_AT_ABS_A_ZP, std::vector<std::string>{destAddress.second});
      }
      ins.emplace_back(MachineInstruction::INC_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHL: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::SHL_MEM_A, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::SHL_MEM_ZP_A, std::vector<std::string>{destAddress.second});
      }
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHR: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::SHR_MEM_A, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::SHR_MEM_ZP_A, std::vector<std::string>{destAddress.second});
      }
      break;
    }
    case bblocks::BBUnaryOperationEnum::SAR: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::DIV2_MEM_A, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::DIV2_MEM_ZP_A, std::vector<std::string>{destAddress.second});
      }
      break;
    }
  }
}

void MachineCodeGenerator::generateUnaryOperatorBMem(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op, uint16_t dest) {
#ifdef MC_DEBUG
  std::cout << "spec: [addr] := op(regB)" << std::endl;
#endif

  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);

  switch (op) {
    case bblocks::BBUnaryOperationEnum::NEG: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::NEG_MEM_B, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::NEG_MEM_ZP_B, std::vector<std::string>{destAddress.second});
      }
      break;
    }
    case bblocks::BBUnaryOperationEnum::NOT: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::INV_MEM_B, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::INV_MEM_ZP_B, std::vector<std::string>{destAddress.second});
      }
      break;
    }
    case bblocks::BBUnaryOperationEnum::INC: {
      ins.emplace_back(MachineInstruction::INC_B);
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::MOV_AT_ABS_B, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::MOV_AT_ABS_B_ZP, std::vector<std::string>{destAddress.second});
      }
      ins.emplace_back(MachineInstruction::DEC_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::DEC: {
      ins.emplace_back(MachineInstruction::DEC_B);
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::MOV_AT_ABS_B, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::MOV_AT_ABS_B_ZP, std::vector<std::string>{destAddress.second});
      }
      ins.emplace_back(MachineInstruction::INC_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHL: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::SHL_MEM_B, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::SHL_MEM_ZP_B, std::vector<std::string>{destAddress.second});
      }
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHR: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::SHR_MEM_B, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::SHR_MEM_ZP_B, std::vector<std::string>{destAddress.second});
      }
      break;
    }
    case bblocks::BBUnaryOperationEnum::SAR: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::DIV2_MEM_B, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::DIV2_MEM_ZP_B, std::vector<std::string>{destAddress.second});
      }
      break;
    }
  }
}

void MachineCodeGenerator::generateUnaryOperatorAStc(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "spec: stack[top] := op(regA)" << std::endl;
#endif

  switch (op) {
    case bblocks::BBUnaryOperationEnum::NEG: {
      ins.emplace_back(MachineInstruction::NEG_STC_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::NOT: {
      ins.emplace_back(MachineInstruction::INV_STC_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::INC: {
      ins.emplace_back(MachineInstruction::INC_A);
      ins.emplace_back(MachineInstruction::PUSH_A);
      ins.emplace_back(MachineInstruction::DEC_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::DEC: {
      ins.emplace_back(MachineInstruction::DEC_A);
      ins.emplace_back(MachineInstruction::PUSH_A);
      ins.emplace_back(MachineInstruction::INC_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHL: {
      ins.emplace_back(MachineInstruction::SHL_STC_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHR: {
      ins.emplace_back(MachineInstruction::SHR_STC_A);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SAR: {
      ins.emplace_back(MachineInstruction::DIV2_STC_A);
      break;
    }
  }
}

void MachineCodeGenerator::generateUnaryOperatorBStc(std::vector<MachineInstruction>& ins, bblocks::BBUnaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "spec: stack[top] := op(regB)" << std::endl;
#endif

  switch (op) {
    case bblocks::BBUnaryOperationEnum::NEG: {
      ins.emplace_back(MachineInstruction::NEG_STC_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::NOT: {
      ins.emplace_back(MachineInstruction::INV_STC_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::INC: {
      ins.emplace_back(MachineInstruction::INC_B);
      ins.emplace_back(MachineInstruction::PUSH_B);
      ins.emplace_back(MachineInstruction::DEC_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::DEC: {
      ins.emplace_back(MachineInstruction::DEC_B);
      ins.emplace_back(MachineInstruction::PUSH_B);
      ins.emplace_back(MachineInstruction::INC_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHL: {
      ins.emplace_back(MachineInstruction::SHL_STC_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SHR: {
      ins.emplace_back(MachineInstruction::SHR_STC_B);
      break;
    }
    case bblocks::BBUnaryOperationEnum::SAR: {
      ins.emplace_back(MachineInstruction::DIV2_STC_B);
      break;
    }
  }
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationVVV& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src1 = instruction.getSource1();
  const int src1Reg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(src1);
  const std::string src2 = instruction.getSource2();
  const int src2Reg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(src2);
  const std::string dest = instruction.getDestination();
  const int destReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(dest);

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          throw std::invalid_argument("Constant cannot be string type");
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          break;
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          throw std::invalid_argument("Constant cannot be string type");
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          const auto src2Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src2]);
          break;
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationVVN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src1 = instruction.getSource1();
  const int src1Reg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(src1);
  const std::string src2 = instruction.getSource2();
  const int src2Reg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(src2);
  const int dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src1Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src1]);
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          throw std::invalid_argument("Constant cannot be string type");
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          const auto src2Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src2]);
          break;
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          throw std::invalid_argument("Constant cannot be string type");
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          const auto src2Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src2]);
          break;
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationVNV& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src1 = instruction.getSource1();
  const int src1Reg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(src1);
  const int src2 = instruction.getSource2();
  const std::string dest = instruction.getDestination();
  const int destReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(dest);

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src1Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src1]);
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          break;
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          break;
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationVNN& instruction) {
  std::vector<MachineInstruction> instructions;
  const std::string src1 = instruction.getSource1();
  const int src1Reg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(src1);
  const int src2 = instruction.getSource2();
  const int dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      throw std::invalid_argument("Constant cannot be string type");
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      const auto src1Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src1]);
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          break;
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          break;
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationNVV& instruction) {
  std::vector<MachineInstruction> instructions;
  const int src1 = instruction.getSource1();
  const std::string src2 = instruction.getSource2();
  const int src2Reg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(src2);
  const std::string dest = instruction.getDestination();
  const int destReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(dest);

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          throw std::invalid_argument("Constant cannot be string type");
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          const auto src2Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src2]);
          break;
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          throw std::invalid_argument("Constant cannot be string type");
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          const auto src2Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src2]);
          break;
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationNVN& instruction) {
  std::vector<MachineInstruction> instructions;
  const int src1 = instruction.getSource1();
  const std::string src2 = instruction.getSource2();
  const int src2Reg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(src2);
  const int dest = instruction.getDestination();

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          throw std::invalid_argument("Constant cannot be string type");
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          const auto src2Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src2]);
          break;
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          throw std::invalid_argument("Constant cannot be string type");
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          const auto src2Addr = MachineCodeGenerator::getBinaryAddress(variableAddresses_[currentScope][src2]);
          break;
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinaryOperation(const bblocks::BBBinaryOperationNNV& instruction) {
  std::vector<MachineInstruction> instructions;
  const int src1 = instruction.getSource1();
  const int src2 = instruction.getSource2();
  const std::string dest = instruction.getDestination();
  const int destReg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(dest);

  switch (instruction.getSource1Type()) {
    case bblocks::BBInstruction::SourceType::CONSTANT: {
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          break;
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          break;
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
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
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          break;
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
    case bblocks::BBInstruction::SourceType::REGISTER: {
      throw std::invalid_argument("Register cannot be number type");
    }
    case bblocks::BBInstruction::SourceType::MEMORY: {
      switch (instruction.getSource2Type()) {
        case bblocks::BBInstruction::SourceType::CONSTANT: {
          break;
        }
        case bblocks::BBInstruction::SourceType::REGISTER: {
          throw std::invalid_argument("Register cannot be number type");
        }
        case bblocks::BBInstruction::SourceType::MEMORY: {
          break;
        }
      }
    }
  }

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsConstConst(uint8_t src1, uint8_t src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op(const, const)" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsConstReg(uint8_t src1, int src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op(const, reg)" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsConstMem(uint8_t src1, uint16_t src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op(const, [addr])" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsConstMemImmReg(uint8_t src1, int src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op(const, [reg])" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsConstMemImmMem(uint8_t src1, uint16_t src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op(const, [[addr]])" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsRegReg(int src1, int src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op(reg, reg)" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsRegMem(int src1, uint16_t src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op(reg, [addr])" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsRegMemImmReg(int src1, int src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op(reg, [reg])" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsRegMemImmMem(int src1, uint16_t src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op(reg, [[addr]])" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsMemMem(uint16_t src1, uint16_t src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op([addr], [addr])" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsMemMemImmReg(uint16_t src1, int src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op([addr], [reg])" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsMemMemImmMem(uint16_t src1, uint16_t src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op([addr], [[addr]])" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsMemImmRegMemImmReg(uint16_t src1, int src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op([reg], [reg])" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsMemImmRegMemImmMem(uint16_t src1, uint16_t src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op([reg], [[addr]])" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpRhsMemImmMemMemImmMem(uint16_t src1, uint16_t src2, int dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "* := op([[addr]], [[addr]])" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpLhsReg(int dest, bblocks::BBBinaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "reg := op(*)" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpLhsMem(uint16_t dest, bblocks::BBBinaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[addr] := op(*)" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpLhsMemImmReg(int dest, bblocks::BBBinaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[reg] := op(reg)" << std::endl;
#endif
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBinOpLhsMemImmMem(uint16_t dest, bblocks::BBBinaryOperationEnum op) {
#ifdef MC_DEBUG
  std::cout << "[[addr]] := op(*)" << std::endl;
#endif
}

void MachineCodeGenerator::generateBinaryOperatorA(std::vector<MachineInstruction>& ins, bblocks::BBBinaryOperationEnum op, bool rev) {
#ifdef MC_DEBUG
  std::cout << "spec: regA := op(regA, regB)" << std::endl;
#endif

  switch (op) {
    case bblocks::BBBinaryOperationEnum::ADD: {
      ins.emplace_back(MachineInstruction::ADD_A);
      break;
    }
    case bblocks::BBBinaryOperationEnum::SUB: {
      if (rev) {
        ins.emplace_back(MachineInstruction::SUB_A_BA);
      }
      else {
        ins.emplace_back(MachineInstruction::SUB_A_AB);
      }
      break;
    }
    case bblocks::BBBinaryOperationEnum::MUL: {
      throw std::invalid_argument("Unimplemented");
    }
    case bblocks::BBBinaryOperationEnum::DIV: {
      throw std::invalid_argument("Unimplemented");
    }
    case bblocks::BBBinaryOperationEnum::MOD: {
      throw std::invalid_argument("Unimplemented");
    }
    case bblocks::BBBinaryOperationEnum::AND: {
      ins.emplace_back(MachineInstruction::AND_A);
      break;
    }
    case bblocks::BBBinaryOperationEnum::OR: {
      ins.emplace_back(MachineInstruction::OR_A);
      break;
    }
    case bblocks::BBBinaryOperationEnum::XOR: {
      ins.emplace_back(MachineInstruction::XOR_A);
      break;
    }
  }
}

void MachineCodeGenerator::generateBinaryOperatorB(std::vector<MachineInstruction>& ins, bblocks::BBBinaryOperationEnum op, bool rev) {
#ifdef MC_DEBUG
  std::cout << "spec: regB := op(regA, regB)" << std::endl;
#endif

  switch (op) {
    case bblocks::BBBinaryOperationEnum::ADD: {
      ins.emplace_back(MachineInstruction::ADD_B);
      break;
    }
    case bblocks::BBBinaryOperationEnum::SUB: {
      if (rev) {
        ins.emplace_back(MachineInstruction::SUB_B_BA);
      }
      else {
        ins.emplace_back(MachineInstruction::SUB_B_AB);
      }
      break;
    }
    case bblocks::BBBinaryOperationEnum::MUL: {
      throw std::invalid_argument("Unimplemented");
    }
    case bblocks::BBBinaryOperationEnum::DIV: {
      throw std::invalid_argument("Unimplemented");
    }
    case bblocks::BBBinaryOperationEnum::MOD: {
      throw std::invalid_argument("Unimplemented");
    }
    case bblocks::BBBinaryOperationEnum::AND: {
      ins.emplace_back(MachineInstruction::AND_B);
      break;
    }
    case bblocks::BBBinaryOperationEnum::OR: {
      ins.emplace_back(MachineInstruction::OR_B);
      break;
    }
    case bblocks::BBBinaryOperationEnum::XOR: {
      ins.emplace_back(MachineInstruction::XOR_B);
      break;
    }
  }
}

void MachineCodeGenerator::generateBinaryOperatorMem(std::vector<MachineInstruction>& ins, bblocks::BBBinaryOperationEnum op, uint16_t dest, bool rev) {
#ifdef MC_DEBUG
  std::cout << "spec: [dest] := op(regA, regB)" << std::endl;
#endif

  std::pair<std::optional<std::string>, std::string> destAddress = getBinaryAddress(dest);

  switch (op) {
    case bblocks::BBBinaryOperationEnum::ADD: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::ADD_MEM, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::ADD_MEM_ZP, std::vector<std::string>{destAddress.second});
      }
      break;
    }
    case bblocks::BBBinaryOperationEnum::SUB: {
      if (rev) {
        if (destAddress.first.has_value()) {
          ins.emplace_back(MachineInstruction::SUB_MEM_BA, std::vector<std::string>{destAddress.first.value(), destAddress.second});
        }
        else {
          ins.emplace_back(MachineInstruction::SUB_MEM_ZP_BA, std::vector<std::string>{destAddress.second});
        }
      }
      else {
        if (destAddress.first.has_value()) {
          ins.emplace_back(MachineInstruction::SUB_MEM_AB, std::vector<std::string>{destAddress.first.value(), destAddress.second});
        }
        else {
          ins.emplace_back(MachineInstruction::SUB_MEM_ZP_AB, std::vector<std::string>{destAddress.second});
        }
      }
      break;
    }
    case bblocks::BBBinaryOperationEnum::MUL: {
      throw std::invalid_argument("Unimplemented");
    }
    case bblocks::BBBinaryOperationEnum::DIV: {
      throw std::invalid_argument("Unimplemented");
    }
    case bblocks::BBBinaryOperationEnum::MOD: {
      throw std::invalid_argument("Unimplemented");
    }
    case bblocks::BBBinaryOperationEnum::AND: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::AND_MEM, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::AND_MEM_ZP, std::vector<std::string>{destAddress.second});
      }
      break;
    }
    case bblocks::BBBinaryOperationEnum::OR: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::OR_MEM, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::OR_MEM_ZP, std::vector<std::string>{destAddress.second});
      }
      break;
    }
    case bblocks::BBBinaryOperationEnum::XOR: {
      if (destAddress.first.has_value()) {
        ins.emplace_back(MachineInstruction::XOR_MEM, std::vector<std::string>{destAddress.first.value(), destAddress.second});
      }
      else {
        ins.emplace_back(MachineInstruction::XOR_MEM_ZP, std::vector<std::string>{destAddress.second});
      }
      break;
    }
  }
}

void MachineCodeGenerator::generateBinaryOperatorStc(std::vector<MachineInstruction>& ins, bblocks::BBBinaryOperationEnum op, bool rev) {
#ifdef MC_DEBUG
  std::cout << "spec: stack[top] := op(regA, regB)" << std::endl;
#endif

  switch (op) {
    case bblocks::BBBinaryOperationEnum::ADD: {
      ins.emplace_back(MachineInstruction::ADD_STC);
      break;
    }
    case bblocks::BBBinaryOperationEnum::SUB: {
      if (rev) {
        ins.emplace_back(MachineInstruction::SUB_STC_BA);
      }
      else {
        ins.emplace_back(MachineInstruction::SUB_STC_AB);
      }
      break;
    }
    case bblocks::BBBinaryOperationEnum::MUL: {
      throw std::invalid_argument("Unimplemented");
    }
    case bblocks::BBBinaryOperationEnum::DIV: {
      throw std::invalid_argument("Unimplemented");
    }
    case bblocks::BBBinaryOperationEnum::MOD: {
      throw std::invalid_argument("Unimplemented");
    }
    case bblocks::BBBinaryOperationEnum::AND: {
      ins.emplace_back(MachineInstruction::AND_STC);
      break;
    }
    case bblocks::BBBinaryOperationEnum::OR: {
      ins.emplace_back(MachineInstruction::OR_STC);
      break;
    }
    case bblocks::BBBinaryOperationEnum::XOR: {
      ins.emplace_back(MachineInstruction::XOR_STC);
      break;
    }
  }
}

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

std::vector<MachineInstruction> MachineCodeGenerator::generateBranchReg(int val, bblocks::BBBranchCondition condition, const std::string& trueLabel, const std::string& falseLabel) {
  std::vector<MachineInstruction> instructions;
  if (val == 1) {}
  else if (val == 2) {}

  appendBranchJumps(instructions, condition, trueLabel, falseLabel);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBranchMem(uint16_t val, bblocks::BBBranchCondition condition, const std::string& trueLabel, const std::string& falseLabel) {
  std::vector<MachineInstruction> instructions;

  appendBranchJumps(instructions, condition, trueLabel, falseLabel);

  return instructions;
}

std::vector<MachineInstruction> MachineCodeGenerator::generateBranchConst(uint8_t val, bblocks::BBBranchCondition condition, const std::string& trueLabel, const std::string& falseLabel) {
  std::vector<MachineInstruction> instructions;

  appendBranchJumps(instructions, condition, trueLabel, falseLabel);

  return instructions;
}

void MachineCodeGenerator::appendBranchJumps(std::vector<MachineInstruction>& instructions, bblocks::BBBranchCondition condition, const std::string& trueLabel, const std::string& falseLabel) {
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

bool MachineCodeGenerator::saveRegA(std::vector<MachineInstruction>& ins, const std::string& dest) {
  const int reg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(dest);

  if (reg == -1 || reg == 2) {
    return false;
  }

  //  if (register A is not active) {
  //    return false;
  //  }

  ins.emplace_back(MachineInstruction::PUSH_A);
  return true;
}

bool MachineCodeGenerator::saveRegB(std::vector<MachineInstruction>& ins, const std::string& dest) {
  const int reg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(dest);

  if (reg == -1 || reg == 1) {
    return false;
  }

  //  if (register B is not active) {
  //    return false;
  //  }

  ins.emplace_back(MachineInstruction::PUSH_B);
  return true;
}

bool MachineCodeGenerator::restoreRegA(std::vector<MachineInstruction>& ins, const std::string& dest) {
  const int reg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(dest);

  if (reg == -1 || reg == 2) {
    return false;
  }

  //  if (register A will be not active) {
  //    return false;
  //  }

  ins.emplace_back(MachineInstruction::POP_A);
  return true;
}

bool MachineCodeGenerator::restoreRegB(std::vector<MachineInstruction>& ins, const std::string& dest) {
  const int reg = regAllocators_.at(currentScope)->getAllocatedRegisters().at(dest);

  if (reg == -1 || reg == 2) {
    return false;
  }

  //  if (register B will be not active) {
  //    return false;
  //  }

  ins.emplace_back(MachineInstruction::POP_B);
  return true;
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