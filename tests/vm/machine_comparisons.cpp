
#include "machine_fixture.h"

namespace mix {

class MachineTestComparisonsSuite : public MachineFixture {};

TEST_F(MachineTestComparisonsSuite, cmpa_less) {
  set_reg_a_value(100);
  set_memory_value(152, 101);

  machine.cmpa(make_cmd(cmd_cmpa, 152));

  EXPECT_EQ(cmp_less, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmpa_equal) {
  set_reg_a_value(100);
  set_memory_value(152, 100);

  machine.cmpa(make_cmd(cmd_cmpa, 152));

  EXPECT_EQ(cmp_equal, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmpa_greater) {
  set_reg_a_value(101);
  set_memory_value(152, 100);

  machine.cmpa(make_cmd(cmd_cmpa, 152));

  EXPECT_EQ(cmp_greater, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp1_less) {
  set_reg_i_value(1, 100);
  set_memory_value(152, 101);

  machine.cmp1(make_cmd(cmd_cmp1, 152));

  EXPECT_EQ(cmp_less, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp1_equal) {
  set_reg_i_value(1, 100);
  set_memory_value(152, 100);

  machine.cmp1(make_cmd(cmd_cmp1, 152));

  EXPECT_EQ(cmp_equal, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp1_greater) {
  set_reg_i_value(1, 101);
  set_memory_value(152, 100);

  machine.cmp1(make_cmd(cmd_cmp1, 152));

  EXPECT_EQ(cmp_greater, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp2_less) {
  set_reg_i_value(2, 100);
  set_memory_value(152, 101);

  machine.cmp2(make_cmd(cmd_cmp2, 152));

  EXPECT_EQ(cmp_less, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp2_equal) {
  set_reg_i_value(2, 100);
  set_memory_value(152, 100);

  machine.cmp2(make_cmd(cmd_cmp2, 152));

  EXPECT_EQ(cmp_equal, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp2_greater) {
  set_reg_i_value(2, 101);
  set_memory_value(152, 100);

  machine.cmp2(make_cmd(cmd_cmp2, 152));

  EXPECT_EQ(cmp_greater, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp3_less) {
  set_reg_i_value(3, 100);
  set_memory_value(152, 101);

  machine.cmp3(make_cmd(cmd_cmp3, 152));

  EXPECT_EQ(cmp_less, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp3_equal) {
  set_reg_i_value(3, 100);
  set_memory_value(152, 100);

  machine.cmp3(make_cmd(cmd_cmp3, 152));

  EXPECT_EQ(cmp_equal, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp3_greater) {
  set_reg_i_value(3, 101);
  set_memory_value(152, 100);

  machine.cmp3(make_cmd(cmd_cmp3, 152));

  EXPECT_EQ(cmp_greater, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp4_less) {
  set_reg_i_value(4, 100);
  set_memory_value(152, 101);

  machine.cmp4(make_cmd(cmd_cmp4, 152));

  EXPECT_EQ(cmp_less, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp4_equal) {
  set_reg_i_value(4, 100);
  set_memory_value(152, 100);

  machine.cmp4(make_cmd(cmd_cmp4, 152));

  EXPECT_EQ(cmp_equal, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp4_greater) {
  set_reg_i_value(4, 101);
  set_memory_value(152, 100);

  machine.cmp4(make_cmd(cmd_cmp4, 152));

  EXPECT_EQ(cmp_greater, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp5_less) {
  set_reg_i_value(5, 100);
  set_memory_value(152, 101);

  machine.cmp5(make_cmd(cmd_cmp5, 152));

  EXPECT_EQ(cmp_less, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp5_equal) {
  set_reg_i_value(5, 100);
  set_memory_value(152, 100);

  machine.cmp5(make_cmd(cmd_cmp5, 152));

  EXPECT_EQ(cmp_equal, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp5_greater) {
  set_reg_i_value(5, 101);
  set_memory_value(152, 100);

  machine.cmp5(make_cmd(cmd_cmp5, 152));

  EXPECT_EQ(cmp_greater, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp6_less) {
  set_reg_i_value(6, 100);
  set_memory_value(152, 101);

  machine.cmp6(make_cmd(cmd_cmp6, 152));

  EXPECT_EQ(cmp_less, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp6_equal) {
  set_reg_i_value(6, 100);
  set_memory_value(152, 100);

  machine.cmp6(make_cmd(cmd_cmp6, 152));

  EXPECT_EQ(cmp_equal, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmp6_greater) {
  set_reg_i_value(6, 101);
  set_memory_value(152, 100);

  machine.cmp6(make_cmd(cmd_cmp6, 152));

  EXPECT_EQ(cmp_greater, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmpx_less) {
  set_reg_x_value(100);
  set_memory_value(152, 101);

  machine.cmpx(make_cmd(cmd_cmpx, 152));

  EXPECT_EQ(cmp_less, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmpx_equal) {
  set_reg_x_value(100);
  set_memory_value(152, 100);

  machine.cmpx(make_cmd(cmd_cmpx, 152));

  EXPECT_EQ(cmp_equal, machine.compare_flag);
}

TEST_F(MachineTestComparisonsSuite, cmpx_greater) {
  set_reg_x_value(101);
  set_memory_value(152, 100);

  machine.cmpx(make_cmd(cmd_cmpx, 152));

  EXPECT_EQ(cmp_greater, machine.compare_flag);
}

} // namespace mix
