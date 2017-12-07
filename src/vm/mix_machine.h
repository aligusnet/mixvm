#ifndef MIX_MACHINE_H
#define MIX_MACHINE_H

#include "mix_instruction.h"
#include "mix_small_word.h"
#include "mix_word.h"

namespace mix {
enum compare_t { cmp_less = -1, cmp_equal, cmp_greater };

enum commands_t {
  cmd_nop = 0,
  cmd_add,
  cmd_sub,
  cmd_mul,
  cmd_div,
  cmd_hlt = 5,
  cmd_lda = 8,
  cmd_ld1,
  cmd_ld2 = 10,
  cmd_ld3,
  cmd_ld4,
  cmd_ld5,
  cmd_ld6,
  cmd_ldx,
  cmd_ldan,
  cmd_ld1n,
  cmd_ld2n,
  cmd_ld3n,
  cmd_ld4n = 20,
  cmd_ld5n,
  cmd_ld6n,
  cmd_ldxn,
  cmd_sta,
  cmd_st1,
  cmd_st2,
  cmd_st3,
  cmd_st4,
  cmd_st5,
  cmd_st6 = 30,
  cmd_stx,
  cmd_stj,
  cmd_stz,
  cmd_jmp = 39,
  cmd_ja = 40,
  cmd_j1,
  cmd_j2,
  cmd_j3,
  cmd_j4,
  cmd_j5,
  cmd_j6,
  cmd_jx = 47,
  cmd_enta = 48,
  cmd_ent1,
  cmd_ent2,
  cmd_ent3,
  cmd_ent4,
  cmd_ent5,
  cmd_ent6,
  cmd_entx,
  cmd_enna = cmd_enta,
  cmd_enn1 = cmd_ent1,
  cmd_enn2 = cmd_ent2,
  cmd_enn3 = cmd_ent3,
  cmd_enn4 = cmd_ent4,
  cmd_enn5 = cmd_ent5,
  cmd_enn6 = cmd_ent6,
  cmd_ennx = cmd_entx,
  cmd_cmpa,
  cmd_cmp1,
  cmd_cmp2,
  cmd_cmp3,
  cmd_cmp4,
  cmd_cmp5,
  cmd_cmp6,
  cmd_cmpx

};

typedef Word big_register;
typedef SmallWord small_register;

struct Machine;
typedef void (Machine::*do_statement)(const Instruction &instruction);

struct Machine {
  static const int SMALL_REGISTERS = 6;
  static const int MEMORY_WORDS = 4000;
  big_register reg_a;
  big_register reg_x;
  small_register reg_i[SMALL_REGISTERS];
  small_register reg_j;
  bool overflow;
  compare_t compare_flag;
  bool halt;

  Word memory[MEMORY_WORDS];

  Machine();
  void print_state(std::ostream &os);
  do_statement *get_statement(const Instruction &instruction);
  void nothing(const Instruction &instruction);

  void nop(const Instruction &instruction); // 0
  void add(const Instruction &instruction); // 1
  void sub(const Instruction &instruction); // 2
  void mul(const Instruction &instruction); // 3
  void div(const Instruction &instruction); // 4
  void hlt(const Instruction &instruction); // 5

  void lda(const Instruction &instruction); // 8
  void ld1(const Instruction &instruction); // 9
  void ld2(const Instruction &instruction); // 10
  void ld3(const Instruction &instruction); // 11
  void ld4(const Instruction &instruction); // 12
  void ld5(const Instruction &instruction); // 13
  void ld6(const Instruction &instruction); // 14
  void ldx(const Instruction &instruction); // 15

  void ldan(const Instruction &instruction); // 16
  void ld1n(const Instruction &instruction); // 17
  void ld2n(const Instruction &instruction); // 18
  void ld3n(const Instruction &instruction); // 19
  void ld4n(const Instruction &instruction); // 20
  void ld5n(const Instruction &instruction); // 21
  void ld6n(const Instruction &instruction); // 22
  void ldxn(const Instruction &instruction); // 23
  void sta(const Instruction &instruction);  // 24
  void st1(const Instruction &instruction);  // 25
  void st2(const Instruction &instruction);  // 26
  void st3(const Instruction &instruction);  // 27
  void st4(const Instruction &instruction);  // 28
  void st5(const Instruction &instruction);  // 29
  void st6(const Instruction &instruction);  // 30
  void stx(const Instruction &instruction);  // 31
  void stj(const Instruction &instruction);  // 32
  void stz(const Instruction &instruction);  // 33

