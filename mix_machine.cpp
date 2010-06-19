/*
 *  mix_machine.cpp
 *  mixvm
 *
 *  Created by Alexander Ignatyev on 19.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "mix_machine.h"
#include <iostream>

namespace mix
{	
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
			&Machine::nothing, 
			&Machine::nothing, 
			&Machine::nothing, 
			&Machine::nothing,
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
			&Machine::nothing,
			&Machine::nothing,	//40
			&Machine::nothing, 
			&Machine::nothing, 
			&Machine::nothing, 
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,	//50
			&Machine::nothing, 
			&Machine::nothing, 
			&Machine::nothing, 
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,	//60
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing	//63
		};
		
		return &statements[data.bytes[byte_c]];
	}
	
	void Machine::nothing(const word &data)
	{
		std::cerr << "mix: do_nothing!!!\n";
	}
	
	void Machine::nop(const word &data)	//0
	{
		print_command(std::cout, data, "nop");
		std::cout << std::endl;
	}
	
	void Machine::hlt(const word &data)	//5
	{
		print_command(std::cout, data, "hlt");
		std::cout << std::endl;
		halt = true;
	}
	
	
	void Machine::lda(const word &data)	//8
	{
		print_command(std::cout, data, "lda");
		std::cout << std::endl;
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
		print_command(std::cout, data, "ld1");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[0], override);
	}
	
	void Machine::ld2(const word &data)	//10
	{
		print_command(std::cout, data, "ld2");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[1], override);
	}
	
	void Machine::ld3(const word &data)	//11
	{
		print_command(std::cout, data, "ld3");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[2], override);
	}
	
	void Machine::ld4(const word &data)	//12
	{
		print_command(std::cout, data, "ld4");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[3], override);
	}
	
	void Machine::ld5(const word &data)	//13
	{
		print_command(std::cout, data, "ld5");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[4], override);
	}
	
	void Machine::ld6(const word &data)	//14
	{
		print_command(std::cout, data, "ld6");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[5], override);
	}
	
	void Machine::ldx(const word &data)	//15
	{
		print_command(std::cout, data, "ldx");
		std::cout << std::endl;
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
		print_command(std::cout, data, "ldan");
		std::cout << std::endl;
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
		print_command(std::cout, data, "ld1n");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[0], override);
	}
	
	void Machine::ld2n(const word &data)	//18
	{
		print_command(std::cout, data, "ld2n");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[1], override);
	}
	
	void Machine::ld3n(const word &data)	//19
	{
		print_command(std::cout, data, "ld3n");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[2], override);
	}
	
	void Machine::ld4n(const word &data)	//20
	{
		print_command(std::cout, data, "ld4n");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[3], override);
	}
	
	void Machine::ld5n(const word &data)	//21
	{
		print_command(std::cout, data, "ld5n");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[4], override);
	}
	
	void Machine::ld6n(const word &data)	//22
	{
		print_command(std::cout, data, "ld6n");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[5], override);
	}
	
	void Machine::ldxn(const word &data)	//23
	{
		print_command(std::cout, data, "ldxn");
		std::cout << std::endl;
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
		print_command(std::cout, data, "sta");
		std::cout << std::endl;
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
		print_command(std::cout, data, "st1");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_i[0]);
		set_value(val, memory[addr], override);
	}
	
	void Machine::st2(const word &data) //26
	{
		print_command(std::cout, data, "st2");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_i[1]);
		set_value(val, memory[addr], override);
	}
	
	void Machine::st3(const word &data) //27
	{
		print_command(std::cout, data, "st3");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_i[2]);
		set_value(val, memory[addr], override);
	}
	
	void Machine::st4(const word &data) //28
	{
		print_command(std::cout, data, "st4");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_i[3]);
		set_value(val, memory[addr], override);
	}
	
	void Machine::st5(const word &data) //29
	{
		print_command(std::cout, data, "st5");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_i[4]);
		set_value(val, memory[addr], override);
	}
	
	void Machine::st6(const word &data) //30
	{
		print_command(std::cout, data, "st6");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_i[5]);
		set_value(val, memory[addr], override);
	}
	
	void Machine::stx(const word &data) //31
	{
		print_command(std::cout, data, "stx");
		std::cout << std::endl;
		
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
		print_command(std::cout, data, "stj");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_j);
		set_value(val, memory[addr], override);
	}
	
	void Machine::stz(const word &data) //33
	{
		print_command(std::cout, data, "stz");
		std::cout << std::endl;
		
		int addr = get_address(data);
		word zero;
		memset(&zero, 0, sizeof(zero));
		set_value(zero, data.bytes[byte_f], memory[addr]);
		
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
