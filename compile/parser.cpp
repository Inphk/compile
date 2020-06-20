#include "parser.h"
#define ENDSIGN 49
parser::parser(vector<token>& tTable):tokenTable(tTable)
{
    flag = true;
    vtMap = { {'Z',0},{'S',1},{'Q',2},{'B',3},{'C',4},{'R',5},{'G',6},{'D',7},{'K',8},{'L',9},{'W',10},{'A',11},{'M',12},
        {'N',13},{'E',14},{'V',15},{'T',16},{'P',17},{'I',18},{'F',19},{'H',20},{'X',21} };
    vnMap = { {1,0}, {2,1}, {3,2}, {4,3}, {5,4}, {6,5}, {7,6}, {8,7}, {9,8}, {10,9}, {11,10}, {12,11}, {13,12}, {14,13}, {15,14},
        {16,15}, {17,16}, {27,17}, {28,18}, {29,19}, {30,20}, {31,21}, {32,22}, {33,23}, {34,24}, {35,25}, {36,26}, {38,27} };
    vnToText = { {22,"if"}, {23,"else"}, {24,"for"}, {25,"while"}, {26,"break"}, {27,"return"}, {28,"continue"}, {29,"float"}, {30,"int"}, {31,"char"}, {32,"name"}, {33,"constNumber"}, {34,"+"}, {35,"-"},
    {36,"*"}, {37,"/"}, {38,"%"}, {39,","}, {40,"="}, {41,"["}, {42,"]"}, {43,"("}, {44,")"}, {45,"{"}, {46,"}"}, {47,";"}, {48,"."}, {49,"EOF"} };
    sem.push(ENDSIGN);
    sem.push(vtMap['Z']);
    getAnalysisFromFile();
    tokenPtr = 0;
}

parser::~parser()
{
    for (unsigned int i = 0; i < row; i++)
        delete[list] analysis[i];
    delete[row] analysis;
}

void parser::getAnalysisFromFile()
{
    fstream file("Analysis.txt");
    file >> row >> list;
    analysis = new int* [row];
    for (unsigned int i = 0; i < row; i++)
    {
        analysis[i] = new int[list];
        for (unsigned int j = 0; j < list; j++)
            file >> analysis[i][j];
    }
}

inline bool parser::isTerminal(int v)
{
    return (v >= 22 && v < 49);
}

