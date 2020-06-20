#pragma once
#include "lexicalAnalyzer.h"
#include <stack>
#include <map>

class parser
{
public:
	parser(vector<token>& tokenTable);
	~parser();
	void getAnalysisFromFile();
	bool isTerminal(int);
	void LL_driver();
	void error(int, int);
	bool isAccepted(int);
private:
	bool flag;
	int **analysis;
	unsigned int row, list, tokenPtr;
	vector<token>& tokenTable;
	stack<int> sem;
	map<char, int> vtMap;
	map<int, int>vnMap;
	map<int, string>vnToText;
};