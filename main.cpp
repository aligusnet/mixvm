#include <iostream>
#include <fstream>

#include "mix_printer.h"
#include "mix_machine.h"


int main (int argc, char * const argv[]) {
	std::ofstream ofs_start("start.txt");
	std::ofstream ofs_finish("finish.txt");
	mix::Machine vm;
	
	vm.memory[0] = mix::make_word(0, 0, 50, 0, 5, 8);
	vm.memory[1] = mix::make_word(0, 0, 50, 0, 3, 15);
	vm.memory[2] = mix::make_word(0, 0, 51, 0, 5, 9);
	vm.memory[3] = mix::make_word(0, 0, 51, 0, 5, 10);
	vm.memory[4] = mix::make_word(0, 0, 51, 0, 5, 11);
	vm.memory[5] = mix::make_word(0, 0, 51, 0, 5, 12);
	vm.memory[6] = mix::make_word(0, 0, 51, 0, 5, 13);
	vm.memory[7] = mix::make_word(0, 0, 51, 0, 5, 14);
	vm.memory[8] = mix::make_word(0, 0, 0, 0, 0, 0);
	vm.memory[9] = mix::make_word(0, 0, 0, 0, 0, 5);
	
	vm.memory[50] = mix::make_word(0, 8, 0, 3, 5, 4);
	vm.memory[51] = mix::make_word(0, 0, 0, 0, 11, 11);
	
	vm.print_state(ofs_start);
	
	vm.run(0);
	
	vm.print_state(ofs_finish);
	
    return 0;
}
