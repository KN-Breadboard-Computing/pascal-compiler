#include "machine_code_generator.hpp"

namespace machine_code {
void MachineCodeGenerator::generate(const std::map<std::string, bblocks::BBControlFlowGraph>& cfg) {
  for (const auto& [functionName, controlFlowGraph] : cfg) {
    for (const auto& block : controlFlowGraph.getBasicBlocks()) {
      for (const auto& instruction : block.second.getInstructions()) {
        machineCode_[functionName].push_back(generate(instruction));
      }
    }
  }
}

void MachineCodeGenerator::saveMachineCode(const std::string& filename) {
  std::fstream file;
  file.open(filename, std::ios::out);

  for (const auto& [functionName, instructions] : machineCode_) {
    file << functionName << ":\n";
    for (const auto& instruction : instructions) {
      file << instruction.toString() << "\n";
    }
  }
}

void MachineCodeGenerator::saveAssembly(const std::string& filename) {
  std::fstream file;
  file.open(filename, std::ios::out);

  for (const auto& [functionName, instructions] : machineCode_) {
    file << functionName << ":\n";
    for (const auto& instruction : instructions) {
      file << instruction.toAssembly() << "\n";
    }
  }
}

MachineInstruction MachineCodeGenerator::generate(const std::unique_ptr<bblocks::BBInstruction>& instruction) {
  switch (instruction->getType()) {
    case bblocks::BBInstruction::Type::MOVE: {
    }
    case bblocks::BBInstruction::Type::UNARY_OPERATION: {
    }
    case bblocks::BBInstruction::Type::BINARY_OPERATION: {
    }
    case bblocks::BBInstruction::Type::BRANCH: {
    }
    case bblocks::BBInstruction::Type::CALL: {
    }
    case bblocks::BBInstruction::Type::RET: {
    }
    case bblocks::BBInstruction::Type::HALT: {
      return MachineInstruction(MachineInstruction::HALT);
    }
    case bblocks::BBInstruction::Type::PHI:
    case bblocks::BBInstruction::Type::UNSPECIFIED: {
      throw std::runtime_error("Unspecified instruction type");
    }
  }
}
}  // namespace machine_code