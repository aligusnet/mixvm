#include "mix_machine.h"
#include <iostream>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define LOG_COMMAND_NAME(data) \
print_command(std::cout, (data), __FUNCTION__); \
std::cout << std::endl;

namespace mix
{
	compare_t compare(value_type lhs, value_type rhs)
	{
		if (lhs < rhs)
		{
			return cmp_less;
		}
		else if(lhs > rhs)
		{
			return cmp_greater;
		}
		else
		{
			return cmp_equal;
		}

	}

	Machine::Machine()
	{
		memset(this, 0, sizeof(Machine));
	}

	void Machine::print_state(std::ostream &os)
	{
		os << "Register A: ";
		print_word(os, reg_a);
		os << std::endl;
		os << "Register X: ";
		print_word(os, reg_x);
		os << std::endl;
		for (int i = 0; i < SMALL_REGISTERS; ++i)
		{
			os << "Register I" << (i+1) << ":";
			print_small_word(os, reg_i[i]);
			os << std::endl;
		}

		os << "Register J:";
		print_small_word(os, reg_j);
		os << std::endl;

		os << "Override: " << override << std::endl;
		os << "CompareFlag: " << compare_flag << std::endl;
		for (int i = 0; i < MEMORY_WORDS; ++i)
		{
			os << "Memory[" << (i) << "]:";
			print_word(os, memory[i]);
			os << std::endl;
		}
	}

	do_statement *Machine::get_statement(const word &data)
	{
		static do_statement statements[] = {
			&Machine::nop, //0
			&Machine::add,
			&Machine::sub,
			&Machine::mul,
			&Machine::div,
			&Machine::hlt,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::lda,
			&Machine::ld1,
			&Machine::ld2,	//10
			&Machine::ld3,
			&Machine::ld4,
			&Machine::ld5,
			&Machine::ld6,
			&Machine::ldx,
			&Machine::ldan,
			&Machine::ld1n,
			&Machine::ld2n,
			&Machine::ld3n,
			&Machine::ld4n,	//20
			&Machine::ld5n,
			&Machine::ld6n,
			&Machine::ldxn,
			&Machine::sta,
			&Machine::st1,
			&Machine::st2,
			&Machine::st3,
			&Machine::st4,
			&Machine::st5,
			&Machine::st6,	//30
			&Machine::stx,
			&Machine::stj,
			&Machine::stz,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::jump,
			&Machine::ja,	//40
			&Machine::j1,
			&Machine::j2,
			&Machine::j3,
			&Machine::j4,
			&Machine::j5,
			&Machine::j6,
			&Machine::jx,
			&Machine::ena,
			&Machine::en1,
			&Machine::en2,	//50
			&Machine::en3,
			&Machine::en4,
			&Machine::en5,
			&Machine::en6,
			&Machine::enx,
			&Machine::cmpa,
			&Machine::cmp1,
			&Machine::cmp2,
			&Machine::cmp3,
			&Machine::cmp4,	//60
			&Machine::cmp5,
			&Machine::cmp6,
			&Machine::cmpx	//63
		};

		return &statements[data.bytes[byte_c]];
	}

	void Machine::nothing(const word &data)
	{
		std::cerr << "mix: do_nothing!!!\n";
	}

	void Machine::nop(const word &data)	//0
	{
		LOG_COMMAND_NAME(data)
	}

