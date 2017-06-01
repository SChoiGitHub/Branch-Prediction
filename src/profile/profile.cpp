#include "profile.h"

std::unordered_map<InsType,int> instructionToInt({
    {InsType::JO,0},    // Jump if overflow
    {InsType::JNO,1},   // Jump if not overflow
    {InsType::JS,2},    // Jump if sign
    {InsType::JNS,3},   // Jump if not sign
    {InsType::JE,4},    // Jump if equal
    {InsType::JZ,5},    // Jump if zero
    {InsType::JNE,6},   // Jump if not equal
    {InsType::JNZ,7},   // Jump if not zero
    {InsType::JB,8},    // Jump if below
    {InsType::JNAE,9},  // Jump if not above or equal
    {InsType::JC,10},    // Jump if carry
    {InsType::JNB,11},   // Jump if not below
    {InsType::JAE,12},   // Jump if above or equal
    {InsType::JNC,13},   // Jump if not carry
    {InsType::JBE,14},   // Jump if below or equal
    {InsType::JNA,15},   // Jump if not above
    {InsType::JA,16},    // Jump if above
    {InsType::JNBE,17},  // Jump if not below or equal
    {InsType::JL,18},    // Jump if less
    {InsType::JNGE,19},  // Jump if not greater or equal
    {InsType::JGE,20},   // Jump if greater or equal
    {InsType::JNL,21},   // Jump if not less
    {InsType::JLE,22},   // Jump if less or equal
    {InsType::JNG,23},   // Jump if not greater
    {InsType::JG,24},    // Jump if greater
    {InsType::JNLE,25},  // Jump if not less or equal
    {InsType::JP,26},    // Jump if parity
    {InsType::JPE,27},   // Jump if parity even
    {InsType::JNP,28},   // Jump if not parity
    {InsType::JPO,29},   // Jump if parity odd
    {InsType::JCXZ,30},  // Jump if %CX register is 0
    {InsType::JECXZ,31}  // Jump if $ECX register is 0
});
std::array<std::string, 32> intToString({
	"JO",    // Jump if overflow
	"JNO",   // Jump if not overflow
	"JS",    // Jump if sign
	"JNS",   // Jump if not sign
	"JE",    // Jump if equal
	"JZ",    // Jump if zero
	"JNE",   // Jump if not equal
	"JNZ",   // Jump if not zero
	"JB",    // Jump if below
	"JNAE",  // Jump if not above or equal
	"JC",    // Jump if carry
	"JNB",   // Jump if not below
	"JAE",   // Jump if above or equal
	"JNC",   // Jump if not carry
	"JBE",   // Jump if below or equal
	"JNA",   // Jump if not above
	"JA",    // Jump if above
	"JNBE",  // Jump if not below or equal
	"JL",    // Jump if less
	"JNGE",  // Jump if not greater or equal
    "JGE",   // Jump if greater or equal
    "JNL",   // Jump if not less
    "JLE",   // Jump if less or equal
    "JNG",   // Jump if not greater
    "JG",    // Jump if greater
    "JNLE",  // Jump if not less or equal
    "JP",    // Jump if parity
    "JPE",   // Jump if parity even
    "JNP",   // Jump if not parity
    "JPO",   // Jump if parity odd
    "JCXZ",  // Jump if %CX register is 0
	"JECXZ"  // Jump if $ECX register is 0
});

void Profile::profile(std::unordered_map<uint64_t,BBlock> all_blocks){
	std::array<int,32> correct_jump_of_type;
	std::array<int,32> total_jump_of_type;
	
	for(int x = 0; x < 32; x++){
		correct_jump_of_type[x] = 0;
		total_jump_of_type[x] = 0;
	}
	for(auto &block : all_blocks){
		try{
			//Iterate between all blocks and profile the jumps that work
			//We found a jump of this type.
			total_jump_of_type[instructionToInt.at(block.second.getLastInstruction().getType())]++;
			if(std::get<1>(block).get_jump_loc() == std::get<1>(block).get_actual_loc()){
				//the Jump location is actually the location it goes to.
				correct_jump_of_type[instructionToInt.at(block.second.getLastInstruction().getType())]++;
			}
		}catch(std::exception e){
			//We found a non-jump instruction. Ignore and continue.
		}
		
	}
	std::cout << "Type\tTaken\tTotal\tPercent Taken\n";
	for(int x = 0; x < 32; x++){
		std::cout << intToString[x] << '\t'<< correct_jump_of_type[x] << '\t' << total_jump_of_type[x] << '\t' << (correct_jump_of_type[x]*1.0/total_jump_of_type[x]) << '\n';
	}
	
}
