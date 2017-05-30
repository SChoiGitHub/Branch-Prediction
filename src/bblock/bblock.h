#ifndef __BBLOCK_H_
#define __BBLOCK_H_

#include <memory>
#include <vector>
#include <exception>
#include <string>
#include <functional>
#include <unordered_map>

#include "../instruction/instruction.h"




class BBlock{
	public:
		BBlock();
		uint64_t getFirstInstructionLocation(); //Doubles as a getTag()
		uint64_t getLastInstructionLocation();
		void addInstruction(Instruction what); //Pushes an instruction.
		void setActual(uint64_t what);
		void discoverFall(uint64_t loc);
		void discoverJump();
		void discoverParents(std::unordered_map<uint64_t,BBlock>& all_blocks);
		uint64_t get_fall_loc(); 
		uint64_t get_jump_loc();
		bool canJump();
		
		
		bool back_h(int heuristic_number_assignment);
		bool back_h_back_branches_only(int heuristic_number_assignment);
		bool back_h_forward_branches_only(int heuristic_number_assignment);
		bool return_h(std::unordered_map<uint64_t,BBlock>& all_blocks, int heuristic_number_assignment);
		bool call_h(std::unordered_map<uint64_t,BBlock>& all_blocks, int heuristic_number_assignment);
		bool combined_h(std::unordered_map<uint64_t,BBlock>& all_blocks, int heuristic_number_assignment);
			
		static void printHeuristicInformation();
		
		std::vector<uint64_t> parents;
	private:
		std::vector<Instruction> my_instructions;
		uint64_t my_jump_location; //This is where the block may jump
		uint64_t my_fall_location; //This is where the block will fall.
		bool can_jump; //True if it has a conditional jump.
		uint64_t actual;
};


#endif
