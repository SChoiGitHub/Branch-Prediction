#include "instruction.h"



#include "../parse/parse.h"

Instruction::Instruction(){
	
}
Instruction::Instruction(std::string& line){
	
	location = Parse::s_to_uint64(line.substr(2,18));
	if(line.substr(43,1) == "j"){
		if(line.substr(44,2) == "mp"){
			type = InsType::JMP;
		}else{
			type = InsType::J;
		}
		arguement = Parse::s_to_uint64(line.substr(51,18));
	}else if(line.substr(43,4) == "call"){
		type = InsType::CALL;
	}else if(line.substr(43,3) == "ret"){
		type = InsType::RET;
	}else{
		type = InsType::INS;
	}
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
