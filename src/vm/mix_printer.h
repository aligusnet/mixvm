/*
 *  mix_printer.h
 *  mixvm
 *
 *  Created by Alexander Ignatyev on 19.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MIX_PRINTER_H
#define MIX_PRINTER_H

#include "mix_small_word.h"
#include <iosfwd>

namespace mix {
void print_small_word(std::ostream &os, const small_word &word);
} // namespace mix

#endif // MIX_PRINTER_H
