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

TEST_F(MixMachineTestSuite, lda) {
  bool isOverflowed;
  set_value(-73, machine.memory[152], isOverflowed);
  machine.lda(make_cmd(cmd_lda, 152));

  EXPECT_EQ(-73, get_value(machine.reg_a));
}

TEST_F(MixMachineTestSuite, ldx) {
  bool isOverflowed;
  set_value(-18, machine.memory[152], isOverflowed);
  machine.ldx(make_cmd(cmd_ldx, 152));

  EXPECT_EQ(-18, get_value(machine.reg_x));
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

}
