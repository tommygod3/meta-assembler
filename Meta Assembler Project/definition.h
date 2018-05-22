#pragma once
#include <string>
using namespace std;

class Definition
{
public:
	Definition(string pmnemonic, string pcode);
	Definition();
	void Load(ifstream& def_file);
	int GetCodeLength();

	string Mnemonic;
	string Code;
};