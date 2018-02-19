#include "stdafx.h"
#include "Parser.h"
#include <iostream>


Parser::Parser()
{
	Cells = new char[ARRAY_SIZE];
}


Parser::~Parser()
{
	free(Cells);
}

void Parser::Load(string code)
{
	Instructions.clear();
	vector<int> Loops;

	int index = 0;
	while (index < code.length())
	{
		Instruction i;

		switch (code[index])
		{
			case '>':
				if (index > 0 && Instructions.back().Type == MoveUp)
				{
					++Instructions.back().Data;
				}
				else
				{
					i.Type = MoveUp;
					i.Data = 1;
					Instructions.push_back(i);
				}
				break;

			case '<':
				if (index > 0 && Instructions.back().Type == MoveDown)
				{
					++Instructions.back().Data;
				}
				else
				{
					i.Type = MoveDown;
					i.Data = 1;
					Instructions.push_back(i);
				}
				break;

			case '+':
				if (index > 0 && Instructions.back().Type == Increment)
				{
					++Instructions.back().Data;
				}
				else
				{
					i.Type = Increment;
					i.Data = 1;
					Instructions.push_back(i);
				}
				break;

			case '-':
				if (index > 0 && Instructions.back().Type == Decrement)
				{
					++Instructions.back().Data;
				}
				else
				{
					i.Type = Decrement;
					i.Data = 1;
					Instructions.push_back(i);
				}
				break;

			case '.':
				i.Type = Show;
				Instructions.push_back(i);
				break;

			case ',':
				i.Type = Read;
				Instructions.push_back(i);
				break;

			case '[':
				i.Type = OpenBracket;
				Instructions.push_back(i);

				Loops.push_back(Instructions.size() - 1);
				break;

			case ']':
				i.Type = CloseBracket;
				i.Data = Loops.back();
				Instructions.push_back(i);

				Instructions[Loops.back()].Data = Instructions.size() - 1;

				Loops.pop_back();
				break;
		}

		++index;
	}

	Instructions.shrink_to_fit();
}

void Parser::Run(bool inputOnStart)
{
	Pointer = 0;

	for (int i = 0; i < ARRAY_SIZE; i++)
		Cells[i] = 0;

	string input;
	
	if (inputOnStart)
	{
		cout << "Input: ";
		cin >> input;
	}

	int index = 0, inputIndex = 0;

	while (index < Instructions.size())
	{
		switch (Instructions[index].Type)
		{
			case MoveUp:
				Pointer += Instructions[index].Data;
				break;

			case MoveDown:
				Pointer -= Instructions[index].Data;
				break;

			case Increment:
				Cells[Pointer] += Instructions[index].Data;
				break;

			case Decrement:
				Cells[Pointer] -= Instructions[index].Data;
				break;

			case Show:
				putchar(Cells[Pointer]);
				break;

			case Read:
				if (inputOnStart) {
					if (inputIndex < input.length())
					{
						Cells[Pointer] = input[inputIndex];
						inputIndex++;
					}
					else
					{
						Cells[Pointer] = 0;
					}
				}
				else
				{
					Cells[Pointer] = getchar();
				}
				break;

			case OpenBracket:
				if (Cells[Pointer] == 0)
					index = Instructions[index].Data;
				break;

			case CloseBracket:
				if (Cells[Pointer] != 0)
					index = Instructions[index].Data - 1;
				break;
		}

		++index;
	}
}