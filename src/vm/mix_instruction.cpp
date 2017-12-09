#include "mix_instruction.h"

#include <sstream>

namespace mix {

enum bytes_format { byte_a1 = 0, byte_a2 = 1, byte_i = 2, byte_f = 3, byte_c = 4 };

short Instruction::get_address() const {
  return word.get_address();
}

Instruction::Instruction(const Word &word) : word{word} {
}

Instruction::Instruction(byte cmd, short addr, byte i, FieldSpecification f) {
  word.sign = Sign::Positive;
  word.set_address(addr);
  word.bytes[byte_i] = i;
  word.bytes[byte_f] = f.encode();
  word.bytes[byte_c] = cmd;
}

Instruction::Instruction(byte cmd, short addr, byte i, byte f) {
  word.sign = Sign::Positive;
  word.set_address(addr);
  word.bytes[byte_i] = i;
  word.bytes[byte_f] = f;
  word.bytes[byte_c] = cmd;
}

byte Instruction::get_operation_code() const {
  return word.bytes[byte_c];
}

FieldSpecification Instruction::get_field_specification() const {
  return FieldSpecification::decode(word.bytes[byte_f]);
}

byte Instruction::get_modification() const {
  return word.bytes[byte_f];
}

byte Instruction::get_specification() const {
  return word.bytes[byte_i];
}

void Instruction::print(std::ostream &os, const char *command_name) const {
  os << command_name << '\t' << static_cast<int>(get_address()) << "," << static_cast<unsigned>(word.bytes[byte_i])
     << FieldSpecification::decode(word.bytes[byte_f]);
}

Word Instruction::as_word() const {
  return word;
}

} // namespace mix
