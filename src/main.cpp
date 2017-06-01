#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <chrono>
#include <functional>
#include <algorithm>
#include <string>

#include "parse/parse.h"
#include "profile/profile.h"


int main(int argc, char *argv[]) {
	
    std::string usage = "Usage: " + std::string(argv[0]) + " -fc <filename> | -h";
    if(argc < 2) {
        std::cout << usage << std::endl;
        return -1;
    }
    std::string path(argv[1]); 
    //I make a hash table. I associate the tags (address line of each block to the blocks themselves.
    std::unordered_map<uint64_t,BBlock> blocks_in_file = Parse::parse_file(path);
    std::cout << "Completed parsing.\n";
    

    Profile::print_profile(blocks_in_file);
    std::cout << "Profiling Complete!\n";
    
    //Now that we have the blocks.
	for(auto& block : blocks_in_file){
		//Iterate between all blocks and associate them with their parents.
		std::get<1>(block).discoverParents(blocks_in_file);
	}
    
    
    for(auto& block : blocks_in_file){
		//Iterate between all blocks and test the heuristics.
		//std::cout << std::get<1>(block).getFirstInstructionLocation() << '\n'; //A line of debugging.
		std::get<1>(block).back_h(0);
		std::get<1>(block).back_h_back_branches_only(1);
		std::get<1>(block).back_h_forward_branches_only(2);
		std::get<1>(block).return_h(3,blocks_in_file);
		std::get<1>(block).call_h(4,blocks_in_file);
		std::get<1>(block).store_h(5,blocks_in_file);
		std::get<1>(block).combined_h(6,blocks_in_file);
	}
	std::cout << "Completed heuristic testing.\n";
	BBlock::printHeuristicInformation();
	
	
}
