#include "stdafx.h"
#include "deflist.h"
#include "definition.h"
#include <iostream>
#include "program.h"
#include <fstream>
#include <sstream>
using namespace std;

Program::Program(string def_file)
{
	FileName = def_file;
	LineCount = 0;
	MAXLINES = 100;
	GetLength();
	Load();
}

Program::~Program()
{
	if (LineCount > 0)
	{
		delete[] PtrToProgram;
	}
}

int Program::GetLength()
{
	ifstream inFile(FileName);
	if (!inFile)
	{
		return -1;
	}
	PtrToProgram = new ProgramLine[MAXLINES];
	for (int i = 0; i < MAXLINES; i++)
	{
		PtrToProgram[i].Load(inFile);
		if (PtrToProgram[i].OpCode.empty())
		{
			LineCount = i;
			break;
		}
	}
	inFile.close();
	return LineCount;
}

int Program::Load()
{
	//Creates list of lines, assigns them their LC default, reads in their values one by one, then "sets labels"
	ifstream inFile(FileName);
	if (!inFile)
	{
		return -1;
	}
	PtrToProgram = new ProgramLine[LineCount];
	for (int i = 0; i < LineCount; i++)
	{
		PtrToProgram[i].LocationCounter = GetHex(i);
		PtrToProgram[i].Load(inFile);
		DirectiveDC(PtrToProgram[i]);
	}
	SetEQU();
	DirectiveORG();
	SetLabels();
	inFile.close();
	return 0;
}

int Program::Save(string out_file)
{
	//Creates a file and saves line by line
	ofstream outFile(out_file);
	for (int i = 0; i < LineCount; i++)
	{
		PtrToProgram[i].Save(outFile);
	}
	outFile.close();
	return 0;
}

string Program::GetHex(int LC)
{
	//Takes integer, turns it into a string that is the number in hex, with zeroes filling before.
	int temp = LC;
	stringstream ss;
	ss << hex << temp;
	string tp = ss.str();
	while (tp.length() < 3)
	{
		tp = "0" + tp;
	}
	return tp;
}

int Program::GetInt(string LI)
{
	//Takes hex string, translates to integer
	unsigned int tp;
	string temp = LI;
	stringstream ss;
	ss << hex << temp;
	ss >> tp;
	return tp;
}

void Program::DirectiveORG()
{
	for (int i = 0; i < LineCount; i++)
	{
		if (PtrToProgram[i].OpCode == "ORG")
		{
			{
				int jump_to = GetInt(PtrToProgram[i].Operand);
				int temp = jump_to - GetInt(PtrToProgram[i].LocationCounter) - 1;
				PtrToProgram[i].Empty();
				Slide(i+1, temp);
			}
		}
	}
}

void Program::DirectiveDC(ProgramLine& line)
{
	if (line.OpCode == "DC")
	{
		line.OpCode = "";
	}
}

void Program::SetEQU()
{
	for (int i = 0; i < LineCount; i++)
	{
		if (PtrToProgram[i].OpCode == "EQU")
		{
			string temp;
			int length = PtrToProgram[i].Label.length();
			char colon = ':';
			for (int k = 0; k < length; k++)
			{
				if (PtrToProgram[i].Label[k] != colon)
				{
					temp += PtrToProgram[i].Label[k];
				}
			}
			for (int j = 0; j < LineCount; j++)
			{
				if (PtrToProgram[j].OpCode == temp)
				{
					PtrToProgram[j].OpCode = PtrToProgram[i].Operand;
				}
				if (PtrToProgram[j].Operand == temp)
				{
					PtrToProgram[j].Operand = PtrToProgram[i].Operand;
				}
				if ((PtrToProgram[j].Label == PtrToProgram[i].Label)&&(i!=j))
				{
					PtrToProgram[j].Label = PtrToProgram[i].Operand;
				}
			}
			PtrToProgram[i].Empty();
			Slide(i+1,-1);
		}
	}
}

void Program::SetLabels()
{
	//Replaces instances of a label with the label's LocationCounter
	for (int i = 0; i < LineCount; i++)
	{
		if ((!PtrToProgram[i].Label.empty())&&(PtrToProgram[i].OpCode!="EQU"))
		{
			string temp;
			int length = PtrToProgram[i].Label.length();
			char colon = ':';
			for (int k = 0; k < length; k++)
			{
				if (PtrToProgram[i].Label[k] != colon)
				{
					temp += PtrToProgram[i].Label[k];
				}
			}
			for (int j = 0; j < LineCount; j++)
			{
				if (PtrToProgram[j].Operand == temp)
				{
					PtrToProgram[j].Operand = PtrToProgram[i].LocationCounter;
				}
			}
		}
	}
}

void Program::ApplyDefinitions(DefinitionList& check)
{
	//Compares program to definition list and for each piece of opcode - replaces mnemonic with code
	for (int i = 0; i < LineCount; i++)
	{
		for (int j = 0; j < check.DefCount; j++)
		{
			if (PtrToProgram[i].OpCode == check.PtrToList[j].Mnemonic)
			{
				PtrToProgram[i].OpCode = check.PtrToList[j].Code;
			}
		}
	}
}

void Program::Slide(int index, int amount)
{
	for (int i = index; i < LineCount; i++)
	{
		if (PtrToProgram[i].OpCode != "EQU")
		{
			int temp = GetInt(PtrToProgram[i].LocationCounter);
			temp = temp + amount;
			PtrToProgram[i].LocationCounter = GetHex(temp);
		}
	}
}