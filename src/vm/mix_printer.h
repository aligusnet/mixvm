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
#include "mix_word.h"
#include <iosfwd>

namespace mix {
void print_small_word(std::ostream &os, const small_word &word);
void print_word(std::ostream &os, const word &word);
void print_command(std::ostream &os, const word &command, const char *command_name);
} // namespace mix

#endif // MIX_PRINTER_H
