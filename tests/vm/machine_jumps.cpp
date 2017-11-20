#include "machine_fixture.h"

namespace mix {
class MachineJumpsTestSuite: public MachineFixture {};

TEST_F(MachineJumpsTestSuite, jmp) {
  machine.jmp(make_cmd(cmd_jmp, 10));

  EXPECT_EQ(10, get_next_instruction_address());
}
  
TEST_F(MachineJumpsTestSuite, jov_jump_if_overflowed) {
  machine.override = true;
  machine.jov(make_cmd(cmd_jmp, 11));
  
  EXPECT_EQ(11, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jov_do_nothing_if_not_overflowed) {
  machine.override = false;
  machine.jov(make_cmd(cmd_jmp, 11));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jnov_jump_if_overflowed) {
  machine.override = true;
  machine.jnov(make_cmd(cmd_jmp, 12));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jnov_do_nothing_if_not_overflowed) {
  machine.override = false;
  machine.jnov(make_cmd(cmd_jmp, 12));
  
  EXPECT_EQ(12, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jl_jump_if_less) {
  machine.compare_flag = cmp_less;
  machine.jl(make_cmd(cmd_jmp, 13));
  
  EXPECT_EQ(13, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jl_not_jump_if_not_less) {
  machine.compare_flag = cmp_equal;
  machine.jl(make_cmd(cmd_jmp, 13));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, je_jump_if_equal) {
  machine.compare_flag = cmp_equal;
  machine.je(make_cmd(cmd_jmp, 13));
  
  EXPECT_EQ(13, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, je_not_jump_if_not_equal) {
  machine.compare_flag = cmp_less;
  machine.je(make_cmd(cmd_jmp, 13));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jg_jump_if_greater) {
  machine.compare_flag = cmp_greater;
  machine.jg(make_cmd(cmd_jmp, 14));
  
  EXPECT_EQ(14, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jg_not_jump_if_not_greater) {
  machine.compare_flag = cmp_equal;
  machine.jg(make_cmd(cmd_jmp, 15));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jge_jump_if_greater) {
  machine.compare_flag = cmp_greater;
  machine.jge(make_cmd(cmd_jmp, 16));
  
  EXPECT_EQ(16, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jge_jump_if_equal) {
  machine.compare_flag = cmp_equal;
  machine.jge(make_cmd(cmd_jmp, 17));
  
  EXPECT_EQ(17, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jge_not_jump_if_less) {
  machine.compare_flag = cmp_less;
  machine.jge(make_cmd(cmd_jmp, 18));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jne_jump_if_less) {
  machine.compare_flag = cmp_less;
  machine.jne(make_cmd(cmd_jmp, 19));
  
  EXPECT_EQ(19, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jle_not_jump_if_equal) {
  machine.compare_flag = cmp_equal;
  machine.jne(make_cmd(cmd_jmp, 20));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jle_jump_if_greater) {
  machine.compare_flag = cmp_greater;
  machine.jne(make_cmd(cmd_jmp, 21));
  
  EXPECT_EQ(21, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jle_jump_if_less) {
  machine.compare_flag = cmp_less;
  machine.jle(make_cmd(cmd_jmp, 22));
  
  EXPECT_EQ(22, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jle_jump_if_equal) {
  machine.compare_flag = cmp_equal;
  machine.jle(make_cmd(cmd_jmp, 23));
  
  EXPECT_EQ(23, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jle_not_jump_if_greater) {
  machine.compare_flag = cmp_greater;
  machine.jle(make_cmd(cmd_jmp, 24));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jan_jump_if_ra_negative) {
  set_reg_a_value(-1);
  machine.jan(make_cmd(cmd_ja, 25));
  
  EXPECT_EQ(25, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jan_not_jump_if_ra_zero) {
  set_reg_a_value(0);
  machine.jan(make_cmd(cmd_ja, 26));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jan_not_jump_if_ra_positive) {
  set_reg_a_value(1);
  machine.jan(make_cmd(cmd_ja, 27));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jaz_not_jump_if_ra_negative) {
  set_reg_a_value(-1);
  machine.jaz(make_cmd(cmd_ja, 28));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jaz_jump_if_ra_zero) {
  set_reg_a_value(0);
  machine.jaz(make_cmd(cmd_ja, 29));
  
  EXPECT_EQ(29, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jaz_not_jump_if_ra_positive) {
  set_reg_a_value(1);
  machine.jaz(make_cmd(cmd_ja, 30));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jap_not_jump_if_ra_negative) {
  set_reg_a_value(-1);
  machine.jap(make_cmd(cmd_ja, 31));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jap_not_jump_if_ra_zero) {
  set_reg_a_value(0);
  machine.jap(make_cmd(cmd_ja, 32));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jap_jump_if_ra_positive) {
  set_reg_a_value(1);
  machine.jap(make_cmd(cmd_ja, 33));
  
  EXPECT_EQ(33, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jann_not_jump_if_ra_negative) {
  set_reg_a_value(-1);
  machine.jann(make_cmd(cmd_ja, 34));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jann_jump_if_ra_zero) {
  set_reg_a_value(0);
  machine.jann(make_cmd(cmd_ja, 35));
  
  EXPECT_EQ(35, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jann_jump_if_ra_positive) {
  set_reg_a_value(1);
  machine.jann(make_cmd(cmd_ja, 36));
  
  EXPECT_EQ(36, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, janz_jump_if_ra_negative) {
  set_reg_a_value(-1);
  machine.janz(make_cmd(cmd_ja, 37));
  
  EXPECT_EQ(37, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, janz_not_jump_if_ra_zero) {
  set_reg_a_value(0);
  machine.janz(make_cmd(cmd_ja, 38));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, janz_jump_if_ra_positive) {
  set_reg_a_value(1);
  machine.janz(make_cmd(cmd_ja, 39));
  
  EXPECT_EQ(39, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, janp_jump_if_ra_negative) {
  set_reg_a_value(-1);
  machine.janp(make_cmd(cmd_ja, 40));
  
  EXPECT_EQ(40, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, janp_jump_if_ra_zero) {
  set_reg_a_value(0);
  machine.janp(make_cmd(cmd_ja, 41));
  
  EXPECT_EQ(41, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, janp_not_jump_if_ra_positive) {
  set_reg_a_value(1);
  machine.janp(make_cmd(cmd_ja, 42));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}
}  // namespace mix

