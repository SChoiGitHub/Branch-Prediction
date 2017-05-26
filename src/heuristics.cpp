#include <random>
#include <algorithm>

#include "bblock/bblock.h"

std::array<int,1> correctPredictions = {0};
std::array<int,1> totalPredictions = {0};


/* The back heuristic predicts that jumping occurs if the jump location
 * at a branch is before the instruction to jump in address.
*/
void BBlock::back_h(){
	if(can_jump){
		//if we can jump, we check this.
		if(my_jump_location < my_instructions.back().getLocation()){
			//we predict jumping because the jump location is before the instruction to jump.
			if(my_jump_location == acutal){
				//We are correct!
				correctPredictions[0]++;
			}
		}else{
			//we predict falling otherwise.
			if(my_fall_location == acutal){
				//We are correct!
				correctPredictions[0]++;
			}
		}
		//Right or wrong, we have made a prediction.
		totalPredictions[0]++;
	}
}
void BBlock::printHeuristicInformation(){
	for(int x = 0; x < 1; x++){
		std::cout << "Heuristic #" << (x+1) << ": There were " << totalPredictions[x] << " total predictions and " << correctPredictions[x] << " were correct.\n";
	}
}
