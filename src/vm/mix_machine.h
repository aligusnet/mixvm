#ifndef MIX_MACHINE_H
#define MIX_MACHINE_H

#include "mix_instruction.h"
#include "mix_small_word.h"
#include "mix_word.h"

#include <array>

namespace mix {
enum compare_t { cmp_less = -1, cmp_equal, cmp_greater };

enum commands_t {
  cmd_nop = 0,
  cmd_add,
  cmd_sub,
  cmd_mul,
  cmd_div,
  cmd_hlt = 5,
  cmd_shift,
  cmd_sla = cmd_shift,
  cmd_sra = cmd_shift,
  cmd_slax = cmd_shift,
  cmd_srax = cmd_shift,
  cmd_slc = cmd_shift,
  cmd_src = cmd_shift,
  cmd_move,
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
  cmd_inca = cmd_enta,
  cmd_inc1 = cmd_ent1,
  cmd_inc2 = cmd_ent2,
  cmd_inc3 = cmd_ent3,
  cmd_inc4 = cmd_ent4,
  cmd_inc5 = cmd_ent5,
  cmd_inc6 = cmd_ent6,
  cmd_incx = cmd_entx,
  cmd_deca = cmd_enta,
  cmd_dec1 = cmd_ent1,
  cmd_dec2 = cmd_ent2,
  cmd_dec3 = cmd_ent3,
  cmd_dec4 = cmd_ent4,
  cmd_dec5 = cmd_ent5,
  cmd_dec6 = cmd_ent6,
  cmd_decx = cmd_entx,
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
typedef void (Machine::*do_statement)(Instruction instruction);

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

  std::array<Word, MEMORY_WORDS> memory;

  Machine();
  void print_state(std::ostream &os);
  do_statement *get_statement(Instruction instruction);
  void nothing(Instruction instruction);

  void nop(Instruction instruction); // 0
  void add(Instruction instruction); // 1
  void sub(Instruction instruction); // 2
  void mul(Instruction instruction); // 3
  void div(Instruction instruction); // 4
  void hlt(Instruction instruction); // 5
  void shift(Instruction instruction); // 6
  void sla(Instruction instruction);   // 6, 0
  void sra(Instruction instruction);   // 6, 1
  void slax(Instruction instruction);  // 6, 2
  void srax(Instruction instruction);  // 6, 3
  void slc(Instruction instruction);   // 6, 4
  void src(Instruction instruction);   // 6, 5
  void move(Instruction instruction);  // 7

  void lda(Instruction instruction); // 8
  void ld1(Instruction instruction); // 9
  void ld2(Instruction instruction); // 10
  void ld3(Instruction instruction); // 11
  void ld4(Instruction instruction); // 12
  void ld5(Instruction instruction); // 13
  void ld6(Instruction instruction); // 14
  void ldx(Instruction instruction); // 15

  void ldan(Instruction instruction); // 16
  void ld1n(Instruction instruction); // 17
  void ld2n(Instruction instruction); // 18
  void ld3n(Instruction instruction); // 19
  void ld4n(Instruction instruction); // 20
  void ld5n(Instruction instruction); // 21
  void ld6n(Instruction instruction); // 22
  void ldxn(Instruction instruction); // 23
  void sta(Instruction instruction);  // 24
  void st1(Instruction instruction);  // 25
  void st2(Instruction instruction);  // 26
  void st3(Instruction instruction);  // 27
  void st4(Instruction instruction);  // 28
  void st5(Instruction instruction);  // 29
  void st6(Instruction instruction);  // 30
  void stx(Instruction instruction);  // 31
  void stj(Instruction instruction);  // 32
  void stz(Instruction instruction);  // 33

  void jump(Instruction instruction); // 39
  void jmp(Instruction instruction);  // 39, 0
  void jsj(Instruction instruction);  // 39, 1
  void jov(Instruction instruction);  // 39, 2
  void jnov(Instruction instruction); // 39, 3
  void jl(Instruction instruction);   // 39, 4
  void je(Instruction instruction);   // 39, 5
  void jg(Instruction instruction);   // 39, 6
  void jge(Instruction instruction);  // 39, 7
  void jne(Instruction instruction);  // 39, 8
  void jle(Instruction instruction);  // 39, 9

