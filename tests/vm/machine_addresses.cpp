#include "machine_fixture.h"

namespace mix {

class MachineAddressesTestSuite : public MachineFixture {};

TEST_F(MachineAddressesTestSuite, enta) {
  machine.enta(make_instruction(cmd_enta, 70));

  EXPECT_EQ(70, get_reg_a_value());
}

TEST_F(MachineAddressesTestSuite, ent1) {
  machine.ent1(make_instruction(cmd_ent1, 71));

  EXPECT_EQ(71, get_reg_i_value(1));
}

TEST_F(MachineAddressesTestSuite, ent2) {
  machine.ent2(make_instruction(cmd_ent2, 72));

  EXPECT_EQ(72, get_reg_i_value(2));
}

TEST_F(MachineAddressesTestSuite, ent3) {
  machine.ent3(make_instruction(cmd_ent3, 73));

  EXPECT_EQ(73, get_reg_i_value(3));
}

TEST_F(MachineAddressesTestSuite, ent4) {
  machine.ent4(make_instruction(cmd_ent4, 74));

  EXPECT_EQ(74, get_reg_i_value(4));
}

TEST_F(MachineAddressesTestSuite, ent5) {
  machine.ent5(make_instruction(cmd_ent5, 75));

  EXPECT_EQ(75, get_reg_i_value(5));
}

TEST_F(MachineAddressesTestSuite, ent6) {
  machine.ent6(make_instruction(cmd_ent6, 76));

  EXPECT_EQ(76, get_reg_i_value(6));
}

TEST_F(MachineAddressesTestSuite, entx) {
  machine.entx(make_instruction(cmd_entx, 77));

  EXPECT_EQ(77, get_reg_x_value());
}

TEST_F(MachineAddressesTestSuite, enna) {
  machine.enna(make_instruction(cmd_enna, 70));

  EXPECT_EQ(-70, get_reg_a_value());
}

TEST_F(MachineAddressesTestSuite, enn1) {
  machine.enn1(make_instruction(cmd_enn1, 71));

  EXPECT_EQ(-71, get_reg_i_value(1));
}

TEST_F(MachineAddressesTestSuite, enn2) {
  machine.enn2(make_instruction(cmd_enn2, 72));

  EXPECT_EQ(-72, get_reg_i_value(2));
}

TEST_F(MachineAddressesTestSuite, enn3) {
  machine.enn3(make_instruction(cmd_enn3, 73));

  EXPECT_EQ(-73, get_reg_i_value(3));
}

TEST_F(MachineAddressesTestSuite, enn4) {
  machine.enn4(make_instruction(cmd_enn4, 74));

  EXPECT_EQ(-74, get_reg_i_value(4));
}

TEST_F(MachineAddressesTestSuite, enn5) {
  machine.enn5(make_instruction(cmd_enn5, 75));

  EXPECT_EQ(-75, get_reg_i_value(5));
}

TEST_F(MachineAddressesTestSuite, enn6) {
  machine.enn6(make_instruction(cmd_enn6, 76));

  EXPECT_EQ(-76, get_reg_i_value(6));
}

TEST_F(MachineAddressesTestSuite, ennx) {
  machine.ennx(make_instruction(cmd_ennx, 77));

  EXPECT_EQ(-77, get_reg_x_value());
}

} // namespace mix
