/*
 *  small_register.h
 *  mixvm
 *
 *  Created by Alexander Ignatyev on 19.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MIX_SMALL_REGISTER_H
#define MIX_SMALL_REGISTER_H

#include "format_range.h"
#include "mix_byte.h"

namespace mix {
const int DATA_BYTES_IN_SMALL_REGISTER = 2;
struct small_word {
  bool sign;
  byte bytes[DATA_BYTES_IN_SMALL_REGISTER];
};

bool is_negative(const small_word &data);
void inc(small_word &sreg, bool &override);
int get_value(const small_word &data, byte format = DEFAULT_FORMAT);
void set_value(value_type val, small_word &data, bool &override);
void set_address(byte *bytes, short addr);
} // namespace mix

#endif // MIX_SMALL_REGISTER_H
