#include <random>
#include <algorithm>

#include "bblock/bblock.h"

int heuristic_count = 7;
std::array<int,7> correct_predictions;
std::array<int,7> total_predictions;
std::array<std::string,7> heuristic_name{
	"General Back Heuristic",
	"Back-Branch Only Back Heuristic",
	"Forward-Branch Only Back Heuristic",
	"Return Heuristic",
	"Call Heuristic",
	"Store Heuristic",
	"Combined Heuristic"
};

/* The back heuristic predicts that jumping occurs if the jump location
 * at a branch is before the instruction to jump in address.
*/
bool BBlock::back_h(int heuristic_number_assignment){
	if(has_conditional_jump){
		//if we can jump, we can use this.
		if(my_jump_location < my_instructions.back().getLocation()){
			//we predict jumping because the jump location is before the instruction to jump.
			if(my_jump_location == actual){
				//We are correct!
				correct_predictions[heuristic_number_assignment]++;
			}
		}else{
			//we predict falling otherwise.
			if(my_fall_location == actual){
				//We are correct!
				correct_predictions[heuristic_number_assignment]++;
			}
		}
		//Right or wrong, we have made a prediction.
		total_predictions[heuristic_number_assignment]++;
		return true; //Shows that this was used.
	}
	return false; //Shows that this was unused.
}

bool BBlock::back_h_back_branches_only(int heuristic_number_assignment){
	if(has_conditional_jump && my_jump_location < my_instructions.back().getLocation()){
		//std::cout << this->getFirstInstructionLocation() << '\n'; //Debug
		
		
		//We can jump and the jump location is before the instruction location.
		//We guess jumping no matter what.
		if(my_jump_location == actual){
			//We are correct!
			correct_predictions[heuristic_number_assignment]++;
		}

		//Right or wrong, we have made a prediction.
		total_predictions[heuristic_number_assignment]++;
		return true; //Shows that this was used.
	}
	return false; //Shows that this was unused.
}

bool BBlock::back_h_forward_branches_only(int heuristic_number_assignment){
	if(has_conditional_jump && my_jump_location >= my_instructions.back().getLocation()){
		//We can jump and the jump location is after the instruction location.
		//We guess falling no matter what
		if(my_fall_location == actual){
			//We are correct!
			correct_predictions[heuristic_number_assignment]++;
		}

		//Right or wrong, we have made a prediction.
		total_predictions[heuristic_number_assignment]++;
		return true; //Shows that this was used.
	}
	return false; //Shows that this was unused.
}

/* The Return heuristic checks if there are any returns in either side
 * of the branch. If there is a return, predict the one that does not
 * have it. If both or neither have returns, then this heuristic fails.
*/

bool BBlock::return_h(int heuristic_number_assignment, std::unordered_map<uint64_t,BBlock>& all_blocks){
	try{
		if(has_conditional_jump){
			if(all_blocks.at(my_fall_location).has_return == all_blocks.at(my_jump_location).has_return){
				return false; //This failed because both either have or does not have a return
			}else if(all_blocks.at(my_fall_location).has_return){
				//fall has return, so we guess the jump
				if(my_jump_location == actual){
					//correct!
					correct_predictions[heuristic_number_assignment]++;
				}
				//regardless, we guessed
				total_predictions[heuristic_number_assignment]++;
				return true; //This heuristic worked.
			}else{
				//jump MUST HAVE return, so we guess fall
				if(my_fall_location == actual){
					//correct!
					correct_predictions[heuristic_number_assignment]++;
				}
				//regardless, we guessed
				total_predictions[heuristic_number_assignment]++;
				return true; //This heuristic worked.
			}
			
		}else{
			return false; //This shows this search was unused.
		}
	}catch(std::exception e){
		//Sometimes, the parsing does not get information on a possible
		//jump because the input file does not have the information.
		return false; //This heuristic failed.
	}
}

/* The Call heuristic checks if there are any call in either side
 * of the branch. If there is a call, predict the one that does
 * have it. If both or neither have calls, then this heuristic fails.
*/

bool BBlock::call_h(int heuristic_number_assignment, std::unordered_map<uint64_t,BBlock>& all_blocks){
	try{
		if(has_conditional_jump){	
			if(all_blocks.at(my_jump_location).has_call == all_blocks.at(my_fall_location).has_call){
				return false; //This failed because both either have or does not have a call
			}else if(all_blocks.at(my_jump_location).has_call){
				//jump has call, so we guess the jump
				if(my_jump_location == actual){
					//correct!
					correct_predictions[heuristic_number_assignment]++;
				}
				//regardless, we guessed.
				total_predictions[heuristic_number_assignment]++;
				return true; //This heuristic worked.
			}else{
				//fall MUST HAVE return, so we guess fall
				if(my_fall_location == actual){
					//correct!
					correct_predictions[heuristic_number_assignment]++;
				}
				//regardless, we guessed.
				total_predictions[heuristic_number_assignment]++;
				return true; //This heuristic worked.
			}
		}else{
			return false; //This shows this search was unused.
		}
	}catch(std::exception e){
		//Sometimes, the parsing does not get information on a possible
		//jump because the input file does not have the information.
		return false; //This heuristic failed.
	}
}

/* The store heuristic predicts that when one of the branches has a store,
 * we will predict the branch that does not have a store.
*/

bool BBlock::store_h(int heuristic_number_assignment, std::unordered_map<uint64_t,BBlock>& all_blocks){
	try{
		if(has_conditional_jump){
			
			
			if(all_blocks.at(my_jump_location).has_store == all_blocks.at(my_fall_location).has_store){
				return false; //This failed because both either have or does not have a store
			}else if(all_blocks.at(my_jump_location).has_store){
				//jump has store, so we guess the fall
				if(my_fall_location == actual){
					//correct!
					correct_predictions[heuristic_number_assignment]++;
				}
				//regardless, we guessed.
				total_predictions[heuristic_number_assignment]++;
				return true; //This heuristic worked.
			}else{
				//fall MUST HAVE store, so we guess jump
				if(my_jump_location == actual){
					//correct!
					correct_predictions[heuristic_number_assignment]++;
				}
				//regardless, we guessed.
				total_predictions[heuristic_number_assignment]++;
				return true; //This heuristic worked.
			}
			
		}else{
			return false; //This shows this search was unused.
		}
	}catch(std::exception e){
		//Sometimes, the parsing does not get information on a possible
		//jump because the input file does not have the information.
		return false; //This heuristic failed.
	}
	return false; //The heuristic was not applied
}

/* The combined heuristic uses multiple heuristics in a certain order
 * until it finds one that can work. It can fail in somecases.
*/

bool BBlock::combined_h(int heuristic_number_assignment, std::unordered_map<uint64_t,BBlock>& all_blocks){
	if(return_h(heuristic_number_assignment, all_blocks)){
		return true;
	}else if(call_h(heuristic_number_assignment, all_blocks)){
		return true;
	}else if(back_h(heuristic_number_assignment)){
		return true;
	}
	
	return false;
}

void BBlock::printHeuristicInformation(){
	std::cout << "Here are your results:\n";
	for(int x = 0; x < heuristic_count; x++){
		std::cout << '\t' << heuristic_name[x] << ": There were " << correct_predictions[x] << " correct predictions out of " << total_predictions[x] << " total predictions. (" << (100.0*correct_predictions[x]/total_predictions[x]) << "% Success)\n";
	}
}
