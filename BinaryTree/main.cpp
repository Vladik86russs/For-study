#include <iostream>
#include <Windows.h>
#include "bTree.h"
using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	bTree tree;
	int a[] = { 8, 3, 10, 1, 6, 14, 4, 7, 13 };
	cout << "Последовательность:\n";
	for (int i = 0; i < 9; i++)
	{
		tree.insert(a[i]);
		cout << " " << a[i];
	}
	Iterator* it = tree.create_dft_iterator();
	cout << "\nПоиск в глубину:\n";
	while (it->has_next())
		cout << " " << it->next();
	cout << "\nУдалим элемент 14 и снова поиск в глубину:\n";
	tree.remove(14);
	it = tree.create_dft_iterator();
	while (it->has_next())
		cout << " " << it->next();
	cout << "\nВставим новый элемент -3 и снова поиск в глубину:\n";
	tree.insert(-3);
	it = tree.create_dft_iterator();
	while (it->has_next())
		cout << " " << it->next();
}