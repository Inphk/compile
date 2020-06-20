#include "parser.h"

int main()
{
	char ch;
	cout << "请确保源程序文件data.txt在当前目录下.（输入任意字符继续）";
	cin >> ch;
	ClexicalAnalyzer lex;
	lex.lexicalDFA();
	if (lex.errorTable.empty())
	{
		parser par(lex.tokenTable);
		par.LL_driver();
	}
	return 0;
}