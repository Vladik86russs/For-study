#include <iostream>
#include <Windows.h>
#include "bTree.h"
using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	bTree tree;
	int a[] = { 8, 3, 10, 1, 6, 14, 4, 7, 13 };
	cout << "������������������:\n";
	for (int i = 0; i < 9; i++)
	{
		tree.insert(a[i]);
		cout << " " << a[i];
	}
	Iterator* it = tree.create_dft_iterator();
	cout << "\n����� � �������:\n";
	while (it->has_next())
		cout << " " << it->next();
	cout << "\n������ ������� 14 � ����� ����� � �������:\n";
	tree.remove(14);
	it = tree.create_dft_iterator();
	while (it->has_next())
		cout << " " << it->next();
	cout << "\n������� ����� ������� -3 � ����� ����� � �������:\n";
	tree.insert(-3);
	it = tree.create_dft_iterator();
	while (it->has_next())
		cout << " " << it->next();
}