void parser::LL_driver()
{
    int status = 0, top = sem.top(), input = vnMap[tokenTable[tokenPtr].tokenClass] + row, line = 0;
    while (sem.top() != ENDSIGN)
    {
        if (tokenTable[tokenPtr].tokenClass == 37)
        {
            tokenPtr++;
            line++;
        }
        if (isTerminal(top))
        {
            if (top == input)
            {
                tokenPtr++;
                sem.pop();
                if (tokenTable[tokenPtr].tokenClass == 37)
                {
                    tokenPtr++;
                    line++;
                }
            }
            else
                error(0, line);
        }
        else
        {
            status = analysis[top][vnMap[tokenTable[tokenPtr].tokenClass]];
            switch (status)
            {
            case 1:sem.pop(); sem.push(vtMap['Z']); sem.push(vtMap['S']); break;
            case 2:sem.pop(); break;
            case 3:sem.pop(); sem.push(vtMap['Q']); sem.push(vtMap['B']); break;
            case 4:sem.pop(); sem.push(vtMap['C']); sem.push(vnMap[11] + row); break;
            case 5:sem.pop(); sem.push(vnMap[8] + row); break;
            case 6:sem.pop(); sem.push(vtMap['G']); sem.push(vtMap['D']); break;
            case 7:sem.pop(); sem.push(vtMap['R']); sem.push(vnMap[31] + row); break;
            case 8:sem.pop(); sem.push(vnMap[34] + row); sem.push(vtMap['A']); sem.push(vnMap[33] + row); sem.push(vnMap[32] + row); sem.push(vtMap['L']);break;
            case 9:sem.pop(); sem.push(vnMap[34] + row); sem.push(vtMap['A']); sem.push(vnMap[33] + row); sem.push(vnMap[32] + row); break;
            case 10:sem.pop(); sem.push(vtMap['Q']); sem.push(vnMap[27] + row); break;
            case 11:sem.pop(); sem.push(vnMap[35] + row); break;
            case 12:sem.pop(); sem.push(vnMap[12] + row); sem.push(vnMap[28] + row); break;
            case 13:sem.pop(); sem.push(vtMap['K']); sem.push(vnMap[30] + row); sem.push(vnMap[12] + row); sem.push(vnMap[29] + row);break;
            case 14:sem.pop(); sem.push(vtMap['L']); sem.push(vnMap[27] + row); break;
            case 15:sem.pop(); sem.push(vtMap['A']); sem.push(vtMap['M']); break;
            case 16:sem.pop(); sem.push(vtMap['N']); sem.push(vtMap['M']); sem.push(vnMap[32] + row); sem.push(vtMap['E']); sem.push(vnMap[31] + row); sem.push(vnMap[1] + row); break;
            case 17:sem.pop(); sem.push(vtMap['M']); sem.push(vnMap[32] + row); sem.push(vtMap['E']); sem.push(vnMap[35] + row); sem.push(vtMap['E']);
                 sem.push(vnMap[35] + row); sem.push(vtMap['E']); sem.push(vnMap[31] + row); sem.push(vnMap[3] + row); break;
            case 18:sem.pop(); sem.push(vtMap['M']); sem.push(vnMap[32] + row); sem.push(vtMap['E']); sem.push(vnMap[31] + row); sem.push(vnMap[4] + row); break;
            case 19:sem.pop(); sem.push(vnMap[35] + row); sem.push(vnMap[5] + row); break;
            case 20:sem.pop(); sem.push(vnMap[35] + row); sem.push(vtMap['E']); sem.push(vnMap[6] + row); break;
            case 21:sem.pop(); sem.push(vnMap[35] + row); sem.push(vnMap[7] + row); break;
            case 22:sem.pop(); sem.push(vnMap[35] + row); sem.push(vtMap['E']); break;
            case 23:sem.pop(); sem.push(vnMap[34] + row); sem.push(vtMap['A']); sem.push(vnMap[33] + row); break;
            case 24:sem.pop(); sem.push(vnMap[10] + row); break;
            case 25:sem.pop(); sem.push(vtMap['M']); sem.push(vnMap[2] + row); break;
            case 26:sem.pop(); sem.push(vtMap['V']); sem.push(vtMap['H']); sem.push(vnMap[11] + row); break;
            case 27:sem.pop(); sem.push(vtMap['T']); sem.push(vtMap['P']); break;
            case 28:sem.pop(); sem.push(vtMap['E']); sem.push(vnMap[28] + row); break;
            case 29:sem.pop(); sem.push(vnMap[9] + row); break;
            case 30:sem.pop(); sem.push(vtMap['T']); sem.push(vtMap['P']); sem.push(vnMap[13] + row); break;
            case 31:sem.pop(); sem.push(vtMap['T']); sem.push(vtMap['P']); sem.push(vnMap[14] + row); break;
            case 32:sem.pop(); sem.push(vtMap['I']); sem.push(vtMap['F']); break;
            case 33:sem.pop(); sem.push(vtMap['I']); sem.push(vtMap['F']); sem.push(vnMap[15] + row); break;
            case 34:sem.pop(); sem.push(vtMap['I']); sem.push(vtMap['F']); sem.push(vnMap[16] + row); break;
            case 35:sem.pop(); sem.push(vtMap['I']); sem.push(vtMap['F']); sem.push(vnMap[17] + row); break;
            case 36:sem.pop(); sem.push(vnMap[12] + row); break;
            case 37:sem.pop(); sem.push(vnMap[32] + row); sem.push(vtMap['E']); sem.push(vnMap[31] + row); break;
            case 38:sem.pop(); sem.push(vtMap['H']); sem.push(vnMap[30] + row); sem.push(vtMap['E']); sem.push(vnMap[29] + row); break;
            case 39:sem.pop(); sem.push(vtMap['H']); sem.push(vtMap['X']); sem.push(vnMap[31] + row); break;
            case 40:sem.pop(); sem.push(vtMap['H']); sem.push(vnMap[11] + row); sem.push(vnMap[36] + row); break;
            case 41:sem.pop(); sem.push(vnMap[32] + row); sem.push(vtMap['L']); break;
            case 42:sem.pop(); sem.push(vnMap[32] + row); break;
            default: error(status ,line); break;
            }
        }
        top = sem.top();
        input = vnMap[tokenTable[tokenPtr].tokenClass] + row;
    }
    if (input == ENDSIGN && top == ENDSIGN && flag)
    { 
        cout << "\n程序正确!" << endl;
    }
    else error(-4, line);
}

