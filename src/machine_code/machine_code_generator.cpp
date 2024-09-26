#include "machine_code_generator.hpp"

#include "../bblocks/instructions/bb_binary_operation.hpp"
#include "../bblocks/instructions/bb_branch.hpp"
#include "../bblocks/instructions/bb_call.hpp"
#include "../bblocks/instructions/bb_halt.hpp"
#include "../bblocks/instructions/bb_move.hpp"
#include "../bblocks/instructions/bb_phi.hpp"
#include "../bblocks/instructions/bb_ret.hpp"
#include "../bblocks/instructions/bb_unary_operation.hpp"

namespace machine_code {
void MachineCodeGenerator::generate(const std::map<std::string, bblocks::BBControlFlowGraph>& cfg) {
  for (const auto& [functionName, controlFlowGraph] : cfg) {
    // enumerate labels of blocks
    enumerateBlockLabels(functionName, controlFlowGraph);

    // calculate live ranges
    liveRanges_.insert({functionName, LiveRangesGenerator{}});
    liveRanges_[functionName].generate(controlFlowGraph, blockBounds_[functionName]);
    liveRanges_[functionName].saveLiveRanges("live_ranges_" + functionName + ".txt");

    // generate machine code
    machineCode_.insert({functionName, std::vector<MachineInstruction>{}});
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

MachineInstruction MachineCodeGenerator::generate(const std::unique_ptr<bblocks::BBInstruction>& instruction) {
  const std::vector<bblocks::BBInstruction::TemplateArgumentType>& templateArguments = instruction->getTemplateTypes();
  switch (instruction->getType()) {
    case bblocks::BBInstruction::Type::MOVE: {
      if (templateArguments[0] == bblocks::BBInstruction::TemplateArgumentType::STRING) {
        if (templateArguments[1] == bblocks::BBInstruction::TemplateArgumentType::STRING) {
          bblocks::BBMoveVV* move = dynamic_cast<bblocks::BBMoveVV*>(instruction.get());
          std::string src = move->getSource();
          std::string dest = move->getDestination();
        }
        else {  // templateArguments[1] == bblocks::BBInstruction::TemplateArgumentType::NUMBER
          bblocks::BBMoveVN* move = dynamic_cast<bblocks::BBMoveVN*>(instruction.get());
          std::string src = move->getSource();
          int dest = move->getDestination();
        }
      }
      else {  // templateArguments[0] == bblocks::BBInstruction::TemplateArgumentType::NUMBER
        if (templateArguments[1] == bblocks::BBInstruction::TemplateArgumentType::STRING) {
          bblocks::BBMoveNV* move = dynamic_cast<bblocks::BBMoveNV*>(instruction.get());
          int src = move->getSource();
          std::string dest = move->getDestination();
        }
        else {  // templateArguments[1] == bblocks::BBInstruction::TemplateArgumentType::NUMBER
          bblocks::BBMoveNN* move = dynamic_cast<bblocks::BBMoveNN*>(instruction.get());
          int src = move->getSource();
          int dest = move->getDestination();
        }
      }
      return MachineInstruction(MachineInstruction::NOP);
    }
    case bblocks::BBInstruction::Type::UNARY_OPERATION: {
      if (templateArguments[0] == bblocks::BBInstruction::TemplateArgumentType::STRING) {
        if (templateArguments[1] == bblocks::BBInstruction::TemplateArgumentType::STRING) {}
        else {  // templateArguments[1] == bblocks::BBInstruction::TemplateArgumentType::NUMBER
        }
      }
      else {  // templateArguments[0] == bblocks::BBInstruction::TemplateArgumentType::NUMBER
        if (templateArguments[1] == bblocks::BBInstruction::TemplateArgumentType::STRING) {}
        else {  // templateArguments[1] == bblocks::BBInstruction::TemplateArgumentType::NUMBER
        }
      }
      return MachineInstruction(MachineInstruction::NOP);
    }
    case bblocks::BBInstruction::Type::BINARY_OPERATION: {
      return MachineInstruction(MachineInstruction::NOP);
    }
    case bblocks::BBInstruction::Type::BRANCH: {
      if (templateArguments[0] == bblocks::BBInstruction::TemplateArgumentType::STRING) {}
      else {  // templateArguments[0] == bblocks::BBInstruction::TemplateArgumentType::NUMBER
      }
      return MachineInstruction(MachineInstruction::NOP);
    }
    case bblocks::BBInstruction::Type::CALL: {
      bblocks::BBCall* call = dynamic_cast<bblocks::BBCall*>(instruction.get());
      return MachineInstruction(MachineInstruction::JMP_REL_FUN);
    }
    case bblocks::BBInstruction::Type::RET: {
      bblocks::BBRet* ret = dynamic_cast<bblocks::BBRet*>(instruction.get());
      return MachineInstruction(MachineInstruction::JMP_REL_RET);
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

std::string MachineCodeGenerator::getBinary(int number) {
  std::bitset<8> binary(number);
  return binary.to_string();
}

}  // namespace machine_code