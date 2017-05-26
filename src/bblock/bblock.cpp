#include "bblock.h"

BBlock::BBlock(){
	can_jump = false;
}
uint64_t BBlock::getFirstInstructionLocation(){
	return my_instructions[0].getLocation();
}
uint64_t BBlock::getLastInstructionLocation(){
	return my_instructions.back().getLocation();
}
void BBlock::addInstruction(Instruction what){
	my_instructions.push_back(what);
	if(what.getType() == InsType::J){
		//We have to care about this since it conditionally jumps now.
		can_jump = true;
	}
}
void BBlock::setActual(uint64_t what){
	acutal = what;
}
void BBlock::discoverFall(uint64_t loc){
	my_fall_location = loc;
}
void BBlock::discoverJump(){
	if(can_jump){
		my_jump_location = my_instructions.back().getArguement();
	}
}

