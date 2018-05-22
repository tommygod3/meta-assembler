#pragma once
#include "stdafx.h"
#include <string>
#include "definition.h"
#include "deflist.h"
#include "programline.h"

class Program
{
public:
	Program(string pro_file);
	~Program();
	int GetLength();
	int Load();
	int Save(string out_file);
	void ApplyDefinitions(DefinitionList& check);
	string GetHex(int LC);
	int GetInt(string LI);
	void DirectiveORG();
	void DirectiveDC(ProgramLine& line);
	void SetLabels();
	void SetEQU();
	void Slide(int index, int amount);

	int MAXLINES;
	int LineCount;
	ProgramLine* PtrToProgram;
	string FileName;
};