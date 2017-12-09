#include "mix_word.h"

namespace mix {

Word::Word(Sign sign, byte a1, byte a2, byte i, byte f, byte c) {
  this->sign = sign;
  this->bytes[0] = a1;
  this->bytes[1] = a2;
  this->bytes[2] = i;
  this->bytes[3] = f;
  this->bytes[4] = c;
}

} // namespace mix
