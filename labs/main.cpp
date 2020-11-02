#include "list.h"
#include <iostream>


using namespace std;


int main()
{
	myList mark;
	int digit;
	size_t position;
	for (int i = 0; i < 10; i++)
		mark.push_back(i);
	mark.print_to_console();
	for (int i = 0; i < 3; i++) 
	{
		cout << "\nmethod pop_back is worked\n";
		mark.pop_back();
		mark.print_to_console();
		cout << "\nmethod pop_front is worked\n";
		mark.pop_front();
		mark.print_to_console();
	}
	

}