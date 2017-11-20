#include <gtest/gtest.h>

#include <vm/mix_machine.h>
#include <vm/mix_word.h>
#include <vm/mix_small_word.h>

namespace mix {

class MixMachineTestSuite: public ::testing::Test {
protected:
  Machine machine;
  bool isOverflowed;
  
  int get_next_instruction_address() {
    return get_value(machine.reg_j);
  }
  
  bool is_next_instruction_address_unchanged() {
    const int NEXT_INSTRUCTION_DEFAULT_ADDRESS = 0;
    return get_next_instruction_address() == NEXT_INSTRUCTION_DEFAULT_ADDRESS;
  }
  
  void set_memory_value(int address, int value) {
    set_value(value, machine.memory[address], isOverflowed);
  }
  
  int get_memory_value(int address) {
    return get_value(machine.memory[address]);
  }
  
  void set_reg_a_value(int value) {
    set_value(value, machine.reg_a, isOverflowed);
  }
  
  int get_reg_a_value() {
    return get_value(machine.reg_a);
  }
  
  void set_reg_x_value(int value) {
    set_value(value, machine.reg_x, isOverflowed);
  }
  
  int get_reg_x_value() {
    return get_value(machine.reg_x);
  }
  
  void set_reg_i_value(int index, int value) {
    set_value(value, machine.reg_i[index-1], isOverflowed);
  }
  