  void ja(Instruction instruction);   // 40
  void jan(Instruction instruction);  // 40, 0
  void jaz(Instruction instruction);  // 40, 1
  void jap(Instruction instruction);  // 40, 2
  void jann(Instruction instruction); // 40, 3
  void janz(Instruction instruction); // 40, 4
  void janp(Instruction instruction); // 40, 5

  void j1(Instruction instruction);   // 41
  void j1n(Instruction instruction);  // 41, 0
  void j1z(Instruction instruction);  // 41, 1
  void j1p(Instruction instruction);  // 41, 2
  void j1nn(Instruction instruction); // 41, 3
  void j1nz(Instruction instruction); // 41, 4
  void j1np(Instruction instruction); // 41, 5

  void j2(Instruction instruction);   // 42
  void j2n(Instruction instruction);  // 42, 0
  void j2z(Instruction instruction);  // 42, 1
  void j2p(Instruction instruction);  // 42, 2
  void j2nn(Instruction instruction); // 42, 3
  void j2nz(Instruction instruction); // 42, 4
  void j2np(Instruction instruction); // 42, 5

  void j3(Instruction instruction);   // 43
  void j3n(Instruction instruction);  // 43, 0
  void j3z(Instruction instruction);  // 43, 1
  void j3p(Instruction instruction);  // 43, 2
  void j3nn(Instruction instruction); // 43, 3
  void j3nz(Instruction instruction); // 43, 4
  void j3np(Instruction instruction); // 43, 5

  void j4(Instruction instruction);   // 44
  void j4n(Instruction instruction);  // 44, 0
  void j4z(Instruction instruction);  // 44, 1
  void j4p(Instruction instruction);  // 44, 2
  void j4nn(Instruction instruction); // 44, 3
  void j4nz(Instruction instruction); // 44, 4
  void j4np(Instruction instruction); // 44, 5

  void j5(Instruction instruction);   // 45
  void j5n(Instruction instruction);  // 45, 0
  void j5z(Instruction instruction);  // 45, 1
  void j5p(Instruction instruction);  // 45, 2
  void j5nn(Instruction instruction); // 45, 3
  void j5nz(Instruction instruction); // 45, 4
  void j5np(Instruction instruction); // 45, 5

  void j6(Instruction instruction);   // 46
  void j6n(Instruction instruction);  // 46, 0
  void j6z(Instruction instruction);  // 46, 1
  void j6p(Instruction instruction);  // 46, 2
  void j6nn(Instruction instruction); // 46, 3
  void j6nz(Instruction instruction); // 46, 4
  void j6np(Instruction instruction); // 46, 5

  void jx(Instruction instruction);   // 47
  void jxn(Instruction instruction);  // 47, 0
  void jxz(Instruction instruction);  // 47, 1
  void jxp(Instruction instruction);  // 47, 2
  void jxnn(Instruction instruction); // 47, 3
  void jxnz(Instruction instruction); // 47, 4
  void jxnp(Instruction instruction); // 47, 5

  void ena(Instruction instruction); // 48
  void en1(Instruction instruction); // 49
  void en2(Instruction instruction); // 50
  void en3(Instruction instruction); // 51
  void en4(Instruction instruction); // 52
  void en5(Instruction instruction); // 53
  void en6(Instruction instruction); // 54
  void enx(Instruction instruction); // 55

  void enta(Instruction instruction); // 48, 2
  void ent1(Instruction instruction); // 49, 2
  void ent2(Instruction instruction); // 50, 2
  void ent3(Instruction instruction); // 51, 2
  void ent4(Instruction instruction); // 52, 2
  void ent5(Instruction instruction); // 53, 2
  void ent6(Instruction instruction); // 54, 2
  void entx(Instruction instruction); // 55, 2

