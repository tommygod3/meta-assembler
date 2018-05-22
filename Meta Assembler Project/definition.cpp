#pragma once
#include "stdafx.h"
#include "definition.h"
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <string>

using namespace std;

//Object for each definition that is read in

Definition::Definition(string pmnemonic, string pcode)
{
	Mnemonic = pmnemonic;
	Code = pcode;
}

Definition::Definition()
{
	Mnemonic = "ERROR_EMPTY";
}

void Definition::Load(ifstream& def_file)
{
	def_file >> Mnemonic >> Code;
}

int Definition::GetCodeLength()
{
	return Code.length();
}