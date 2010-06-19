/*
 *  format_range.cpp
 *  mixvm
 *
 *  Created by Alexander Ignatyev on 19.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "format_range.h"

namespace mix
{
	format_range decode_format(byte f)
	{
		format_range fmt;
		fmt.low = f/(8);
		fmt.high = f - fmt.low*8;
		return fmt;
	}
	
	byte encode_format(format_range fmt)
	{
		return fmt.low*8+fmt.high;
	}
	
	byte encode_format(byte low, byte high)
	{
		return low*8+high;
	}
}