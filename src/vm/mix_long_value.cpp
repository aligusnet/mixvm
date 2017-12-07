#include "mix_long_value.h"
#include "mix_word.h"

namespace mix {
long_value_type LongValue::get(const Word &high_word, const Word &low_word) {
  long_value_type value = 0;
  for (int i = 0; i < Word::DATA_BYTES; ++i) {
    value *= VALUES_IN_BYTE;
    value += high_word.bytes[i];
  }

  for (int i = 0; i < Word::DATA_BYTES; ++i) {
    value *= VALUES_IN_BYTE;
    value += low_word.bytes[i];
  }

  if (high_word.sign == Sign::Negative) {
    value *= -1;
  }

  return value;
}

bool LongValue::set(long_value_type val, Word &high_word, Word &low_word) {
  high_word.sign = mix::get_sign(val);
  low_word.sign = high_word.sign;
  if (val < 0)
    val *= -1;
  for (int i = Word::DATA_BYTES - 1; i >= 0; --i) {
    low_word.bytes[i] = val % VALUES_IN_BYTE;
    val /= VALUES_IN_BYTE;
  }

  for (int i = Word::DATA_BYTES - 1; i >= 0; --i) {
    high_word.bytes[i] = val % VALUES_IN_BYTE;
    val /= VALUES_IN_BYTE;
  }

  return val > 0;
}

} // namespace mix
