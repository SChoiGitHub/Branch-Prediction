#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <chrono>
#include <functional>
#include <algorithm>
#include <string>
#include <thread>

#include "parse/parse.h"
#include "profile/profile.h"


std::unordered_map<uint64_t,BBlock> blocks_in_file;


void do_back_h(){
    for(auto& block : blocks_in_file){
		std::get<1>(block).back_h(0);
	}
}

void do_back_h_back_branches_only(){
    for(auto& block : blocks_in_file){
		std::get<1>(block).back_h_back_branches_only(1);
	}
}
void do_back_h_forward_branches_only(){
    for(auto& block : blocks_in_file){
		std::get<1>(block).back_h_forward_branches_only(2);
	}
}
void do_return_h(){
    for(auto& block : blocks_in_file){
		std::get<1>(block).return_h(3,blocks_in_file);
	}
}
void do_call_h(){
    for(auto& block : blocks_in_file){
		std::get<1>(block).call_h(4,blocks_in_file);
	}
}
void do_store_h(){
    for(auto& block : blocks_in_file){
		std::get<1>(block).store_h(5,blocks_in_file);
	}
}
void do_combined_h(){
    for(auto& block : blocks_in_file){
		std::get<1>(block).combined_h(6,blocks_in_file);
	}
}

int main(int argc, char *argv[]) {
	
    std::string usage = "Usage: " + std::string(argv[0]) + " -fc <filename> | -h";
    if(argc < 2) {
        std::cout << usage << std::endl;
        return -1;
    }
    std::string path(argv[1]); 
    //I make a hash table. I associate the tags (address line of each block to the blocks themselves.
    blocks_in_file = Parse::parse_file(path);
    std::cout << "Completed parsing.\n";
    

    Profile::print_profile(blocks_in_file);
    std::cout << "Profiling Complete!\n";
    
    //Now that we have the blocks.
	for(auto& block : blocks_in_file){
		//Iterate between all blocks and associate them with their parents.
		std::get<1>(block).discoverParents(blocks_in_file);
	}
    
    std::thread back(do_back_h);
    std::thread back_b(do_back_h_back_branches_only);
    std::thread back_f(do_back_h_forward_branches_only);
	std::thread return_h(do_return_h);
    std::thread call_h(do_call_h);
    std::thread combined_h(do_combined_h);
    
    if(back.joinable()){
		back.join();
	}
	if(back_b.joinable()){
		back_b.join();
	}
	if(back_f.joinable()){
		back_f.join();
	}
    if(return_h.joinable()){
		return_h.join();
	}
	if(call_h.joinable()){
		call_h.join();
	}
	if(combined_h.joinable()){
		combined_h.join();
	}
	
	
	std::cout << "Completed heuristic testing.\n";
	BBlock::printHeuristicInformation();
	
	
}