  int get_reg_i_value(int index) {
    return get_value(machine.reg_i[index-1]);
  }
};

TEST_F(MixMachineTestSuite, start_state) {
  EXPECT_EQ(0, get_reg_a_value());
  EXPECT_EQ(0, get_reg_x_value());
  EXPECT_EQ(0, get_reg_i_value(1));
  EXPECT_EQ(0, get_reg_i_value(2));
  EXPECT_EQ(0, get_reg_i_value(3));
  EXPECT_EQ(0, get_reg_i_value(4));
  EXPECT_EQ(0, get_reg_i_value(5));
}

TEST_F(MixMachineTestSuite, add) {
  set_reg_a_value(-7);
  set_memory_value(152, 5);
  
  machine.add(make_cmd(cmd_add, 152));

  EXPECT_EQ(-2, get_reg_a_value());
  EXPECT_EQ(5, get_memory_value(152));
}

TEST_F(MixMachineTestSuite, sub) {
  set_reg_a_value(-7);
  set_memory_value(152, 5);

  machine.sub(make_cmd(cmd_sub, 152));

  EXPECT_EQ(-12, get_reg_a_value());
  EXPECT_EQ(5, get_memory_value(152));
}

TEST_F(MixMachineTestSuite, mul) {
  set_reg_a_value(-7);
  set_memory_value(152, 5);
  machine.mul(make_cmd(cmd_mul, 152));

  EXPECT_EQ(0, get_reg_a_value());
  EXPECT_EQ(-35, get_reg_x_value());
  EXPECT_EQ(5, get_memory_value(152));
}

TEST_F(MixMachineTestSuite, mul_2_big_numbers) {
  set_reg_a_value(-73193);
  set_memory_value(152, 53781);
  machine.mul(make_cmd(cmd_mul, 152));

  EXPECT_EQ(-73193l*53781l, get_long_value(machine.reg_a, machine.reg_x));
  EXPECT_EQ(53781, get_memory_value(152));
}

TEST_F(MixMachineTestSuite, div) {
  set_long_value(-73193l*53781l - 11, machine.reg_a, machine.reg_x, isOverflowed);
  set_memory_value(152, 53781);

  machine.div(make_cmd(cmd_div, 152));

  EXPECT_EQ(-73193, get_reg_a_value());
  EXPECT_EQ(-11, get_reg_x_value());
}

TEST_F(MixMachineTestSuite, hlt) {
  machine.halt = false;
  machine.hlt(make_cmd(cmd_hlt));
  EXPECT_TRUE(machine.halt);
}

TEST_F(MixMachineTestSuite, lda) {
  set_memory_value(152, -73);
  machine.lda(make_cmd(cmd_lda, 152));

  EXPECT_EQ(-73, get_reg_a_value());
}

TEST_F(MixMachineTestSuite, ld1) {
  set_memory_value(152, 11);
  machine.ld1(make_cmd(cmd_ld1, 152));

  EXPECT_EQ(11, get_reg_i_value(1));
}

TEST_F(MixMachineTestSuite, ld2) {
  set_memory_value(152, 12);
  machine.ld2(make_cmd(cmd_ld2, 152));

  EXPECT_EQ(12, get_reg_i_value(2));
}

TEST_F(MixMachineTestSuite, ld3) {
  set_memory_value(152, 13);
  machine.ld3(make_cmd(cmd_ld3, 152));

  EXPECT_EQ(13, get_reg_i_value(3));
}

TEST_F(MixMachineTestSuite, ld4) {
  set_memory_value(152, 14);
  machine.ld4(make_cmd(cmd_ld4, 152));

  EXPECT_EQ(14, get_reg_i_value(4));
}

TEST_F(MixMachineTestSuite, ld5) {
  set_memory_value(152, 15);
  machine.ld5(make_cmd(cmd_ld5, 152));

  EXPECT_EQ(15, get_reg_i_value(5));
}

TEST_F(MixMachineTestSuite, ldx) {
  set_memory_value(152, -18);
  machine.ldx(make_cmd(cmd_ldx, 152));

  EXPECT_EQ(-18, get_reg_x_value());
}

TEST_F(MixMachineTestSuite, ldan) {
  set_value(-73, machine.memory[152], isOverflowed);
  machine.ldan(make_cmd(cmd_ldan, 152));

  EXPECT_EQ(73, get_value(machine.reg_a));
}

TEST_F(MixMachineTestSuite, ld1n) {
  set_value(11, machine.memory[152], isOverflowed);
  machine.ld1n(make_cmd(cmd_ld1n, 152));

  EXPECT_EQ(-11, get_value(machine.reg_i[0]));
}

TEST_F(MixMachineTestSuite, ld2n) {
  set_value(12, machine.memory[152], isOverflowed);
  machine.ld2n(make_cmd(cmd_ld2n, 152));

  EXPECT_EQ(-12, get_value(machine.reg_i[1]));
}

TEST_F(MixMachineTestSuite, ld3n) {
  set_value(13, machine.memory[152], isOverflowed);
  machine.ld3n(make_cmd(cmd_ld3n, 152));

  EXPECT_EQ(-13, get_value(machine.reg_i[2]));
}

TEST_F(MixMachineTestSuite, ld4n) {
  set_value(14, machine.memory[152], isOverflowed);
  machine.ld4n(make_cmd(cmd_ld4n, 152));

  EXPECT_EQ(-14, get_value(machine.reg_i[3]));
}

TEST_F(MixMachineTestSuite, ld5n) {
  set_value(15, machine.memory[152], isOverflowed);
  machine.ld5n(make_cmd(cmd_ld5n, 152));

  EXPECT_EQ(-15, get_value(machine.reg_i[4]));
}

TEST_F(MixMachineTestSuite, ldxn) {
  set_value(18, machine.memory[152], isOverflowed);
  machine.ldxn(make_cmd(cmd_ldxn, 152));

  EXPECT_EQ(-18, get_value(machine.reg_x));
}

TEST_F(MixMachineTestSuite, sta) {
  set_value(-73, machine.reg_a, isOverflowed);
  machine.sta(make_cmd(cmd_sta, 152));

  EXPECT_EQ(-73, get_value(machine.memory[152]));
}

TEST_F(MixMachineTestSuite, st1) {
  set_value(11, machine.reg_i[0], isOverflowed);
  machine.st1(make_cmd(cmd_st1, 152));

  EXPECT_EQ(11, get_value(machine.memory[152]));
}

TEST_F(MixMachineTestSuite, st2) {
  set_value(12, machine.reg_i[1], isOverflowed);
  machine.st2(make_cmd(cmd_st2, 152));

  EXPECT_EQ(12, get_value(machine.memory[152]));
}

TEST_F(MixMachineTestSuite, st3) {
  set_value(13, machine.reg_i[2], isOverflowed);
  machine.st3(make_cmd(cmd_st3, 152));

  EXPECT_EQ(13, get_value(machine.memory[152]));
}

TEST_F(MixMachineTestSuite, st4) {
  set_value(14, machine.reg_i[3], isOverflowed);
  machine.st4(make_cmd(cmd_st4, 152));

  EXPECT_EQ(14, get_value(machine.memory[152]));
}

TEST_F(MixMachineTestSuite, st5) {
  set_value(15, machine.reg_i[4], isOverflowed);
  machine.st5(make_cmd(cmd_st5, 152));

  EXPECT_EQ(15, get_value(machine.memory[152]));
}

TEST_F(MixMachineTestSuite, stx) {
  set_value(-18, machine.reg_x, isOverflowed);
  machine.stx(make_cmd(cmd_stx, 152));

  EXPECT_EQ(-18, get_value(machine.memory[152]));
}

TEST_F(MixMachineTestSuite, stj) {
  set_value(99, machine.reg_j, isOverflowed);
  machine.stj(make_cmd(cmd_stj, 152));

  EXPECT_EQ(99, get_value(machine.memory[152]));
}

TEST_F(MixMachineTestSuite, stz) {
  set_value(-75, machine.memory[152], isOverflowed);
  machine.stz(make_cmd(cmd_stz, 152));

  EXPECT_EQ(0, get_value(machine.memory[152]));
}

TEST_F(MixMachineTestSuite, jmp) {
  machine.jmp(make_cmd(cmd_jmp, 10));

  EXPECT_EQ(10, get_next_instruction_address());
}
    
TEST_F(MixMachineTestSuite, jov_jump_if_overflowed) {
  machine.override = true;
  machine.jov(make_cmd(cmd_jmp, 11));
  
  EXPECT_EQ(11, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jov_do_nothing_if_not_overflowed) {
  machine.override = false;
  machine.jov(make_cmd(cmd_jmp, 11));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jnov_jump_if_overflowed) {
  machine.override = true;
  machine.jnov(make_cmd(cmd_jmp, 12));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jnov_do_nothing_if_not_overflowed) {
  machine.override = false;
  machine.jnov(make_cmd(cmd_jmp, 12));
  
  EXPECT_EQ(12, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jl_jump_if_less) {
  machine.compare_flag = cmp_less;
  machine.jl(make_cmd(cmd_jmp, 13));
  
  EXPECT_EQ(13, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jl_not_jump_if_not_less) {
  machine.compare_flag = cmp_equal;
  machine.jl(make_cmd(cmd_jmp, 13));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, je_jump_if_equal) {
  machine.compare_flag = cmp_equal;
  machine.je(make_cmd(cmd_jmp, 13));
  
  EXPECT_EQ(13, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, je_not_jump_if_not_equal) {
  machine.compare_flag = cmp_less;
  machine.je(make_cmd(cmd_jmp, 13));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jg_jump_if_greater) {
  machine.compare_flag = cmp_greater;
  machine.jg(make_cmd(cmd_jmp, 14));
  
  EXPECT_EQ(14, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jg_not_jump_if_not_greater) {
  machine.compare_flag = cmp_equal;
  machine.jg(make_cmd(cmd_jmp, 15));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jge_jump_if_greater) {
  machine.compare_flag = cmp_greater;
  machine.jge(make_cmd(cmd_jmp, 16));
  
  EXPECT_EQ(16, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jge_jump_if_equal) {
  machine.compare_flag = cmp_equal;
  machine.jge(make_cmd(cmd_jmp, 17));
  
  EXPECT_EQ(17, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jge_not_jump_if_less) {
  machine.compare_flag = cmp_less;
  machine.jge(make_cmd(cmd_jmp, 18));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jne_jump_if_less) {
  machine.compare_flag = cmp_less;
  machine.jne(make_cmd(cmd_jmp, 19));
  
  EXPECT_EQ(19, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jle_not_jump_if_equal) {
  machine.compare_flag = cmp_equal;
  machine.jne(make_cmd(cmd_jmp, 20));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jle_jump_if_greater) {
  machine.compare_flag = cmp_greater;
  machine.jne(make_cmd(cmd_jmp, 21));
  
  EXPECT_EQ(21, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jle_jump_if_less) {
  machine.compare_flag = cmp_less;
  machine.jle(make_cmd(cmd_jmp, 22));
  
  EXPECT_EQ(22, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jle_jump_if_equal) {
  machine.compare_flag = cmp_equal;
  machine.jle(make_cmd(cmd_jmp, 23));
  
  EXPECT_EQ(23, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jle_not_jump_if_greater) {
  machine.compare_flag = cmp_greater;
  machine.jle(make_cmd(cmd_jmp, 24));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jan_jump_if_ra_negative) {
  set_value(-1, machine.reg_a, isOverflowed);
  machine.jan(make_cmd(cmd_ja, 25));
  
  EXPECT_EQ(25, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jan_not_jump_if_ra_zero) {
  set_value(0, machine.reg_a, isOverflowed);
  machine.jan(make_cmd(cmd_ja, 26));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jan_not_jump_if_ra_positive) {
  set_value(1, machine.reg_a, isOverflowed);
  machine.jan(make_cmd(cmd_ja, 27));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jaz_not_jump_if_ra_negative) {
  set_value(-1, machine.reg_a, isOverflowed);
  machine.jaz(make_cmd(cmd_ja, 28));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jaz_jump_if_ra_zero) {
  set_value(0, machine.reg_a, isOverflowed);
  machine.jaz(make_cmd(cmd_ja, 29));
  
  EXPECT_EQ(29, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jaz_not_jump_if_ra_positive) {
  set_value(1, machine.reg_a, isOverflowed);
  machine.jaz(make_cmd(cmd_ja, 30));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jap_not_jump_if_ra_negative) {
  set_value(-1, machine.reg_a, isOverflowed);
  machine.jap(make_cmd(cmd_ja, 31));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jap_not_jump_if_ra_zero) {
  set_value(0, machine.reg_a, isOverflowed);
  machine.jap(make_cmd(cmd_ja, 32));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jap_jump_if_ra_positive) {
  set_value(1, machine.reg_a, isOverflowed);
  machine.jap(make_cmd(cmd_ja, 33));
  
  EXPECT_EQ(33, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jann_not_jump_if_ra_negative) {
  set_value(-1, machine.reg_a, isOverflowed);
  machine.jann(make_cmd(cmd_ja, 34));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, jann_jump_if_ra_zero) {
  set_value(0, machine.reg_a, isOverflowed);
  machine.jann(make_cmd(cmd_ja, 35));
  
  EXPECT_EQ(35, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, jann_jump_if_ra_positive) {
  set_value(1, machine.reg_a, isOverflowed);
  machine.jann(make_cmd(cmd_ja, 36));
  
  EXPECT_EQ(36, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, janz_jump_if_ra_negative) {
  set_value(-1, machine.reg_a, isOverflowed);
  machine.janz(make_cmd(cmd_ja, 37));
  
  EXPECT_EQ(37, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, janz_not_jump_if_ra_zero) {
  set_value(0, machine.reg_a, isOverflowed);
  machine.janz(make_cmd(cmd_ja, 38));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

TEST_F(MixMachineTestSuite, janz_jump_if_ra_positive) {
  set_value(1, machine.reg_a, isOverflowed);
  machine.janz(make_cmd(cmd_ja, 39));
  
  EXPECT_EQ(39, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, janp_jump_if_ra_negative) {
  set_value(-1, machine.reg_a, isOverflowed);
  machine.janp(make_cmd(cmd_ja, 40));
  
  EXPECT_EQ(40, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, janp_jump_if_ra_zero) {
  set_value(0, machine.reg_a, isOverflowed);
  machine.janp(make_cmd(cmd_ja, 41));
  
  EXPECT_EQ(41, get_next_instruction_address());
}

TEST_F(MixMachineTestSuite, janp_not_jump_if_ra_positive) {
  set_value(1, machine.reg_a, isOverflowed);
  machine.janp(make_cmd(cmd_ja, 42));
  
  EXPECT_TRUE(is_next_instruction_address_unchanged());
}

}

