#include "parser.h"

int main()
{
	char ch;
	cout << "��ȷ��Դ�����ļ�data.txt�ڵ�ǰĿ¼��.�����������ַ�������";
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