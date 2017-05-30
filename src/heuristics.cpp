#include <random>
#include <algorithm>

#include "bblock/bblock.h"

int heuristic_count = 5;
std::array<int,5> correct_predictions;
std::array<int,5> total_predictions;
std::array<std::string,5> heuristic_name{
	"General Back Heuristic",
	"Back-Branch Only Back Heuristic",
	"Forward-Branch Only Back Heuristic",
	"Return Heuristic",
	"Call Heuristic"
};
int back_h_assignment = 0;
int back_h_back_branches_only_assignment = 1;
int back_h_forward_branches_only_assignment = 2;
int return_h_assignment = 3;
int call_h_assignment = 4;


/* The back heuristic predicts that jumping occurs if the jump location
 * at a branch is before the instruction to jump in address.
*/
bool BBlock::back_h(){
	if(can_jump){
		//if we can jump, we can use this.
		if(my_jump_location < my_instructions.back().getLocation()){
			//we predict jumping because the jump location is before the instruction to jump.
			if(my_jump_location == actual){
				//We are correct!
				correct_predictions[back_h_assignment]++;
			}
		}else{
			//we predict falling otherwise.
			if(my_fall_location == actual){
				//We are correct!
				correct_predictions[back_h_assignment]++;
			}
		}
		//Right or wrong, we have made a prediction.
		total_predictions[back_h_assignment]++;
		return true; //Shows that this was used.
	}
	return false; //Shows that this was unused.
}

bool BBlock::back_h_back_branches_only(){
	if(can_jump && my_jump_location < my_instructions.back().getLocation()){
		//We can jump and the jump location is before the instruction location.
		//We guess jumping no matter what.
		if(my_jump_location == actual){
			//We are correct!
			correct_predictions[back_h_back_branches_only_assignment]++;
		}

		//Right or wrong, we have made a prediction.
		total_predictions[back_h_back_branches_only_assignment]++;
		return true; //Shows that this was used.
	}
	return false; //Shows that this was unused.
}

bool BBlock::back_h_forward_branches_only(){
	if(can_jump && my_jump_location >= my_instructions.back().getLocation()){
		//We can jump and the jump location is after the instruction location.
		//We guess falling no matter what
		if(my_fall_location == actual){
			//We are correct!
			correct_predictions[back_h_forward_branches_only_assignment]++;
		}

		//Right or wrong, we have made a prediction.
		total_predictions[back_h_forward_branches_only_assignment]++;
		return true; //Shows that this was used.
	}
	return false; //Shows that this was unused.
}

/* The Return heuristic checks if there are any returns in either side
 * of the branch. If there is a return, predict the one that does not
 * have it. If both or neither have returns, then this heuristic fails.
*/

bool BBlock::return_h(std::unordered_map<uint64_t,BBlock>& all_blocks){
	try{
		if(can_jump){
			//These lines search the fall and jump block of a return.
			bool jump_has_ret = false;
			for(Instruction i : all_blocks.at(my_jump_location).my_instructions){
				if(i.getType() ==  InsType::RET){
					jump_has_ret = true;
					break;
				}
			}
			
			bool fall_has_ret = false;
			for(Instruction i : all_blocks.at(my_fall_location).my_instructions){
				if(i.getType() ==  InsType::RET){
					fall_has_ret = true;
					break;
				}
			}
			
			if(fall_has_ret == jump_has_ret){
				return false; //This failed because both either have or does not have a return
			}else if(fall_has_ret){
				//fall has return, so we guess the jump
				if(my_jump_location == actual){
					//correct!
					correct_predictions[return_h_assignment]++;
				}
				//regardless, we guessed
				total_predictions[return_h_assignment]++;
				
				return true; //This heuristic worked.
			}else{
				//jump MUST HAVE return, so we guess fall
				if(my_fall_location == actual){
					//correct!
					correct_predictions[return_h_assignment]++;
				}
				//regardless, we guessed
				total_predictions[return_h_assignment]++;
				
				return true; //This heuristic worked.
			}
			
		}else{
			return false; //This shows this search was unused.
		}
	}catch(std::exception e){
		return false; //This heuristic failed.
	}
}

/* The Call heuristic checks if there are any call in either side
 * of the branch. If there is a call, predict the one that does
 * have it. If both or neither have calls, then this heuristic fails.
*/

bool BBlock::call_h(std::unordered_map<uint64_t,BBlock>& all_blocks){
	try{
		if(can_jump){
			
			//These lines search the fall and jump block of a return.
			bool jump_has_call = false;
			for(Instruction i : all_blocks.at(my_jump_location).my_instructions){
				if(i.getType() ==  InsType::CALL){
					jump_has_call = true;
					break;
				}
			}
			
			bool fall_has_call = false;
			for(Instruction i : all_blocks.at(my_fall_location).my_instructions){
				if(i.getType() ==  InsType::CALL){
					fall_has_call = true;
					break;
				}
			}
			
			if(jump_has_call == fall_has_call){
				return false; //This failed because both either have or does not have a call
			}else if(jump_has_call){
				//jump has call, so we guess the jump
				if(my_jump_location == actual){
					//correct!
					correct_predictions[call_h_assignment]++;
				}
				//regardless, we guessed.
				total_predictions[call_h_assignment]++;
				
				return true; //This heuristic worked.
			}else{
				//fall MUST HAVE return, so we guess fall
				if(my_fall_location == actual){
					//correct!
					correct_predictions[call_h_assignment]++;
				}
				//regardless, we guessed.
				total_predictions[call_h_assignment]++;
				
				return true; //This heuristic worked.
			}
			
		}else{
			return false; //This shows this search was unused.
		}
	}catch(std::exception e){
		return false; //This heuristic failed.
	}
}

void BBlock::printHeuristicInformation(){
	for(int x = 0; x < heuristic_count; x++){
		std::cout << heuristic_name[x] << ": There were " << correct_predictions[x] << " correct predictions out of " << total_predictions[x] << " total predictions. (" << (100.0*correct_predictions[x]/total_predictions[x]) << "% Success)\n";
	}
}
