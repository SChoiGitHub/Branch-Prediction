#include "instruction.h"



#include "../parse/parse.h"

std::unordered_map<std::string,InsType> stringToInstruction({
    {"INS",InsType::INS}, // unhandled case
    {"CALL",InsType::CALL}, //CALL
    {"RET",InsType::RET}, //RETURN
    {"REP STOS",InsType::REP_STOS},  // A Store Command
    {"JMP",InsType::JMP},   // Unconditional jmp
    {"JO",InsType::JO},    // Jump if overflow
    {"JNO",InsType::JNO},   // Jump if not overflow
    {"JS",InsType::JS},    // Jump if sign
    {"JNS",InsType::JNS},   // Jump if not sign
    {"JE",InsType::JE},    // Jump if equal
    {"JZ",InsType::JZ},    // Jump if zero
    {"JNE",InsType::JNE},   // Jump if not equal
    {"JNZ",InsType::JNZ},   // Jump if not zero
    {"JB",InsType::JB},    // Jump if below
    {"JNAE",InsType::JNAE},  // Jump if not above or equal
    {"JC",InsType::JC},    // Jump if carry
    {"JNB",InsType::JNB},   // Jump if not below
    {"JAE",InsType::JAE},   // Jump if above or equal
    {"JNC",InsType::JNC},   // Jump if not carry
    {"JBE",InsType::JBE},   // Jump if below or equal
    {"JNA",InsType::JNA},   // Jump if not above
    {"JA",InsType::JA},    // Jump if above
    {"JNBE",InsType::JNBE},  // Jump if not below or equal
    {"JL",InsType::JL},    // Jump if less
    {"JNGE",InsType::JNGE},  // Jump if not greater or equal
    {"JGE",InsType::JGE},   // Jump if greater or equal
    {"JNL",InsType::JNL},   // Jump if not less
    {"JLE",InsType::JLE},   // Jump if less or equal
    {"JNG",InsType::JNG},   // Jump if not greater
    {"JG",InsType::JG},    // Jump if greater
    {"JNLE",InsType::JNLE},  // Jump if not less or equal
    {"JP",InsType::JP},    // Jump if parity
    {"JPE",InsType::JPE},   // Jump if parity even
    {"JNP",InsType::JNP},   // Jump if not parity
    {"JPO",InsType::JPO},   // Jump if parity odd
    {"JCXZ",InsType::JCXZ},  // Jump if %CX register is 0
    {"JECXZ",InsType::JECXZ}  // Jump if $ECX register is 0
});

Instruction::Instruction(){
	
}
Instruction::Instruction(std::string& line){
	location = Parse::s_to_uint64(line.substr(2,18));
	try{
		//We can TRY to parse the file to give us the type.
		type = stringToInstruction.at(processInstructionType(line.substr(43,8)));
		if(isJump()){
			arguement = Parse::s_to_uint64(line.substr(51,18));
		}
	}catch(std::exception e){
		//This is an unhandled case
		type = InsType::INS;
	}
}
std::string Instruction::processInstructionType(std::string input){
	if(input == "rep stos"){
		std::cout << "found rep stos\n";
	}
	
	
	
	std::string processed_output = "";
	bool was_spaced = false;
	for(char i : input){
		if('a' <= i && i <= 'z'){
			if(was_spaced){
				processed_output +=  ' ';
				was_spaced = false;
			}
			processed_output +=  (char) toupper(i);
		}else{
			was_spaced = true;
		}	
	}
	return processed_output;
}
uint64_t Instruction::getLocation(){
	return location;
}
InsType Instruction::getType(){
	return type;
}
uint64_t Instruction::getArguement(){
	return arguement;
}
bool Instruction::isJump(){
	return (InsType::JMP <= type && type <= InsType::JECXZ);
}
