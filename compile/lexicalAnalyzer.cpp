#include "lexicalAnalyzer.h"

ClexicalAnalyzer::ClexicalAnalyzer()
{
	status = errorStatus = begin = row = list = 0;
	initText();
}

const string ClexicalAnalyzer::reservedWord[WORDNUM] = { "","if","else","for","while","break","return","continue","float","int","char" };

void ClexicalAnalyzer::outPutInfo()		//输出各表的信息到屏幕和文件中
{
	ofstream fout("info.txt", std::ios::out);
	cout << "源程序：" << endl;
	for (unsigned int i = 0; i < text.size(); i++)
		cout << i << '\t' << text[i];
	cout << "\n" << endl;
	cout << "token表：" << endl;
	fout << "token表：" << endl;
	for (unsigned int i = 0; i < tokenTable.size(); i++)
	{
		cout << "Class:\t" << tokenTable[i].tokenClass << '\t';
		if (-1 != tokenTable[i].address)
		{
			if (11 == tokenTable[i].tokenClass)
			{
				cout << "Address:name表： " << tokenTable[i].address << endl;
				fout << "Address:name表： " << tokenTable[i].address << endl;
			}
			else if (12 == tokenTable[i].tokenClass)
			{
				cout << "Address:const表： " << tokenTable[i].address << endl;
				fout << "Address:const表： " << tokenTable[i].address << endl;
			}
		}

	}
	cout << "\nname表：" << endl;
	fout << "\nname表：" << endl;
	for (unsigned int i = 0; i < nameTable.size(); i++)
	{
		cout << i << "\t" << nameTable[i] << endl;
		fout << i << "\t" << nameTable[i] << endl;
	}
	cout << "\nconst表：" << endl;
	fout << "\nconst表：" << endl;
	for (unsigned int i = 0; i < constTable.size(); i++)
	{
		cout << i << "\t" << constTable[i] << endl;
		fout << i << "\t" << constTable[i] << endl;
	}
	fout.clear();
	fout.close();
}

int ClexicalAnalyzer::isReservedWord(string tokenStr)	//判断是否是保留字,返回保留字的编码
{
	for (unsigned int i = 0; i < WORDNUM; i++)
		if (reservedWord[i].compare(tokenStr) == 0)
			return i;
	return 0;
}

bool ClexicalAnalyzer::isExist(string tokenStr)
{
	for (unsigned int i = 0; i < nameTable.size(); i++)
		if (nameTable[i].compare(tokenStr) == 0)
			return true;
	return false;
}

void ClexicalAnalyzer::getToken()	//从自动机的终止状态获取对应状态的token
{
	string tokenStr;
	for (unsigned int i = begin; i < list; i++)
		tokenStr.insert(tokenStr.end(), text[row].at(i));
	switch (status)
	{
	case 2:			//标识符或保留字
	{
		int tClass = isReservedWord(tokenStr);
		if (tClass > 0)
		{
			token mtoken(tClass);
			tokenTable.push_back(mtoken);
		}
		else
		{
			if (!isExist(tokenStr))
			{
				nameTable.push_back(tokenStr);
				token mtoken(11, nameTable.size() - 1);
				tokenTable.push_back(mtoken);
			}
		}
		break;
	}
	case 4:			//正整数
	case 6:			//普通浮点小数
	case 8:			//科学浮点小数
	case 10:		//科学浮点小数
	case 12:		//零
	{
		constTable.push_back(tokenStr);
		token mtoken(12, constTable.size() - 1);
		break;
	}
	case 14:		// +
	{token mtoken(13); break; }
	case 16:		// -
	{token mtoken(14); break; }
	case 18:		// *
	{token mtoken(15); break; }
	case 20:		// /
	{token mtoken(16); break; }
	case 22:		// %
	{token mtoken(17); break; }
	case 24:		// >
	{token mtoken(18); break; }
	case 26:		// >=
	{token mtoken(19); break; }
	case 28:		// <
	{token mtoken(20); break; }
	case 30:		// <=
	{token mtoken(21); break; }
	case 32:		// =
	{token mtoken(22); break; }
	case 34:		// ==
	{token mtoken(23); break; }
	case 36:		// !
	{token mtoken(24); break; }
	case 38:		// !=
	{token mtoken(25); break; }
	case 41:		// &&
	{token mtoken(26); break; }
	case 44:		// ||
	{token mtoken(27); break; }
	case 46:		// , [ ] ( ) { } ; '\n'
	{token mtoken(singleChClass(text[row].at(begin))); break; }
	}
	begin = list;
	list--;
}

void ClexicalAnalyzer::getErrorToken()		//出错处理
{
	if (errorStatus == -1)	//无法识别的字符
	{
		//错误信息收集
		errorToken etoken("存在无法识别的字符", row);
		errorTable.push_back(etoken);
	}
	else if (errorStatus == 3)	//数字后跟字母
	{
		//错误信息收集
		string message = "期望 ";
		message.insert(message.end(), text[row].at(list - 1));
		message.append(" 是数字");
		errorToken etoken(message, row);

		//向后识别直到正确字符
		list--;
		while (kindOfChar(text[row].at(list)) == 2)
			list++;
	}
	else if (errorStatus == 7)	//浮点小数科学计数表示法的e、E后跟非+、-、数字
	{
		//错误信息收集
		errorToken etoken("无法识别的数字表示", row);
		errorTable.push_back(etoken);

		//向后识别直到正确字符
		list--;
		while (kindOfChar(text[row].at(list)) == 0 || kindOfChar(text[row].at(list)) == 2 || kindOfChar(text[row].at(list)) == 3)
			list++;
	}
	else if (errorStatus == 39)	//单个&
	{
		//错误信息收集
		errorToken etoken("无法识别单个&", row);
		errorTable.push_back(etoken);
	}
	else if (errorStatus == 42)	//单个|
	{
		//错误信息收集
		errorToken etoken("无法识别单个|", row);
		errorTable.push_back(etoken);
	}
	status = 0;
	list--;
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
			else if (kindOfChar(ch) == 2)
			{
				errorStatus = 3;
				status = -1;
			}
			else if (kindOfChar(ch) != 0 && kindOfChar(ch) != 3)
				status = 4;
			break;
		case 4:	getToken(); status = 0; break;	//正整数
		case 5:
			if (ch == 'E' || ch == 'e')
				status = 7;
			else if (kindOfChar(ch) != 0 && kindOfChar(ch) != 3)
				status = 6;
			break;
		case 6:	getToken(); status = 0; break;	//小数浮点
		case 7:
			if (ch == '+' || ch == '-')
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
		for (list = 0; list < text[row].size(); list++)
		{
			if (text[row].at(list) == '\r')
				;
			else
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
	while (fin.get(oneText, MAX))
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
	case 2: return 2;
	case 3: return 3;
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