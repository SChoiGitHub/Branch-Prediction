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
void BBlock::discoverParents(std::unordered_map<uint64_t,BBlock>& all_blocks){
	if(all_blocks.find(get_fall_loc()) != all_blocks.end()){
		//if fall exists, then we have to make it know that this block is its parent.
		all_blocks.at(get_fall_loc()).parents.push_back(getFirstInstructionLocation());
	}
	if(all_blocks.find(get_jump_loc()) != all_blocks.end() && can_jump){
		//if jump exists, then we have to make it know that this block is its parent.
		all_blocks.at(get_jump_loc()).parents.push_back(getFirstInstructionLocation());
	}
}
void BBlock::discoverFall(uint64_t loc){
	my_fall_location = loc;
}
void BBlock::discoverJump(){
	if(can_jump){
		my_jump_location = my_instructions.back().getArguement();
	}
}
uint64_t BBlock::get_fall_loc(){
	return my_fall_location;
}
uint64_t BBlock::get_jump_loc(){
	return my_jump_location;
}
bool BBlock::canJump(){
	return can_jump;
}
