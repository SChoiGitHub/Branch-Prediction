#ifndef __PROFILE_H_
#define __PROFILE_H_

#include <memory>
#include <unordered_map>
#include <iostream>
#include <exception>

#include "../bblock/bblock.h"
class Profile{
	public:
		//Precondition: all_blocks is a valid unordered map containing information on the input file's BBlocks
		//Postcondition: none
		static void print_profile(std::unordered_map<uint64_t,BBlock>& all_blocks); //This prints out the information.
};
#endif
