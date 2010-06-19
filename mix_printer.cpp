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
#include "format_range.h"

namespace mix
{
	void print_small_word(std::ostream &os, const small_word &word)
	{
		os << word.sign;
		for(int i = 0; i < DATA_BYTES_IN_SMALL_REGISTER; ++i)
		{
			os << ", " << (int)word.bytes[i];
		}
	}
	
	void print_word(std::ostream &os, const word &word)
	{
		os << word.sign;
		for(int i = 0; i < DATA_BYTES_IN_WORD; ++i)
		{
			os << ", " << (int)word.bytes[i];
		}
	}
	
	void print_command(std::ostream &os, const word &command, const char *command_name)
	{
		os << command_name << "\t" << (unsigned)get_address(command) << "," << (unsigned)command.bytes[byte_i];
		format_range fmt = decode_format(command.bytes[byte_f]);
		os << "(" << (int)fmt.low << ":" << (int)fmt.high << ")";
	}
}