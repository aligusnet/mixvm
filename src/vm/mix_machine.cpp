#include "mix_machine.h"
#include "mix_long_value.h"

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define LOG_COMMAND_NAME(data)                                                                                         \
  (data).print_instruction(std::cout, __FUNCTION__);                                                                   \
  std::cout << std::endl;

namespace mix {
Machine::Machine() {
  memset(this, 0, sizeof(Machine));
}

void Machine::run(short initial_address) {
  halt = false;
  reg_j.set_address(initial_address);
  while (!halt) {
    const auto &instruction = memory[reg_j.get_value()];
    overflow = reg_j.inc();
    execute_instruction(instruction);
  }
}

void Machine::nothing(const Word &data) {
  LOG_COMMAND_NAME(data)
}

void Machine::nop(const Word &data) { // 0
  LOG_COMMAND_NAME(data)
}

void Machine::add(const Word &data) { // 1
  LOG_COMMAND_NAME(data)

  const auto m = get_memory_value(data);
  const auto r = reg_a.get_value();
  overflow = reg_a.set_value(r + m);
}

void Machine::sub(const Word &data) { // 2
  LOG_COMMAND_NAME(data)

  const auto m = get_memory_value(data);
  const auto r = reg_a.get_value();
  overflow = reg_a.set_value(r - m);
}

void Machine::mul(const Word &data) { // 3
  LOG_COMMAND_NAME(data)

  long_value_type m = get_memory_value(data);
  long_value_type r = reg_a.get_value();
  overflow = LongValue::set(r * m, reg_a, reg_x);
}

void Machine::div(const Word &data) { // 4
  LOG_COMMAND_NAME(data)

  value_type val_reg_a = reg_a.get_value();
  value_type val_mem = get_memory_value(data);

  if (abs(val_reg_a) < abs(val_mem)) {
    long_value_type val = LongValue::get(reg_a, reg_x);
    long_value_type quotient = val / val_mem;
    value_type remainder = val - quotient * val_mem;
    overflow = reg_x.set_value(remainder);
    reg_x.set_sign(reg_a.get_sign());
    overflow = reg_a.set_value(quotient);
  } else {
    overflow = true;
  }
}

void Machine::hlt(const Word &data) { // 5
  LOG_COMMAND_NAME(data)
  halt = true;
}

void Machine::lda(const Word &data) { // 8
  LOG_COMMAND_NAME(data)
  load_big_register(&reg_a, data);
}

void Machine::ldx(const Word &data) { // 15
  LOG_COMMAND_NAME(data)
  load_big_register(&reg_x, data);
}

void Machine::ld1(const Word &data) { // 9
  LOG_COMMAND_NAME(data)
  load_index_register(1, data);
}

void Machine::ld2(const Word &data) { // 10
  LOG_COMMAND_NAME(data)
  load_index_register(2, data);
}

void Machine::ld3(const Word &data) { // 11
  LOG_COMMAND_NAME(data)
  load_index_register(3, data);
}

void Machine::ld4(const Word &data) { // 12
  LOG_COMMAND_NAME(data)
  load_index_register(4, data);
}

void Machine::ld5(const Word &data) { // 13
  LOG_COMMAND_NAME(data)
  load_index_register(5, data);
}

void Machine::ld6(const Word &data) { // 14
  LOG_COMMAND_NAME(data)
  load_index_register(6, data);
}

void Machine::ldan(const Word &data) { // 16
  LOG_COMMAND_NAME(data)
  load_register_negative(&reg_a, data);
}

void Machine::ldxn(const Word &data) { // 23
  LOG_COMMAND_NAME(data)
  load_register_negative(&reg_x, data);
}

void Machine::ld1n(const Word &data) { // 17
  LOG_COMMAND_NAME(data)
  load_index_register_negative(1, data);
}

void Machine::ld2n(const Word &data) { // 18
  LOG_COMMAND_NAME(data)
  load_index_register_negative(2, data);
}

void Machine::ld3n(const Word &data) { // 19
  LOG_COMMAND_NAME(data)
  load_index_register_negative(3, data);
}

void Machine::ld4n(const Word &data) { // 20
  LOG_COMMAND_NAME(data)
  load_index_register_negative(4, data);
}

void Machine::ld5n(const Word &data) { // 21
  LOG_COMMAND_NAME(data)
  load_index_register_negative(5, data);
}

void Machine::ld6n(const Word &data) { // 22
  LOG_COMMAND_NAME(data)
  load_index_register_negative(6, data);
}

void Machine::sta(const Word &data) { // 24
  LOG_COMMAND_NAME(data)
  store_big_register(reg_a, data);
}

void Machine::stx(const Word &data) { // 31
  LOG_COMMAND_NAME(data)
  store_big_register(reg_x, data);
}

void Machine::st1(const Word &data) { // 25
  LOG_COMMAND_NAME(data)
  store_index_register(1, data);
}

void Machine::st2(const Word &data) { // 26
  LOG_COMMAND_NAME(data)
  store_index_register(2, data);
}

void Machine::st3(const Word &data) { // 27
  LOG_COMMAND_NAME(data)
  store_index_register(3, data);
}

void Machine::st4(const Word &data) { // 28
  LOG_COMMAND_NAME(data)
  store_index_register(4, data);
}

void Machine::st5(const Word &data) { // 29
  LOG_COMMAND_NAME(data)
  store_index_register(5, data);
}

void Machine::st6(const Word &data) { // 30
  LOG_COMMAND_NAME(data)
  store_index_register(6, data);
}

void Machine::stj(const Word &data) { // 32
  LOG_COMMAND_NAME(data)
  store_small_register(reg_j, data);
}

void Machine::stz(const Word &data) { // 33
  LOG_COMMAND_NAME(data)

  int addr = extract_address(data);
  Word zero;
  memset(&zero, 0, sizeof(zero));
  memory[addr].set_value(zero, data.get_field_specification());
}

void Machine::jump(const Word &data) { // 39
  switch (data.get_modification()) {
  case 0:
    jmp(data);
    break;
  case 1:
    jsj(data);
    break;
  case 2:
    jov(data);
    break;
  case 3:
    jnov(data);
    break;
  case 4:
    jl(data);
    break;
  case 5:
    je(data);
    break;
  case 6:
    jg(data);
    break;
  case 7:
    jge(data);
    break;
  case 8:
    jne(data);
    break;
  case 9:
    jle(data);
    break;
  };
}

void Machine::jmp(const Word &data) { // 39, 0
  LOG_COMMAND_NAME(data)
  unconditionally_jump(data);
}

void Machine::jsj(const Word &instruction) { // 39, 1
  LOG_COMMAND_NAME(instruction)

  // "The next instruction is taken from M"
  // "<...> the contents of rJ are unchanged"

  // I guess this means that
  // the next instruction is executed from memory location M

  const auto address = extract_address(instruction);
  const auto &next_instruction = memory[address];
  execute_instruction(next_instruction);
}

void Machine::jov(const Word &data) { // 39, 2
  LOG_COMMAND_NAME(data)

  if (overflow) {
    overflow = false;
    unconditionally_jump(data);
  }
}

void Machine::jnov(const Word &data) { // 39, 3
  LOG_COMMAND_NAME(data)

  if (!overflow) {
    unconditionally_jump(data);
  }
}

void Machine::jl(const Word &data) { // 39, 4
  LOG_COMMAND_NAME(data)

  if (compare_flag == cmp_less) {
    unconditionally_jump(data);
  }
}

void Machine::je(const Word &data) { // 39, 5
  LOG_COMMAND_NAME(data)

  if (compare_flag == cmp_equal) {
    unconditionally_jump(data);
  }
}

void Machine::jg(const Word &data) { // 39, 6
  LOG_COMMAND_NAME(data)

  if (compare_flag == cmp_greater) {
    unconditionally_jump(data);
  }
}

void Machine::jge(const Word &data) { // 39, 7
  LOG_COMMAND_NAME(data)

  if (compare_flag != cmp_less) {
    unconditionally_jump(data);
  }
}

void Machine::jne(const Word &data) { // 39, 8
  LOG_COMMAND_NAME(data)

  if (compare_flag != cmp_equal) {
    unconditionally_jump(data);
  }
}

void Machine::jle(const Word &data) { // 39, 9
  LOG_COMMAND_NAME(data)

  if (compare_flag != cmp_greater) {
    unconditionally_jump(data);
  }
}

void Machine::ja(const Word &data) { // 40
  switch (data.get_modification()) {
  case 0:
    jan(data);
    break;
  case 1:
    jaz(data);
    break;
  case 2:
    jap(data);
    break;
  case 3:
    jann(data);
    break;
  case 4:
    janz(data);
    break;
  case 5:
    janp(data);
    break;
  };
}

void Machine::jan(const Word &data) { // 40, 0
  LOG_COMMAND_NAME(data)
  jump_if_negative(reg_a, data);
}

void Machine::jaz(const Word &data) { // 40, 1
  LOG_COMMAND_NAME(data)
  jump_if_zero(reg_a, data);
}

void Machine::jap(const Word &data) { // 40, 2
  LOG_COMMAND_NAME(data)
  jump_if_positive(reg_a, data);
}

void Machine::jann(const Word &data) { // 40, 3
  LOG_COMMAND_NAME(data)
  jump_if_non_negative(reg_a, data);
}

void Machine::janz(const Word &data) { // 40, 4
  LOG_COMMAND_NAME(data)
  jump_if_non_zero(reg_a, data);
}

void Machine::janp(const Word &data) { // 40, 5
  LOG_COMMAND_NAME(data)
  jump_if_non_positive(reg_a, data);
}

void Machine::j1(const Word &data) { // 41
  switch (data.get_modification()) {
  case 0:
    j1n(data);
    break;
  case 1:
    j1z(data);
    break;
  case 2:
    j1p(data);
    break;
  case 3:
    j1nn(data);
    break;
  case 4:
    j1nz(data);
    break;
  case 5:
    j1np(data);
    break;
  };
}

void Machine::j1n(const Word &data) { // 41, 0
  LOG_COMMAND_NAME(data)
  jump_if_index_register_negative(1, data);
}

void Machine::j1z(const Word &data) { // 41, 1
  LOG_COMMAND_NAME(data)
  jump_if_index_register_zero(1, data);
}

void Machine::j1p(const Word &data) { // 41, 2
  LOG_COMMAND_NAME(data)
  jump_if_index_register_positive(1, data);
}

void Machine::j1nn(const Word &data) { // 41, 3
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_negative(1, data);
}

void Machine::j1nz(const Word &data) { // 41, 4
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_zero(1, data);
}

void Machine::j1np(const Word &data) { // 41, 5
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_positive(1, data);
}

void Machine::j2(const Word &data) { // 41
  switch (data.get_modification()) {
  case 0:
    j2n(data);
    break;
  case 1:
    j2z(data);
    break;
  case 2:
    j2p(data);
    break;
  case 3:
    j2nn(data);
    break;
  case 4:
    j2nz(data);
    break;
  case 5:
    j2np(data);
    break;
  };
}

void Machine::j2n(const Word &data) { // 42, 0
  LOG_COMMAND_NAME(data)
  jump_if_index_register_negative(2, data);
}

void Machine::j2z(const Word &data) { // 42, 1
  LOG_COMMAND_NAME(data)
  jump_if_index_register_zero(2, data);
}

void Machine::j2p(const Word &data) { // 42, 2
  LOG_COMMAND_NAME(data)
  jump_if_index_register_positive(2, data);
}

void Machine::j2nn(const Word &data) { // 42, 3
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_negative(2, data);
}

void Machine::j2nz(const Word &data) { // 42, 4
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_zero(2, data);
}

void Machine::j2np(const Word &data) { // 42, 5
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_positive(2, data);
}

void Machine::j3(const Word &data) { // 43
  switch (data.get_modification()) {
  case 0:
    j3n(data);
    break;
  case 1:
    j3z(data);
    break;
  case 2:
    j3p(data);
    break;
  case 3:
    j3nn(data);
    break;
  case 4:
    j3nz(data);
    break;
  case 5:
    j3np(data);
    break;
  };
}

void Machine::j3n(const Word &data) { // 43, 0
  LOG_COMMAND_NAME(data)
  jump_if_index_register_negative(3, data);
}

void Machine::j3z(const Word &data) { // 43, 1
  LOG_COMMAND_NAME(data)
  jump_if_index_register_zero(3, data);
}

void Machine::j3p(const Word &data) { // 43, 2
  LOG_COMMAND_NAME(data)
  jump_if_index_register_positive(3, data);
}

void Machine::j3nn(const Word &data) { // 43, 3
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_negative(3, data);
}

void Machine::j3nz(const Word &data) { // 43, 4
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_zero(3, data);
}

void Machine::j3np(const Word &data) { // 43, 5
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_positive(3, data);
}

void Machine::j4(const Word &data) { // 44
  switch (data.get_modification()) {
  case 0:
    j4n(data);
    break;
  case 1:
    j4z(data);
    break;
  case 2:
    j4p(data);
    break;
  case 3:
    j4nn(data);
    break;
  case 4:
    j4nz(data);
    break;
  case 5:
    j4np(data);
    break;
  };
}

void Machine::j4n(const Word &data) { // 44, 0
  LOG_COMMAND_NAME(data)
  jump_if_index_register_negative(4, data);
}

void Machine::j4z(const Word &data) { // 44, 1
  LOG_COMMAND_NAME(data)
  jump_if_index_register_zero(4, data);
}

void Machine::j4p(const Word &data) { // 44, 2
  LOG_COMMAND_NAME(data)
  jump_if_index_register_positive(4, data);
}

void Machine::j4nn(const Word &data) { // 44, 3
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_negative(4, data);
}

void Machine::j4nz(const Word &data) { // 44, 4
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_zero(4, data);
}

void Machine::j4np(const Word &data) { // 44, 5
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_positive(4, data);
}

void Machine::j5(const Word &data) { // 45
  switch (data.get_modification()) {
  case 0:
    j5n(data);
    break;
  case 1:
    j5z(data);
    break;
  case 2:
    j5p(data);
    break;
  case 3:
    j5nn(data);
    break;
  case 4:
    j5nz(data);
    break;
  case 5:
    j5np(data);
    break;
  };
}

void Machine::j5n(const Word &data) { // 45, 0
  LOG_COMMAND_NAME(data)
  jump_if_index_register_negative(5, data);
}

void Machine::j5z(const Word &data) { // 45, 1
  LOG_COMMAND_NAME(data)
  jump_if_index_register_zero(5, data);
}

void Machine::j5p(const Word &data) { // 45, 2
  LOG_COMMAND_NAME(data)
  jump_if_index_register_positive(5, data);
}

void Machine::j5nn(const Word &data) { // 45, 3
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_negative(5, data);
}

void Machine::j5nz(const Word &data) { // 45, 4
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_zero(5, data);
}

void Machine::j5np(const Word &data) { // 45, 5
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_positive(5, data);
}

void Machine::j6(const Word &data) { // 46
  switch (data.get_modification()) {
  case 0:
    j6n(data);
    break;
  case 1:
    j6z(data);
    break;
  case 2:
    j6p(data);
    break;
  case 3:
    j6nn(data);
    break;
  case 4:
    j6nz(data);
    break;
  case 5:
    j6np(data);
    break;
  };
}

void Machine::j6n(const Word &data) { // 46, 0
  LOG_COMMAND_NAME(data)
  jump_if_index_register_negative(6, data);
}

void Machine::j6z(const Word &data) { // 46, 1
  LOG_COMMAND_NAME(data)
  jump_if_index_register_zero(6, data);
}

void Machine::j6p(const Word &data) { // 46, 2
  LOG_COMMAND_NAME(data)
  jump_if_index_register_positive(6, data);
}

void Machine::j6nn(const Word &data) { // 46, 3
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_negative(6, data);
}

void Machine::j6nz(const Word &data) { // 46, 4
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_zero(6, data);
}

void Machine::j6np(const Word &data) { // 46, 5
  LOG_COMMAND_NAME(data)
  jump_if_index_register_non_positive(6, data);
}

void Machine::jx(const Word &data) { // 47
  switch (data.get_modification()) {
  case 0:
    jxn(data);
    break;
  case 1:
    jxz(data);
    break;
  case 2:
    jxp(data);
    break;
  case 3:
    jxnn(data);
    break;
  case 4:
    jxnz(data);
    break;
  case 5:
    jxnp(data);
    break;
  };
}

void Machine::jxn(const Word &data) { // 47, 0
  LOG_COMMAND_NAME(data)
  jump_if_negative(reg_x, data);
}

void Machine::jxz(const Word &data) { // 47, 1
  LOG_COMMAND_NAME(data)
  jump_if_zero(reg_x, data);
}

void Machine::jxp(const Word &data) { // 47, 2
  LOG_COMMAND_NAME(data)
  jump_if_positive(reg_x, data);
}

void Machine::jxnn(const Word &data) { // 47, 3
  LOG_COMMAND_NAME(data)
  jump_if_non_negative(reg_x, data);
}

void Machine::jxnz(const Word &data) { // 47, 4
  LOG_COMMAND_NAME(data)
  jump_if_non_zero(reg_x, data);
}

void Machine::jxnp(const Word &data) { // 47, 5
  LOG_COMMAND_NAME(data)
  jump_if_non_positive(reg_x, data);
}

void Machine::ena(const Word &data) { // 48
  switch (data.get_modification()) {
  case 2:
    enta(data);
    break;
  case 3:
    enna(data);
    break;
  default:
    nothing(data);
    break;
  };
}

void Machine::en1(const Word &data) { // 49
  switch (data.get_modification()) {
  case 2:
    ent1(data);
    break;
  case 3:
    enn1(data);
    break;
  default:
    nothing(data);
    break;
  };
}

void Machine::en2(const Word &data) { // 50
  switch (data.get_modification()) {
  case 2:
    ent2(data);
    break;
  case 3:
    enn2(data);
    break;
  default:
    nothing(data);
    break;
  };
}

void Machine::en3(const Word &data) { // 51
  switch (data.get_modification()) {
  case 2:
    ent3(data);
    break;
  case 3:
    enn3(data);
    break;
  default:
    nothing(data);
    break;
  };
}

void Machine::en4(const Word &data) { // 52
  switch (data.get_modification()) {
  case 2:
    ent4(data);
    break;
  case 3:
    enn4(data);
    break;
  default:
    nothing(data);
    break;
  };
}

void Machine::en5(const Word &data) { // 53
  switch (data.get_modification()) {
  case 2:
    ent5(data);
    break;
  case 3:
    enn5(data);
    break;
  default:
    nothing(data);
    break;
  };
}

void Machine::en6(const Word &data) { // 54
  switch (data.get_modification()) {
  case 2:
    ent6(data);
    break;
  case 3:
    enn6(data);
    break;
  default:
    nothing(data);
    break;
  };
}

void Machine::enx(const Word &data) { // 55
  switch (data.get_modification()) {
  case 2:
    entx(data);
    break;
  case 3:
    ennx(data);
    break;
  default:
    nothing(data);
    break;
  };
}

void Machine::enta(const Word &data) { // 48, 2
  LOG_COMMAND_NAME(data)
  transfer_address_to_register(&reg_a, data);
}

void Machine::ent1(const Word &data) { // 49, 2
  LOG_COMMAND_NAME(data)
  transfer_address_to_index_register(1, data);
}

void Machine::ent2(const Word &data) { // 50, 2
  LOG_COMMAND_NAME(data)
  transfer_address_to_index_register(2, data);
}

void Machine::ent3(const Word &data) { // 51, 2
  LOG_COMMAND_NAME(data)
  transfer_address_to_index_register(3, data);
}

void Machine::ent4(const Word &data) { // 52, 2
  LOG_COMMAND_NAME(data)
  transfer_address_to_index_register(4, data);
}

void Machine::ent5(const Word &data) { // 53, 2
  LOG_COMMAND_NAME(data)
  transfer_address_to_index_register(5, data);
}

void Machine::ent6(const Word &data) { // 54, 2
  LOG_COMMAND_NAME(data)
  transfer_address_to_index_register(6, data);
}

void Machine::entx(const Word &data) { // 55, 2
  transfer_address_to_register(&reg_x, data);
}

void Machine::enna(const Word &data) { // 48, 3
  LOG_COMMAND_NAME(data)
  transfer_negative_address_to_register(&reg_a, data);
}

void Machine::enn1(const Word &data) { // 49, 3
  LOG_COMMAND_NAME(data)
  transfer_negative_address_to_index_register(1, data);
}

void Machine::enn2(const Word &data) { // 50, 3
  LOG_COMMAND_NAME(data)
  transfer_negative_address_to_index_register(2, data);
}

void Machine::enn3(const Word &data) { // 51, 3
  LOG_COMMAND_NAME(data)
  transfer_negative_address_to_index_register(3, data);
}

void Machine::enn4(const Word &data) { // 52, 3
  LOG_COMMAND_NAME(data)
  transfer_negative_address_to_index_register(4, data);
}

void Machine::enn5(const Word &data) { // 53, 3
  LOG_COMMAND_NAME(data)
  transfer_negative_address_to_index_register(5, data);
}

void Machine::enn6(const Word &data) { // 54, 3
  LOG_COMMAND_NAME(data)
  transfer_negative_address_to_index_register(6, data);
}

void Machine::ennx(const Word &data) { // 55, 3
  LOG_COMMAND_NAME(data)
  transfer_negative_address_to_register(&reg_x, data);
}

void Machine::cmpa(const Word &data) { // 56
  LOG_COMMAND_NAME(data)
  compare_register_and_memory(reg_a, data);
}

void Machine::cmp1(const Word &data) { // 57
  LOG_COMMAND_NAME(data)
  compare_index_register_and_memory(1, data);
}

void Machine::cmp2(const Word &data) { // 58
  LOG_COMMAND_NAME(data)
  compare_index_register_and_memory(2, data);
}

void Machine::cmp3(const Word &data) { // 59
  LOG_COMMAND_NAME(data)
  compare_index_register_and_memory(3, data);
}

void Machine::cmp4(const Word &data) { // 60
  LOG_COMMAND_NAME(data)
  compare_index_register_and_memory(4, data);
}

void Machine::cmp5(const Word &data) { // 61
  LOG_COMMAND_NAME(data)
  compare_index_register_and_memory(5, data);
}

void Machine::cmp6(const Word &data) { // 62
  LOG_COMMAND_NAME(data)
  compare_index_register_and_memory(6, data);
}

void Machine::cmpx(const Word &data) { // 63
  LOG_COMMAND_NAME(data)
  compare_register_and_memory(reg_x, data);
}

void Machine::execute_instruction(const Word &instruction) {
  do_statement statement = *get_statement(instruction);
  (this->*statement)(instruction);
}

void Machine::load_big_register(big_register *reg, const Word &instruction) const {
  const auto address = extract_address(instruction);
  memset(reg, 0, sizeof(big_register));
  reg->set_value(memory[address], instruction.get_field_specification());
  FieldSpecification fmt = instruction.get_field_specification();
  int nbytes = DATA_BYTES_IN_WORD - fmt.high;
  if (nbytes > 0) {
    reg->right_shift(nbytes);
  }
}

void Machine::load_index_register(int index, const Word &instruction) {
  const auto address = extract_address(instruction);
  value_type val = memory[address].get_value();
  overflow = reg_i[index - 1].set_value(val);
}

void Machine::load_register_negative(big_register *reg, const Word &instruction) const {
  load_big_register(reg, instruction);
  reg->flip_sign();
}

void Machine::load_index_register_negative(int index, const Word &instruction) {
  load_index_register(index, instruction);
  reg_i[index - 1].flip_sign();
}

void Machine::store_big_register(big_register reg, const Word &instruction) {
  FieldSpecification fs = instruction.get_field_specification();
  int nbytes = DATA_BYTES_IN_WORD - fs.high;
  if (nbytes > 0) {
    reg.left_shift(nbytes);
  }

  const auto address = extract_address(instruction);
  memory[address].set_value(reg, fs);
}

void Machine::store_index_register(int index, const Word &instruction) {
  store_small_register(reg_i[index - 1], instruction);
}

void Machine::store_small_register(const small_register &reg, const Word &instruction) {
  const auto address = extract_address(instruction);
  const auto value = reg.get_value();
  overflow = memory[address].set_value(value);
}

void Machine::jump_if_index_register_negative(byte index, const Word &instruction) {
  jump_if_negative(reg_i[index - 1], instruction);
}

void Machine::jump_if_index_register_zero(byte index, const Word &instruction) {
  jump_if_zero(reg_i[index - 1], instruction);
}

void Machine::jump_if_index_register_positive(byte index, const Word &instruction) {
  jump_if_positive(reg_i[index - 1], instruction);
}

void Machine::jump_if_index_register_non_negative(byte index, const Word &instruction) {
  jump_if_non_negative(reg_i[index - 1], instruction);
}

void Machine::jump_if_index_register_non_zero(byte index, const Word &instruction) {
  jump_if_non_zero(reg_i[index - 1], instruction);
}

void Machine::jump_if_index_register_non_positive(byte index, const Word &instruction) {
  jump_if_non_positive(reg_i[index - 1], instruction);
}

template <typename Register> void Machine::jump_if_negative(const Register &reg, const Word &instruction) {
  if (reg.get_sign() == Sign::Negative) {
    unconditionally_jump(instruction);
  }
}

template <typename Register> void Machine::jump_if_zero(const Register &reg, const Word &instruction) {
  const auto val = reg.get_value();
  if (val == 0) {
    unconditionally_jump(instruction);
  }
}

template <typename Register> void Machine::jump_if_positive(const Register &reg, const Word &instruction) {
  const auto val = reg.get_value();
  if (val > 0) {
    unconditionally_jump(instruction);
  }
}

template <typename Register> void Machine::jump_if_non_negative(const Register &reg, const Word &instruction) {
  if (reg.get_sign() != Sign::Negative) {
    unconditionally_jump(instruction);
  }
}

template <typename Register> void Machine::jump_if_non_zero(const Register &reg, const Word &instruction) {
  const auto val = reg.get_value();
  if (val != 0) {
    unconditionally_jump(instruction);
  }
}

template <typename Register> void Machine::jump_if_non_positive(const Register &reg, const Word &instruction) {
  const auto val = reg.get_value();
  if (val <= 0) {
    unconditionally_jump(instruction);
  }
}

void Machine::unconditionally_jump(const Word &instruction) {
  const auto address = extract_address(instruction);
  overflow = reg_j.set_value(address);
}

void Machine::transfer_address_to_index_register(byte index, const Word &instruction) {
  transfer_address_to_register(&reg_i[index - 1], instruction);
}

void Machine::transfer_negative_address_to_index_register(byte index, const Word &instruction) {
  transfer_negative_address_to_register(&reg_i[index - 1], instruction);
}

template <typename Register>
void Machine::transfer_negative_address_to_register(Register *reg, const mix::Word &instruction) {
  transfer_address_to_register(reg, instruction);
  reg->flip_sign();
}

template <typename Register> void Machine::transfer_address_to_register(Register *reg, const Word &instruction) {
  const auto value = extract_address(instruction);
  overflow = reg->set_value(value);
}

void Machine::compare_index_register_and_memory(byte index, const Word &instruction) {
  compare_register_and_memory(reg_i[index - 1], instruction);
}

template <typename Register> void Machine::compare_register_and_memory(const Register &reg, const Word &instruction) {
  const auto lhs = reg.get_value(instruction.get_field_specification());
  const auto rhs = get_memory_value(instruction);
  compare_flag = compare(lhs, rhs);
}

compare_t Machine::compare(value_type lhs, value_type rhs) {
  if (lhs < rhs)
    return cmp_less;
  if (lhs > rhs)
    return cmp_greater;
  return cmp_equal;
}

value_type Machine::get_memory_value(const Word &instruction) const {
  const auto address = extract_address(instruction);
  return memory[address].get_value(instruction.get_field_specification());
}

unsigned short Machine::extract_address(const Word &instruction) const {
  unsigned short address = instruction.get_address();
  int index_specification = instruction.get_specification();
  if (index_specification) {
    address += reg_i[index_specification - 1].get_value();
  }
  return address;
}

do_statement *Machine::get_statement(const Word &data) {
  static do_statement statements[] = {
      &Machine::nop, // 0
      &Machine::add,     &Machine::sub,     &Machine::mul,     &Machine::div,     &Machine::hlt,
      &Machine::nothing, &Machine::nothing, &Machine::lda,     &Machine::ld1,
      &Machine::ld2, // 10
      &Machine::ld3,     &Machine::ld4,     &Machine::ld5,     &Machine::ld6,     &Machine::ldx,
      &Machine::ldan,    &Machine::ld1n,    &Machine::ld2n,    &Machine::ld3n,
      &Machine::ld4n, // 20
      &Machine::ld5n,    &Machine::ld6n,    &Machine::ldxn,    &Machine::sta,     &Machine::st1,
      &Machine::st2,     &Machine::st3,     &Machine::st4,     &Machine::st5,
      &Machine::st6, // 30
      &Machine::stx,     &Machine::stj,     &Machine::stz,     &Machine::nothing, &Machine::nothing,
      &Machine::nothing, &Machine::nothing, &Machine::nothing, &Machine::jump,
      &Machine::ja, // 40
      &Machine::j1,      &Machine::j2,      &Machine::j3,      &Machine::j4,      &Machine::j5,
      &Machine::j6,      &Machine::jx,      &Machine::ena,     &Machine::en1,
      &Machine::en2, // 50
      &Machine::en3,     &Machine::en4,     &Machine::en5,     &Machine::en6,     &Machine::enx,
      &Machine::cmpa,    &Machine::cmp1,    &Machine::cmp2,    &Machine::cmp3,
      &Machine::cmp4, // 60
      &Machine::cmp5,    &Machine::cmp6,
      &Machine::cmpx // 63
  };

  return &statements[data.get_operation_code()];
}

void Machine::print_state(std::ostream &os) {
  os << "Register A: " << reg_a << std::endl;
  os << "Register X: " << reg_x << std::endl;
  for (int i = 0; i < SMALL_REGISTERS; ++i) {
    os << "Register I" << (i + 1) << ":" << reg_i[i] << std::endl;
  }
  os << "Register J: " << reg_j << std::endl;
  os << "Overflow: " << overflow << std::endl;
  os << "CompareFlag: " << compare_flag << std::endl;
  for (int i = 0; i < MEMORY_WORDS; ++i) {
    os << "Memory[" << (i) << "]:" << memory[i] << std::endl;
  }
}
} // namespace mix
