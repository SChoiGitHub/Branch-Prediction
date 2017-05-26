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
		arguement = Parse::s_to_uint64(line.substr(50,18));
	}else if(line.substr(43,4) == "call"){
		type = InsType::CALL;
	}else if(line.substr(43,3) == "ret"){
		type = InsType::RET;
	}else{
		type = InsType::INS;
	}
}
/*
Instruction::Instruction(uint64_t loc, std::string inputType, uint64_t arg){
	location = loc;
	if(inputType == "JMP  "){
		type = InsType::JMP;
		arguement = arg;
	}else if(inputType.at(0) == 'J'){
		type = InsType::J;
		arguement = arg;
	}else if(inputType == "CALL "){
		type = InsType::CALL;
	}else if(inputType == "RET  "){
		type = InsType::RET;
	}else{
		type = InsType::INS;
	}
}
* */
uint64_t Instruction::getLocation(){
	return location;
}
InsType Instruction::getType(){
	return type;
}
uint64_t Instruction::getArguement(){
	return arguement;
}