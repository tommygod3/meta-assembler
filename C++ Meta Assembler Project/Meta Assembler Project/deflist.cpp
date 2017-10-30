#include "stdafx.h"
#include "deflist.h"
#include <iostream>
#include <fstream>
using namespace std;

//Object for the list of definitions, made up of list of definitions

DefinitionList::DefinitionList(string def_file)
{
	FileName = def_file;
	DefCount = 0;
	MAXDEFS = 100;
	GetLength();
	Load();
}

DefinitionList::~DefinitionList()
{
	if (DefCount > 0)
	{
		delete[] PtrToList;
	}
}

int DefinitionList::GetLength()
{
	ifstream inFile(FileName);
	if (!inFile)
	{
		return -1;
	}
	PtrToList = new Definition[MAXDEFS];
	for (int i = 0; i < MAXDEFS; i++)
	{
		PtrToList[i].Load(inFile);
		if ((PtrToList[i].Mnemonic.empty()) || (PtrToList[i].Code.empty()))
		{
			DefCount = i;
			break;
		}
	}
	inFile.close();
	return DefCount;
}

int DefinitionList::Load()
{
	ifstream inFile(FileName);
	if (!inFile)
	{
		return -1;
	}
	PtrToList = new Definition[DefCount];
	for (int i = 0; i < DefCount; i++)
	{
		PtrToList[i].Load(inFile);
	}
	inFile.close();
	return 0;
}

