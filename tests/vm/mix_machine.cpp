#include <gtest/gtest.h>

#include <vm/mix_machine.h>
#include <vm/mix_word.h>
#include <vm/mix_small_word.h>

namespace mix {

class MixMachineTestSuite: public ::testing::Test {
protected:
  Machine machine;
};

TEST_F(MixMachineTestSuite, start_state) {
  EXPECT_EQ(0, get_value(machine.reg_a));
  EXPECT_EQ(0, get_value(machine.reg_x));
  EXPECT_EQ(0, get_value(machine.reg_i[0]));
  EXPECT_EQ(0, get_value(machine.reg_i[1]));
  EXPECT_EQ(0, get_value(machine.reg_i[2]));
  EXPECT_EQ(0, get_value(machine.reg_i[3]));
  EXPECT_EQ(0, get_value(machine.reg_i[4]));
}

TEST_F(MixMachineTestSuite, add) {
  bool isOverflowed;
  set_value(-7, machine.reg_a, isOverflowed);
  set_value(5, machine.memory[152], isOverflowed);
  machine.add(make_cmd(cmd_add, 152));

  EXPECT_EQ(-2, get_value(machine.reg_a));
  EXPECT_EQ(5, get_value(machine.memory[152]));
}

TEST_F(MixMachineTestSuite, sub) {
  bool isOverflowed;
  set_value(-7, machine.reg_a, isOverflowed);
  set_value(5, machine.memory[152], isOverflowed);
  machine.sub(make_cmd(cmd_sub, 152));

  EXPECT_EQ(-12, get_value(machine.reg_a));
  EXPECT_EQ(5, get_value(machine.memory[152]));
}

TEST_F(MixMachineTestSuite, mul) {
  bool isOverflowed;
  set_value(-7, machine.reg_a, isOverflowed);
  set_value(5, machine.memory[152], isOverflowed);
  machine.mul(make_cmd(cmd_mul, 152));

  EXPECT_EQ(0, get_value(machine.reg_a));
  EXPECT_EQ(-35, get_value(machine.reg_x));
  EXPECT_EQ(5, get_value(machine.memory[152]));
}

TEST_F(MixMachineTestSuite, mul_2_big_numbers) {
  bool isOverflowed;
  set_value(-73193, machine.reg_a, isOverflowed);
  set_value(53781, machine.memory[152], isOverflowed);
  machine.mul(make_cmd(cmd_mul, 152));

  EXPECT_EQ(-73193l*53781l, get_long_value(machine.reg_a, machine.reg_x));
  EXPECT_EQ(53781, get_value(machine.memory[152]));
}

TEST_F(MixMachineTestSuite, div) {
  bool isOverflowed;
  set_long_value(-73193l*53781l - 11, machine.reg_a, machine.reg_x, isOverflowed);
  set_value(53781, machine.memory[152], isOverflowed);

  machine.div(make_cmd(cmd_div, 152));

  EXPECT_EQ(-73193, get_value(machine.reg_a));
  EXPECT_EQ(-11, get_value(machine.reg_x));
}

TEST_F(MixMachineTestSuite, hlt) {
  machine.halt = false;
  machine.hlt(make_cmd(cmd_hlt));
  EXPECT_TRUE(machine.halt);
}

TEST_F(MixMachineTestSuite, lda) {
  bool isOverflowed;
  set_value(-73, machine.memory[152], isOverflowed);
  machine.lda(make_cmd(cmd_lda, 152));

  EXPECT_EQ(-73, get_value(machine.reg_a));
}

TEST_F(MixMachineTestSuite, ld1) {
  bool isOverflowed;
  set_value(11, machine.memory[152], isOverflowed);
  machine.ld1(make_cmd(cmd_ld1, 152));

  EXPECT_EQ(11, get_value(machine.reg_i[0]));
}

TEST_F(MixMachineTestSuite, ld2) {
  bool isOverflowed;
  set_value(12, machine.memory[152], isOverflowed);
  machine.ld2(make_cmd(cmd_ld1, 152));

  EXPECT_EQ(12, get_value(machine.reg_i[1]));
}

TEST_F(MixMachineTestSuite, ld3) {
  bool isOverflowed;
  set_value(13, machine.memory[152], isOverflowed);
  machine.ld3(make_cmd(cmd_ld1, 152));

  EXPECT_EQ(13, get_value(machine.reg_i[2]));
}

TEST_F(MixMachineTestSuite, ld4) {
  bool isOverflowed;
  set_value(14, machine.memory[152], isOverflowed);
  machine.ld4(make_cmd(cmd_ld1, 152));

  EXPECT_EQ(14, get_value(machine.reg_i[3]));
}

TEST_F(MixMachineTestSuite, ld5) {
  bool isOverflowed;
  set_value(15, machine.memory[152], isOverflowed);
  machine.ld5(make_cmd(cmd_ld1, 152));

  EXPECT_EQ(15, get_value(machine.reg_i[4]));
}

TEST_F(MixMachineTestSuite, ldx) {
  bool isOverflowed;
  set_value(-18, machine.memory[152], isOverflowed);
  machine.ldx(make_cmd(cmd_ldx, 152));

  EXPECT_EQ(-18, get_value(machine.reg_x));
}

TEST_F(MixMachineTestSuite, ldan) {
  bool isOverflowed;
  set_value(-73, machine.memory[152], isOverflowed);
  machine.ldan(make_cmd(cmd_ldan, 152));

  EXPECT_EQ(73, get_value(machine.reg_a));
}

TEST_F(MixMachineTestSuite, ld1n) {
  bool isOverflowed;
  set_value(11, machine.memory[152], isOverflowed);
  machine.ld1n(make_cmd(cmd_ld1n, 152));

  EXPECT_EQ(-11, get_value(machine.reg_i[0]));
}

TEST_F(MixMachineTestSuite, ld2n) {
  bool isOverflowed;
  set_value(12, machine.memory[152], isOverflowed);
  machine.ld2n(make_cmd(cmd_ld2n, 152));

  EXPECT_EQ(-12, get_value(machine.reg_i[1]));
}

TEST_F(MixMachineTestSuite, ld3n) {
  bool isOverflowed;
  set_value(13, machine.memory[152], isOverflowed);
  machine.ld3n(make_cmd(cmd_ld3n, 152));

  EXPECT_EQ(-13, get_value(machine.reg_i[2]));
}

TEST_F(MixMachineTestSuite, ld4n) {
  bool isOverflowed;
  set_value(14, machine.memory[152], isOverflowed);
  machine.ld4n(make_cmd(cmd_ld4n, 152));

  EXPECT_EQ(-14, get_value(machine.reg_i[3]));
}

TEST_F(MixMachineTestSuite, ld5n) {
  bool isOverflowed;
  set_value(15, machine.memory[152], isOverflowed);
  machine.ld5n(make_cmd(cmd_ld5n, 152));

  EXPECT_EQ(-15, get_value(machine.reg_i[4]));
}

TEST_F(MixMachineTestSuite, ldxn) {
  bool isOverflowed;
  set_value(18, machine.memory[152], isOverflowed);
  machine.ldxn(make_cmd(cmd_ldxn, 152));

  EXPECT_EQ(-18, get_value(machine.reg_x));
}


}
