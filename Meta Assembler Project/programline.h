#pragma once
#include "stdafx.h"
#include <string>
#include "deflist.h"

class ProgramLine
{
public:
	ProgramLine(string label, string opcode, string operand);
	ProgramLine();
	void Load(ifstream& pro_file);
	void Save(ofstream& out_file);
	void Empty();
	void Space();
	int GetOperandLength();

	string LocationCounter;
	string Label;
	string OpCode;
	string Operand;
};