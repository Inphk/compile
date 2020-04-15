#pragma once
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class token
{
	int tokenClass;
	int address;

public:
	token(token &mtoken)
	{
		tokenClass = mtoken.tokenClass;
		address = mtoken.address;
	}
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

class ClexicalAnalyzer
{
public:
	static const int MAX = 1024;

	ClexicalAnalyzer()
	{
		status = begin = row = list = 0;
		initText();
	}
	~ClexicalAnalyzer()
	{

	}
	void lexicalDFA();

private:
	vector<string> nameTable;
	vector<string> constTable;
	vector<token> tokenTable;
	vector<string> text;
	int status, begin, row, list;

	void initText();
	int isReservedWord(string tokenStr);
	void getToken();
	void move(char ch);
	int isOtherCh(char ch);
	int kindOfChar(char ch);
};

int ClexicalAnalyzer::isReservedWord(string tokenStr)
{

}

void ClexicalAnalyzer::getToken()
{
	string tokenStr;
	for (int i = begin; i <list; i++)
		tokenStr.insert(tokenStr.end, text[row].at(i));
	switch (status)
	{
	case 2: 
		int tClass = isReservedWord(tokenStr);
		if (tClass)
		{
			token mtoken(tClass);
			tokenTable.push_back(mtoken);
		}
		break;
	case 4: break;
	case 6: break;
	case 8: break;
	case 10: break;
	case 12: break;
	case 14: break;
	case 16: break;
	case 18: break;
	case 20: break;
	case 22: break;
	case 24: break;
	case 26: break;
	case 28: break;
	case 30: break;
	case 32: break;
	case 34: break;
	case 36: break;
	case 38: break;
	case 41: break;
	case 44: break;
	case 46: break;
	case 47: break;
	default:
		break;
	}
}

void ClexicalAnalyzer::move(char ch)
{
	switch (status)
	{
	case 0:
		switch (kindOfChar(ch))
		{
		case 1: break;
		case 0: status =11; break;
		case 2: status = 1; break;
		case 3: status = 3; break;
		case 5: status = 13; break;
		case 6: status = 15; break;
		case 7: status = 17; break;
		case 8: status = 19; break;
		case 9: status = 21; break;
		case 10: status = 23; break;
		case 11: status = 27; break;
		case 12: status = 31; break;
		case 13: status = 35; break;
		case 14: status = 39; break;
		case 15: status = 42; break;
		case 16: status = 45; break;
		default: status = 47; break;
		}
		break;
	case 1:
		if (kindOfChar(ch) != 2 && kindOfChar(ch) != 3)
			status = 2;
		break;
	case 2:
		getToken();
	default:
		break;
	}
}

void ClexicalAnalyzer::lexicalDFA()
{
	for (row = 0; row < text.size(); row++)
	{
		begin = 0;
		for (list = 0; list < text[row].size(); list++)
		{
			move(text[row].at(list));
		}
	}
}

void ClexicalAnalyzer::initText()	//从文件中读取内容
{
	ifstream fin("data.txt", std::ios::in);
	char oneText[MAX];
	while (fin.get(oneText,MAX))
		text.push_back(oneText);
	fin.clear();
	fin.close();
}

int ClexicalAnalyzer::isOtherCh(char ch)
{
	switch (ch)
	{
	case ',': return 27;
	case '[': return 29;
	case ']': return 30;
	case '(': return 31;
	case ')': return 32;
	case '{': return 33;
	case '}': return 34;
	case ';': return 35;
	case '.': return 36;
	case '\n': return 37;
	case 'EOF': return 87;
	default: return 0;
	}
}

int ClexicalAnalyzer::kindOfChar(char ch)
{
	if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
		ch = 2;
	if (ch >= '1' && ch <= '9')
		ch = 3;
	if (isOtherCh(ch))
		ch = 16;
	switch (ch)
	{
	case '0': return 0;
	case ' ': return 1;
	case 2  : return 2;
	case 3  : return 3;
	case '.': return 4;
	case '+': return 5;
	case '-': return 6;
	case '*': return 7;
	case '/': return 8;
	case '%': return 9;
	case '>': return 10;
	case '<': return 11;
	case '=': return 12;
	case '!': return 13;
	case '&': return 14;
	case '|': return 15;
	case 16 : return 16;
	default: return 26;
	}
}