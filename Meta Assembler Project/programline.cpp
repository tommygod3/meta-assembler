#pragma once
#include "stdafx.h"
#include "programline.h"
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <string>
using namespace std;

ProgramLine::ProgramLine(string label, string opcode, string operand)
{
	Label = label;
	OpCode = opcode;
	Operand = operand;
}

ProgramLine::ProgramLine()
{
	Label = "";
}

void ProgramLine::Load(ifstream& pro_file)
{
	string temp;
	char space = ' ';
	char tab = '\t';
	int counter = 0;
	getline(pro_file, temp);
	int length = temp.length();
	int x = 0;
	for (int i = x; i < length; i++)
	{
		if (x == 0)
		{
			if ((temp[i] != space) && (temp[i] != tab))
			{
				Label += temp[i];
			}
			else if (Label.empty())
			{
				Label = "";
				x = i + 1;
				break;
			}
			else if (!Label.empty())
			{
				x = i + 1;
				break;
			}
		}
	}
	for (int i = x; i < length; i++)
	{
		if ((temp[i] != space) && (temp[i] != tab))
		{
			OpCode += temp[i];
		}
		else if (OpCode.empty())
		{
			OpCode = "";
			x = i + 1;
			break;
		}
		else if (!OpCode.empty())
		{
			x = i + 1;
			break;
		}
	}
	for (int i = x; i < length; i++)
	{
		if ((temp[i] != space) && (temp[i] != tab))
		{
			Operand += temp[i];
		}
		else if (Operand.empty())
		{
			Operand = "";
			x = i + 1;
			break;
		}
		else if (!Operand.empty())
		{
			x = i + 1;
			break;
		}
	}
}

void ProgramLine::Save(ofstream& out_file)
{
	if (!LocationCounter.empty())
	{
		out_file << LocationCounter << " " << ":" << " " << OpCode << Operand << endl;
	}
}

int ProgramLine::GetOperandLength()
{
	return Operand.length();
}

void ProgramLine::Empty()
{
	LocationCounter = "";
}

void ProgramLine::Space()
{
	OpCode = "";
	Operand = "0000";
}