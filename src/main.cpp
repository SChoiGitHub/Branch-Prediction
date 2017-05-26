#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <chrono>
#include <functional>
#include <algorithm>

#include "parse/parse.h"



int main(int argc, char *argv[]) {
    std::string usage = "Usage: " + std::string(argv[0]) + " -fc <filename> | -h";
    if(argc < 2) {
        std::cout << usage << std::endl;
        return -1;
    }
    std::string path(argv[1]); 
    std::unordered_map<uint64_t,BBlock> blocks_in_file = Parse::parse_file(path);
    std::cout << "Completed parsing.\n";
    
    for(auto block : blocks_in_file){
		std::cout << std::get<1>(block).getFirstInstructionLocation() << '\n';
		std::get<1>(block).back_h();
		
	}
	std::cout << "Completed heuristic testing.\n";
	BBlock::printHeuristicInformation();
	
}