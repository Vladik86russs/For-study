#include "list.h"
#include <iostream>


using namespace std;


int main()
{
	myList mark, mark2;
	for (int i = 0; i < 10; i++)
		mark.push_back(i);
	for (int i = 3; i < 10; i++)
		mark2.push_back(i);
	cout << mark.find_first(&mark2);
	cout << endl;
	mark2.print_to_console();
	return 0;
}