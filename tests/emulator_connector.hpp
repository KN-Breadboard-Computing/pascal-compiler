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

  void loadRom(const std::vector<uint8_t>& rom) {
    if (rom.size() > emulator_->memory.size()) {
      throw std::runtime_error("ROM size exceeds memory size");
    }

    for (std::size_t i = 0; i < rom.size(); ++i) {
      emulator_->memory[i] = rom[i];
    }
  }

  void runSingleInstruction() {
    if (run_next_emulator_instruction(emulator_.get(), config_.get()) != 0) {
      throw std::runtime_error("Error executing instruction");
    }
  }

  void run(const std::vector<uint8_t>& rom) {
    for (std::size_t i = 0; i < rom.size(); ++i) {
      emulator_->memory[i] = rom[i];
    }

    while (emulator_->is_halted == 0 && emulator_->program_counter < rom.size()) {
      if (run_next_emulator_instruction(emulator_.get(), config_.get()) != 0) {
        break;
      }
    }
  }

  bool assertRegA(uint8_t expected) { return emulator_->a_register == expected; }
  bool assertRegB(uint8_t expected) { return emulator_->b_register == expected; }
  bool assertMemory(uint16_t address, uint8_t expected) { return emulator_->memory[address] == expected; }
  bool assertTmp(uint16_t expected) { return emulator_->tmp_register_16 == expected; }
  bool assertTmpHigh(uint8_t expected) { return emulator_->tmp_register_8[1] == expected; }
  bool assertTmpLow(uint8_t expected) { return emulator_->tmp_register_8[0] == expected; }
  bool assertPc(uint16_t expected) { return emulator_->program_counter == expected; }
  bool assertStc(uint16_t expected) { return emulator_->stack_pointer == expected; }
  bool assertFlags(uint8_t expected) { return emulator_->flag_register == expected; }
  bool assertIntData(uint8_t expected) { return emulator_->interrupt_data == expected; }
  bool assertIntSignals(uint8_t expected) { return emulator_->interrupt_signals == expected; }
  bool assertHalted(bool expected) { return emulator_->is_halted == expected; }
  bool assertClockCyclesCounter(uint32_t expected) { return emulator_->clock_cycles_counter == expected; }
  bool assertInstructionCounter(uint32_t expected) { return emulator_->instruction_counter == expected; }

  ~EmulatorConnector() = default;

 private:
  std::unique_ptr<Emulator> emulator_;
  std::unique_ptr<Config> config_;
};

#endif  // EMULATOR_CONNECTOR_HPP