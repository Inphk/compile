#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class token
{
public:
	int tokenClass;
	int address;

	token(int tClass)
	{
		tokenClass = tClass;
		address = -1;
	}
	token(int tClass, int address)
	{
		tokenClass = tClass;
		this->address = address;
	}
};

class errorToken
{
public:
	string errorMessage;
	int address;

	errorToken(string message, int address)
	{
		errorMessage = message;
		this->address = address;
	}
};

class ClexicalAnalyzer
{
public:
	static const int MAX = 1024, WORDNUM = 11;

	ClexicalAnalyzer();
	void lexicalDFA();

private:
	vector<string> nameTable;
	vector<string> constTable;
	vector<token> tokenTable;
	vector<errorToken> errorTable;
	vector<string> text;
	int status, errorStatus, begin;
	unsigned int row, list;
	static const string reservedWord[WORDNUM];

	void initText();
	void outPutInfo();
	int isReservedWord(string tokenStr);
	bool isExist(string tokenStr);
	void getToken();
	void getErrorToken();
	void move(char ch);
	int singleChClass(char ch);
	int kindOfChar(char ch);
};

