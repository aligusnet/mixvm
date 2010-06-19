/*
 *  format_range.h
 *  mixvm
 *
 *  Created by Alexander Ignatyev on 19.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FORMAT_RANGE_H
#define FORMAT_RANGE_H

#include "mix_byte.h"
namespace mix
{
	const byte DEFAULT_FORMAT = 5;
	struct format_range
	{
		byte low;
		byte high;
	};
	
	format_range decode_format(byte f);
	byte encode_format(format_range fmt);
	byte encode_format(byte low, byte high);
}

#endif //FORMAT_RANGE_H