  void jump(const Instruction &instruction); // 39
  void jmp(const Instruction &instruction);  // 39, 0
  void jsj(const Instruction &instruction);  // 39, 1
  void jov(const Instruction &instruction);  // 39, 2
  void jnov(const Instruction &instruction); // 39, 3
  void jl(const Instruction &instruction);   // 39, 4
  void je(const Instruction &instruction);   // 39, 5
  void jg(const Instruction &instruction);   // 39, 6
  void jge(const Instruction &instruction);  // 39, 7
  void jne(const Instruction &instruction);  // 39, 8
  void jle(const Instruction &instruction);  // 39, 9

  void ja(const Instruction &instruction);   // 40
  void jan(const Instruction &instruction);  // 40, 0
  void jaz(const Instruction &instruction);  // 40, 1
  void jap(const Instruction &instruction);  // 40, 2
  void jann(const Instruction &instruction); // 40, 3
  void janz(const Instruction &instruction); // 40, 4
  void janp(const Instruction &instruction); // 40, 5

  void j1(const Instruction &instruction);   // 41
  void j1n(const Instruction &instruction);  // 41, 0
  void j1z(const Instruction &instruction);  // 41, 1
  void j1p(const Instruction &instruction);  // 41, 2
  void j1nn(const Instruction &instruction); // 41, 3
  void j1nz(const Instruction &instruction); // 41, 4
  void j1np(const Instruction &instruction); // 41, 5

  void j2(const Instruction &instruction);   // 42
  void j2n(const Instruction &instruction);  // 42, 0
  void j2z(const Instruction &instruction);  // 42, 1
  void j2p(const Instruction &instruction);  // 42, 2
  void j2nn(const Instruction &instruction); // 42, 3
  void j2nz(const Instruction &instruction); // 42, 4
  void j2np(const Instruction &instruction); // 42, 5

  void j3(const Instruction &instruction);   // 43
  void j3n(const Instruction &instruction);  // 43, 0
  void j3z(const Instruction &instruction);  // 43, 1
  void j3p(const Instruction &instruction);  // 43, 2
  void j3nn(const Instruction &instruction); // 43, 3
  void j3nz(const Instruction &instruction); // 43, 4
  void j3np(const Instruction &instruction); // 43, 5

  void j4(const Instruction &instruction);   // 44
  void j4n(const Instruction &instruction);  // 44, 0
  void j4z(const Instruction &instruction);  // 44, 1
  void j4p(const Instruction &instruction);  // 44, 2
  void j4nn(const Instruction &instruction); // 44, 3
  void j4nz(const Instruction &instruction); // 44, 4
  void j4np(const Instruction &instruction); // 44, 5

  void j5(const Instruction &instruction);   // 45
  void j5n(const Instruction &instruction);  // 45, 0
  void j5z(const Instruction &instruction);  // 45, 1
  void j5p(const Instruction &instruction);  // 45, 2
  void j5nn(const Instruction &instruction); // 45, 3
  void j5nz(const Instruction &instruction); // 45, 4
  void j5np(const Instruction &instruction); // 45, 5

  void j6(const Instruction &instruction);   // 46
  void j6n(const Instruction &instruction);  // 46, 0
  void j6z(const Instruction &instruction);  // 46, 1
  void j6p(const Instruction &instruction);  // 46, 2
  void j6nn(const Instruction &instruction); // 46, 3
  void j6nz(const Instruction &instruction); // 46, 4
  void j6np(const Instruction &instruction); // 46, 5

  void jx(const Instruction &instruction);   // 47
  void jxn(const Instruction &instruction);  // 47, 0
  void jxz(const Instruction &instruction);  // 47, 1
  void jxp(const Instruction &instruction);  // 47, 2
  void jxnn(const Instruction &instruction); // 47, 3
  void jxnz(const Instruction &instruction); // 47, 4
  void jxnp(const Instruction &instruction); // 47, 5

