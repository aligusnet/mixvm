#include "machine_fixture.h"

namespace mix {

class MachineTestSuite : public MachineFixture {};

TEST_F(MachineTestSuite, start_state) {
  EXPECT_EQ(0, get_reg_a_value());
  EXPECT_EQ(0, get_reg_x_value());
  EXPECT_EQ(0, get_reg_i_value(1));
  EXPECT_EQ(0, get_reg_i_value(2));
  EXPECT_EQ(0, get_reg_i_value(3));
  EXPECT_EQ(0, get_reg_i_value(4));
  EXPECT_EQ(0, get_reg_i_value(5));
}

TEST_F(MachineTestSuite, hlt) {
  machine.halt = false;
  machine.hlt(make_cmd(cmd_hlt));
  EXPECT_TRUE(machine.halt);
}

} // namespace mix
