#include "mix_machine.h"
#include "mix_array_shifter.h"
#include "mix_long_value.h"

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define LOG_COMMAND_NAME(instruction)                                                                                  \
  (instruction).print(std::cout, __FUNCTION__);                                                                        \
  std::cout << std::endl;

namespace mix {
Machine::Machine() {
  memset(this, 0, sizeof(Machine));
}

void Machine::run(short initial_address) {
  halt = false;
  reg_j.set_address(initial_address);
  while (!halt) {
    const auto &instruction = Instruction(memory[reg_j.get_value()]);
    overflow = reg_j.inc();
    execute_instruction(instruction);
  }
}

void Machine::nothing(Instruction instruction) {
  LOG_COMMAND_NAME(instruction)
}

void Machine::nop(Instruction instruction) { // 0
  LOG_COMMAND_NAME(instruction)
}

void Machine::add(Instruction instruction) { // 1
  LOG_COMMAND_NAME(instruction)

  const auto m = get_memory_value(instruction);
  const auto r = reg_a.get_value();
  overflow = reg_a.set_value(r + m);
}

void Machine::sub(Instruction instruction) { // 2
  LOG_COMMAND_NAME(instruction)

  const auto m = get_memory_value(instruction);
  const auto r = reg_a.get_value();
  overflow = reg_a.set_value(r - m);
}

void Machine::mul(Instruction instruction) { // 3
  LOG_COMMAND_NAME(instruction)

  long_value_type m = get_memory_value(instruction);
  long_value_type r = reg_a.get_value();
  overflow = LongValue::set(r * m, reg_a, reg_x);
}

void Machine::div(Instruction instruction) { // 4
  LOG_COMMAND_NAME(instruction)

  value_type val_reg_a = reg_a.get_value();
  value_type val_mem = get_memory_value(instruction);

  if (abs(val_reg_a) < abs(val_mem)) {
    long_value_type val = LongValue::get(reg_a, reg_x);
    value_type quotient = static_cast<value_type>(val / val_mem);
    value_type remainder = static_cast<value_type>(val - quotient * val_mem);
    overflow = reg_x.set_value(remainder);
    reg_x.set_sign(reg_a.get_sign());
    overflow = reg_a.set_value(quotient);
  } else {
    overflow = true;
  }
}

void Machine::hlt(Instruction instruction) { // 5
  LOG_COMMAND_NAME(instruction)
  halt = true;
}

void Machine::shift(Instruction instruction) { // 6
  switch (instruction.get_modification()) {
  case 0:
    sla(instruction);
    break;
  case 1:
    sra(instruction);
    break;
  case 2:
    slax(instruction);
    break;
  case 3:
    srax(instruction);
    break;
  case 4:
    slc(instruction);
    break;
  case 5:
    src(instruction);
    break;
  };
}

void Machine::sla(Instruction instruction) { // 6, 0
  LOG_COMMAND_NAME(instruction)
  auto num_elements = instruction.get_address();
  shift_left(&reg_a.bytes, num_elements);
}

void Machine::sra(Instruction instruction) { // 6, 1
  LOG_COMMAND_NAME(instruction)
  auto num_elements = instruction.get_address();
  shift_right(&reg_a.bytes, num_elements);
}

void Machine::slax(Instruction instruction) { // 6, 2
  LOG_COMMAND_NAME(instruction)
  auto num_elements = instruction.get_address();
  double_shift_left(&reg_a.bytes, &reg_x.bytes, num_elements);
}

void Machine::srax(Instruction instruction) { // 6, 3
  LOG_COMMAND_NAME(instruction)
  auto num_elements = instruction.get_address();
  double_shift_right(&reg_a.bytes, &reg_x.bytes, num_elements);
}

void Machine::slc(Instruction instruction) { // 6, 4
  LOG_COMMAND_NAME(instruction)
  auto num_elements = instruction.get_address();
  double_rotate_left(&reg_a.bytes, &reg_x.bytes, num_elements);
}

void Machine::src(Instruction instruction) { // 6, 5
  LOG_COMMAND_NAME(instruction)
  auto num_elements = instruction.get_address();
  double_rotate_right(&reg_a.bytes, &reg_x.bytes, num_elements);
}

void Machine::lda(Instruction instruction) { // 8
  LOG_COMMAND_NAME(instruction)
  load_big_register(&reg_a, instruction);
}

void Machine::ldx(Instruction instruction) { // 15
  LOG_COMMAND_NAME(instruction)
  load_big_register(&reg_x, instruction);
}

void Machine::ld1(Instruction instruction) { // 9
  LOG_COMMAND_NAME(instruction)
  load_index_register(1, instruction);
}

void Machine::ld2(Instruction instruction) { // 10
  LOG_COMMAND_NAME(instruction)
  load_index_register(2, instruction);
}

void Machine::ld3(Instruction instruction) { // 11
  LOG_COMMAND_NAME(instruction)
  load_index_register(3, instruction);
}

void Machine::ld4(Instruction instruction) { // 12
  LOG_COMMAND_NAME(instruction)
  load_index_register(4, instruction);
}

void Machine::ld5(Instruction instruction) { // 13
  LOG_COMMAND_NAME(instruction)
  load_index_register(5, instruction);
}

void Machine::ld6(Instruction instruction) { // 14
  LOG_COMMAND_NAME(instruction)
  load_index_register(6, instruction);
}

void Machine::ldan(Instruction instruction) { // 16
  LOG_COMMAND_NAME(instruction)
  load_register_negative(&reg_a, instruction);
}

void Machine::ldxn(Instruction instruction) { // 23
  LOG_COMMAND_NAME(instruction)
  load_register_negative(&reg_x, instruction);
}

void Machine::ld1n(Instruction instruction) { // 17
  LOG_COMMAND_NAME(instruction)
  load_index_register_negative(1, instruction);
}

void Machine::ld2n(Instruction instruction) { // 18
  LOG_COMMAND_NAME(instruction)
  load_index_register_negative(2, instruction);
}

void Machine::ld3n(Instruction instruction) { // 19
  LOG_COMMAND_NAME(instruction)
  load_index_register_negative(3, instruction);
}

void Machine::ld4n(Instruction instruction) { // 20
  LOG_COMMAND_NAME(instruction)
  load_index_register_negative(4, instruction);
}

void Machine::ld5n(Instruction instruction) { // 21
  LOG_COMMAND_NAME(instruction)
  load_index_register_negative(5, instruction);
}

void Machine::ld6n(Instruction instruction) { // 22
  LOG_COMMAND_NAME(instruction)
  load_index_register_negative(6, instruction);
}

void Machine::sta(Instruction instruction) { // 24
  LOG_COMMAND_NAME(instruction)
  store_big_register(reg_a, instruction);
}

void Machine::stx(Instruction instruction) { // 31
  LOG_COMMAND_NAME(instruction)
  store_big_register(reg_x, instruction);
}

void Machine::st1(Instruction instruction) { // 25
  LOG_COMMAND_NAME(instruction)
  store_index_register(1, instruction);
}

void Machine::st2(Instruction instruction) { // 26
  LOG_COMMAND_NAME(instruction)
  store_index_register(2, instruction);
}

void Machine::st3(Instruction instruction) { // 27
  LOG_COMMAND_NAME(instruction)
  store_index_register(3, instruction);
}

void Machine::st4(Instruction instruction) { // 28
  LOG_COMMAND_NAME(instruction)
  store_index_register(4, instruction);
}

void Machine::st5(Instruction instruction) { // 29
  LOG_COMMAND_NAME(instruction)
  store_index_register(5, instruction);
}

void Machine::st6(Instruction instruction) { // 30
  LOG_COMMAND_NAME(instruction)
  store_index_register(6, instruction);
}

void Machine::stj(Instruction instruction) { // 32
  LOG_COMMAND_NAME(instruction)
  store_small_register(reg_j, instruction);
}

void Machine::stz(Instruction instruction) { // 33
  LOG_COMMAND_NAME(instruction)

  int addr = extract_address(instruction);
  Word zero;
  memset(&zero, 0, sizeof(zero));
  memory[addr].set_value(zero, instruction.get_field_specification());
}

void Machine::jump(Instruction instruction) { // 39
  switch (instruction.get_modification()) {
  case 0:
    jmp(instruction);
    break;
  case 1:
    jsj(instruction);
    break;
  case 2:
    jov(instruction);
    break;
  case 3:
    jnov(instruction);
    break;
  case 4:
    jl(instruction);
    break;
  case 5:
    je(instruction);
    break;
  case 6:
    jg(instruction);
    break;
  case 7:
    jge(instruction);
    break;
  case 8:
    jne(instruction);
    break;
  case 9:
    jle(instruction);
    break;
  };
}

void Machine::jmp(Instruction instruction) { // 39, 0
  LOG_COMMAND_NAME(instruction)
  unconditionally_jump(instruction);
}

void Machine::jsj(Instruction instruction) { // 39, 1
  LOG_COMMAND_NAME(instruction)

  // "The next instruction is taken from M"
  // "<...> the contents of rJ are unchanged"

  // I guess this means that
  // the next instruction is executed from memory location M

  const auto address = extract_address(instruction);
  const auto &next_instruction = Instruction(memory[address]);
  execute_instruction(next_instruction);
}

void Machine::jov(Instruction instruction) { // 39, 2
  LOG_COMMAND_NAME(instruction)

  if (overflow) {
    overflow = false;
    unconditionally_jump(instruction);
  }
}

void Machine::jnov(Instruction instruction) { // 39, 3
  LOG_COMMAND_NAME(instruction)

  if (!overflow) {
    unconditionally_jump(instruction);
  }
}

void Machine::jl(Instruction instruction) { // 39, 4
  LOG_COMMAND_NAME(instruction)

  if (compare_flag == cmp_less) {
    unconditionally_jump(instruction);
  }
}

void Machine::je(Instruction instruction) { // 39, 5
  LOG_COMMAND_NAME(instruction)

  if (compare_flag == cmp_equal) {
    unconditionally_jump(instruction);
  }
}

void Machine::jg(Instruction instruction) { // 39, 6
  LOG_COMMAND_NAME(instruction)

  if (compare_flag == cmp_greater) {
    unconditionally_jump(instruction);
  }
}

void Machine::jge(Instruction instruction) { // 39, 7
  LOG_COMMAND_NAME(instruction)

  if (compare_flag != cmp_less) {
    unconditionally_jump(instruction);
  }
}

void Machine::jne(Instruction instruction) { // 39, 8
  LOG_COMMAND_NAME(instruction)

  if (compare_flag != cmp_equal) {
    unconditionally_jump(instruction);
  }
}

void Machine::jle(Instruction instruction) { // 39, 9
  LOG_COMMAND_NAME(instruction)

  if (compare_flag != cmp_greater) {
    unconditionally_jump(instruction);
  }
}

void Machine::ja(Instruction instruction) { // 40
  switch (instruction.get_modification()) {
  case 0:
    jan(instruction);
    break;
  case 1:
    jaz(instruction);
    break;
  case 2:
    jap(instruction);
    break;
  case 3:
    jann(instruction);
    break;
  case 4:
    janz(instruction);
    break;
  case 5:
    janp(instruction);
    break;
  };
}

void Machine::jan(Instruction instruction) { // 40, 0
  LOG_COMMAND_NAME(instruction)
  jump_if_negative(reg_a, instruction);
}

void Machine::jaz(Instruction instruction) { // 40, 1
  LOG_COMMAND_NAME(instruction)
  jump_if_zero(reg_a, instruction);
}

void Machine::jap(Instruction instruction) { // 40, 2
  LOG_COMMAND_NAME(instruction)
  jump_if_positive(reg_a, instruction);
}

void Machine::jann(Instruction instruction) { // 40, 3
  LOG_COMMAND_NAME(instruction)
  jump_if_non_negative(reg_a, instruction);
}

void Machine::janz(Instruction instruction) { // 40, 4
  LOG_COMMAND_NAME(instruction)
  jump_if_non_zero(reg_a, instruction);
}

void Machine::janp(Instruction instruction) { // 40, 5
  LOG_COMMAND_NAME(instruction)
  jump_if_non_positive(reg_a, instruction);
}

void Machine::j1(Instruction instruction) { // 41
  switch (instruction.get_modification()) {
  case 0:
    j1n(instruction);
    break;
  case 1:
    j1z(instruction);
    break;
  case 2:
    j1p(instruction);
    break;
  case 3:
    j1nn(instruction);
    break;
  case 4:
    j1nz(instruction);
    break;
  case 5:
    j1np(instruction);
    break;
  };
}

void Machine::j1n(Instruction instruction) { // 41, 0
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_negative(1, instruction);
}

void Machine::j1z(Instruction instruction) { // 41, 1
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_zero(1, instruction);
}

void Machine::j1p(Instruction instruction) { // 41, 2
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_positive(1, instruction);
}

void Machine::j1nn(Instruction instruction) { // 41, 3
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_negative(1, instruction);
}

void Machine::j1nz(Instruction instruction) { // 41, 4
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_zero(1, instruction);
}

void Machine::j1np(Instruction instruction) { // 41, 5
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_positive(1, instruction);
}

void Machine::j2(Instruction instruction) { // 41
  switch (instruction.get_modification()) {
  case 0:
    j2n(instruction);
    break;
  case 1:
    j2z(instruction);
    break;
  case 2:
    j2p(instruction);
    break;
  case 3:
    j2nn(instruction);
    break;
  case 4:
    j2nz(instruction);
    break;
  case 5:
    j2np(instruction);
    break;
  };
}

void Machine::j2n(Instruction instruction) { // 42, 0
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_negative(2, instruction);
}

void Machine::j2z(Instruction instruction) { // 42, 1
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_zero(2, instruction);
}

void Machine::j2p(Instruction instruction) { // 42, 2
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_positive(2, instruction);
}

void Machine::j2nn(Instruction instruction) { // 42, 3
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_negative(2, instruction);
}

void Machine::j2nz(Instruction instruction) { // 42, 4
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_zero(2, instruction);
}

void Machine::j2np(Instruction instruction) { // 42, 5
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_positive(2, instruction);
}

void Machine::j3(Instruction instruction) { // 43
  switch (instruction.get_modification()) {
  case 0:
    j3n(instruction);
    break;
  case 1:
    j3z(instruction);
    break;
  case 2:
    j3p(instruction);
    break;
  case 3:
    j3nn(instruction);
    break;
  case 4:
    j3nz(instruction);
    break;
  case 5:
    j3np(instruction);
    break;
  };
}

void Machine::j3n(Instruction instruction) { // 43, 0
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_negative(3, instruction);
}

void Machine::j3z(Instruction instruction) { // 43, 1
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_zero(3, instruction);
}

void Machine::j3p(Instruction instruction) { // 43, 2
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_positive(3, instruction);
}

void Machine::j3nn(Instruction instruction) { // 43, 3
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_negative(3, instruction);
}

void Machine::j3nz(Instruction instruction) { // 43, 4
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_zero(3, instruction);
}

void Machine::j3np(Instruction instruction) { // 43, 5
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_positive(3, instruction);
}

void Machine::j4(Instruction instruction) { // 44
  switch (instruction.get_modification()) {
  case 0:
    j4n(instruction);
    break;
  case 1:
    j4z(instruction);
    break;
  case 2:
    j4p(instruction);
    break;
  case 3:
    j4nn(instruction);
    break;
  case 4:
    j4nz(instruction);
    break;
  case 5:
    j4np(instruction);
    break;
  };
}

void Machine::j4n(Instruction instruction) { // 44, 0
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_negative(4, instruction);
}

void Machine::j4z(Instruction instruction) { // 44, 1
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_zero(4, instruction);
}

void Machine::j4p(Instruction instruction) { // 44, 2
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_positive(4, instruction);
}

void Machine::j4nn(Instruction instruction) { // 44, 3
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_negative(4, instruction);
}

void Machine::j4nz(Instruction instruction) { // 44, 4
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_zero(4, instruction);
}

void Machine::j4np(Instruction instruction) { // 44, 5
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_positive(4, instruction);
}

void Machine::j5(Instruction instruction) { // 45
  switch (instruction.get_modification()) {
  case 0:
    j5n(instruction);
    break;
  case 1:
    j5z(instruction);
    break;
  case 2:
    j5p(instruction);
    break;
  case 3:
    j5nn(instruction);
    break;
  case 4:
    j5nz(instruction);
    break;
  case 5:
    j5np(instruction);
    break;
  };
}

void Machine::j5n(Instruction instruction) { // 45, 0
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_negative(5, instruction);
}

void Machine::j5z(Instruction instruction) { // 45, 1
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_zero(5, instruction);
}

void Machine::j5p(Instruction instruction) { // 45, 2
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_positive(5, instruction);
}

void Machine::j5nn(Instruction instruction) { // 45, 3
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_negative(5, instruction);
}

void Machine::j5nz(Instruction instruction) { // 45, 4
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_zero(5, instruction);
}

void Machine::j5np(Instruction instruction) { // 45, 5
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_positive(5, instruction);
}

void Machine::j6(Instruction instruction) { // 46
  switch (instruction.get_modification()) {
  case 0:
    j6n(instruction);
    break;
  case 1:
    j6z(instruction);
    break;
  case 2:
    j6p(instruction);
    break;
  case 3:
    j6nn(instruction);
    break;
  case 4:
    j6nz(instruction);
    break;
  case 5:
    j6np(instruction);
    break;
  };
}

void Machine::j6n(Instruction instruction) { // 46, 0
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_negative(6, instruction);
}

void Machine::j6z(Instruction instruction) { // 46, 1
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_zero(6, instruction);
}

void Machine::j6p(Instruction instruction) { // 46, 2
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_positive(6, instruction);
}

void Machine::j6nn(Instruction instruction) { // 46, 3
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_negative(6, instruction);
}

void Machine::j6nz(Instruction instruction) { // 46, 4
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_zero(6, instruction);
}

void Machine::j6np(Instruction instruction) { // 46, 5
  LOG_COMMAND_NAME(instruction)
  jump_if_index_register_non_positive(6, instruction);
}

void Machine::jx(Instruction instruction) { // 47
  switch (instruction.get_modification()) {
  case 0:
    jxn(instruction);
    break;
  case 1:
    jxz(instruction);
    break;
  case 2:
    jxp(instruction);
    break;
  case 3:
    jxnn(instruction);
    break;
  case 4:
    jxnz(instruction);
    break;
  case 5:
    jxnp(instruction);
    break;
  };
}

void Machine::jxn(Instruction instruction) { // 47, 0
  LOG_COMMAND_NAME(instruction)
  jump_if_negative(reg_x, instruction);
}

void Machine::jxz(Instruction instruction) { // 47, 1
  LOG_COMMAND_NAME(instruction)
  jump_if_zero(reg_x, instruction);
}

void Machine::jxp(Instruction instruction) { // 47, 2
  LOG_COMMAND_NAME(instruction)
  jump_if_positive(reg_x, instruction);
}

void Machine::jxnn(Instruction instruction) { // 47, 3
  LOG_COMMAND_NAME(instruction)
  jump_if_non_negative(reg_x, instruction);
}

void Machine::jxnz(Instruction instruction) { // 47, 4
  LOG_COMMAND_NAME(instruction)
  jump_if_non_zero(reg_x, instruction);
}

void Machine::jxnp(Instruction instruction) { // 47, 5
  LOG_COMMAND_NAME(instruction)
  jump_if_non_positive(reg_x, instruction);
}

void Machine::ena(Instruction instruction) { // 48
  switch (instruction.get_modification()) {
  case 0:
    inca(instruction);
    break;
  case 1:
    deca(instruction);
    break;
  case 2:
    enta(instruction);
    break;
  case 3:
    enna(instruction);
    break;
  default:
    nothing(instruction);
    break;
  };
}

void Machine::en1(Instruction instruction) { // 49
  switch (instruction.get_modification()) {
  case 0:
    inc1(instruction);
    break;
  case 1:
    dec1(instruction);
    break;
  case 2:
    ent1(instruction);
    break;
  case 3:
    enn1(instruction);
    break;
  default:
    nothing(instruction);
    break;
  };
}

void Machine::en2(Instruction instruction) { // 50
  switch (instruction.get_modification()) {
  case 0:
    inc2(instruction);
    break;
  case 1:
    dec2(instruction);
    break;
  case 2:
    ent2(instruction);
    break;
  case 3:
    enn2(instruction);
    break;
  default:
    nothing(instruction);
    break;
  };
}

void Machine::en3(Instruction instruction) { // 51
  switch (instruction.get_modification()) {
  case 0:
    inc3(instruction);
    break;
  case 1:
    dec3(instruction);
    break;
  case 2:
    ent3(instruction);
    break;
  case 3:
    enn3(instruction);
    break;
  default:
    nothing(instruction);
    break;
  };
}

void Machine::en4(Instruction instruction) { // 52
  switch (instruction.get_modification()) {
  case 0:
    inc4(instruction);
    break;
  case 1:
    dec4(instruction);
    break;
  case 2:
    ent4(instruction);
    break;
  case 3:
    enn4(instruction);
    break;
  default:
    nothing(instruction);
    break;
  };
}

void Machine::en5(Instruction instruction) { // 53
  switch (instruction.get_modification()) {
  case 0:
    inc5(instruction);
    break;
  case 1:
    dec5(instruction);
    break;
  case 2:
    ent5(instruction);
    break;
  case 3:
    enn5(instruction);
    break;
  default:
    nothing(instruction);
    break;
  };
}

void Machine::en6(Instruction instruction) { // 54
  switch (instruction.get_modification()) {
  case 0:
    inc6(instruction);
    break;
  case 1:
    dec6(instruction);
    break;
  case 2:
    ent6(instruction);
    break;
  case 3:
    enn6(instruction);
    break;
  default:
    nothing(instruction);
    break;
  };
}

void Machine::enx(Instruction instruction) { // 55
  switch (instruction.get_modification()) {
  case 0:
    incx(instruction);
    break;
  case 1:
    decx(instruction);
    break;
  case 2:
    entx(instruction);
    break;
  case 3:
    ennx(instruction);
    break;
  default:
    nothing(instruction);
    break;
  };
}

void Machine::enta(Instruction instruction) { // 48, 2
  LOG_COMMAND_NAME(instruction)
  transfer_address_to_register(&reg_a, instruction);
}

void Machine::ent1(Instruction instruction) { // 49, 2
  LOG_COMMAND_NAME(instruction)
  transfer_address_to_index_register(1, instruction);
}

void Machine::ent2(Instruction instruction) { // 50, 2
  LOG_COMMAND_NAME(instruction)
  transfer_address_to_index_register(2, instruction);
}

void Machine::ent3(Instruction instruction) { // 51, 2
  LOG_COMMAND_NAME(instruction)
  transfer_address_to_index_register(3, instruction);
}

void Machine::ent4(Instruction instruction) { // 52, 2
  LOG_COMMAND_NAME(instruction)
  transfer_address_to_index_register(4, instruction);
}

void Machine::ent5(Instruction instruction) { // 53, 2
  LOG_COMMAND_NAME(instruction)
  transfer_address_to_index_register(5, instruction);
}

void Machine::ent6(Instruction instruction) { // 54, 2
  LOG_COMMAND_NAME(instruction)
  transfer_address_to_index_register(6, instruction);
}

void Machine::entx(Instruction instruction) { // 55, 2
  transfer_address_to_register(&reg_x, instruction);
}

void Machine::enna(Instruction instruction) { // 48, 3
  LOG_COMMAND_NAME(instruction)
  transfer_negative_address_to_register(&reg_a, instruction);
}

void Machine::enn1(Instruction instruction) { // 49, 3
  LOG_COMMAND_NAME(instruction)
  transfer_negative_address_to_index_register(1, instruction);
}

void Machine::enn2(Instruction instruction) { // 50, 3
  LOG_COMMAND_NAME(instruction)
  transfer_negative_address_to_index_register(2, instruction);
}

void Machine::enn3(Instruction instruction) { // 51, 3
  LOG_COMMAND_NAME(instruction)
  transfer_negative_address_to_index_register(3, instruction);
}

void Machine::enn4(Instruction instruction) { // 52, 3
  LOG_COMMAND_NAME(instruction)
  transfer_negative_address_to_index_register(4, instruction);
}

void Machine::enn5(Instruction instruction) { // 53, 3
  LOG_COMMAND_NAME(instruction)
  transfer_negative_address_to_index_register(5, instruction);
}

void Machine::enn6(Instruction instruction) { // 54, 3
  LOG_COMMAND_NAME(instruction)
  transfer_negative_address_to_index_register(6, instruction);
}

void Machine::ennx(Instruction instruction) { // 55, 3
  LOG_COMMAND_NAME(instruction)
  transfer_negative_address_to_register(&reg_x, instruction);
}

void Machine::inca(Instruction instruction) { // 48, 0
  LOG_COMMAND_NAME(instruction)
  increment_register(&reg_a);
}

void Machine::inc1(Instruction instruction) { // 49, 0
  LOG_COMMAND_NAME(instruction)
  increment_index_register(1);
}

void Machine::inc2(Instruction instruction) { // 50, 0
  LOG_COMMAND_NAME(instruction)
  increment_index_register(2);
}

void Machine::inc3(Instruction instruction) { // 51, 0
  LOG_COMMAND_NAME(instruction)
  increment_index_register(3);
}

void Machine::inc4(Instruction instruction) { // 52, 0
  LOG_COMMAND_NAME(instruction)
  increment_index_register(4);
}

void Machine::inc5(Instruction instruction) { // 53, 0
  LOG_COMMAND_NAME(instruction)
  increment_index_register(5);
}

void Machine::inc6(Instruction instruction) { // 54, 0
  LOG_COMMAND_NAME(instruction)
  increment_index_register(6);
}

void Machine::incx(Instruction instruction) { // 55, 0
  LOG_COMMAND_NAME(instruction)
  increment_register(&reg_x);
}

void Machine::deca(Instruction instruction) { // 48, 1
  LOG_COMMAND_NAME(instruction)
  decrement_register(&reg_a);
}

void Machine::dec1(Instruction instruction) { // 49, 1
  LOG_COMMAND_NAME(instruction)
  decrement_index_register(1);
}

void Machine::dec2(Instruction instruction) { // 50, 1
  LOG_COMMAND_NAME(instruction)
  decrement_index_register(2);
}

void Machine::dec3(Instruction instruction) { // 51, 1
  LOG_COMMAND_NAME(instruction)
  decrement_index_register(3);
}

void Machine::dec4(Instruction instruction) { // 52, 1
  LOG_COMMAND_NAME(instruction)
  decrement_index_register(4);
}

void Machine::dec5(Instruction instruction) { // 53, 1
  LOG_COMMAND_NAME(instruction)
  decrement_index_register(5);
}

void Machine::dec6(Instruction instruction) { // 54, 1
  LOG_COMMAND_NAME(instruction)
  decrement_index_register(6);
}

void Machine::decx(Instruction instruction) { // 55, 1
  LOG_COMMAND_NAME(instruction)
  decrement_register(&reg_x);
}

void Machine::cmpa(Instruction instruction) { // 56
  LOG_COMMAND_NAME(instruction)
  compare_register_and_memory(reg_a, instruction);
}

void Machine::cmp1(Instruction instruction) { // 57
  LOG_COMMAND_NAME(instruction)
  compare_index_register_and_memory(1, instruction);
}

void Machine::cmp2(Instruction instruction) { // 58
  LOG_COMMAND_NAME(instruction)
  compare_index_register_and_memory(2, instruction);
}

void Machine::cmp3(Instruction instruction) { // 59
  LOG_COMMAND_NAME(instruction)
  compare_index_register_and_memory(3, instruction);
}

void Machine::cmp4(Instruction instruction) { // 60
  LOG_COMMAND_NAME(instruction)
  compare_index_register_and_memory(4, instruction);
}

void Machine::cmp5(Instruction instruction) { // 61
  LOG_COMMAND_NAME(instruction)
  compare_index_register_and_memory(5, instruction);
}

void Machine::cmp6(Instruction instruction) { // 62
  LOG_COMMAND_NAME(instruction)
  compare_index_register_and_memory(6, instruction);
}

void Machine::cmpx(Instruction instruction) { // 63
  LOG_COMMAND_NAME(instruction)
  compare_register_and_memory(reg_x, instruction);
}

void Machine::execute_instruction(Instruction instruction) {
  do_statement statement = *get_statement(instruction);
  (this->*statement)(instruction);
}

void Machine::load_big_register(big_register *reg, Instruction instruction) const {
  const auto address = extract_address(instruction);
  memset(reg, 0, sizeof(big_register));
  reg->set_value(memory[address], instruction.get_field_specification());
  FieldSpecification fmt = instruction.get_field_specification();
  int nbytes = big_register::DATA_BYTES - fmt.high;
  if (nbytes > 0) {
    reg->right_shift(nbytes);
  }
}

void Machine::load_index_register(int index, Instruction instruction) {
  const auto address = extract_address(instruction);
  value_type val = memory[address].get_value();
  overflow = reg_i[index - 1].set_value(val);
}

void Machine::load_register_negative(big_register *reg, Instruction instruction) const {
  load_big_register(reg, instruction);
  reg->flip_sign();
}

void Machine::load_index_register_negative(int index, Instruction instruction) {
  load_index_register(index, instruction);
  reg_i[index - 1].flip_sign();
}

void Machine::store_big_register(big_register reg, Instruction instruction) {
  FieldSpecification fs = instruction.get_field_specification();
  int nbytes = big_register::DATA_BYTES - fs.high;
  if (nbytes > 0) {
    reg.left_shift(nbytes);
  }

  const auto address = extract_address(instruction);
  memory[address].set_value(reg, fs);
}

void Machine::store_index_register(int index, Instruction instruction) {
  store_small_register(reg_i[index - 1], instruction);
}

void Machine::store_small_register(const small_register &reg, Instruction instruction) {
  const auto address = extract_address(instruction);
  const auto value = reg.get_value();
  overflow = memory[address].set_value(value);
}

void Machine::jump_if_index_register_negative(byte index, Instruction instruction) {
  jump_if_negative(reg_i[index - 1], instruction);
}

void Machine::jump_if_index_register_zero(byte index, Instruction instruction) {
  jump_if_zero(reg_i[index - 1], instruction);
}

void Machine::jump_if_index_register_positive(byte index, Instruction instruction) {
  jump_if_positive(reg_i[index - 1], instruction);
}

void Machine::jump_if_index_register_non_negative(byte index, Instruction instruction) {
  jump_if_non_negative(reg_i[index - 1], instruction);
}

void Machine::jump_if_index_register_non_zero(byte index, Instruction instruction) {
  jump_if_non_zero(reg_i[index - 1], instruction);
}

void Machine::jump_if_index_register_non_positive(byte index, Instruction instruction) {
  jump_if_non_positive(reg_i[index - 1], instruction);
}

template <typename Register> void Machine::jump_if_negative(const Register &reg, Instruction instruction) {
  if (reg.get_sign() == Sign::Negative) {
    unconditionally_jump(instruction);
  }
}

template <typename Register> void Machine::jump_if_zero(const Register &reg, Instruction instruction) {
  const auto val = reg.get_value();
  if (val == 0) {
    unconditionally_jump(instruction);
  }
}

template <typename Register> void Machine::jump_if_positive(const Register &reg, Instruction instruction) {
  const auto val = reg.get_value();
  if (val > 0) {
    unconditionally_jump(instruction);
  }
}

template <typename Register> void Machine::jump_if_non_negative(const Register &reg, Instruction instruction) {
  if (reg.get_sign() != Sign::Negative) {
    unconditionally_jump(instruction);
  }
}

template <typename Register> void Machine::jump_if_non_zero(const Register &reg, Instruction instruction) {
  const auto val = reg.get_value();
  if (val != 0) {
    unconditionally_jump(instruction);
  }
}

template <typename Register> void Machine::jump_if_non_positive(const Register &reg, Instruction instruction) {
  const auto val = reg.get_value();
  if (val <= 0) {
    unconditionally_jump(instruction);
  }
}

void Machine::unconditionally_jump(Instruction instruction) {
  const auto address = extract_address(instruction);
  overflow = reg_j.set_value(address);
}

void Machine::transfer_address_to_index_register(byte index, Instruction instruction) {
  transfer_address_to_register(&reg_i[index - 1], instruction);
}

void Machine::transfer_negative_address_to_index_register(byte index, Instruction instruction) {
  transfer_negative_address_to_register(&reg_i[index - 1], instruction);
}

template <typename Register>
void Machine::transfer_negative_address_to_register(Register *reg, Instruction instruction) {
  transfer_address_to_register(reg, instruction);
  reg->flip_sign();
}

template <typename Register> void Machine::transfer_address_to_register(Register *reg, Instruction instruction) {
  const auto value = extract_address(instruction);
  overflow = reg->set_value(value);
}

void Machine::increment_index_register(byte index) {
  increment_register(&reg_i[index - 1]);
}

template <typename Register> void Machine::increment_register(Register *reg) {
  auto value = reg->get_value();
  overflow = reg->set_value(value + 1);
}

void Machine::decrement_index_register(byte index) {
  decrement_register(&reg_i[index - 1]);
}

template <typename Register> void Machine::decrement_register(Register *reg) {
  auto value = reg->get_value();
  overflow = reg->set_value(value - 1);
}

void Machine::compare_index_register_and_memory(byte index, Instruction instruction) {
  compare_register_and_memory(reg_i[index - 1], instruction);
}

template <typename Register> void Machine::compare_register_and_memory(const Register &reg, Instruction instruction) {
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

value_type Machine::get_memory_value(Instruction instruction) const {
  const auto address = extract_address(instruction);
  return memory[address].get_value(instruction.get_field_specification());
}

unsigned short Machine::extract_address(Instruction instruction) const {
  unsigned short address = instruction.get_address();
  int index_specification = instruction.get_specification();
  if (index_specification) {
    address += reg_i[index_specification - 1].get_value();
  }
  return address;
}

do_statement *Machine::get_statement(Instruction instruction) {
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

  return &statements[instruction.get_operation_code()];
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
