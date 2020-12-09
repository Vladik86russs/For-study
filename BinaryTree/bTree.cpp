#include "bTree.h"
#include <iostream>
using namespace std;

void bTree::deleter(node* point) // recusive deletion
{
	if (point == NULL) return;
	if (point->left != NULL)
	{
		node* lNode = point->left;
		deleter(lNode);
	}
	if (point->right != NULL)
	{
		node* rNode = point->right;
		deleter(rNode);
	}
	delete point;
}

bTree::bTree(int digit) // constructor
{
	root = new node;
	root->data = digit;
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
}

bTree::bTree() // constructor
{
	root = NULL;
}

bTree::~bTree() // destructor
{
	deleter(root);
}

bool bTree::contains(int digit) // To find element in tree
{
	if (root == NULL) return false;
	node* current = root;
	while (1)
	{
		// if element is found
		if (current->data == digit) return true;
		// Search for an element
		if (digit > current->data)
		{
			if (current->right != NULL)
				current = current->right;
			else return false;
		}
		else
		{
			if (current->left != NULL)
				current = current->left;
			else return false;
		}
	}
}

void bTree::insert(int digit)
{
	// creating new node
	node* insertedNode = new node;
	insertedNode->data = digit;
	insertedNode->parent = NULL;
	insertedNode->left = NULL;
	insertedNode->right = NULL;
	
	// search the place for new node
	if (root == NULL)
	{
		root = insertedNode;
	}
	else
	{
		node* current = root;
		while (1)
		{
			if (digit > current->data)
			{
				if(current->right != NULL)
				current = current->right;
				else
				{
					insertedNode->parent = current;
					current->right = insertedNode;
					break;
				}
			}
			else
			{
				if (current->left != NULL)
					current = current->left;
				else
				{
					insertedNode->parent = current;
					current->left = insertedNode;
					break;
				}
			}
		}
	}
}

void bTree::remove(int digit)
{
	if (root == NULL) return;
	node* current = root;
	// search for element
	while (1)
	{
		if (current->data == digit)
		{
			// if current doesn't have child
			if (current->left == NULL && current->right == NULL)
			{
				if (current->parent != NULL)
				{
					if (current->parent->left == current)
						current->parent->left = NULL;
					else
						current->parent->right = NULL;
				}
				else
				{
					// if root is last element
					root = NULL;
				}
				delete current;
				return;
			}
			// if current have 1 child
			else if (current->left == NULL || current->right == NULL)
			{
				if (current->left != NULL)
				{
					swap(current->data, current->left->data);
					delete current->left;
					current->left = NULL;
				}
				else
				{
					swap(current->data, current->right->data);
					delete current->right;
					current->right = NULL;
				}
				return;
			}
			// if have 2
			else
			{
				node* currentForSwap = current->left;
				while (currentForSwap->right != NULL)
					currentForSwap = currentForSwap->right;
				swap(current->data, currentForSwap->data);
				if (currentForSwap->parent->right == currentForSwap)
					currentForSwap->parent->right = NULL;
				else
					currentForSwap->parent->left = NULL;
				delete currentForSwap;
			}
		}

		// search for element
		if (digit > current->data)
		{
			if (current->right != NULL)
				current = current->right;
			else return;
		}
		else
		{
			if (current->left != NULL)
				current = current->left;
			else return;
		}
	}
}

Iterator* bTree::create_dft_iterator()
{
	if (root == NULL) throw out_of_range("tree is empty");
	return new dft_iterator(root);
}

bTree::dft_iterator::dft_iterator(node* start)
{
	current = start;
	stack.push(current);
}

bool bTree::dft_iterator::has_next()
{
	return !stack.isEmpty();
}

int bTree::dft_iterator::next()
{
	if (!has_next()) throw out_of_range("tree is empty");
	current = stack.pop(); // put out of the stack
	if (current->right != NULL)
		stack.push(current->right); //  put in the stack
	if (current->left != NULL)
		stack.push(current->left); //  put in the stack
	return current->data;
}

Iterator* bTree::create_bft_iterator()
{
	if (root == NULL) throw out_of_range("tree is empty");
	return new bft_iterator(root);
}

bTree::bft_iterator::bft_iterator(node* start)
{
	current = start;
	queue.enqueue(current);
}

bool bTree::bft_iterator::has_next()
{
	return !queue.isEmpty();
}

int bTree::bft_iterator::next()
{
	if (!has_next()) throw out_of_range("tree is empty");
	current = queue.dequeue(); // put out of the queue
	if (current->left != NULL)
		queue.enqueue(current->left); // put in the queue
	if (current->right != NULL)
		queue.enqueue(current->right); // put in the queue
	return current->data;
}
