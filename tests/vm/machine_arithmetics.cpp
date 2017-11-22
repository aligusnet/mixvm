#include "machine_fixture.h"

#include <vm/mix_word.h>

namespace mix {
class MachineArithmeticsTestSuite : public MachineFixture {};

TEST_F(MachineArithmeticsTestSuite, add) {
  set_reg_a_value(-7);
  set_memory_value(152, 5);

  machine.add(make_cmd(cmd_add, 152));

  EXPECT_EQ(-2, get_reg_a_value());
  EXPECT_EQ(5, get_memory_value(152));
}

TEST_F(MachineArithmeticsTestSuite, sub) {
  set_reg_a_value(-7);
  set_memory_value(152, 5);

  machine.sub(make_cmd(cmd_sub, 152));

  EXPECT_EQ(-12, get_reg_a_value());
  EXPECT_EQ(5, get_memory_value(152));
}

TEST_F(MachineArithmeticsTestSuite, mul) {
  set_reg_a_value(-7);
  set_memory_value(152, 5);
  machine.mul(make_cmd(cmd_mul, 152));

  EXPECT_EQ(0, get_reg_a_value());
  EXPECT_EQ(-35, get_reg_x_value());
  EXPECT_EQ(5, get_memory_value(152));
}

TEST_F(MachineArithmeticsTestSuite, mul_2_big_numbers) {
  set_reg_a_value(-73193);
  set_memory_value(152, 53781);
  machine.mul(make_cmd(cmd_mul, 152));

  EXPECT_EQ(-73193l * 53781l, get_long_value(machine.reg_a, machine.reg_x));
  EXPECT_EQ(53781, get_memory_value(152));
}

TEST_F(MachineArithmeticsTestSuite, div) {
  set_long_value(-73193l * 53781l - 11, machine.reg_a, machine.reg_x, isOverflowed);
  set_memory_value(152, 53781);

  machine.div(make_cmd(cmd_div, 152));

  EXPECT_EQ(-73193, get_reg_a_value());
  EXPECT_EQ(-11, get_reg_x_value());
}

} // namespace mix
