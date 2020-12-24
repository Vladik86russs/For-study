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

void Error(Expression* exp, int posError)
{
	for (int i = 0; i < exp->get_size(); i++)
	{
		//set red color
		if (i == posError) SetColor(12);
		for (int j = 0; j < exp->at(i).size(); j++)
			cout << exp->at(i)[j];
		//set black color
		if (i == posError) SetColor(0);
	}
	cout << "     <- Вы ввели выражение неверно";
}

void Answer(double result, Expression* pfExp)
{
	cout << "\n\tПостфиксная форма:\n\t";
	for (int i = 0; i < pfExp->get_size(); i++)
		cout << pfExp->at(i) << " ";
	cout << "\n\tОтвет:\n\t";
	cout << result;
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
		if (posError != -1) Error(&exp, posError);
		else
		{
			double result;
			exp.postfix(&pfExp);
			posError = pfExp.result(result);
			if (posError != -1) Error(&exp, posError);
			else Answer(result, &pfExp);
		}
		cout << "\nПопробовать еще раз? (Да/Нет) - ";
		getline(cin, answer);
		if (answer == "Да") flaqCycle = 1;
		else if (answer == "Нет")
			{
				flaqCycle = 0;
				cout << "\nДосвидули!\n";
			}
	} while (flaqCycle);
	return 0;
}