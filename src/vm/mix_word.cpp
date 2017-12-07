#include "mix_word.h"

namespace mix {

Word::Word(Sign sign, byte a1, byte a2, byte i, byte f, byte c) {
  this->sign = sign;
  this->bytes[byte_a1] = a1;
  this->bytes[byte_a2] = a2;
  this->bytes[byte_i] = i;
  this->bytes[byte_f] = f;
  this->bytes[byte_c] = c;
}

Word Word::make_as_instruction(byte cmd, short addr, byte i, FieldSpecification f) {
  Word result;
  result.sign = Sign::Positive;
  result.set_address(addr);
  result.bytes[byte_i] = i;
  result.bytes[byte_f] = f.encode();
  result.bytes[byte_c] = cmd;
  return result;
}

} // namespace mix
