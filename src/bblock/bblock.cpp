#include "bblock.h"

BBlock::BBlock(){
	has_conditional_jump = false;
	has_store = false;
	has_return = false;
	has_call = false;
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
	}else{
		switch(what.getType()){
			case InsType::REP_STOS:
				has_store = true;
				break;
			case InsType::RET:
				has_return = true;
				break;
			case InsType::CALL:
				has_call = true;
				break;
			default:
				//Yes, nothing.
				break;
		}
	}
}
void BBlock::setActual(uint64_t what){
	actual = what;
}
void BBlock::discoverParents(std::unordered_map<uint64_t,BBlock>& all_blocks){
	try{
		//Get our fall location's BBlock. Make it know that this block is its parent.
		(all_blocks.at(get_fall_loc())).existing_parents.push_back(this->getFirstInstructionLocation());
		existing_children.push_back(get_fall_loc());
	}catch(std::exception e){
		//Sometimes, we do not have information on the block...
		//This exception catching prevents total shutdown in case it does not exist.
	}
	if(has_conditional_jump){
		//if jump exists, then we have to make it know that this block is its parent.
		try{
			(all_blocks.at(get_jump_loc())).existing_parents.push_back(getFirstInstructionLocation());
			existing_children.push_back(get_jump_loc());
		}catch(std::exception e){
			//Sometimes, we do not have information on the block...
			//This exception catching prevents total shutdown in case it does not exist.
		}
	}
	try{
		//Sometimes, acutal is not a fall location or a jump location.
		(all_blocks.at(actual)).existing_parents.push_back(getFirstInstructionLocation());
		existing_children.push_back(actual);
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
uint64_t BBlock::get_actual_loc(){
	return actual;
}
Instruction BBlock::getLastInstruction(){
	return my_instructions.back();
}