void parser::error(int errcode, int line)
{
    flag = false;
    switch (errcode)
    {
    case -1:
        cout << line << "不允许的声明" << endl; 
        while (tokenTable[tokenPtr].tokenClass != 8 && tokenTable[tokenPtr].tokenClass != 9 && tokenTable[tokenPtr].tokenClass != 10)
        {
            if (tokenTable[tokenPtr].tokenClass == 38)
                return;
            if (tokenTable[tokenPtr].tokenClass == 35)
            {
                while (!isAccepted(sem.top()))
                    sem.pop();
                return;
            }
            if (tokenTable[tokenPtr].tokenClass == 37)
            {
                tokenPtr++;
                while (sem.top() != 0 && sem.top() != 11)
                    sem.pop();
                return;
            }
            tokenPtr++;
        }
        break;
    case -2:
        cout << line << " 不允许的声明" << endl; 
        while (tokenTable[tokenPtr].tokenClass != 8 && tokenTable[tokenPtr].tokenClass != 9 && tokenTable[tokenPtr].tokenClass != 10)
        {
            if (tokenTable[tokenPtr].tokenClass == 38)
                return;
            if (tokenTable[tokenPtr].tokenClass == 35)
            {
                while (!isAccepted(sem.top()))
                    sem.pop();
                return;
            }
            if (tokenTable[tokenPtr].tokenClass == 37)
            {
                tokenPtr++;
                while (sem.top() != 0 && sem.top() != 11)
                    sem.pop();
                return;
            }
            tokenPtr++;
        }
        break;
    case -3:
        cout << line << " 应输入标识符" << endl; 
        while (tokenTable[tokenPtr].tokenClass != 11)
        {
            if (tokenTable[tokenPtr].tokenClass == 38)
                return;
            if (tokenTable[tokenPtr].tokenClass == 35)
            {
                while (!isAccepted(sem.top()))
                    sem.pop();
                return;
            }
            if (tokenTable[tokenPtr].tokenClass == 37)
            {
                tokenPtr++;
                while (sem.top() != 0 && sem.top() != 11)
                    sem.pop();
                return;
            }
            tokenPtr++;
        }
        break;
    case -4:
        cout << "程序错误!" << endl; 
        break;
    case -5:
        cout << line << " 期盼一个;" << endl; 
        while (tokenTable[tokenPtr].tokenClass != 27 && tokenTable[tokenPtr].tokenClass != 35)
        {
            if (tokenTable[tokenPtr].tokenClass == 38)
                return;
            if (tokenTable[tokenPtr].tokenClass == 37)
            {
                tokenPtr++;
                while (sem.top() != 0 && sem.top() != 11)
                    sem.pop();
                return;
            }
            tokenPtr++;
        }
        break;
    case -11:
        cout << line << " 期盼一个)" << endl; 
        while (tokenTable[tokenPtr].tokenClass != 9 && tokenTable[tokenPtr].tokenClass != 10 && tokenTable[tokenPtr].tokenClass != 8 && tokenTable[tokenPtr].tokenClass != 32)
        {
            if (tokenTable[tokenPtr].tokenClass == 38)
                return;
            if (tokenTable[tokenPtr].tokenClass == 35)
            {
                while (!isAccepted(sem.top()))
                    sem.pop();
                return;
            }
            if (tokenTable[tokenPtr].tokenClass == 37)
            {
                tokenPtr++;
                while (sem.top() != 0 && sem.top() != 11)
                    sem.pop();
                return;
            }
            tokenPtr++;
        }
        break;
    case -12:
        cout << line << " 期盼一个;" << endl; 
        while (tokenTable[tokenPtr].tokenClass != 35)
        {
            if (tokenTable[tokenPtr].tokenClass == 38)
                return;
            if (tokenTable[tokenPtr].tokenClass == 37)
            {
                tokenPtr++;
                while (sem.top() != 0 && sem.top() != 11)
                    sem.pop();
                return;
            }
            tokenPtr++;
        }
        break;
    case -15:
        cout << line << " 期盼一个表达式" << endl; 
        while (tokenTable[tokenPtr].tokenClass != 11 && tokenTable[tokenPtr].tokenClass != 12 && tokenTable[tokenPtr].tokenClass != 31)
        {
            if (tokenTable[tokenPtr].tokenClass == 38)
                return;
            if (tokenTable[tokenPtr].tokenClass == 35)
            {
                while (!isAccepted(sem.top()))
                    sem.pop();
                return;
            }
            if (tokenTable[tokenPtr].tokenClass == 37)
            {
                tokenPtr++;
                while (sem.top() != 0 && sem.top() != 11)
                    sem.pop();
                return;
            }
            tokenPtr++;
        }
        break;
    case -16:
        cout << line << " 表达式存在语法错误" << endl; 
        while (tokenTable[tokenPtr].tokenClass != 12 && tokenTable[tokenPtr].tokenClass != 31)
        {
            if (tokenTable[tokenPtr].tokenClass == 38)
                return;
            if (tokenTable[tokenPtr].tokenClass == 35)
            {
                while (!isAccepted(sem.top()))
                    sem.pop();
                return;
            }
            if (tokenTable[tokenPtr].tokenClass == 37)
            {
                tokenPtr++;
                while (sem.top() != 0 && sem.top() != 11)
                    sem.pop();
                return;
            }
            tokenPtr++;
        }
        break;
    case -17:
        cout << line << " 错误的表达式" << endl;
        while (tokenTable[tokenPtr].tokenClass != 30 && tokenTable[tokenPtr].tokenClass != 32 && tokenTable[tokenPtr].tokenClass != 35)
        {
            if (tokenTable[tokenPtr].tokenClass == 38)
                return;
            if (tokenTable[tokenPtr].tokenClass == 37)
            {
                tokenPtr++;
                while (sem.top() != 0 && sem.top() != 11)
                    sem.pop();
                return;
            }
            tokenPtr++;
        }
        break;
    case 0:
        cout << line << " \'" << vnToText[vnMap[tokenTable[tokenPtr].tokenClass] + row] << "\'" << " 之前期盼一个" << vnToText[sem.top()] << endl;
        while (vnMap[tokenTable[tokenPtr].tokenClass] != sem.top())
        {
            if (tokenTable[tokenPtr].tokenClass == 38)
                return;
            if (tokenTable[tokenPtr].tokenClass == 35)
            {
                while (!isAccepted(sem.top()))
                    sem.pop();
                return;
            }
            if (tokenTable[tokenPtr].tokenClass == 37)
            {
                tokenPtr++;
                while (sem.top() != 0 && sem.top() != 11)
                    sem.pop();
                return;
            }
            tokenPtr++;
        }
        break;
    default:
        cout << "分析表文件内容错误" << endl; 
        exit(0);
        break;
    }
}

bool parser::isAccepted(int top)
{
    switch (top)
    {
    case 4:
    case 6:
    case 7:
    case 8:
    case 11:
    case 12:
    case 13:
    case 15:
    case 16:
    case 18:
    case 20:
    case 47: return true;
    default: return false;
    }
}