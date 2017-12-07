#ifndef TESTS_MACHINE_FIXTURE
#define TESTS_MACHINE_FIXTURE

#include <gtest/gtest.h>

#include <vm/mix_machine.h>

namespace mix {

class MachineFixture : public ::testing::Test {
protected:
  Machine machine;
  bool isOverflowed;

  Instruction make_instruction(byte cmd, short addr = 0, FieldSpecification f = FieldSpecification::DEFAULT);

  void set_next_instruction_address(int address);
  int get_next_instruction_address() const;
  bool is_next_instruction_address_unchanged() const;

  void set_memory_value(int address, int value);
  int get_memory_value(int address) const;

  void set_reg_a_value(int value);
  int get_reg_a_value() const;

  void set_reg_x_value(int value);
  int get_reg_x_value() const;

  void set_reg_i_value(int index, int value);
  int get_reg_i_value(int index) const;

  void expect_eq(const Word &expected, const Word &actual) const;
};
} // namespace mix

#endif // TESTS_MACHINE_FIXTURE
