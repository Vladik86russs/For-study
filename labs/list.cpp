#include "list.h"
#include <iostream>
#include <stdexcept>

using namespace std;

myList::myList(int digitIn)
{
	head = new LinkedList;
	head->next = NULL;
	head->data = digitIn;
	tail = head;
	countNodes++;
}

myList::myList()
{
	tail = NULL;
	head = NULL;
}

myList::~myList()
{
}


int myList::at(size_t position)
{
	now = head;
	if (position >= countNodes || position < 0) //exception
	{
		throw out_of_range("Index is greater than list size");
	}
	for (int i = 0; i < position; i++) // cycle to look for needful node
	{
		now = now->next;
	}
	return now->data;
}


void myList::clear()
{
	now = head;
	for (int i = 0; i < countNodes; i++) // cycle to delete nodes
	{
		LinkedList* removable = now;
		now = now->next;
		delete removable;
	}
	head = NULL;
	tail = NULL;
	countNodes = 0;
}


size_t myList::find_first(myList otherList)
{

	if (otherList.isEmpty() || isEmpty()) throw invalid_argument("list is empty");
	now = head;
	for (int i = 0; i < countNodes; i++) // looking for first coincidence
	{
		if (at(i) == otherList.at(0))  
		{
			for (int j = 1; j < otherList.get_size(); j++) // checking other nodes
			{
				if (at(i + j) != otherList.at(j)) break;
				if (j == otherList.get_size() - 1) return size_t(i);
			}
		}
	}
	throw domain_error("not found"); // exception
}


size_t myList::get_size()
{
	return size_t(countNodes);
}


void myList::insert(int digitIn, size_t position)
{
	if (position > countNodes || position < 0) // exception
	{
		throw out_of_range("Index is greater than list size");
	}
	now = head;
	if (position != 0) 
	{
		for (int i = 0; i < position - 1; i++) // cycle to look for needful node
		{
			now = now->next;
		}
		LinkedList* inserted = new LinkedList; // creating node
		inserted->data = digitIn;
		inserted->next = now->next;
		now->next = inserted;
		if (position == countNodes)
			tail = now;
	}
	else
	{
		LinkedList* inserted = new LinkedList;
		inserted->data = digitIn;
		inserted->next = head;
		head = inserted;
		tail = head;
	}
	countNodes++;
}


bool myList::isEmpty()
{
	if (head == NULL) return true;
	else return false;
}


void myList::pop_back() 
{
	if (countNodes == 0) throw out_of_range("List is empty"); // exception
	now = head;
	if (countNodes == 1)
	{
		delete head;
		head = NULL;
		tail = NULL;
		now = NULL;
	}
	else
	{
		for (int i = 0; i < countNodes - 2; i++) //cycle to look for needful node
		{
			now = now->next;
		}
		now->next = NULL;
		delete tail;
		tail = now;
	}
	countNodes--;
}


void myList::pop_front()
{
	if (countNodes == 0) throw out_of_range("List is empty"); //exception
	if (countNodes == 1)
	{
		delete head;
		head = NULL;
		tail = NULL;
		now = NULL;
	}
	else
	{
		now = head;
		head = head->next;
		delete now;
	}
	countNodes--;
}


void myList::print_to_console()
{
	if (countNodes == 0) throw out_of_range("List is empty"); //exception
	now = head;
	std::cout << " | ";
	for (int i = 0; i < countNodes; i++)
	{
		std::cout << now->data << " | ";
		now = now->next;
	}
}


void myList::push_back(int digitIn)
{
	if (head == NULL)
	{
		head = new LinkedList;
		tail = head;
		head->data = digitIn;
		countNodes++;
	}
	else
	{
		tail->next = new LinkedList;
		tail = tail->next;
		tail->data = digitIn;
		tail->next = NULL;
		countNodes++;
	}
}


void myList::push_front(int digitIn)
{
	if (head == NULL)
	{
		head = new LinkedList;
		tail = head;
		head->data = digitIn;
		countNodes++;
	}
	else
	{
		now = new LinkedList;
		now->next = head;
		now->data = digitIn;
		head = now;
		countNodes++;
	}
}


void myList::remove(size_t position)
{
	if (position < 0 || position >= countNodes) // exception
	{
		throw out_of_range("Index is greater than list size");
	}
	if (position != 0)
	{
		now = head;
		for (int i = 0; i < position - 1; i++) // cycle to look for needful node
		{
			now = now->next;
		}
		LinkedList* removable = now->next;
		now->next = removable->next;
		delete removable;
	}
	else
	{
		LinkedList* removable = head;
		head = head->next;
		delete removable;
	}
	countNodes--;
}


void myList::set(size_t position, int digitIn)
{
	if (position < 0 || position >= countNodes) // exception
		throw out_of_range("Index is greater than list size");
	now = head;
	for (int i = 0; i < position; i++) // cycle to look for needful node
	{
		now = now->next;
	}
	now->data = digitIn;
}