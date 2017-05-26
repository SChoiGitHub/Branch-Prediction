#include <random>
#include <algorithm>

#include "bblock/bblock.h"

int heuristic_count = 3;
std::array<int,3> correct_predictions;
std::array<int,3> total_predictions;
std::array<std::string,3> heuristic_name{
	"General Back Heuristic",
	"Back-Branch Only Back Heuristic",
	"Forward-Branch Only Back Heuristic"
};
int back_h_assignment = 0;
int back_h_back_branches_only_assignment = 1;
int back_h_forward_branches_only_assignment = 2;

/* The back heuristic predicts that jumping occurs if the jump location
 * at a branch is before the instruction to jump in address.
*/
bool BBlock::back_h(){
	if(can_jump){
		//if we can jump, we can use this.
		if(my_jump_location < my_instructions.back().getLocation()){
			//we predict jumping because the jump location is before the instruction to jump.
			if(my_jump_location == acutal){
				//We are correct!
				correct_predictions[back_h_assignment]++;
			}
		}else{
			//we predict falling otherwise.
			if(my_fall_location == acutal){
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
		if(my_jump_location == acutal){
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
		if(my_fall_location == acutal){
			//We are correct!
			correct_predictions[back_h_forward_branches_only_assignment]++;
		}

		//Right or wrong, we have made a prediction.
		total_predictions[back_h_forward_branches_only_assignment]++;
		return true; //Shows that this was used.
	}
	return false; //Shows that this was unused.
}

void BBlock::printHeuristicInformation(){
	for(int x = 0; x < heuristic_count; x++){
		std::cout << heuristic_name[x] << ": There were " << correct_predictions[x] << " correct predictions out of " << total_predictions[x] << " total predictions. (" << (100.0*correct_predictions[x]/total_predictions[x]) << "% Success)\n";
	}
}
