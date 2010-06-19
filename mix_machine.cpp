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
	void set_address(byte *bytes, short addr)
	{
		bytes[0] = addr/VALUES_IN_BYTE;
		bytes[1] = addr - bytes[0]*VALUES_IN_BYTE;
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
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,	//20
			&Machine::nothing, 
			&Machine::nothing, 
			&Machine::nothing, 
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,	//30
			&Machine::nothing, 
			&Machine::nothing, 
			&Machine::nothing, 
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
		set_value(memory[addr], data.bytes[byte_f], reg_a);
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
		set_value(memory[addr], data.bytes[byte_f], reg_x);
	}
	
	void Machine::run(short initial_address)
	{
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