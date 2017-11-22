/*
 *  mix_small_register.cpp
 *  mixvm
 *
 *  Created by Alexander Ignatyev on 19.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "mix_small_word.h"
namespace mix {
bool is_negative(const small_word &data) {
  return data.sign == NEG_SIGN;
}

void inc(small_word &sreg, bool &override) {
  override = false;
  if (sreg.bytes[1] < VALUES_IN_BYTE - 1) {
    ++sreg.bytes[1];
  } else if (sreg.bytes[0] < VALUES_IN_BYTE - 1) {
    sreg.bytes[1] = 0;
    ++sreg.bytes[0];
  } else {
    override = true;
    sreg.bytes[1] = 0;
    sreg.bytes[0] = 0;
  }
}

int get_value(const small_word &data, byte format) {
  static const int DIFF_IN_WORDS = 3;
  format_range fmt = decode_format(format);
  bool negative = false;
  if (fmt.low == 0) {
    negative = data.sign == POS_SIGN ? false : true;
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
    value += data.bytes[i];
  }
  if (negative) {
    value *= -1;
  }
  return value;
}

void set_value(value_type val, small_word &data, bool &override) {
  data.sign = val < 0 ? NEG_SIGN : POS_SIGN;
  if (val < 0)
    val *= -1;
  value_type tmp = val / VALUES_IN_BYTE;
  if (tmp > VALUES_IN_BYTE) {
    override = true;
    data.bytes[0] = VALUES_IN_BYTE - 1;
    data.bytes[1] = VALUES_IN_BYTE - 1;
  } else {
    override = false;
    data.bytes[0] = tmp;
    data.bytes[1] = val - tmp * VALUES_IN_BYTE;
  }
}
} // namespace mix