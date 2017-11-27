#include "mix_small_word.h"

#include <sstream>

namespace mix {
bool SmallWord::inc() {
  bool isOverflowed = false;
  if (bytes[1] < VALUES_IN_BYTE - 1) {
    ++bytes[1];
  } else if (bytes[0] < VALUES_IN_BYTE - 1) {
    bytes[1] = 0;
    ++bytes[0];
  } else {
    isOverflowed = true;
    bytes[1] = 0;
    bytes[0] = 0;
  }
  return isOverflowed;
}

bool SmallWord::set_value(value_type val) {
  bool isOverflowed = false;
  sign = mix::get_sign(val);
  if (val < 0)
    val *= -1;
  value_type tmp = val / VALUES_IN_BYTE;
  if (tmp > VALUES_IN_BYTE) {
    isOverflowed = true;
    bytes[0] = VALUES_IN_BYTE - 1;
    bytes[1] = VALUES_IN_BYTE - 1;
  } else {
    isOverflowed = false;
    bytes[0] = tmp;
    bytes[1] = val - tmp * VALUES_IN_BYTE;
  }
  return isOverflowed;
}

int SmallWord::get_value(FieldSpecification fmt) const {
  static const int DIFF_IN_WORDS = 3;
  bool negative = false;
  if (fmt.low == 0) {
    negative = sign == Sign::Positive ? false : true;
  }
  if (fmt.low < DIFF_IN_WORDS) {
    fmt.low = 0;
  }
  fmt.high -= DIFF_IN_WORDS;
  if (fmt.high > DATA_BYTES_IN_SMALL_REGISTER) {
    fmt.high = DATA_BYTES_IN_SMALL_REGISTER;
  }
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

void SmallWord::set_address(short addr) {
  bytes[0] = addr / VALUES_IN_BYTE;
  bytes[1] = addr - bytes[0] * VALUES_IN_BYTE;
}

Sign SmallWord::get_sign() const {
  return sign;
}

void SmallWord::set_sign(Sign sign) {
  this->sign = sign;
}

void SmallWord::flip_sign() {
  sign = mix::flip_sign(sign);
}

void SmallWord::print(std::ostream &os) const {
  os << to_char(sign);
  for (int i = 0; i < DATA_BYTES_IN_SMALL_REGISTER; ++i) {
    os << ", " << (int)bytes[i];
  }
}

std::ostream &operator<<(std::ostream &os, const SmallWord &sw) {
  sw.print(os);
  return os;
}

} // namespace mix
