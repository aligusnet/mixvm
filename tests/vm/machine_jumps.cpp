#include "machine_fixture.h"

namespace mix {
class MachineJumpsTestSuite : public MachineFixture {};

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

TEST_F(MachineJumpsTestSuite, j1n_jump_if_ra_negative) {
  set_reg_i_value(1, -1);
  machine.j1n(make_cmd(cmd_j1, 25));

  EXPECT_EQ(25, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j1n_not_jump_if_ra_zero) {
  set_reg_i_value(1, 0);
  machine.j1n(make_cmd(cmd_j1, 26));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j1n_not_jump_if_ra_positive) {
  set_reg_i_value(1, 1);
  machine.j1n(make_cmd(cmd_j1, 27));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j1z_not_jump_if_ra_negative) {
  set_reg_i_value(1, -1);
  machine.j1z(make_cmd(cmd_j1, 28));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j1z_jump_if_ra_zero) {
  set_reg_i_value(1, 0);
  machine.j1z(make_cmd(cmd_j1, 29));

  EXPECT_EQ(29, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j1z_not_jump_if_ra_positive) {
  set_reg_i_value(1, 1);
  machine.j1z(make_cmd(cmd_j1, 30));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j1p_not_jump_if_ra_negative) {
  set_reg_i_value(1, -1);
  machine.j1p(make_cmd(cmd_j1, 31));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j1p_not_jump_if_ra_zero) {
  set_reg_i_value(1, 0);
  machine.j1p(make_cmd(cmd_j1, 32));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j1p_jump_if_ra_positive) {
  set_reg_i_value(1, 1);
  machine.j1p(make_cmd(cmd_j1, 33));

  EXPECT_EQ(33, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j1nn_not_jump_if_ra_negative) {
  set_reg_i_value(1, -1);
  machine.j1nn(make_cmd(cmd_j1, 34));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j1nn_jump_if_ra_zero) {
  set_reg_i_value(1, 0);
  machine.j1nn(make_cmd(cmd_j1, 35));

  EXPECT_EQ(35, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j1nn_jump_if_ra_positive) {
  set_reg_i_value(1, 1);
  machine.j1nn(make_cmd(cmd_j1, 36));

  EXPECT_EQ(36, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j1nz_jump_if_ra_negative) {
  set_reg_i_value(1, -1);
  machine.j1nz(make_cmd(cmd_j1, 37));

  EXPECT_EQ(37, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j1nz_not_jump_if_ra_zero) {
  set_reg_i_value(1, 0);
  machine.j1nz(make_cmd(cmd_j1, 38));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j1nz_jump_if_ra_positive) {
  set_reg_i_value(1, 1);
  machine.j1nz(make_cmd(cmd_j1, 39));

  EXPECT_EQ(39, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j1np_jump_if_ra_negative) {
  set_reg_i_value(1, -1);
  machine.j1np(make_cmd(cmd_j1, 40));

  EXPECT_EQ(40, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j1np_jump_if_ra_zero) {
  set_reg_i_value(1, 0);
  machine.j1np(make_cmd(cmd_j1, 41));

  EXPECT_EQ(41, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j1np_not_jump_if_ra_positive) {
  set_reg_i_value(1, 1);
  machine.j1np(make_cmd(cmd_j1, 42));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j2n_jump_if_ra_negative) {
  set_reg_i_value(2, -1);
  machine.j2n(make_cmd(cmd_j2, 25));

  EXPECT_EQ(25, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j2n_not_jump_if_ra_zero) {
  set_reg_i_value(2, 0);
  machine.j2n(make_cmd(cmd_j2, 26));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j2n_not_jump_if_ra_positive) {
  set_reg_i_value(2, 1);
  machine.j2n(make_cmd(cmd_j2, 27));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j2z_not_jump_if_ra_negative) {
  set_reg_i_value(2, -1);
  machine.j2z(make_cmd(cmd_j2, 28));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j2z_jump_if_ra_zero) {
  set_reg_i_value(2, 0);
  machine.j2z(make_cmd(cmd_j2, 29));

  EXPECT_EQ(29, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j2z_not_jump_if_ra_positive) {
  set_reg_i_value(2, 1);
  machine.j2z(make_cmd(cmd_j2, 30));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j2p_not_jump_if_ra_negative) {
  set_reg_i_value(2, -1);
  machine.j2p(make_cmd(cmd_j2, 31));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j2p_not_jump_if_ra_zero) {
  set_reg_i_value(2, 0);
  machine.j2p(make_cmd(cmd_j2, 32));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j2p_jump_if_ra_positive) {
  set_reg_i_value(2, 1);
  machine.j2p(make_cmd(cmd_j2, 33));

  EXPECT_EQ(33, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j2nn_not_jump_if_ra_negative) {
  set_reg_i_value(2, -1);
  machine.j2nn(make_cmd(cmd_j2, 34));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j2nn_jump_if_ra_zero) {
  set_reg_i_value(2, 0);
  machine.j2nn(make_cmd(cmd_j2, 35));

  EXPECT_EQ(35, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j2nn_jump_if_ra_positive) {
  set_reg_i_value(2, 1);
  machine.j2nn(make_cmd(cmd_j2, 36));

  EXPECT_EQ(36, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j2nz_jump_if_ra_negative) {
  set_reg_i_value(2, -1);
  machine.j2nz(make_cmd(cmd_j2, 37));

  EXPECT_EQ(37, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j2nz_not_jump_if_ra_zero) {
  set_reg_i_value(2, 0);
  machine.j2nz(make_cmd(cmd_j2, 38));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j2nz_jump_if_ra_positive) {
  set_reg_i_value(2, 1);
  machine.j2nz(make_cmd(cmd_j2, 39));

  EXPECT_EQ(39, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j2np_jump_if_ra_negative) {
  set_reg_i_value(2, -1);
  machine.j2np(make_cmd(cmd_j2, 40));

  EXPECT_EQ(40, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j2np_jump_if_ra_zero) {
  set_reg_i_value(2, 0);
  machine.j2np(make_cmd(cmd_j2, 41));

  EXPECT_EQ(41, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j2np_not_jump_if_ra_positive) {
  set_reg_i_value(2, 1);
  machine.j2np(make_cmd(cmd_j2, 42));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j3n_jump_if_ra_negative) {
  set_reg_i_value(3, -1);
  machine.j3n(make_cmd(cmd_j3, 25));

  EXPECT_EQ(25, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j3n_not_jump_if_ra_zero) {
  set_reg_i_value(3, 0);
  machine.j3n(make_cmd(cmd_j3, 26));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j3n_not_jump_if_ra_positive) {
  set_reg_i_value(3, 1);
  machine.j3n(make_cmd(cmd_j3, 27));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j3z_not_jump_if_ra_negative) {
  set_reg_i_value(3, -1);
  machine.j3z(make_cmd(cmd_j3, 28));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j3z_jump_if_ra_zero) {
  set_reg_i_value(3, 0);
  machine.j3z(make_cmd(cmd_j3, 29));

  EXPECT_EQ(29, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j3z_not_jump_if_ra_positive) {
  set_reg_i_value(3, 1);
  machine.j3z(make_cmd(cmd_j3, 30));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j3p_not_jump_if_ra_negative) {
  set_reg_i_value(3, -1);
  machine.j3p(make_cmd(cmd_j3, 31));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j3p_not_jump_if_ra_zero) {
  set_reg_i_value(3, 0);
  machine.j3p(make_cmd(cmd_j3, 32));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j3p_jump_if_ra_positive) {
  set_reg_i_value(3, 1);
  machine.j3p(make_cmd(cmd_j3, 33));

  EXPECT_EQ(33, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j3nn_not_jump_if_ra_negative) {
  set_reg_i_value(3, -1);
  machine.j3nn(make_cmd(cmd_j3, 34));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j3nn_jump_if_ra_zero) {
  set_reg_i_value(3, 0);
  machine.j3nn(make_cmd(cmd_j3, 35));

  EXPECT_EQ(35, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j3nn_jump_if_ra_positive) {
  set_reg_i_value(3, 1);
  machine.j3nn(make_cmd(cmd_j3, 36));

  EXPECT_EQ(36, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j3nz_jump_if_ra_negative) {
  set_reg_i_value(3, -1);
  machine.j3nz(make_cmd(cmd_j3, 37));

  EXPECT_EQ(37, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j3nz_not_jump_if_ra_zero) {
  set_reg_i_value(3, 0);
  machine.j3nz(make_cmd(cmd_j3, 38));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j3nz_jump_if_ra_positive) {
  set_reg_i_value(3, 1);
  machine.j3nz(make_cmd(cmd_j3, 39));

  EXPECT_EQ(39, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j3np_jump_if_ra_negative) {
  set_reg_i_value(3, -1);
  machine.j3np(make_cmd(cmd_j3, 40));

  EXPECT_EQ(40, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j3np_jump_if_ra_zero) {
  set_reg_i_value(3, 0);
  machine.j3np(make_cmd(cmd_j3, 41));

  EXPECT_EQ(41, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j3np_not_jump_if_ra_positive) {
  set_reg_i_value(3, 1);
  machine.j3np(make_cmd(cmd_j3, 42));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j4n_jump_if_ra_negative) {
  set_reg_i_value(4, -1);
  machine.j4n(make_cmd(cmd_j4, 25));

  EXPECT_EQ(25, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j4n_not_jump_if_ra_zero) {
  set_reg_i_value(4, 0);
  machine.j4n(make_cmd(cmd_j4, 26));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j4n_not_jump_if_ra_positive) {
  set_reg_i_value(4, 1);
  machine.j4n(make_cmd(cmd_j4, 27));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j4z_not_jump_if_ra_negative) {
  set_reg_i_value(4, -1);
  machine.j4z(make_cmd(cmd_j4, 28));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j4z_jump_if_ra_zero) {
  set_reg_i_value(4, 0);
  machine.j4z(make_cmd(cmd_j4, 29));

  EXPECT_EQ(29, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j4z_not_jump_if_ra_positive) {
  set_reg_i_value(4, 1);
  machine.j4z(make_cmd(cmd_j4, 30));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j4p_not_jump_if_ra_negative) {
  set_reg_i_value(4, -1);
  machine.j4p(make_cmd(cmd_j4, 31));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j4p_not_jump_if_ra_zero) {
  set_reg_i_value(4, 0);
  machine.j4p(make_cmd(cmd_j4, 32));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j4p_jump_if_ra_positive) {
  set_reg_i_value(4, 1);
  machine.j4p(make_cmd(cmd_j4, 33));

  EXPECT_EQ(33, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j4nn_not_jump_if_ra_negative) {
  set_reg_i_value(4, -1);
  machine.j4nn(make_cmd(cmd_j4, 34));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j4nn_jump_if_ra_zero) {
  set_reg_i_value(4, 0);
  machine.j4nn(make_cmd(cmd_j4, 35));

  EXPECT_EQ(35, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j4nn_jump_if_ra_positive) {
  set_reg_i_value(4, 1);
  machine.j4nn(make_cmd(cmd_j4, 36));

  EXPECT_EQ(36, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j4nz_jump_if_ra_negative) {
  set_reg_i_value(4, -1);
  machine.j4nz(make_cmd(cmd_j4, 37));

  EXPECT_EQ(37, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j4nz_not_jump_if_ra_zero) {
  set_reg_i_value(4, 0);
  machine.j4nz(make_cmd(cmd_j4, 38));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j4nz_jump_if_ra_positive) {
  set_reg_i_value(4, 1);
  machine.j4nz(make_cmd(cmd_j4, 39));

  EXPECT_EQ(39, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j4np_jump_if_ra_negative) {
  set_reg_i_value(4, -1);
  machine.j4np(make_cmd(cmd_j4, 40));

  EXPECT_EQ(40, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j4np_jump_if_ra_zero) {
  set_reg_i_value(4, 0);
  machine.j4np(make_cmd(cmd_j4, 41));

  EXPECT_EQ(41, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j4np_not_jump_if_ra_positive) {
  set_reg_i_value(4, 1);
  machine.j4np(make_cmd(cmd_j4, 42));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j5n_jump_if_ra_negative) {
  set_reg_i_value(5, -1);
  machine.j5n(make_cmd(cmd_j5, 25));

  EXPECT_EQ(25, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j5n_not_jump_if_ra_zero) {
  set_reg_i_value(5, 0);
  machine.j5n(make_cmd(cmd_j5, 26));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j5n_not_jump_if_ra_positive) {
  set_reg_i_value(5, 1);
  machine.j5n(make_cmd(cmd_j5, 27));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j5z_not_jump_if_ra_negative) {
  set_reg_i_value(5, -1);
  machine.j5z(make_cmd(cmd_j5, 28));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j5z_jump_if_ra_zero) {
  set_reg_i_value(5, 0);
  machine.j5z(make_cmd(cmd_j5, 29));

  EXPECT_EQ(29, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j5z_not_jump_if_ra_positive) {
  set_reg_i_value(5, 1);
  machine.j5z(make_cmd(cmd_j5, 30));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j5p_not_jump_if_ra_negative) {
  set_reg_i_value(5, -1);
  machine.j5p(make_cmd(cmd_j5, 31));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j5p_not_jump_if_ra_zero) {
  set_reg_i_value(5, 0);
  machine.j5p(make_cmd(cmd_j5, 32));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j5p_jump_if_ra_positive) {
  set_reg_i_value(5, 1);
  machine.j5p(make_cmd(cmd_j5, 33));

  EXPECT_EQ(33, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j5nn_not_jump_if_ra_negative) {
  set_reg_i_value(5, -1);
  machine.j5nn(make_cmd(cmd_j5, 34));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j5nn_jump_if_ra_zero) {
  set_reg_i_value(5, 0);
  machine.j5nn(make_cmd(cmd_j5, 35));

  EXPECT_EQ(35, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j5nn_jump_if_ra_positive) {
  set_reg_i_value(5, 1);
  machine.j5nn(make_cmd(cmd_j5, 36));

  EXPECT_EQ(36, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j5nz_jump_if_ra_negative) {
  set_reg_i_value(5, -1);
  machine.j5nz(make_cmd(cmd_j5, 37));

  EXPECT_EQ(37, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j5nz_not_jump_if_ra_zero) {
  set_reg_i_value(5, 0);
  machine.j5nz(make_cmd(cmd_j5, 38));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j5nz_jump_if_ra_positive) {
  set_reg_i_value(5, 1);
  machine.j5nz(make_cmd(cmd_j5, 39));

  EXPECT_EQ(39, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j5np_jump_if_ra_negative) {
  set_reg_i_value(5, -1);
  machine.j5np(make_cmd(cmd_j5, 40));

  EXPECT_EQ(40, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j5np_jump_if_ra_zero) {
  set_reg_i_value(5, 0);
  machine.j5np(make_cmd(cmd_j5, 41));

  EXPECT_EQ(41, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j5np_not_jump_if_ra_positive) {
  set_reg_i_value(5, 1);
  machine.j5np(make_cmd(cmd_j5, 42));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j6n_jump_if_ra_negative) {
  set_reg_i_value(6, -1);
  machine.j6n(make_cmd(cmd_j6, 25));

  EXPECT_EQ(25, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j6n_not_jump_if_ra_zero) {
  set_reg_i_value(6, 0);
  machine.j6n(make_cmd(cmd_j6, 26));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j6n_not_jump_if_ra_positive) {
  set_reg_i_value(6, 1);
  machine.j6n(make_cmd(cmd_j6, 27));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j6z_not_jump_if_ra_negative) {
  set_reg_i_value(6, -1);
  machine.j6z(make_cmd(cmd_j6, 28));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j6z_jump_if_ra_zero) {
  set_reg_i_value(6, 0);
  machine.j6z(make_cmd(cmd_j6, 29));

  EXPECT_EQ(29, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j6z_not_jump_if_ra_positive) {
  set_reg_i_value(6, 1);
  machine.j6z(make_cmd(cmd_j6, 30));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j6p_not_jump_if_ra_negative) {
  set_reg_i_value(6, -1);
  machine.j6p(make_cmd(cmd_j6, 31));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j6p_not_jump_if_ra_zero) {
  set_reg_i_value(6, 0);
  machine.j6p(make_cmd(cmd_j6, 32));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j6p_jump_if_ra_positive) {
  set_reg_i_value(6, 1);
  machine.j6p(make_cmd(cmd_j6, 33));

  EXPECT_EQ(33, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j6nn_not_jump_if_ra_negative) {
  set_reg_i_value(6, -1);
  machine.j6nn(make_cmd(cmd_j6, 34));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j6nn_jump_if_ra_zero) {
  set_reg_i_value(6, 0);
  machine.j6nn(make_cmd(cmd_j6, 35));

  EXPECT_EQ(35, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j6nn_jump_if_ra_positive) {
  set_reg_i_value(6, 1);
  machine.j6nn(make_cmd(cmd_j6, 36));

  EXPECT_EQ(36, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j6nz_jump_if_ra_negative) {
  set_reg_i_value(6, -1);
  machine.j6nz(make_cmd(cmd_j6, 37));

  EXPECT_EQ(37, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j6nz_not_jump_if_ra_zero) {
  set_reg_i_value(6, 0);
  machine.j6nz(make_cmd(cmd_j6, 38));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, j6nz_jump_if_ra_positive) {
  set_reg_i_value(6, 1);
  machine.j6nz(make_cmd(cmd_j6, 39));

  EXPECT_EQ(39, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j6np_jump_if_ra_negative) {
  set_reg_i_value(6, -1);
  machine.j6np(make_cmd(cmd_j6, 40));

  EXPECT_EQ(40, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j6np_jump_if_ra_zero) {
  set_reg_i_value(6, 0);
  machine.j6np(make_cmd(cmd_j6, 41));

  EXPECT_EQ(41, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, j6np_not_jump_if_ra_positive) {
  set_reg_i_value(6, 1);
  machine.j6np(make_cmd(cmd_j6, 42));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jxn_jump_if_ra_negative) {
  set_reg_x_value(-1);
  machine.jxn(make_cmd(cmd_jx, 25));

  EXPECT_EQ(25, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jxn_not_jump_if_ra_zero) {
  set_reg_x_value(0);
  machine.jxn(make_cmd(cmd_jx, 26));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jxn_not_jump_if_ra_positive) {
  set_reg_x_value(1);
  machine.jxn(make_cmd(cmd_jx, 27));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jxz_not_jump_if_ra_negative) {
  set_reg_x_value(-1);
  machine.jxz(make_cmd(cmd_jx, 28));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jxz_jump_if_ra_zero) {
  set_reg_x_value(0);
  machine.jxz(make_cmd(cmd_jx, 29));

  EXPECT_EQ(29, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jxz_not_jump_if_ra_positive) {
  set_reg_x_value(1);
  machine.jxz(make_cmd(cmd_jx, 30));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jxp_not_jump_if_ra_negative) {
  set_reg_x_value(-1);
  machine.jxp(make_cmd(cmd_jx, 31));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jxp_not_jump_if_ra_zero) {
  set_reg_x_value(0);
  machine.jxp(make_cmd(cmd_jx, 32));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jxp_jump_if_ra_positive) {
  set_reg_x_value(1);
  machine.jxp(make_cmd(cmd_jx, 33));

  EXPECT_EQ(33, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jxnn_not_jump_if_ra_negative) {
  set_reg_x_value(-1);
  machine.jxnn(make_cmd(cmd_jx, 34));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jxnn_jump_if_ra_zero) {
  set_reg_x_value(0);
  machine.jxnn(make_cmd(cmd_jx, 35));

  EXPECT_EQ(35, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jxnn_jump_if_ra_positive) {
  set_reg_x_value(1);
  machine.jxnn(make_cmd(cmd_jx, 36));

  EXPECT_EQ(36, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jxnz_jump_if_ra_negative) {
  set_reg_x_value(-1);
  machine.jxnz(make_cmd(cmd_jx, 37));

  EXPECT_EQ(37, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jxnz_not_jump_if_ra_zero) {
  set_reg_x_value(0);
  machine.jxnz(make_cmd(cmd_jx, 38));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MachineJumpsTestSuite, jxnz_jump_if_ra_positive) {
  set_reg_x_value(1);
  machine.jxnz(make_cmd(cmd_jx, 39));

  EXPECT_EQ(39, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jxnp_jump_if_ra_negative) {
  set_reg_x_value(-1);
  machine.jxnp(make_cmd(cmd_jx, 40));

  EXPECT_EQ(40, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jxnp_jump_if_ra_zero) {
  set_reg_x_value(0);
  machine.jxnp(make_cmd(cmd_jx, 41));

  EXPECT_EQ(41, get_next_instruction_address());
}

TEST_F(MachineJumpsTestSuite, jxnp_not_jump_if_ra_positive) {
  set_reg_x_value(1);
  machine.jxnp(make_cmd(cmd_jx, 42));

  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

} // namespace mix
