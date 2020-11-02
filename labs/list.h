#pragma once
class myList
{
public:
	myList(int digitIn); // constructor with digit
	myList(); // only costructor
	~myList(); // destructor
	void push_back(int digitIn); // method to add to the end
	void push_front(int digitIn); // method to add to the begin
	void pop_back(); // method for deleting the last one
	void pop_front(); // method for deleting the first one
	void insert(int digitIn, size_t position); // method to insert
	int at(size_t position); // method to return data
	void remove(size_t position);  // method for deleting position's element
	size_t get_size(); // method to return size of list
	void print_to_console(); // method to print to console
	void clear(); // method to clear list
	void set(size_t position, int digitIn); // method t change data of element
	bool isEmpty(); // method to find out if the list is empty
	size_t find_first(myList otherList); // method to find out position second list in first list
private:
	struct LinkedList
	{
		int data;
		LinkedList* next;
	};
	LinkedList* head;
	LinkedList* tail;
	LinkedList* now;
	int countNodes = 0; // count of nodes
};