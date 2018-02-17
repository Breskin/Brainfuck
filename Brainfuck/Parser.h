#pragma once

#include <string>
#include <vector>

using namespace std;

enum InstructionType
{
	MoveUp, MoveDown, Increment, Decrement, Show, Read, OpenBracket, CloseBracket
};

struct Instruction
{
	InstructionType Type;
	int Data;
};

class Parser
{
	public:
		Parser();
		~Parser();
		void Load(string);
		void Run(bool);

	private:
		const int ARRAY_SIZE = 30000;
		vector<Instruction> Instructions;
		int Pointer;
		char* Cells;
};

