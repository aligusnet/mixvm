/*
 *  word.h
 *  mixvm
 *
 *  Created by Alexander Ignatyev on 19.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MIX_WORD_H
#define MIX_WORD_H

#include "mix_byte.h"
#include "format_range.h"

namespace mix
{
	//const int SIGN_BYTES_IN_WORD = 1;
	const int DATA_BYTES_IN_WORD = 5;
	//const int BYTES_IN_WORD = DATA_BYTES_IN_WORD+SIGN_BYTES_IN_WORD;
	const int VALUES_IN_WORD = VALUES_IN_BYTE*VALUES_IN_BYTE*VALUES_IN_BYTE*VALUES_IN_BYTE*VALUES_IN_BYTE; //DATA_BYTES_IN_WORD times
	
	struct word
	{
		bool sign;
		byte bytes[DATA_BYTES_IN_WORD];
	};
	
	enum bytes_format
	{
		byte_a1 = 0,
		byte_a2 = 1,
		byte_i = 2,
		byte_f = 3,
		byte_c = 4
	};
	
	bool is_negative(const word &data);
	unsigned short get_address(const word &data);
	void right_shift(word &data, int count);
	void left_shift(word &data, int count);
	void set_value(const word &from, int format, word &to);
	void set_value(value_type val, word &to, bool &override);
	value_type get_value(const word &data, byte format = DEFAULT_FORMAT);
	void set_address(byte *bytes, short addr);
	word make_word(bool sign, byte a1, byte a2, byte i, byte f, byte c);
	word make_cmd(byte cmd, short addr, byte f);
	
}

#endif //MIX_WORD_H
