#include "parse.h"

/*
 * converts a string to a uint64_t
 * local file scoped
 */
int Parse::get_instruction_size(std::string s){
	int letters_count = 0;
	for(char a : s){
		if(a != ' '){
			letters_count++;
		}
	}
	return letters_count/2;
}

 
uint64_t Parse::s_to_uint64(std::string s){
    std::stringstream sstr(s);
    uint64_t ret;
    sstr >> std::hex >> ret;
    return ret;
}

std::unordered_map<uint64_t,BBlock> Parse::parse_file(std::string path) {
    std::ifstream file(path); //Open the file.
    std::unordered_map<uint64_t,BBlock> all_blocks; //These are all the blocks.
    int instruction_size = 0; //Temporarily stores the size of the instruction.

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
					//We need to keep track of the size. The size + the last instruction location is the fall.
					instruction_size = get_instruction_size(line_in_block.substr(22,21));
				}else if(line_in_block.substr(0,3) == "   "){
					//This is an extension to size.
					instruction_size += get_instruction_size(line_in_block.substr(22,21));
				}else if(line_in_block.substr(0,7) == "Actual:"){
					//This is where the BBlock actually goes.
					parsing.setActual(s_to_uint64("0x" + line_in_block.substr(8,16)));
					//The loop should cancel now.
					break;
				}else if(file.eof()){
					//This is the last block of the entire file.
					parsing.setActual(0xFFFFFFFFFFFFFFFF);
					//This loop should cancel now.
					break;
				}
			}while(line_in_block.substr(0,7) != "Actual:" && !file.eof());
			parsing.discoverJump(); //The parsed block should know where it jumps.
			parsing.discoverFall(parsing.getLastInstructionLocation() + instruction_size); //The fall of "parsing" is its last instruction plus the size of it.
			all_blocks.insert({{parsing.getFirstInstructionLocation(),parsing}});
		}
    }

    file.close();
    return all_blocks;
}

