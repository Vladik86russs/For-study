#pragma once
#include <iostream>
using namespace std;

template <class type>
class Stack
{
private:
	// node of stack
	struct stackNode
	{
		type data;
		stackNode* prev;
	};
	stackNode* topNode;
	int countNodes;
public:
	Stack()
	{
		topNode = NULL;
		countNodes = 0;
	}
	~Stack()
	{
		if (countNodes > 0)
		{
			while (topNode->prev != NULL)
			{
				stackNode* cur = topNode;
				topNode = topNode->prev;
				delete cur;
			}
			delete topNode;
		}
	}
	// to add in stack
	void push(type el)
	{
		// creating a new node
		stackNode* cur = new stackNode;
		cur->data = el;
		cur->prev = NULL;
		if (countNodes == 0)
		{
			//insert new node
			topNode = cur;
			countNodes++;
		}
		else
		{
			//insert new node
			cur->prev = topNode;
			topNode = cur;
			countNodes++;
		}
	}
	// to delete and return from stack
	type pop()
	{
		if (countNodes == 0) throw out_of_range("stack is empty");
		stackNode* cur = topNode;
		topNode = topNode->prev;
		type el = cur->data;
		delete cur;
		countNodes--;
		return el;
	}
	// to return from stack
	type top()
	{
		if (countNodes == 0) throw out_of_range("stack is empty");
		return topNode->data;
	}
	// to check for empty
	bool isEmpty()
	{
		if (countNodes == 0) return 1;
		else return 0;
	}
};
