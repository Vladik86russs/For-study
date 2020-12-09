#pragma once
#include <iostream>
using namespace std;

template <class type>
class Queue
{
private:
	// node of queue
	struct queueNode
	{
		type data;
		queueNode* next;
	};
	queueNode* head;
	queueNode* tail;
	int countNodes;
public:
	Queue()
	{
		head = NULL;
		tail = NULL;
		countNodes = 0;
	}
	~Queue()
	{
		if (countNodes > 0)
		{
			while (head->next != NULL)
			{
				queueNode* cur = head;
				head = head->next;
				delete cur;
			}
			delete head;
		}
	}
	// to add in queue
	void enqueue(type el)
	{
		queueNode* cur = new queueNode;
		cur->data = el;
		cur->next = NULL;
		if (countNodes == 0)
		{
			head = cur;
			tail = cur;
		}
		else
		{
			tail->next = cur;
			tail = cur;
		}
		countNodes++;
	}
	// to delete and return from queue
	type dequeue()
	{
		if (countNodes == 0) throw out_of_range("stack is empty");
		queueNode* cur = head;
		head = head->next;
		type el = cur->data;
		delete cur;
		countNodes--;
		return el;
	}
	// to return from queue
	type peek()
	{
		if (countNodes == 0) throw out_of_range("stack is empty");
		return head->data;
	}
	// to check for empty
	bool isEmpty()
	{
		if (countNodes == 0) return 1;
		else return 0;
	}
};