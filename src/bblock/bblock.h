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
		//Precondition: None
		//Postcondition: BBlock initialized
		BBlock();
		//Precondition: BBlock exists
		//Postcondition: No Changes
		//Return: returns the location of the first instruction in the BBlock
		uint64_t getFirstInstructionLocation(); //Doubles as a getTag()
		//Precondition: BBlock exists
		//Postcondition: No Changes
		//Return: returns the location of the last instruction in the BBlock
		uint64_t getLastInstructionLocation();
		//Precondition: BBlock exists
		//Postcondition: adds an instruction to the instruction vector
		void addInstruction(Instruction what);
		//Precondition: BBlock exists
		//Postcondition: sets the acutal location of this block, as in where it actually goes during its test run.
		void setActual(uint64_t what);
		//Precondition: BBlock exists
		//Postcondition: Sets the fall location to to loc
		void discoverFall(uint64_t loc);
		//Precondition: BBlock exists
		//Postcondition: If this block has a conditional jump, set the jump location of this block to that block's arguement.
		void discoverJump();
		//Precondition: BBlock exists, all_blocks contains information on all BBlocks
		//Postcondition: Adds this block's first address to the parent vectors of the fall, jump, and actual location.
		void discoverParents(std::unordered_map<uint64_t,BBlock>& all_blocks);
		
		//These methods just get the location of fall, jump, and actual locations
		uint64_t get_fall_loc(); 
		uint64_t get_jump_loc();
		uint64_t get_actual_loc();
		
		Instruction getLastInstruction();
		
		bool back_h(int heuristic_number_assignment);
		bool back_h_back_branches_only(int heuristic_number_assignment);
		bool back_h_forward_branches_only(int heuristic_number_assignment);
		bool return_h(int heuristic_number_assignment, std::unordered_map<uint64_t,BBlock>& all_blocks);
		bool call_h(int heuristic_number_assignment, std::unordered_map<uint64_t,BBlock>& all_blocks);
		bool store_h(int heuristic_number_assignment, std::unordered_map<uint64_t,BBlock>& all_blocks);
		bool combined_h(int heuristic_number_assignment, std::unordered_map<uint64_t,BBlock>& all_blocks);
		
		static void printHeuristicInformation();
		
		//These are here for graphing purposes.
		std::vector<uint64_t> existing_parents; //This vector stores the parent BBlocks that exist.
		std::vector<uint64_t> existing_children; //This vector stores the children BBlocks that exist.
	private:
		std::vector<Instruction> my_instructions; //This vector stores the instructions used by this block.
		uint64_t my_jump_location; //This is where the block may jump
		uint64_t my_fall_location; //This is where the block will fall.
		bool has_conditional_jump; //True if it has a conditional jump.
		bool has_store; //True if it has a store instruction
		bool has_call; //True if it has a call instruction
		bool has_return; //True if it has a return instruction
		uint64_t actual; //Where the block actually goes to when it ends.
};

#endif
