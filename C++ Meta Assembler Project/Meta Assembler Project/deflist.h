#pragma once
#include "stdafx.h"
#include <string>
#include "definition.h"

class DefinitionList
{
public:
	DefinitionList(string def_file);
	~DefinitionList();
	int GetLength();
	int Load();

	int MAXDEFS;
	int DefCount;
	Definition* PtrToList;
	string FileName;
};