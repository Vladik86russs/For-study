#pragma once
#include "Iterator.h"
#include "Stack.h"
#include "Queue.h"

class bTree
{
private:
	struct node
	{
		int data;
		node* parent;
		node* right;
		node* left;
	};
	node* root;
	void deleter(node* point); // To delete the tree
public:
	bTree(int);
	bTree();
	~bTree();
	bool contains(int); // To find element in tree
	void insert(int); // To insert element in tree
	void remove(int); // To delete element in tree
	Iterator* create_dft_iterator(); // To return dft_iterator
	class dft_iterator : public Iterator
	{
	public:
		dft_iterator(node* start);
		bool has_next() override;
		int next() override;
	private:
		node* current;
		Stack <node*> stack;
	};
	Iterator* create_bft_iterator(); // To return bft_iterator
	class bft_iterator : public Iterator
	{
	public:
		bft_iterator(node* start);
		bool has_next() override;
		int next() override;
	private:
		node* current;
		Queue <node*> queue;
	};
};