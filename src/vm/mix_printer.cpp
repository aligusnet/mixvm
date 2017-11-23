/*
 *  mix_printer.cpp
 *  mixvm
 *
 *  Created by Alexander Ignatyev on 19.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "mix_printer.h"
#include <iostream>

namespace mix {
void print_small_word(std::ostream &os, const small_word &word) {
  os << (word.sign == POS_SIGN ? "+" : "-");
  for (int i = 0; i < DATA_BYTES_IN_SMALL_REGISTER; ++i) {
    os << ", " << (int)word.bytes[i];
  }
}
} // namespace mix
