#ifndef MIX_LONG_VALUE
#define MIX_LONG_VALUE

#include "mix_byte.h"

namespace mix {
class Word;

struct LongValue {
  static long_value_type get(const Word &high_word, const Word &low_word);
  // return true if overflowed
  static bool set(long_value_type val, Word &high_word, Word &low_word);
};

} // namespace mix

#endif // MIX_LONG_VALUE