  void ena(const Instruction &instruction); // 48
  void en1(const Instruction &instruction); // 49
  void en2(const Instruction &instruction); // 50
  void en3(const Instruction &instruction); // 51
  void en4(const Instruction &instruction); // 52
  void en5(const Instruction &instruction); // 53
  void en6(const Instruction &instruction); // 54
  void enx(const Instruction &instruction); // 55

  void enta(const Instruction &instruction); // 48, 2
  void ent1(const Instruction &instruction); // 49, 2
  void ent2(const Instruction &instruction); // 50, 2
  void ent3(const Instruction &instruction); // 51, 2
  void ent4(const Instruction &instruction); // 52, 2
  void ent5(const Instruction &instruction); // 53, 2
  void ent6(const Instruction &instruction); // 54, 2
  void entx(const Instruction &instruction); // 55, 2

  void enna(const Instruction &instruction); // 48, 3
  void enn1(const Instruction &instruction); // 49, 3
  void enn2(const Instruction &instruction); // 50, 3
  void enn3(const Instruction &instruction); // 51, 3
  void enn4(const Instruction &instruction); // 52, 3
  void enn5(const Instruction &instruction); // 53, 3
  void enn6(const Instruction &instruction); // 54, 3
  void ennx(const Instruction &instruction); // 55, 3

  void cmpa(const Instruction &instruction); // 56
  void cmp1(const Instruction &instruction); // 57
  void cmp2(const Instruction &instruction); // 58
  void cmp3(const Instruction &instruction); // 59
  void cmp4(const Instruction &instruction); // 60
  void cmp5(const Instruction &instruction); // 61
  void cmp6(const Instruction &instruction); // 62
  void cmpx(const Instruction &instruction); // 63

  void run(short initial_address);

private:
  void execute_instruction(const Instruction &instruction);
  value_type get_memory_value(const Instruction &instruction) const;
  unsigned short extract_address(const Instruction &instruction) const;

  void load_big_register(big_register *reg, const Instruction &instruction) const;
  void load_index_register(int index, const Instruction &instruction);
  void load_register_negative(big_register *reg, const Instruction &instruction) const;
  void load_index_register_negative(int index, const Instruction &instruction);

  void store_big_register(big_register reg, const Instruction &instruction);
  void store_small_register(const small_register &reg, const Instruction &instruction);
  void store_index_register(int index, const Instruction &instruction);

  void unconditionally_jump(const Instruction &instruction);

  void jump_if_index_register_negative(byte index, const Instruction &instruction);
  void jump_if_index_register_zero(byte index, const Instruction &instruction);
  void jump_if_index_register_positive(byte index, const Instruction &instruction);
  void jump_if_index_register_non_negative(byte index, const Instruction &instruction);
  void jump_if_index_register_non_zero(byte index, const Instruction &instruction);
  void jump_if_index_register_non_positive(byte index, const Instruction &instruction);

  template <typename Register> void jump_if_negative(const Register &reg, const Instruction &instruction);
  template <typename Register> void jump_if_zero(const Register &reg, const Instruction &instruction);
  template <typename Register> void jump_if_positive(const Register &reg, const Instruction &instruction);
  template <typename Register> void jump_if_non_negative(const Register &reg, const Instruction &instruction);
  template <typename Register> void jump_if_non_zero(const Register &reg, const Instruction &instruction);
  template <typename Register> void jump_if_non_positive(const Register &reg, const Instruction &instruction);

  template <typename Register> void transfer_address_to_register(Register *reg, const Instruction &instruction);
  void transfer_address_to_index_register(byte index, const Instruction &instruction);
  template <typename Register>
  void transfer_negative_address_to_register(Register *reg, const Instruction &instruction);
  void transfer_negative_address_to_index_register(byte index, const Instruction &instruction);

  template <typename Register> void compare_register_and_memory(const Register &reg, const Instruction &instruction);
  void compare_index_register_and_memory(byte index, const Instruction &instruction);
  static compare_t compare(value_type lhs, value_type rhs);
};

} // namespace mix

#endif // MIX_MACHINE_H