	void Machine::add(const word &data)	//1
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);

		value_type val = get_value(memory[addr], data.bytes[byte_f]);
		val += get_value(reg_a);
		set_value(val, reg_a, override);
	}

	void Machine::sub(const word &data)	//2
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type val = get_value(memory[addr], data.bytes[byte_f]) * -1;
		val += get_value(reg_a);
		set_value(val, reg_a, override);
	}

	void Machine::mul(const word &data)	//3
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);

		long_value_type val1 = get_value(reg_a);
		long_value_type val2 = get_value(memory[addr], data.bytes[byte_f]);
		long_value_type val = val1*val2;
		set_long_value(val, reg_a, reg_x, override);
	}

	void Machine::div(const word &data)	//4
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);

		value_type val_reg_a = get_value(reg_a);
		value_type val_mem = get_value(memory[addr], data.bytes[byte_f]);
		if (abs(val_reg_a) < abs(val_mem))
		{
			long_value_type val = get_long_value(reg_a, reg_x);
			long_value_type quotient = val/val_mem;
			value_type remainder = val - quotient*val_mem;
			set_value((value_type)remainder, reg_x, override);
			reg_x.sign = reg_a.sign;
			set_value((value_type)quotient, reg_a, override);
		}
		else
		{
			override = true;
		}


	}

	void Machine::hlt(const word &data)	//5
	{
		LOG_COMMAND_NAME(data)
		halt = true;
	}


	void Machine::lda(const word &data)	//8
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		memset(&reg_a, 0, sizeof(reg_a));
		set_value(memory[addr], data.bytes[byte_f], reg_a);
		format_range fmt = decode_format(data.bytes[byte_f]);
		int count = DATA_BYTES_IN_WORD - fmt.high;
		if (count > 0)
		{
			right_shift(reg_a, count);
		}
	}

	void Machine::ld1(const word &data)	//9
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[0], override);
	}

	void Machine::ld2(const word &data)	//10
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[1], override);
	}

	void Machine::ld3(const word &data)	//11
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[2], override);
	}

	void Machine::ld4(const word &data)	//12
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[3], override);
	}

	void Machine::ld5(const word &data)	//13
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[4], override);
	}

	void Machine::ld6(const word &data)	//14
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[5], override);
	}

	void Machine::ldx(const word &data)	//15
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		memset(&reg_x, 0, sizeof(reg_x));
		set_value(memory[addr], data.bytes[byte_f], reg_x);
		format_range fmt = decode_format(data.bytes[byte_f]);
		int count = DATA_BYTES_IN_WORD - fmt.high;
		if (count > 0)
		{
			right_shift(reg_x, count);
		}
	}

	void Machine::ldan(const word &data)	//16
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		memset(&reg_a, 0, sizeof(reg_a));
		set_value(memory[addr], data.bytes[byte_f], reg_a);
		format_range fmt = decode_format(data.bytes[byte_f]);
		int count = DATA_BYTES_IN_WORD - fmt.high;
		if (count > 0)
		{
			right_shift(reg_a, count);
		}
		reg_a.sign = !reg_a.sign;
	}

	void Machine::ld1n(const word &data)	//17
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[0], override);
	}

	void Machine::ld2n(const word &data)	//18
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[1], override);
	}

	void Machine::ld3n(const word &data)	//19
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[2], override);
	}

	void Machine::ld4n(const word &data)	//20
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[3], override);
	}

	void Machine::ld5n(const word &data)	//21
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[4], override);
	}

	void Machine::ld6n(const word &data)	//22
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[5], override);
	}

	void Machine::ldxn(const word &data)	//23
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		memset(&reg_x, 0, sizeof(reg_x));
		set_value(memory[addr], data.bytes[byte_f], reg_x);
		format_range fmt = decode_format(data.bytes[byte_f]);
		int count = DATA_BYTES_IN_WORD - fmt.high;
		if (count > 0)
		{
			right_shift(reg_x, count);
		}
		reg_x.sign = !reg_x.sign;
	}

	void Machine::sta(const word &data) //24
	{
		LOG_COMMAND_NAME(data)
		int addr = get_address(data);
		format_range fmt = decode_format(data.bytes[byte_f]);
		int count = DATA_BYTES_IN_WORD - fmt.high;
		big_register tmp_reg = reg_a;
		if (count > 0)
		{
			left_shift(tmp_reg, count);
		}

		set_value(tmp_reg, data.bytes[byte_f], memory[addr]);
	}

	void Machine::st1(const word &data) //25
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type val = get_value(reg_i[0]);
		set_value(val, memory[addr], override);
	}

	void Machine::st2(const word &data) //26
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type val = get_value(reg_i[1]);
		set_value(val, memory[addr], override);
	}

	void Machine::st3(const word &data) //27
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type val = get_value(reg_i[2]);
		set_value(val, memory[addr], override);
	}

	void Machine::st4(const word &data) //28
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type val = get_value(reg_i[3]);
		set_value(val, memory[addr], override);
	}

	void Machine::st5(const word &data) //29
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type val = get_value(reg_i[4]);
		set_value(val, memory[addr], override);
	}

	void Machine::st6(const word &data) //30
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type val = get_value(reg_i[5]);
		set_value(val, memory[addr], override);
	}

	void Machine::stx(const word &data) //31
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		format_range fmt = decode_format(data.bytes[byte_f]);
		int count = DATA_BYTES_IN_WORD - fmt.high;
		big_register tmp_reg = reg_x;
		if (count > 0)
		{
			left_shift(tmp_reg, count);
		}

		set_value(tmp_reg, data.bytes[byte_f], memory[addr]);
	}

	void Machine::stj(const word &data) //32
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type val = get_value(reg_j);
		set_value(val, memory[addr], override);
	}

	void Machine::stz(const word &data) //33
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		word zero;
		memset(&zero, 0, sizeof(zero));
		set_value(zero, data.bytes[byte_f], memory[addr]);

	}

	void Machine::jump(const word &data) //39
	{
		switch (data.bytes[byte_f])
		{
			case 0:
				jmp(data);
				break;
			case 1:
				jsj(data);
				break;
			case 2:
				jov(data);
				break;
			case 3:
				jnov(data);
				break;
			case 4:
				jl(data);
				break;
			case 5:
				je(data);
				break;
			case 6:
				jg(data);
				break;
			case 7:
				jge(data);
				break;
			case 8:
				jne(data);
				break;
			case 9:
				jle(data);
				break;
		};

	}

	void Machine::jmp(const word &data) //39, 0
	{
		LOG_COMMAND_NAME(data)

		value_type addr = get_address(data);
		set_value(addr, reg_j, override);
	}

	void Machine::jsj(const word &data) //39, 1
	{
		LOG_COMMAND_NAME(data)

		//int addr = get_address(data);
		//set_value(addr, reg_j);
	}

	void Machine::jov(const word &data) //39, 2
	{
		LOG_COMMAND_NAME(data)

		if (override)
		{
			override = false;
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jnov(const word &data) //39, 3
	{
		LOG_COMMAND_NAME(data)

		if (!override)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jl(const word &data) //39, 4
	{
		LOG_COMMAND_NAME(data)

		if (compare_flag == cmp_less)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::je(const word &data) //39, 5
	{
		LOG_COMMAND_NAME(data)

		if (compare_flag == cmp_equal)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jg(const word &data) //39, 6
	{
		LOG_COMMAND_NAME(data)

		if (compare_flag == cmp_greater)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jge(const word &data) //39, 7
	{
		LOG_COMMAND_NAME(data)

		if (compare_flag != cmp_less)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jne(const word &data) //39, 8
	{
		LOG_COMMAND_NAME(data)

		if (compare_flag != cmp_equal)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jle(const word &data) //39, 9
	{
		LOG_COMMAND_NAME(data)

		if (compare_flag != cmp_greater)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::ja(const word &data) //40
	{
		switch (data.bytes[byte_f])
		{
			case 0:
				jan(data);
				break;
			case 1:
				jaz(data);
				break;
			case 2:
				jap(data);
				break;
			case 3:
				jann(data);
				break;
			case 4:
				janz(data);
				break;
			case 5:
				janp(data);
				break;
		};

	}

	void Machine::jan(const word &data) //40, 0
	{
		LOG_COMMAND_NAME(data)

		if (reg_a.sign == NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jaz(const word &data) //40, 1
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_a);
		if (val == 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jap(const word &data) //40, 2
	{
		LOG_COMMAND_NAME(data)

        value_type val = get_value(reg_a);
		if (val > 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jann(const word &data) //40, 3
	{
		LOG_COMMAND_NAME(data)

		if (reg_a.sign != NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::janz(const word &data) //40, 4
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_a);
		if (val != 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::janp(const word &data) //40, 5
	{
		LOG_COMMAND_NAME(data)

        value_type val = get_value(reg_a);
		if (val <= 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j1(const word &data) //41
	{
		switch (data.bytes[byte_f])
		{
			case 0:
				j1n(data);
				break;
			case 1:
				j1z(data);
				break;
			case 2:
				j1p(data);
				break;
			case 3:
				j1nn(data);
				break;
			case 4:
				j1nz(data);
				break;
			case 5:
				j1np(data);
				break;
		};

	}

	void Machine::j1n(const word &data) //41, 0
	{
		LOG_COMMAND_NAME(data)

		if (reg_i[0].sign == NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j1z(const word &data) //41, 1
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_i[0]);
		if (val == 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j1p(const word &data) //41, 2
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_i[0]);
		if (val > 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j1nn(const word &data) //41, 3
	{
		LOG_COMMAND_NAME(data)

		if (reg_i[0].sign != NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j1nz(const word &data) //41, 4
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_i[0]);
		if (val != 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j1np(const word &data) //41, 5
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_i[0]);
		if (val <= 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j2(const word &data) //41
	{
		switch (data.bytes[byte_f])
		{
			case 0:
				j2n(data);
				break;
			case 1:
				j2z(data);
				break;
			case 2:
				j2p(data);
				break;
			case 3:
				j2nn(data);
				break;
			case 4:
				j2nz(data);
				break;
			case 5:
				j2np(data);
				break;
		};

	}

	void Machine::j2n(const word &data) //42, 0
	{
		LOG_COMMAND_NAME(data)

		if (reg_i[1].sign == NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j2z(const word &data) //42, 1
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_i[1]);
		if (val == 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j2p(const word &data) //42, 2
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_i[1]);
		if (val > 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j2nn(const word &data) //42, 3
	{
		LOG_COMMAND_NAME(data)

		if (reg_i[1].sign != NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j2nz(const word &data) //42, 4
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_i[1]);
		if (val != 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j2np(const word &data) //42, 5
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_i[1]);
		if (val <= 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j3(const word &data) //43
	{
		switch (data.bytes[byte_f])
		{
			case 0:
				j3n(data);
				break;
			case 1:
				j3z(data);
				break;
			case 2:
				j3p(data);
				break;
			case 3:
				j3nn(data);
				break;
			case 4:
				j3nz(data);
				break;
			case 5:
				j3np(data);
				break;
		};

	}

	void Machine::j3n(const word &data) //43, 0
	{
		LOG_COMMAND_NAME(data)

		if (reg_i[2].sign == NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j3z(const word &data) //43, 1
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_i[2]);
		if (val == 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j3p(const word &data) //43, 2
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_i[2]);
		if (val > 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j3nn(const word &data) //43, 3
	{
		LOG_COMMAND_NAME(data)

		if (reg_i[2].sign != NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j3nz(const word &data) //43, 4
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_i[2]);
		if (val != 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j3np(const word &data) //43, 5
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_i[2]);
		if (val <= 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j4(const word &data) //44
	{
		switch (data.bytes[byte_f])
		{
			case 0:
				j4n(data);
				break;
			case 1:
				j4z(data);
				break;
			case 2:
				j4p(data);
				break;
			case 3:
				j4nn(data);
				break;
			case 4:
				j4nz(data);
				break;
			case 5:
				j4np(data);
				break;
		};

	}

	void Machine::j4n(const word &data) //44, 0
	{
		LOG_COMMAND_NAME(data)

		if (reg_i[3].sign == NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j4z(const word &data) //44, 1
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_i[3]);
		if (val == 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j4p(const word &data) //44, 2
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_i[3]);
		if (val > 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j4nn(const word &data) //44, 3
	{
		LOG_COMMAND_NAME(data)

		if (reg_i[3].sign != NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j4nz(const word &data) //44, 4
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_i[3]);
		if (val != 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j4np(const word &data) //44, 5
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_i[3]);
		if (val <= 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j5(const word &data) //45
	{
		switch (data.bytes[byte_f])
		{
			case 0:
				j5n(data);
				break;
			case 1:
				j5z(data);
				break;
			case 2:
				j5p(data);
				break;
			case 3:
				j5nn(data);
				break;
			case 4:
				j5nz(data);
				break;
			case 5:
				j5np(data);
				break;
		};

	}

	void Machine::j5n(const word &data) //45, 0
	{
		LOG_COMMAND_NAME(data)

		if (reg_i[4].sign == NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j5z(const word &data) //45, 1
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_i[4]);
		if (val == 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j5p(const word &data) //45, 2
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_i[4]);
		if (val > 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j5nn(const word &data) //45, 3
	{
		LOG_COMMAND_NAME(data)

		if (reg_i[4].sign != NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j5nz(const word &data) //45, 4
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_i[4]);
		if (val != 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j5np(const word &data) //45, 5
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_i[4]);
		if (val <= 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j6(const word &data) //46
	{
		switch (data.bytes[byte_f])
		{
			case 0:
				j6n(data);
				break;
			case 1:
				j6z(data);
				break;
			case 2:
				j6p(data);
				break;
			case 3:
				j6nn(data);
				break;
			case 4:
				j6nz(data);
				break;
			case 5:
				j6np(data);
				break;
		};

	}

	void Machine::j6n(const word &data) //46, 0
	{
		LOG_COMMAND_NAME(data)

		if (reg_i[5].sign == NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j6z(const word &data) //46, 1
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_i[5]);
		if (val == 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j6p(const word &data) //46, 2
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_i[5]);
		if (val > 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j6nn(const word &data) //46, 3
	{
		LOG_COMMAND_NAME(data)

		if (reg_i[5].sign != NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j6nz(const word &data) //46, 4
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_i[5]);
		if (val != 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::j6np(const word &data) //46, 5
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_i[5]);
		if (val <= 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jx(const word &data) //47
	{
		switch (data.bytes[byte_f])
		{
			case 0:
				jxn(data);
				break;
			case 1:
				jxz(data);
				break;
			case 2:
				jxp(data);
				break;
			case 3:
				jxnn(data);
				break;
			case 4:
				jxnz(data);
				break;
			case 5:
				jxnp(data);
				break;
		};

	}

	void Machine::jxn(const word &data) //47, 0
	{
		LOG_COMMAND_NAME(data)

		if (reg_x.sign == NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jxz(const word &data) //47, 1
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_x);
		if (val == 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jxp(const word &data) //47, 2
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_x);
		if (val > 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jxnn(const word &data) //47, 3
	{
		LOG_COMMAND_NAME(data)

		if (reg_x.sign != NEG_SIGN)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jxnz(const word &data) //47, 4
	{
		LOG_COMMAND_NAME(data)

		value_type val = get_value(reg_x);
		if (val != 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::jxnp(const word &data) //47, 5
	{
		LOG_COMMAND_NAME(data)

    value_type val = get_value(reg_x);
		if (val <= 0)
		{
			int addr = get_address(data);
			set_value(addr, reg_j, override);
		}
	}

	void Machine::ena(const word &data) //48
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				enta(data);
				break;
			case 3:
				enna(data);
				break;
			default:
				nothing(data);
				break;
		};
	}

	void Machine::en1(const word &data) //49
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				ent1(data);
				break;
			case 3:
				enn1(data);
				break;
			default:
				nothing(data);
				break;
		};
	}

	void Machine::en2(const word &data) //50
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				ent2(data);
				break;
			case 3:
				enn2(data);
				break;
			default:
				nothing(data);
				break;
		};
	}

	void Machine::en3(const word &data) //51
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				ent3(data);
				break;
			case 3:
				enn3(data);
				break;
			default:
				nothing(data);
				break;
		};
	}

	void Machine::en4(const word &data) //52
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				ent4(data);
				break;
			case 3:
				enn4(data);
				break;
			default:
				nothing(data);
				break;
		};
	}

	void Machine::en5(const word &data) //53
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				ent5(data);
				break;
			case 3:
				enn5(data);
				break;
			default:
				nothing(data);
				break;
		};
	}

	void Machine::en6(const word &data) //54
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				ent6(data);
				break;
			case 3:
				enn6(data);
				break;
			default:
				nothing(data);
				break;
		};
	}

	void Machine::enx(const word &data) //55
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				entx(data);
				break;
			case 3:
				ennx(data);
				break;
			default:
				nothing(data);
				break;
		};
	}

	void Machine::enta(const word &data) //48, 2
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_a, override);
	}

	void Machine::ent1(const word &data) //49, 2
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[0], override);
	}

	void Machine::ent2(const word &data) //50, 2
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[1], override);
	}

	void Machine::ent3(const word &data) //51, 2
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[2], override);
	}

	void Machine::ent4(const word &data) //52, 2
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[3], override);
	}

	void Machine::ent5(const word &data) //53, 2
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[4], override);
	}

	void Machine::ent6(const word &data) //54, 2
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[5], override);
	}

	void Machine::entx(const word &data) //55, 2
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_x, override);
	}

	void Machine::enna(const word &data) //48, 3
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_a, override);
		reg_a.sign = !reg_a.sign;
	}

	void Machine::enn1(const word &data) //49, 3
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[0], override);
		reg_i[0].sign = !reg_i[0].sign;
	}

	void Machine::enn2(const word &data) //50, 3
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[1], override);
		reg_i[1].sign = !reg_i[1].sign;
	}

	void Machine::enn3(const word &data) //51, 3
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[2], override);
		reg_i[2].sign = !reg_i[2].sign;
	}

	void Machine::enn4(const word &data) //52, 3
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[3], override);
		reg_i[3].sign = !reg_i[3].sign;
	}

	void Machine::enn5(const word &data) //53, 3
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[4], override);
		reg_i[4].sign = !reg_i[4].sign;
	}

	void Machine::enn6(const word &data) //54, 3
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[5], override);
		reg_i[5].sign = !reg_i[5].sign;
	}

	void Machine::ennx(const word &data) //55, 3
	{
		LOG_COMMAND_NAME(data)

		value_type val = (value_type)get_address(data);
		set_value(val, reg_x, override);
		reg_x.sign = !reg_x.sign;
	}

	void Machine::cmpa(const word &data) //56
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type lhs = get_value(reg_a, data.bytes[byte_f]);
		value_type rhs = get_value(memory[addr], data.bytes[byte_f]);
		compare_flag = compare(lhs, rhs);
	}

	void Machine::cmp1(const word &data) //57
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type lhs = get_value(reg_i[0], data.bytes[byte_f]);
		value_type rhs = get_value(memory[addr], data.bytes[byte_f]);
		compare_flag = compare(lhs, rhs);
	}

	void Machine::cmp2(const word &data) //58
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type lhs = get_value(reg_i[1], data.bytes[byte_f]);
		value_type rhs = get_value(memory[addr], data.bytes[byte_f]);
		compare_flag = compare(lhs, rhs);
	}

	void Machine::cmp3(const word &data) //59
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type lhs = get_value(reg_i[2], data.bytes[byte_f]);
		value_type rhs = get_value(memory[addr], data.bytes[byte_f]);
		compare_flag = compare(lhs, rhs);
	}

	void Machine::cmp4(const word &data) //60
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type lhs = get_value(reg_i[3], data.bytes[byte_f]);
		value_type rhs = get_value(memory[addr], data.bytes[byte_f]);
		compare_flag = compare(lhs, rhs);
	}

	void Machine::cmp5(const word &data) //61
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type lhs = get_value(reg_i[4], data.bytes[byte_f]);
		value_type rhs = get_value(memory[addr], data.bytes[byte_f]);
		compare_flag = compare(lhs, rhs);
	}

	void Machine::cmp6(const word &data) //62
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type lhs = get_value(reg_i[5], data.bytes[byte_f]);
		value_type rhs = get_value(memory[addr], data.bytes[byte_f]);
		compare_flag = compare(lhs, rhs);
	}

	void Machine::cmpx(const word &data) //63
	{
		LOG_COMMAND_NAME(data)

		int addr = get_address(data);
		value_type lhs = get_value(reg_x, data.bytes[byte_f]);
		value_type rhs = get_value(memory[addr], data.bytes[byte_f]);
		compare_flag = compare(lhs, rhs);
	}

	void Machine::run(short initial_address)
	{
		halt = false;
		set_address(reg_j.bytes, initial_address);
		while(!halt)
		{
			short command_addr = get_value(reg_j);
			inc(reg_j, override);
			do_statement statement = *get_statement(memory[command_addr]);
			(this->*statement)(memory[command_addr]);
		}
	}
}
