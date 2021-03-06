// Brainfuck.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include <iostream>
#include <fstream>

using namespace std;

string readfile(string filename)
{
	ifstream file;
	file.open(filename);

	string text;

	while (!file.eof())
	{
		string line;
		file >> line;

		text = text + line;
	}

	file.close();

	return text;
}

int main(int argc, char* argv[])
{
	Parser parser;

	for (int i = 1; i < argc; i++)
	{
		cout << argv[i] << endl;
		parser.Load(readfile(argv[i]));
		parser.Run("");
	}

	string halt;
	cin >> halt;

    return 0;
}

