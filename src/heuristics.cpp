#include <random>
#include <algorithm>

#include "bblock/bblock.h"

std::array<int,1> correctPredictions = {0};
std::array<int,1> totalPredictions = {0};

void BBlock::back_h(){
	
	if(can_jump){
		if(my_jump_location < my_instructions.back().getLocation()){
			if(my_jump_location == acutal){
				correctPredictions[0]++;
			}
		}else{
			if(my_fall_location == acutal){
				correctPredictions[0]++;
			}
		}
		totalPredictions[0]++;
	}
}
void BBlock::printHeuristicInformation(){
	for(int x = 0; x < 1; x++){
		std::cout << "There were " << totalPredictions[x] << " total predictions and " << correctPredictions[x] << " were correct.\n";
	}
}
