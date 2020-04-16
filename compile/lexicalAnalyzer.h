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
		status = errorStatus = begin = row = list = 0;
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
	vector<token> errorTable;
	vector<string> text;
	int status, errorStatus, begin, row, list;

	void initText();
	void outPutInfo();
	int isReservedWord(string tokenStr);
	void getToken();
	void getErrorToken();
	void move(char ch);
	int singleChClass(char ch);
	int kindOfChar(char ch);
};

void ClexicalAnalyzer::outPutInfo()		//输出各表的信息到屏幕和文件中
{

}

int ClexicalAnalyzer::isReservedWord(string tokenStr)	//判断是否是保留字
{

}

void ClexicalAnalyzer::getToken()	//从自动机的终止状态获取对应状态的token
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
	list--;
}

void ClexicalAnalyzer::getErrorToken()
{

}

void ClexicalAnalyzer::move(char ch)	//该函数包含自动机每个状态该做的事情以及下一步该转变的状态
{
	if (kindOfChar(ch) == 26)
	{
		errorStatus = -1;
		status = -1;
	}
	else
	{
		switch (status)
		{
		case 0:
			switch (kindOfChar(ch))
			{
			case 1: break;
			case 0: status = 11; break;
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
			if (kindOfChar(ch) != 2 && kindOfChar(ch) != 3 && kindOfChar(ch) != 0)
				status = 2;
			break;
		case 2:	getToken(); status = 0; break;	//标识符或保留字
		case 3:
			if (kindOfChar(ch) == 4)
				status = 5;
			else if (kindOfChar(ch) != 0 && kindOfChar(ch) != 3)
				status = 4;
			else
			{
				errorStatus = 3;
				status = -1;
			}
			break;
		case 4:	getToken(); status = 0; break;	//正整数
		case 5:
			if (ch == 'E' && ch == 'e')
				status = 7;
			else if (kindOfChar(ch) != 0 && kindOfChar(ch) != 3)
				status = 6;
			else
			{
				errorStatus = 5;
				status = -1;
			}
			break;
		case 6:	getToken(); status = 0; break;	//小数浮点
		case 7:
			if (ch == '+' && ch == '-')
				status = 9;
			else if (kindOfChar(ch) != 0 && kindOfChar(ch) != 3)
				status = 8;
			else
			{
				errorStatus = 7;
				status = -1;
			}
			break;
		case 8:	getToken(); status = 0; break;	//科学浮点
		case 9:
			if (kindOfChar(ch) != 2 && kindOfChar(ch) != 3 && kindOfChar(ch) != 0)
				status = 10;
			break;
		case 10: getToken(); status = 0; break;	//科学浮点
		case 11: status = 12; break;
		case 12: getToken(); status = 0; break;	//零
		case 13: status = 14; break;
		case 14: getToken(); status = 0; break;	// +
		case 15: status = 16; break;
		case 16: getToken(); status = 0; break;	// -
		case 17: status = 18; break;
		case 18: getToken(); status = 0; break;	// *
		case 19: status = 20; break;
		case 20: getToken(); status = 0; break;	// /
		case 21: status = 22; break;
		case 22: getToken(); status = 0; break;	// %
		case 23:
			if (kindOfChar(ch) != 12)
				status = 24;
			else
				status = 25;
			break;
		case 24: getToken(); status = 0; break;	// >
		case 25: status = 26; break;
		case 26: getToken(); status = 0; break;	// >=
		case 27:
			if (kindOfChar(ch) != 12)
				status = 28;
			else
				status = 29;
			break;
		case 28: getToken(); status = 0; break;	// <
		case 29: status = 30; break;
		case 30: getToken(); status = 0; break;	// <=
		case 31:
			if (kindOfChar(ch) != 12)
				status = 32;
			else
				status = 33;
			break;
		case 32: getToken(); status = 0; break;	// =
		case 33: status = 34; break;
		case 34: getToken(); status = 0; break;	// ==
		case 35:
			if (kindOfChar(ch) != 12)
				status = 36;
			else
				status = 37;
			break;
		case 36: getToken(); status = 0; break;	// !
		case 37: status = 38; break;
		case 38: getToken(); status = 0; break;	// !=
		case 39:
			if (kindOfChar(ch) == 14)
				status = 40;
			else
			{
				errorStatus = 39;
				status = -1;
			}
			break;
		case 40: status = 41; break;
		case 41: getToken(); status = 0; break;	// &&
		case 42:
			if (kindOfChar(ch) == 15)
				status = 43;
			else
			{
				errorStatus = 42;
				status = -1;
			}
			break;
		case 43: status = 44; break;
		case 44: getToken(); status = 0; break;	// ||
		case 45: status = 46; break;
		case 46: getToken(); status = 0; break;	// , [ ] ( ) { } ; '\n' 'EOF' 
		default: getErrorToken(); break;		//错误处理
		}
	}
}

void ClexicalAnalyzer::lexicalDFA()			//词法分析自动机
{
	for (row = 0; row < text.size(); row++)
	{
		begin = 0;
		for (list=0; list < text[row].size();list++)
		{
			move(text[row].at(list));
		}
	}
	tokenTable.push_back(token(38));
	outPutInfo();
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

int ClexicalAnalyzer::singleChClass(char ch)	//可单个识别的字符
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
	case '\n': return 37;
	case 'EOF': return 38;
	default: return 0;
	}
}

int ClexicalAnalyzer::kindOfChar(char ch)	//将字符按划为不同的种类，自动机将根据自身状态及字符的种类转变状态
{
	if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
		ch = 2;
	else if (ch >= '1' && ch <= '9')
		ch = 3;
	else if (singleChClass(ch))
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
	case 16: return 16;
	default: return 26;
	}
}