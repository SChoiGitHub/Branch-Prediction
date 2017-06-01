#ifndef __PARSE_H_
#define __PARSE_H_

#include <string>
#include <sstream>
#include <memory>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <exception>

#include "../bblock/bblock.h"
class Parse{
	public:
		//Precondition: string contains the part of the instruction line that is between the address and the instruction type.
		//Postcondition: none
		//Return: This returns the size of the instruction.
		static int get_instruction_size(std::string s); //We only need this to get the fall locations.
		//Precondition: s is a uint64 as a string
		//Postcondition: none
		//Return: This parses s as a uint64
		static uint64_t s_to_uint64(std::string s); 
		//Precondition: path is a valid file containing information that can be parsed.
		//Postcondition: none
		//Return: An unordered_map (aka, a Hash table) that relates (or uses as a key) the block tag to the basic blocks that contain that tag. This unordered map contains information on all the BBlocks in the input file.
		static std::unordered_map<uint64_t,BBlock> parse_file(std::string path);
};
#endif
