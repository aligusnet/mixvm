#include "machine_fixture.h"

namespace mix {
class MachineLoadsTestSuite: public MachineFixture {};

TEST_F(MachineLoadsTestSuite, lda) {
  set_memory_value(152, -73);
  machine.lda(make_cmd(cmd_lda, 152));

  EXPECT_EQ(-73, get_reg_a_value());
}

TEST_F(MachineLoadsTestSuite, ld1) {
  set_memory_value(152, 11);
  machine.ld1(make_cmd(cmd_ld1, 152));

  EXPECT_EQ(11, get_reg_i_value(1));
}

TEST_F(MachineLoadsTestSuite, ld2) {
  set_memory_value(152, 12);
  machine.ld2(make_cmd(cmd_ld2, 152));

  EXPECT_EQ(12, get_reg_i_value(2));
}

TEST_F(MachineLoadsTestSuite, ld3) {
  set_memory_value(152, 13);
  machine.ld3(make_cmd(cmd_ld3, 152));

  EXPECT_EQ(13, get_reg_i_value(3));
}

TEST_F(MachineLoadsTestSuite, ld4) {
  set_memory_value(152, 14);
  machine.ld4(make_cmd(cmd_ld4, 152));

  EXPECT_EQ(14, get_reg_i_value(4));
}

TEST_F(MachineLoadsTestSuite, ld5) {
  set_memory_value(152, 15);
  machine.ld5(make_cmd(cmd_ld5, 152));

  EXPECT_EQ(15, get_reg_i_value(5));
}

TEST_F(MachineLoadsTestSuite, ldx) {
  set_memory_value(152, -18);
  machine.ldx(make_cmd(cmd_ldx, 152));

  EXPECT_EQ(-18, get_reg_x_value());
}

TEST_F(MachineLoadsTestSuite, ldan) {
  set_memory_value(152, -73);
  machine.ldan(make_cmd(cmd_ldan, 152));

  EXPECT_EQ(73, get_reg_a_value());
}

TEST_F(MachineLoadsTestSuite, ld1n) {
  set_memory_value(152, 11);
  machine.ld1n(make_cmd(cmd_ld1n, 152));

  EXPECT_EQ(-11, get_reg_i_value(1));
}

TEST_F(MachineLoadsTestSuite, ld2n) {
  set_memory_value(152, 12);
  machine.ld2n(make_cmd(cmd_ld2n, 152));

  EXPECT_EQ(-12, get_reg_i_value(2));
}

TEST_F(MachineLoadsTestSuite, ld3n) {
  set_memory_value(152, 13);
  machine.ld3n(make_cmd(cmd_ld3n, 152));

  EXPECT_EQ(-13, get_reg_i_value(3));
}

TEST_F(MachineLoadsTestSuite, ld4n) {
  set_memory_value(152, 14);
  machine.ld4n(make_cmd(cmd_ld4n, 152));

  EXPECT_EQ(-14, get_reg_i_value(4));
}

TEST_F(MachineLoadsTestSuite, ld5n) {
  set_memory_value(152, 15);
  machine.ld5n(make_cmd(cmd_ld5n, 152));

  EXPECT_EQ(-15, get_reg_i_value(5));
}

TEST_F(MachineLoadsTestSuite, ldxn) {
  set_memory_value(152, 18);
  machine.ldxn(make_cmd(cmd_ldxn, 152));

  EXPECT_EQ(-18, get_reg_x_value());
}
}  // namespace mix

