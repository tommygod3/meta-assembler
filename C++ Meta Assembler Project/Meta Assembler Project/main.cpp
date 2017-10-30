// Meta Assembler Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "deflist.h"
#include "program.h"

int main(int argc, char* argv[])
{
	DefinitionList deflist("definitions.txt");
	Program creation("ProgramIn.txt");
	creation.ApplyDefinitions(deflist);
	creation.Save("ProgramOut.cdm");
	return 0;
}