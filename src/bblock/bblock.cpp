#include "bblock.h"

BBlock::BBlock(){
	has_conditional_jump = false;
}
uint64_t BBlock::getFirstInstructionLocation(){
	return my_instructions[0].getLocation();
}
uint64_t BBlock::getLastInstructionLocation(){
	return my_instructions.back().getLocation();
}
void BBlock::addInstruction(Instruction what){
	my_instructions.push_back(what);
	if(what.isJump() && what.getType() != InsType::JMP){
		//We have to care about this since it conditionally jumps now.
		has_conditional_jump = true;
	}
}
void BBlock::setActual(uint64_t what){
	actual = what;
}
void BBlock::discoverParents(std::unordered_map<uint64_t,BBlock>& all_blocks){
	try{
		//Get our fall location's BBlock. Make it know that this block is its parent.
		(all_blocks.at(get_fall_loc())).parents.push_back(this->getFirstInstructionLocation());
	}catch(std::exception e){
		//Sometimes, we do not have information on the block...
		//This exception catching prevents total shutdown in case it does not exist.
	}
	if(has_conditional_jump){
		//if jump exists, then we have to make it know that this block is its parent.
		try{
			(all_blocks.at(get_jump_loc())).parents.push_back(this->getFirstInstructionLocation());
		}catch(std::exception e){
			//Sometimes, we do not have information on the block...
			//This exception catching prevents total shutdown in case it does not exist.
		}
	}
	try{
		//Sometimes, acutal is not a fall location or a jump location.
		(all_blocks.at(actual)).parents.push_back(this->getFirstInstructionLocation());
	}catch(std::exception e){
		//In case something goes horribly wrong.
		//The last block may not have a BBlock, since it does not have an actual.
	}
}
void BBlock::discoverFall(uint64_t loc){
	my_fall_location = loc;
}
void BBlock::discoverJump(){
	if(has_conditional_jump){
		my_jump_location = my_instructions.back().getArguement();
	}
}
uint64_t BBlock::get_fall_loc(){
	return my_fall_location;
}
uint64_t BBlock::get_jump_loc(){
	return my_jump_location;
}
bool BBlock::conditional_jump(){
	return has_conditional_jump;
}
