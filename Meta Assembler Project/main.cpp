// Meta Assembler Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "deflist.h"
#include "program.h"

int main(int argc, char* argv[])
{
	DefinitionList deflist("ExampleDefinitions.txt");
	Program creation("ExampleProgramIn.txt");
	creation.ApplyDefinitions(deflist);
	creation.Save("ExampleProgramOut.cdm");
	return 0;
}
