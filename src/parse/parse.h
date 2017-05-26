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
		static int get_instruction_size(std::string s);
		static uint64_t s_to_uint64(std::string s);
		static std::unordered_map<uint64_t,BBlock> parse_file(std::string path);
};
#endif
