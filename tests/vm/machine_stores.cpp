#include "machine_fixture.h"

namespace mix {
class MachineStoresTestSuite : public MachineFixture {};

TEST_F(MachineStoresTestSuite, sta) {
  set_reg_a_value(-73);
  machine.sta(make_cmd(cmd_sta, 152));

  EXPECT_EQ(-73, get_memory_value(152));
}

TEST_F(MachineStoresTestSuite, st1) {
  set_reg_i_value(1, 11);
  machine.st1(make_cmd(cmd_st1, 152));

  EXPECT_EQ(11, get_memory_value(152));
}

TEST_F(MachineStoresTestSuite, st2) {
  set_reg_i_value(2, 12);
  machine.st2(make_cmd(cmd_st2, 152));

  EXPECT_EQ(12, get_memory_value(152));
}

TEST_F(MachineStoresTestSuite, st3) {
  set_reg_i_value(3, 13);
  machine.st3(make_cmd(cmd_st3, 152));

  EXPECT_EQ(13, get_memory_value(152));
}

TEST_F(MachineStoresTestSuite, st4) {
  set_reg_i_value(4, 14);
  machine.st4(make_cmd(cmd_st4, 152));

  EXPECT_EQ(14, get_memory_value(152));
}

TEST_F(MachineStoresTestSuite, st5) {
  set_reg_i_value(5, 15);
  machine.st5(make_cmd(cmd_st5, 152));

  EXPECT_EQ(15, get_memory_value(152));
}

TEST_F(MachineStoresTestSuite, st6) {
  set_reg_i_value(6, 16);
  machine.st6(make_cmd(cmd_st6, 152));

  EXPECT_EQ(16, get_memory_value(152));
}

TEST_F(MachineStoresTestSuite, stx) {
  set_reg_x_value(-18);
  machine.stx(make_cmd(cmd_stx, 152));

  EXPECT_EQ(-18, get_memory_value(152));
}

TEST_F(MachineStoresTestSuite, stj) {
  set_next_instruction_address(99);
  machine.stj(make_cmd(cmd_stj, 152));

  EXPECT_EQ(99, get_memory_value(152));
}

TEST_F(MachineStoresTestSuite, stz) {
  set_memory_value(152, -75);
  machine.stz(make_cmd(cmd_stz, 152));

  EXPECT_EQ(0, get_memory_value(152));
}

} // namespace mix
