#include <string>
#include <iostream>
#include <Windows.h>
#include "Expression.h"

using namespace std;

void SetColor(int text)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console,  (( 15 << 4) | text));
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	system("color F0");
	bool flaqCycle = 0;
	do
	{
		system("cls");
		string str, answer; int posError;
		getline(cin, str);
		Expression exp;
		Expression pfExp;
		posError = exp.createExp(str);
		// if there is error
		if (posError != -1)
		{
			for (int i = 0; i < exp.get_size(); i++)
			{
				//set red color
				if (i == posError) SetColor(12);
				cout << exp.at(i);
				//set black color
				if (i == posError) SetColor(0);
			}
			cout << "     <- �� ����� ��������� �������";
			cout << "\n����������� ��� ���? (��/���) - ";
			getline(cin, answer);
			if (answer == "��") flaqCycle = 1;
			else if (answer == "���")
			{
				flaqCycle = 0;
				cout << "\n���������!";
			}
		}
		// if there are not errors
		else
		{
			exp.postfix(&pfExp);
			cout << "\n\t����������� �����:\n\t";
			for (int i = 0; i < pfExp.get_size(); i++)
				cout << pfExp.at(i) << " ";
			cout << "\n\t�����:\n\t";
			cout << pfExp.result();
			cout << "\n����������� ��� ���? (��/���) - ";
			getline(cin, answer);
			if (answer == "��") flaqCycle = 1;
			else if (answer == "���")
			{
				flaqCycle = 0;
				cout << "\n���������!\n";
			}
		}
	} while (flaqCycle);
	return 0;
}