#ifndef MIX_SIGN_H
#define MIX_SIGN_H

namespace mix {

enum class Sign { Positive = 0, Negative = 1 };

Sign flip_sign(Sign sign);
char to_char(Sign sign);

template <typename T> Sign get_sign(T value) {
  return value < 0 ? Sign::Negative : Sign::Positive;
}

} // namespace mix

#endif // MIX_SIGN_H
