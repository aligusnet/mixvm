#ifndef MIX_MACHINE_H
#define MIX_MACHINE_H

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
typedef void (Machine::*do_statement)(const Word &command);

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
  do_statement *get_statement(const Word &data);
  void nothing(const Word &data);

  void nop(const Word &data); // 0
  void add(const Word &data); // 1
  void sub(const Word &data); // 2
  void mul(const Word &data); // 3
  void div(const Word &data); // 4
  void hlt(const Word &data); // 5

  void lda(const Word &data); // 8
  void ld1(const Word &data); // 9
  void ld2(const Word &data); // 10
  void ld3(const Word &data); // 11
  void ld4(const Word &data); // 12
  void ld5(const Word &data); // 13
  void ld6(const Word &data); // 14
  void ldx(const Word &data); // 15

  void ldan(const Word &data); // 16
  void ld1n(const Word &data); // 17
  void ld2n(const Word &data); // 18
  void ld3n(const Word &data); // 19
  void ld4n(const Word &data); // 20
  void ld5n(const Word &data); // 21
  void ld6n(const Word &data); // 22
  void ldxn(const Word &data); // 23
  void sta(const Word &data);  // 24
  void st1(const Word &data);  // 25
  void st2(const Word &data);  // 26
  void st3(const Word &data);  // 27
  void st4(const Word &data);  // 28
  void st5(const Word &data);  // 29
  void st6(const Word &data);  // 30
  void stx(const Word &data);  // 31
  void stj(const Word &data);  // 32
  void stz(const Word &data);  // 33

  void jump(const Word &data); // 39
  void jmp(const Word &data);  // 39, 0
  void jsj(const Word &data);  // 39, 1
  void jov(const Word &data);  // 39, 2
  void jnov(const Word &data); // 39, 3
  void jl(const Word &data);   // 39, 4
  void je(const Word &data);   // 39, 5
  void jg(const Word &data);   // 39, 6
  void jge(const Word &data);  // 39, 7
  void jne(const Word &data);  // 39, 8
  void jle(const Word &data);  // 39, 9

  void ja(const Word &data);   // 40
  void jan(const Word &data);  // 40, 0
  void jaz(const Word &data);  // 40, 1
  void jap(const Word &data);  // 40, 2
  void jann(const Word &data); // 40, 3
  void janz(const Word &data); // 40, 4
  void janp(const Word &data); // 40, 5

  void j1(const Word &data);   // 41
  void j1n(const Word &data);  // 41, 0
  void j1z(const Word &data);  // 41, 1
  void j1p(const Word &data);  // 41, 2
  void j1nn(const Word &data); // 41, 3
  void j1nz(const Word &data); // 41, 4
  void j1np(const Word &data); // 41, 5

  void j2(const Word &data);   // 42
  void j2n(const Word &data);  // 42, 0
  void j2z(const Word &data);  // 42, 1
  void j2p(const Word &data);  // 42, 2
  void j2nn(const Word &data); // 42, 3
  void j2nz(const Word &data); // 42, 4
  void j2np(const Word &data); // 42, 5

  void j3(const Word &data);   // 43
  void j3n(const Word &data);  // 43, 0
  void j3z(const Word &data);  // 43, 1
  void j3p(const Word &data);  // 43, 2
  void j3nn(const Word &data); // 43, 3
  void j3nz(const Word &data); // 43, 4
  void j3np(const Word &data); // 43, 5

  void j4(const Word &data);   // 44
  void j4n(const Word &data);  // 44, 0
  void j4z(const Word &data);  // 44, 1
  void j4p(const Word &data);  // 44, 2
  void j4nn(const Word &data); // 44, 3
  void j4nz(const Word &data); // 44, 4
  void j4np(const Word &data); // 44, 5

  void j5(const Word &data);   // 45
  void j5n(const Word &data);  // 45, 0
  void j5z(const Word &data);  // 45, 1
  void j5p(const Word &data);  // 45, 2
  void j5nn(const Word &data); // 45, 3
  void j5nz(const Word &data); // 45, 4
  void j5np(const Word &data); // 45, 5

  void j6(const Word &data);   // 46
  void j6n(const Word &data);  // 46, 0
  void j6z(const Word &data);  // 46, 1
  void j6p(const Word &data);  // 46, 2
  void j6nn(const Word &data); // 46, 3
  void j6nz(const Word &data); // 46, 4
  void j6np(const Word &data); // 46, 5

  void jx(const Word &data);   // 47
  void jxn(const Word &data);  // 47, 0
  void jxz(const Word &data);  // 47, 1
  void jxp(const Word &data);  // 47, 2
  void jxnn(const Word &data); // 47, 3
  void jxnz(const Word &data); // 47, 4
  void jxnp(const Word &data); // 47, 5

  void ena(const Word &data); // 48
  void en1(const Word &data); // 49
  void en2(const Word &data); // 50
  void en3(const Word &data); // 51
  void en4(const Word &data); // 52
  void en5(const Word &data); // 53
  void en6(const Word &data); // 54
  void enx(const Word &data); // 55

  void enta(const Word &data); // 48, 2
  void ent1(const Word &data); // 49, 2
  void ent2(const Word &data); // 50, 2
  void ent3(const Word &data); // 51, 2
  void ent4(const Word &data); // 52, 2
  void ent5(const Word &data); // 53, 2
  void ent6(const Word &data); // 54, 2
  void entx(const Word &data); // 55, 2

  void enna(const Word &data); // 48, 3
  void enn1(const Word &data); // 49, 3
  void enn2(const Word &data); // 50, 3
  void enn3(const Word &data); // 51, 3
  void enn4(const Word &data); // 52, 3
  void enn5(const Word &data); // 53, 3
  void enn6(const Word &data); // 54, 3
  void ennx(const Word &data); // 55, 3

  void cmpa(const Word &data); // 56
  void cmp1(const Word &data); // 57
  void cmp2(const Word &data); // 58
  void cmp3(const Word &data); // 59
  void cmp4(const Word &data); // 60
  void cmp5(const Word &data); // 61
  void cmp6(const Word &data); // 62
  void cmpx(const Word &data); // 63

  void run(short initial_address);

  unsigned short extract_address(const Word &instruction) const;

  void load_big_register(big_register *reg, const Word &instruction) const;
  void load_index_register(int index, const Word &instruction);
  void load_register_negative(big_register *reg, const Word &instruction) const;
  void load_index_register_negative(int index, const Word &instruction);

  void store_big_register(big_register reg, const Word &instruction);
  void store_small_register(const small_register &reg, const Word &instruction);
  void store_index_register(int index, const Word &instruction);
};

} // namespace mix

#endif // MIX_MACHINE_H
