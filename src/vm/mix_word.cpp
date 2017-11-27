#include "mix_word.h"

#include <sstream>

namespace mix {
enum bytes_format { byte_a1 = 0, byte_a2 = 1, byte_i = 2, byte_f = 3, byte_c = 4 };

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

short Word::get_address() const {
  short address = 0;
  address += bytes[byte_a1] * VALUES_IN_BYTE;
  address += bytes[byte_a2];
  if (sign == Sign::Negative) {
    address *= -1;
  }
  return address;
}

void Word::set_address(short address) {
  bytes[0] = address / VALUES_IN_BYTE;
  bytes[1] = address - bytes[0] * VALUES_IN_BYTE;
}

void Word::right_shift(int nbytes) {
  for (int i = DATA_BYTES_IN_WORD - 1; i - nbytes >= 0; --i) {
    bytes[i] = bytes[i - nbytes];
  }
  for (int i = 0; i < nbytes; ++i) {
    bytes[i] = 0;
  }
}

void Word::left_shift(int nbytes) {
  for (int i = 0; i + nbytes < DATA_BYTES_IN_WORD; ++i) {
    bytes[i] = bytes[i + nbytes];
  }

  for (int i = DATA_BYTES_IN_WORD - 1; i > (DATA_BYTES_IN_WORD - nbytes); --i) {
    bytes[i] = 0;
  }
}

void Word::set_value(const Word &source, FieldSpecification fmt) {
  if (fmt.low < 0)
    fmt.low = 0;
  if (fmt.high > 5)
    fmt.high = 5;

  if (fmt.low == 0) {
    // copy_sign
    sign = source.sign;
    ++fmt.low; // remove sign
  }

  for (int i = fmt.low - 1; i < fmt.high; ++i) {
    bytes[i] = source.bytes[i];
  }
}

bool Word::set_value(int val) {
  sign = mix::get_sign(val);
  if (val < 0)
    val *= -1;
  for (int i = DATA_BYTES_IN_WORD - 1; i >= 0; --i) {
    bytes[i] = val % VALUES_IN_BYTE;
    val /= VALUES_IN_BYTE;
  }
  return val > 0;
}

value_type Word::get_value(FieldSpecification fmt) const {
  bool negative = false;
  if (fmt.low > 0) {
    --fmt.low;
  } else if (sign == Sign::Negative) {
    negative = true;
  }

  if (fmt.high > 5)
    fmt.high = 5;
  int value = 0;
  for (int i = fmt.low; i < fmt.high; ++i) {
    value *= VALUES_IN_BYTE;
    value += bytes[i];
  }
  if (negative) {
    value *= -1;
  }
  return value;
}

byte Word::get_operation_code() const {
  return bytes[byte_c];
}

FieldSpecification Word::get_field_specification() const {
  return FieldSpecification::decode(bytes[byte_f]);
}

byte Word::get_modification() const {
  return bytes[byte_f];
}

byte Word::get_specification() const {
  return bytes[byte_i];
}

Sign Word::get_sign() const {
  return sign;
}

void Word::set_sign(Sign value) {
  sign = value;
}

void Word::flip_sign() {
  sign = mix::flip_sign(sign);
}

void Word::print_word(std::ostream &os) const {
  os << to_char(sign);
  for (int i = 0; i < DATA_BYTES_IN_WORD; ++i) {
    os << ", " << (int)bytes[i];
  }
}

void Word::print_instruction(std::ostream &os, const char *command_name) const {
  os << command_name << "\t" << (unsigned)get_address() << "," << (unsigned)bytes[byte_i];
  FieldSpecification fmt = FieldSpecification::decode(bytes[byte_f]);
  os << "(" << (int)fmt.low << ":" << (int)fmt.high << ")";
}

std::ostream &operator<<(std::ostream &os, const Word &word) {
  word.print_word(os);
  return os;
}

Word make_cmd(byte cmd, short addr, FieldSpecification f) {
  return Word::make_as_instruction(cmd, addr, 0, f);
}

} // namespace mix
