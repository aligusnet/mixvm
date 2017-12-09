#ifndef MIX_GENERIC_WORD_H
#define MIX_GENERIC_WORD_H

#include "mix_byte.h"
#include "mix_field_specification.h"
#include "mix_sign.h"

#include <array>
#include <ostream>

namespace mix {

template <int A, int B> struct power { static constexpr int value = A * power<A, B - 1>::value; };
template <int A> struct power<A, 0> { static constexpr int value = 1; };

template <int N> class GenericWord {
public:
  static constexpr int DATA_BYTES = N;
  static constexpr int VALUES_IN_WORD = power<VALUES_IN_BYTE, DATA_BYTES>::value;

  value_type get_value(FieldSpecification fmt = FieldSpecification::DEFAULT) const {
    bool negative = false;

    if (fmt.low > 0)
      --fmt.low;
    else if (sign == Sign::Negative)
      negative = true;

    if (fmt.high > DATA_BYTES)
      fmt.high = DATA_BYTES;

    int value = 0;
    for (int i = fmt.low; i < fmt.high; ++i) {
      value *= VALUES_IN_BYTE;
      value += bytes[i];
    }

    if (negative)
      value *= -1;

    return value;
  }

  // return true if overflowed
  bool set_value(int val) {
    sign = mix::get_sign(val);
    if (val < 0)
      val *= -1;
    for (int i = DATA_BYTES - 1; i >= 0; --i) {
      bytes[i] = val % VALUES_IN_BYTE;
      val /= VALUES_IN_BYTE;
    }
    return val > 0;
  }

  short get_address() const {
    static_assert(DATA_BYTES >= 2, "address functions applied only to words with data bytes >= 2");

    short value = bytes[0] * VALUES_IN_BYTE;
    value += bytes[1];
    if (sign == Sign::Negative)
      value *= -1;
    return value;
  }

  void set_address(short address) {
    static_assert(DATA_BYTES >= 2, "address functions applied only to words with data bytes >= 2");

    sign = mix::get_sign(address);
    if (address < 0)
      address *= -1;
    bytes[0] = address / VALUES_IN_BYTE;
    bytes[1] = address % VALUES_IN_BYTE;
  }

  void set_value(const GenericWord<DATA_BYTES> &source, FieldSpecification fmt) {
    if (fmt.low < 0)
      fmt.low = 0;

    if (fmt.high > DATA_BYTES)
      fmt.high = DATA_BYTES;

    if (fmt.low == 0) {
      sign = source.sign; // copy_sign
      ++fmt.low;          // remove sign
    }

    for (int i = fmt.low - 1; i < fmt.high; ++i) {
      bytes[i] = source.bytes[i];
    }
  }

  void right_shift(int nbytes) {
    for (int i = DATA_BYTES - 1; i - nbytes >= 0; --i) {
      bytes[i] = bytes[i - nbytes];
    }
    for (int i = 0; i < nbytes; ++i) {
      bytes[i] = 0;
    }
  }

  void left_shift(int nbytes) {
    for (int i = 0; i + nbytes < DATA_BYTES; ++i) {
      bytes[i] = bytes[i + nbytes];
    }

    for (int i = DATA_BYTES - 1; i > (DATA_BYTES - nbytes); --i) {
      bytes[i] = 0;
    }
  }

  Sign get_sign() const {
    return sign;
  }

  void set_sign(Sign value) {
    sign = value;
  }

  void flip_sign() {
    sign = mix::flip_sign(sign);
  }

  void print(std::ostream &os) const {
    os << to_char(sign);
    for (int i = 0; i < DATA_BYTES; ++i) {
      os << ", " << static_cast<int>(bytes[i]);
    }
  }

  Sign sign;
  std::array<byte, DATA_BYTES> bytes;
};

template <int N> std::ostream &operator<<(std::ostream &os, const GenericWord<N> &word) {
  word.print(os);
  return os;
}

template <int N> bool operator==(const GenericWord<N> &lhs, const GenericWord<N> &rhs) {
  return lhs.sign == rhs.sign && lhs.bytes == rhs.bytes;
}

} // namespace mix

#endif // MIX_GENERIC_WORD_H
