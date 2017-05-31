#ifndef __PROFILE_H_
#define __PROFILE_H_

#include <memory>
#include <unordered_map>
#include <iostream>
#include <exception>

#include "../bblock/bblock.h"
class Profile{
	public:
		static void profile(std::unordered_map<uint64_t,BBlock> all_blocks);
};
#endif
