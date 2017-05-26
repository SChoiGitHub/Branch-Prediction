#ifndef __BBLOCK_H_
#define __BBLOCK_H_

#include <memory>
#include <vector>
#include <exception>
#include <string>
#include <functional>

#include "../instruction/instruction.h"




class BBlock{
	public:
		BBlock();
		uint64_t getFirstInstructionLocation(); //Doubles as a getTag()
		void addInstruction(Instruction what); //Pushes an instruction.
		void setActual(uint64_t what);
		void discoverFall(uint64_t loc);
		void discoverJump();
		
		void back_h();
		

		
		static void printHeuristicInformation();
	private:
		std::vector<Instruction> my_instructions;
		uint64_t my_jump_location;
		uint64_t my_fall_location;
		bool can_jump; //True if it has a conditional jump.
		uint64_t acutal;
};


#endif
