#ifndef __INS_H_
#define __INS_H_

#include <stdint.h>
#include <string>
#include <iostream>
#include <unordered_map>

enum class InsType {
    INS, // unhandled case
    CALL, //CALL
    RET, //RETURN
    REP_STOS, //A store command
    JMP,   // Unconditional jmp
    JO,    // Jump if overflow
    JNO,   // Jump if not overflow
    JS,    // Jump if sign
    JNS,   // Jump if not sign
    JE,    // Jump if equal
    JZ,    // Jump if zero
    JNE,   // Jump if not equal
    JNZ,   // Jump if not zero
    JB,    // Jump if below
    JNAE,  // Jump if not above or equal
    JC,    // Jump if carry
    JNB,   // Jump if not below
    JAE,   // Jump if above or equal
    JNC,   // Jump if not carry
    JBE,   // Jump if below or equal
    JNA,   // Jump if not above
    JA,    // Jump if above
    JNBE,  // Jump if not below or equal
    JL,    // Jump if less
    JNGE,  // Jump if not greater or equal
    JGE,   // Jump if greater or equal
    JNL,   // Jump if not less
    JLE,   // Jump if less or equal
    JNG,   // Jump if not greater
    JG,    // Jump if greater
    JNLE,  // Jump if not less or equal
    JP,    // Jump if parity
    JPE,   // Jump if parity even
    JNP,   // Jump if not parity
    JPO,   // Jump if parity odd
    JCXZ,  // Jump if %CX register is 0
    JECXZ  // Jump if $ECX register is 0
};

class Instruction{
	public:
		Instruction(); //Blank constructor that should never be used.
		//Precondition: line contains instruction details.
		//Postcondition: instruction is created
		Instruction(std::string& line);
		//Precondition: string contains the instruction type.
		//Postcondition: none
		//Return: This parses the input, turning it into an InsType
		static std::string processInstructionType(const std::string& input);
		//Precondition: Instruction exists.
		//Postcondition: none.
		//Return: if this instruction is a jump (both unconditional and conditional), return true. Otherwise, false.
		bool isJump();
		
		//The methods below are self-explanatory. They are get methods.
		uint64_t getLocation();
		InsType getType();
		uint64_t getArguement();

	private:
		uint64_t location;
		InsType type;
		uint64_t arguement;
};

#endif
