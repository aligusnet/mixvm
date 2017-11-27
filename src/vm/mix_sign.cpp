#include "mix_sign.h"

namespace mix {
Sign flip_sign(Sign sign) {
  return sign == Sign::Positive ? Sign::Negative : Sign::Positive;
}

char to_char(Sign sign) {
  return sign == Sign::Positive ? '+' : '-';
}

} // namespace mix
