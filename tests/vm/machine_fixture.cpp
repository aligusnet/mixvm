#include "machine_fixture.h"

#include <vm/mix_small_word.h>
#include <vm/mix_word.h>

namespace mix {

Instruction MachineFixture::make_instruction(byte cmd, short addr, FieldSpecification f) {
  return Instruction(Word::make_as_instruction(cmd, addr, 0, f));
}

void MachineFixture::set_next_instruction_address(int address) {
  isOverflowed = machine.reg_j.set_value(address);
}

int MachineFixture::get_next_instruction_address() const {
  return machine.reg_j.get_value();
}

bool MachineFixture::is_next_instruction_address_unchanged() const {
  const int NEXT_INSTRUCTION_DEFAULT_ADDRESS = 0;
  return get_next_instruction_address() == NEXT_INSTRUCTION_DEFAULT_ADDRESS;
}

void MachineFixture::set_memory_value(int address, int value) {
  isOverflowed = machine.memory[address].set_value(value);
}

int MachineFixture::get_memory_value(int address) const {
  return machine.memory[address].get_value();
}

void MachineFixture::set_reg_a_value(int value) {
  isOverflowed = machine.reg_a.set_value(value);
}

int MachineFixture::get_reg_a_value() const {
  return machine.reg_a.get_value();
}

void MachineFixture::set_reg_x_value(int value) {
  isOverflowed = machine.reg_x.set_value(value);
}

int MachineFixture::get_reg_x_value() const {
  return machine.reg_x.get_value();
}

void MachineFixture::set_reg_i_value(int index, int value) {
  isOverflowed = machine.reg_i[index - 1].set_value(value);
}

int MachineFixture::get_reg_i_value(int index) const {
  return machine.reg_i[index - 1].get_value();
}

void MachineFixture::expect_eq(const Word &expected, const Word &actual) const {
  EXPECT_EQ(expected, actual);
}
} // namespace mix
