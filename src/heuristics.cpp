#include <random>
#include <algorithm>

#include "bblock/bblock.h"

std::array<int,1> correctPredictions;
std::array<int,1> totalPredictions;
int back_h_assignment = 0;

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
				correctPredictions[back_h_assignment]++;
			}
		}else{
			//we predict falling otherwise.
			if(my_fall_location == acutal){
				//We are correct!
				correctPredictions[back_h_assignment]++;
			}
		}
		//Right or wrong, we have made a prediction.
		totalPredictions[back_h_assignment]++;
		return true; //Shows that this was used.
	}
	return false; //Shows that this was unused.
}
void BBlock::printHeuristicInformation(){
	for(int x = 0; x < 1; x++){
		std::cout << "Heuristic #" << (x+1) << ": There were " << correctPredictions[x] << " correct predictions out of " << totalPredictions[x] << " total predictions. (" << (100.0*correctPredictions[x]/totalPredictions[x]) << "% Success)\n";
	}
}
