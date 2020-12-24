#pragma once
#include <string>

using namespace std;

class Expression
{
private:
	//type of element
	enum typeEl { digit, leftBracket, rightBracket, oper, function };
	//priority of operator
	enum priority { low, medium, high, extra };
	
	struct node
	{
	public:
		string element;
		typeEl type;
		priority prior;
		node* prev;
		node* next;
		node(string element, typeEl type, priority prior)
		{
			this->element = element;
			this->type = type;
			this->prior = prior;
			this->prev = NULL;
			this->next = NULL;
		}
	};

	size_t countNodes;
	node* head;
	node* tail;
	const double pi = 3.14159;
	const double e = 2.71828;
public:
	Expression();
	~Expression();
	string at(size_t);
	void push_back(string, typeEl, priority);
	string back(); // return last element
	void pop_back();
	size_t get_size();
	int createExp(string); // Converts string to expression
	int checkForErrors(); // for searching errors
	void postfix(Expression*); // converts infix expression to postfix expression
	double string_to_double(string);
	int result(double&); // Calculates the answer for postfix expression
	double ln(double); //  natural logarithm
	double log(double); // decimal logarithm
	double exponent(double, double); // calculates the number in the degree
	double root(double, size_t); // calculates the number in the root
	double sqrt(double); // square root
	double cos(double);
	double sin(double);
	double tg(double);
	double ctg(double);
	double sh(double); // hyperbolic sine
	double factorial(size_t);
};