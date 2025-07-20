#ifndef EMULATOR_CONNECTOR_HPP
#define EMULATOR_CONNECTOR_HPP

#include <memory>
#include <string_view>
#include <vector>

#include "../../emulator/src/emulator.h"

constexpr std::string_view instruction_set_path = "../computer/config/instructions.json";

class EmulatorConnector {
 public:
  EmulatorConnector() {
    emulator_ = std::make_unique<Emulator>();
    init_emulator(emulator_.get());

    config_ = std::make_unique<Config>();
    load_config(config_.get(), instruction_set_path.data());
  }

  EmulatorConnector(const EmulatorConnector&) = delete;
  EmulatorConnector(EmulatorConnector&&) = default;

  EmulatorConnector& operator=(const EmulatorConnector&) = delete;
  EmulatorConnector& operator=(EmulatorConnector&&) = default;

  void setRegA(uint8_t value) { emulator_->a_register = value; }
  void setRegB(uint8_t value) { emulator_->b_register = value; }
  void clearMemory() { std::fill(std::begin(emulator_->memory), std::end(emulator_->memory), 0); }
  void setMemory(uint16_t address, uint8_t value) { emulator_->memory[address] = value; }
  void setTmp(uint16_t value) { emulator_->tmp_register_16 = value; }
  void setTmpHigh(uint8_t value) { emulator_->tmp_register_8[1] = value; }
  void setTmpLow(uint8_t value) { emulator_->tmp_register_8[0] = value; }
  void setPc(uint16_t value) { emulator_->program_counter = value; }
  void setStc(uint16_t value) { emulator_->stack_pointer = value; }
  void setFlags(uint8_t value) { emulator_->flag_register = value; }
  void setIntData(uint8_t value) { emulator_->interrupt_data = value; }
  void setIntSignals(uint8_t value) { emulator_->interrupt_signals = value; }
  void setHalted(bool value) { emulator_->is_halted = value; }
  void setClockCyclesCounter(uint32_t value) { emulator_->clock_cycles_counter = value; }
  void setInstructionCounter(uint32_t value) { emulator_->instruction_counter = value; }

  uint8_t getRegA() const { return emulator_->a_register; }
  uint8_t getRegB() const { return emulator_->b_register; }
  uint8_t getMemory(uint16_t address) const { return emulator_->memory[address]; }
  std::vector<uint8_t> getMemorySnapshot() const { return std::vector<uint8_t>(std::begin(emulator_->memory), std::end(emulator_->memory)); }
  uint8_t getStack(uint16_t address) const { return emulator_->stack[address]; }
  std::vector<uint8_t> getStackSnapshot() const { return std::vector<uint8_t>(std::begin(emulator_->stack), std::end(emulator_->stack)); }
  uint16_t getTmp() const { return emulator_->tmp_register_16; }
  uint8_t getTmpHigh() const { return emulator_->tmp_register_8[1]; }
  uint8_t getTmpLow() const { return emulator_->tmp_register_8[0]; }
  uint16_t getPc() const { return emulator_->program_counter; }
  uint16_t getStc() const { return emulator_->stack_pointer; }
  uint8_t getFlags() const { return emulator_->flag_register; }
  uint8_t getIntData() const { return emulator_->interrupt_data; }
  uint8_t getIntSignals() const { return emulator_->interrupt_signals; }
  bool isHalted() const { return emulator_->is_halted; }
  uint32_t getClockCyclesCounter() const { return emulator_->clock_cycles_counter; }
  uint32_t getInstructionCounter() const { return emulator_->instruction_counter; }

  void loadRom(const std::vector<uint8_t>& rom) {
    for (std::size_t i = 0; i < rom.size(); ++i) {
      emulator_->memory[i] = rom[i];
    }
  }

  void runSingleInstruction() {
    if (run_next_emulator_instruction(emulator_.get(), config_.get()) != 0) {
      throw std::runtime_error("Error executing instruction");
    }
  }

  void runInstructions(uint16_t count) {
    for (uint16_t i = 0; i < count; ++i) {
      runSingleInstruction();
    }
  }

  void run(const std::vector<uint8_t>& rom) {
    for (std::size_t i = 0; i < rom.size(); ++i) {
      emulator_->memory[i] = rom[i];
    }

    while (emulator_->is_halted == 0 && emulator_->program_counter < rom.size()) {
      if (run_next_emulator_instruction(emulator_.get(), config_.get()) != 0) {
        throw std::runtime_error("Error executing instruction");
      }
    }
  }

  ~EmulatorConnector() = default;

 private:
  std::unique_ptr<Emulator> emulator_;
  std::unique_ptr<Config> config_;
};

#endif  // EMULATOR_CONNECTOR_HPP