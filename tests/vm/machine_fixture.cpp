#include "machine_fixture.h"

#include <vm/mix_word.h>
#include <vm/mix_small_word.h>

namespace mix {

void MachineFixture::set_next_instruction_address(int address) {
  set_value(address, machine.reg_j, isOverflowed);
}

int MachineFixture::get_next_instruction_address() const {
  return get_value(machine.reg_j);
}

bool MachineFixture::is_next_instruction_address_unchanged() const {
  const int NEXT_INSTRUCTION_DEFAULT_ADDRESS = 0;
  return get_next_instruction_address() == NEXT_INSTRUCTION_DEFAULT_ADDRESS;
}

void MachineFixture::set_memory_value(int address, int value) {
  set_value(value, machine.memory[address], isOverflowed);
}

int MachineFixture::get_memory_value(int address) const {
  return get_value(machine.memory[address]);
}

void MachineFixture::set_reg_a_value(int value) {
  set_value(value, machine.reg_a, isOverflowed);
}

int MachineFixture::get_reg_a_value() const {
  return get_value(machine.reg_a);
}

void MachineFixture::set_reg_x_value(int value) {
  set_value(value, machine.reg_x, isOverflowed);
}

int MachineFixture::get_reg_x_value() const {
  return get_value(machine.reg_x);
}

void MachineFixture::set_reg_i_value(int index, int value) {
  set_value(value, machine.reg_i[index-1], isOverflowed);
}

int MachineFixture::get_reg_i_value(int index) const {
  return get_value(machine.reg_i[index-1]);
}
}  // namespace mix
