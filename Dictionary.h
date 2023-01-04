#ifndef DICTIONARY_H
#define DICTINARY_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

class Dictionary {
public:
	void SetDictionary(vector<string>& strArr, int category);
	void StatementHint(string strOriginal);
	void AlphabetHint(string strOriginal);
};

#endif