  void enna(Instruction instruction); // 48, 3
  void enn1(Instruction instruction); // 49, 3
  void enn2(Instruction instruction); // 50, 3
  void enn3(Instruction instruction); // 51, 3
  void enn4(Instruction instruction); // 52, 3
  void enn5(Instruction instruction); // 53, 3
  void enn6(Instruction instruction); // 54, 3
  void ennx(Instruction instruction); // 55, 3

  void inca(Instruction instruction); // 48, 0
  void inc1(Instruction instruction); // 49, 0
  void inc2(Instruction instruction); // 50, 0
  void inc3(Instruction instruction); // 51, 0
  void inc4(Instruction instruction); // 52, 0
  void inc5(Instruction instruction); // 53, 0
  void inc6(Instruction instruction); // 54, 0
  void incx(Instruction instruction); // 55, 0

  void deca(Instruction instruction); // 48, 1
  void dec1(Instruction instruction); // 49, 1
  void dec2(Instruction instruction); // 50, 1
  void dec3(Instruction instruction); // 51, 1
  void dec4(Instruction instruction); // 52, 1
  void dec5(Instruction instruction); // 53, 1
  void dec6(Instruction instruction); // 54, 1
  void decx(Instruction instruction); // 55, 1

  void cmpa(Instruction instruction); // 56
  void cmp1(Instruction instruction); // 57
  void cmp2(Instruction instruction); // 58
  void cmp3(Instruction instruction); // 59
  void cmp4(Instruction instruction); // 60
  void cmp5(Instruction instruction); // 61
  void cmp6(Instruction instruction); // 62
  void cmpx(Instruction instruction); // 63

  void run(short initial_address);

private:
  void execute_instruction(Instruction instruction);
  value_type get_memory_value(Instruction instruction) const;
  unsigned short extract_address(Instruction instruction) const;

  void load_big_register(big_register *reg, Instruction instruction) const;
  void load_index_register(int index, Instruction instruction);
  void load_register_negative(big_register *reg, Instruction instruction) const;
  void load_index_register_negative(int index, Instruction instruction);

  void store_big_register(big_register reg, Instruction instruction);
  void store_small_register(const small_register &reg, Instruction instruction);
  void store_index_register(int index, Instruction instruction);

  void unconditionally_jump(Instruction instruction);

  void jump_if_index_register_negative(byte index, Instruction instruction);
  void jump_if_index_register_zero(byte index, Instruction instruction);
  void jump_if_index_register_positive(byte index, Instruction instruction);
  void jump_if_index_register_non_negative(byte index, Instruction instruction);
  void jump_if_index_register_non_zero(byte index, Instruction instruction);
  void jump_if_index_register_non_positive(byte index, Instruction instruction);

  template <typename Register> void jump_if_negative(const Register &reg, Instruction instruction);
  template <typename Register> void jump_if_zero(const Register &reg, Instruction instruction);
  template <typename Register> void jump_if_positive(const Register &reg, Instruction instruction);
  template <typename Register> void jump_if_non_negative(const Register &reg, Instruction instruction);
  template <typename Register> void jump_if_non_zero(const Register &reg, Instruction instruction);
  template <typename Register> void jump_if_non_positive(const Register &reg, Instruction instruction);

  template <typename Register> void transfer_address_to_register(Register *reg, Instruction instruction);
  void transfer_address_to_index_register(byte index, Instruction instruction);
  template <typename Register> void transfer_negative_address_to_register(Register *reg, Instruction instruction);
  void transfer_negative_address_to_index_register(byte index, Instruction instruction);

  template <typename Register> void increment_register(Register *reg);
  void increment_index_register(byte index);
  template <typename Register> void decrement_register(Register *reg);
  void decrement_index_register(byte index);

  template <typename Register> void compare_register_and_memory(const Register &reg, Instruction instruction);
  void compare_index_register_and_memory(byte index, Instruction instruction);
  static compare_t compare(value_type lhs, value_type rhs);
};

} // namespace mix

#endif // MIX_MACHINE_H
