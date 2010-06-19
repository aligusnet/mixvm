/*
 *  mix_word.cpp
 *  mixvm
 *
 *  Created by Alexander Ignatyev on 19.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "mix_word.h"
#include "format_range.h"

namespace mix
{
	bool is_negative(const word &data)
	{
		return data.sign;
	}
	
	unsigned short get_address(const word &data)
	{
		unsigned short address = 0;
		address += data.bytes[byte_a1] * VALUES_IN_BYTE;
		address += data.bytes[byte_a2];
		if(is_negative(data))
		{
			address *= -1;
		}
		address += data.bytes[byte_i];
		return address;
	}
	
	void right_shift(word &data, int count)
	{
		for(int i = DATA_BYTES_IN_WORD-1; i-count >=   0; --i)
		{
			data.bytes[i] = data.bytes[i-count];
		}
		for(int i = 0; i < count; ++i)
		{
			data.bytes[i] = 0;
		}
	}
	
	void set_value(const word &from, int format, word &to)
	{
		format_range fmt = decode_format(format);
		if(fmt.low < 0) fmt.low = 0;
		if(fmt.high > 5) fmt.high = 5;
		
		if(fmt.low == 0)
		{
			//copy_sign
			to.sign = from.sign;
			++fmt.low; //remove sign
		}
		
		//convert for data bytes
		--fmt.low;
		--fmt.high;
		
		for(int i = 0; i < fmt.low; ++i)
		{
			to.bytes[i] = 0;
		}
		for(int i = fmt.low; i <= fmt.high; ++i)
		{
			to.bytes[i] = from.bytes[i];
		}
		
		int count = DATA_BYTES_IN_WORD - fmt.high - 1;
		if(count > 0)
		{
			right_shift(to, count);
		}
		
	}
	
	value_type get_value(const word &data, byte format)
	{
		format_range fmt = decode_format(format);
		bool negative = false;
		if (fmt.low > 0)
		{	
			--fmt.low;
		}
		else if (is_negative(data))
		{
			negative = true;
		}

		if (fmt.high > 5) fmt.high = 5; 
		int value = 0;
		for (int i = fmt.low; i < fmt.high; ++i)
		{
			value *= VALUES_IN_BYTE;
			value += data.bytes[i];
		}
		if(negative)
		{
			value *= -1;
		}
		return value;
	}
	
	word make_word(bool sign, byte a1, byte a2, byte i, byte f, byte c)
	{
		word result;
		result.sign = sign;
		result.bytes[byte_a1] = a1;
		result.bytes[byte_a2] = a2;
		result.bytes[byte_i] = i;
		result.bytes[byte_f] = f;
		result.bytes[byte_c] = c;
		return result;
	}
	
}