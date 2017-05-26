#ifndef __INS_H_
#define __INS_H_

#include <stdint.h>
#include <string>
#include <iostream>


enum class InsType {
    INS, // unhandled case
    JMP, //Unconditional jump
    J, //Jump with conditions
    CALL, //CALL
    RET //RETURN
};

class Instruction{
	public:
		Instruction(); //Blank constructor that should never be used.
		Instruction(std::string& line);
		uint64_t getLocation();
		InsType getType();
		uint64_t getArguement();
	private:
		uint64_t location;
		InsType type;
		uint64_t arguement;
};

#endif
