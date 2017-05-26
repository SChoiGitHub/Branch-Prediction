#include "parse.h"

/*
 * converts a string to a uint64_t
 * local file scoped
 */
uint64_t Parse::s_to_uint64(std::string s){
    std::stringstream sstr(s);
    uint64_t ret;
    sstr >> std::hex >> ret;
    return ret;
}

std::unordered_map<uint64_t,BBlock> Parse::parse_file(std::string path) {
    std::ifstream file(path); //Open the file.
    std::unordered_map<uint64_t,BBlock> all_blocks; //These are all the blocks.
    uint64_t previous_block_addr = 0x000000000; //This is the previous block parsed, none here yet.

    for(std::string line; getline(file, line);) {
        if(line.length() == 0) continue; //Ignore empty lines
		if(line.substr(0,6) == "Block "){
			//We found a block! Time to scan the info.
			std::string line_in_block; //temporarily store the lines.
			BBlock parsing; //The block we will make.
			do{
				getline(file, line_in_block); //Get the line.
				if(line_in_block.length() >= 4 && line_in_block.substr(2,2) == "0x"){
					//we found an instruction.
					//s_to_uint64(line_in_block.substr(4,16)) = location
					//line_in_block.substr(43,5) = instruction type
					//s_to_uint64(line_in_block.substr(53,16)) = address of the jump, if applicable.
					parsing.addInstruction(Instruction(line_in_block));
				}else if(line_in_block.substr(0,7) == "Actual:"){
					//This is where the BBlock actually goes.
					parsing.setActual(s_to_uint64("0x" + line_in_block.substr(8,16)));
					//The loop should cancel now.
					break;
				}else if(file.eof()){
					//This is the last block.
					parsing.setActual(0xFFFFFFFFFFFFFFFF);
					//This loop should cancel now.
					break;
				}
			}while(line_in_block.substr(0,7) != "Actual:" && !file.eof());
			parsing.discoverJump(); //The parsed block should know where it jumps.
			all_blocks.insert({{parsing.getFirstInstructionLocation(),parsing}});
			try{
				//The previous block falls to the one we are parsing.
				if(parsing.getFirstInstructionLocation() != previous_block_addr){
					//There is a chance the the first block may begin at 0x0000000000000000
					all_blocks.at(previous_block_addr).discoverFall(parsing.getFirstInstructionLocation());
				}
			}catch(std::exception e){
				//The above will fail the first time because there are no blocks.
				//Ignore it can continue.
			}
			previous_block_addr = parsing.getFirstInstructionLocation(); 
		}
    }

    file.close();
    return all_blocks;
}
