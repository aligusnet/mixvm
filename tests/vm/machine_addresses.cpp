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

TEST_F(MachineAddressesTestSuite, inca) {
  set_reg_a_value(100);
  machine.inca(make_instruction(cmd_inca));

  EXPECT_EQ(101, get_reg_a_value());
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, inca_overflowed) {
  set_reg_a_value(big_register::VALUES_IN_WORD - 1);
  machine.inca(make_instruction(cmd_inca));

  EXPECT_EQ(0, get_reg_a_value());
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, inc1) {
  set_reg_i_value(1, 100);
  machine.inc1(make_instruction(cmd_inc1));

  EXPECT_EQ(101, get_reg_i_value(1));
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, inc1_overflowed) {
  set_reg_i_value(1, small_register::VALUES_IN_WORD - 1);
  machine.inc1(make_instruction(cmd_inc1));

  EXPECT_EQ(0, get_reg_i_value(1));
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, inc2) {
  set_reg_i_value(2, 100);
  machine.inc2(make_instruction(cmd_inc2));

  EXPECT_EQ(101, get_reg_i_value(2));
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, inc2_overflowed) {
  set_reg_i_value(2, small_register::VALUES_IN_WORD - 1);
  machine.inc2(make_instruction(cmd_inc2));

  EXPECT_EQ(0, get_reg_i_value(2));
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, inc3) {
  set_reg_i_value(3, 100);
  machine.inc3(make_instruction(cmd_inc3));

  EXPECT_EQ(101, get_reg_i_value(3));
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, inc3_overflowed) {
  set_reg_i_value(3, small_register::VALUES_IN_WORD - 1);
  machine.inc3(make_instruction(cmd_inc3));

  EXPECT_EQ(0, get_reg_i_value(3));
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, inc4) {
  set_reg_i_value(4, 100);
  machine.inc4(make_instruction(cmd_inc4));

  EXPECT_EQ(101, get_reg_i_value(4));
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, inc4_overflowed) {
  set_reg_i_value(4, small_register::VALUES_IN_WORD - 1);
  machine.inc4(make_instruction(cmd_inc4));

  EXPECT_EQ(0, get_reg_i_value(4));
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, inc5) {
  set_reg_i_value(5, 100);
  machine.inc5(make_instruction(cmd_inc5));

  EXPECT_EQ(101, get_reg_i_value(5));
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, inc5_overflowed) {
  set_reg_i_value(5, small_register::VALUES_IN_WORD - 1);
  machine.inc5(make_instruction(cmd_inc5));

  EXPECT_EQ(0, get_reg_i_value(5));
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, inc6) {
  set_reg_i_value(6, 100);
  machine.inc6(make_instruction(cmd_inc6));

  EXPECT_EQ(101, get_reg_i_value(6));
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, inc6_overflowed) {
  set_reg_i_value(6, small_register::VALUES_IN_WORD - 1);
  machine.inc6(make_instruction(cmd_inc6));

  EXPECT_EQ(0, get_reg_i_value(6));
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, incx) {
  set_reg_x_value(100);
  machine.incx(make_instruction(cmd_incx));

  EXPECT_EQ(101, get_reg_x_value());
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, incx_overflowed) {
  set_reg_x_value(big_register::VALUES_IN_WORD - 1);
  machine.incx(make_instruction(cmd_incx));

  EXPECT_EQ(0, get_reg_x_value());
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, deca) {
  set_reg_a_value(-100);
  machine.deca(make_instruction(cmd_deca));

  EXPECT_EQ(-101, get_reg_a_value());
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, deca_oveflowed) {
  set_reg_a_value(-1 * big_register::VALUES_IN_WORD + 1);
  machine.deca(make_instruction(cmd_deca));

  EXPECT_EQ(0, get_reg_a_value());
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, dec1) {
  set_reg_i_value(1, -100);
  machine.dec1(make_instruction(cmd_dec1));

  EXPECT_EQ(-101, get_reg_i_value(1));
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, dec1_overflowed) {
  set_reg_i_value(1, -1 * small_register::VALUES_IN_WORD + 1);
  machine.dec1(make_instruction(cmd_dec1));

  EXPECT_EQ(0, get_reg_i_value(1));
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, dec2) {
  set_reg_i_value(2, -100);
  machine.dec2(make_instruction(cmd_dec2));

  EXPECT_EQ(-101, get_reg_i_value(2));
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, dec2_overflowed) {
  set_reg_i_value(2, -1 * small_register::VALUES_IN_WORD + 1);
  machine.dec2(make_instruction(cmd_dec2));

  EXPECT_EQ(0, get_reg_i_value(2));
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, dec3) {
  set_reg_i_value(3, -100);
  machine.dec3(make_instruction(cmd_dec3));

  EXPECT_EQ(-101, get_reg_i_value(3));
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, dec3_overflowed) {
  set_reg_i_value(3, -1 * small_register::VALUES_IN_WORD + 1);
  machine.dec3(make_instruction(cmd_dec3));

  EXPECT_EQ(0, get_reg_i_value(3));
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, dec4) {
  set_reg_i_value(4, -100);
  machine.dec4(make_instruction(cmd_dec4));

  EXPECT_EQ(-101, get_reg_i_value(4));
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, dec4_overflowed) {
  set_reg_i_value(4, -1 * small_register::VALUES_IN_WORD + 1);
  machine.dec4(make_instruction(cmd_dec4));

  EXPECT_EQ(0, get_reg_i_value(4));
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, dec5) {
  set_reg_i_value(5, -100);
  machine.dec5(make_instruction(cmd_dec5));

  EXPECT_EQ(-101, get_reg_i_value(5));
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, dec5_overflowed) {
  set_reg_i_value(5, -1 * small_register::VALUES_IN_WORD + 1);
  machine.dec5(make_instruction(cmd_dec5));

  EXPECT_EQ(0, get_reg_i_value(5));
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, dec6) {
  set_reg_i_value(6, -100);
  machine.dec6(make_instruction(cmd_dec6));

  EXPECT_EQ(-101, get_reg_i_value(6));
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, dec6_overflowed) {
  set_reg_i_value(6, -1 * small_register::VALUES_IN_WORD + 1);
  machine.dec6(make_instruction(cmd_dec6));

  EXPECT_EQ(0, get_reg_i_value(6));
  EXPECT_TRUE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, decx) {
  set_reg_x_value(-100);
  machine.decx(make_instruction(cmd_decx));

  EXPECT_EQ(-101, get_reg_x_value());
  EXPECT_FALSE(machine.overflow);
}

TEST_F(MachineAddressesTestSuite, decx_oveflowed) {
  set_reg_x_value(-1 * big_register::VALUES_IN_WORD + 1);
  machine.decx(make_instruction(cmd_decx));

  EXPECT_EQ(0, get_reg_x_value());
  EXPECT_TRUE(machine.overflow);
}

} // namespace mix
