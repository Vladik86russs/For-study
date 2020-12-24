#include "Expression.h"
#include <stdexcept>
#include "../BinaryTree/Stack.h"

Expression::Expression()
{
	head = NULL;
	tail = NULL;
	countNodes = 0;
}

Expression::~Expression()
{
	while (countNodes > 0)
		pop_back();
}

string Expression::at(size_t pos)
{
	if (pos >= countNodes) throw out_of_range("Pos is larger than expression size");
	node* cur = head;
	for (int i = 0; i < pos; i++)
	{
		cur = cur->next;
	}
	return cur->element;
}

void Expression::push_back(string el, typeEl type, priority prior)
{
	node* cur = new node(el, type, prior);
	if (countNodes == 0)
	{
		head = cur;
		tail = cur;
	}
	else
	{
		tail->next = cur;
		cur->prev = tail;
		tail = cur;
	}
	countNodes++;
}

string Expression::back()
{
	if (countNodes == 0) throw out_of_range("Expression is empty");
	return tail->element;
}

void Expression::pop_back()
{
	if (countNodes == 0) out_of_range ("Expression is empty");
	if (countNodes == 1)
	{
		delete head;
		head = NULL;
		tail = NULL;
	}
	else
	{
		tail = tail->prev;
		delete tail->next;
		tail->next = NULL;
	}
	countNodes--;
}

size_t Expression::get_size()
{
	return countNodes;
}

int Expression::createExp(string str)
{
	if (str.size() == 0) throw out_of_range("string is empty");
	for (int i = 0; i < str.size(); i++)
	{
		string el;
		// the number is found
		if (str[i] >= '0' && str[i] <= '9')
		{
			int j = i;
			for (j; j < str.size(); j++)
			{
				if ((str[j] >= '0' && str[j] <= '9') || str[j] == ',')
				{
					//remember the symbols
					el.push_back(str[j]); 
				}
				else break;
			}
			//save the digit
			push_back(el, digit, low);
			//return the lost one
			i = j - 1;
		}
		// the word is found
		else if (str[i] >= 'a' && str[i] <= 'z')
		{
			int j = i;
			for (j; j < str.size(); j++)
			{
				if (str[j] >= 'a' && str[j] <= 'z')
				{
					//remember the symbols
					el.push_back(str[j]);
				}
				else break;
			}

			// save the word as function or const
			if (el == "cos") push_back("cos", function, extra);
			else if (el == "sin") push_back("sin", function, extra);
			else if (el == "tg") push_back("tg", function, extra);
			else if (el == "ctg") push_back("ctg", function, extra);
			else if (el == "ln") push_back("ln", function, extra);
			else if (el == "log") push_back("log", function, extra);
			else if (el == "sqrt") push_back("sqrt", function, extra);
			else if (el == "sh") push_back("sh", function, extra);
			else if (el == "pi") push_back("pi", digit, low);
			else if (el == "e") push_back("e", digit, low);
			else return i;
			//return the lost one
			i = j - 1;
		}
		// the operator is found
		else if ((str[i] >= '(' && str[i] <= '+') || str[i] == '-' || str[i] == '/' || str[i] == '^') // +,-,*,/,(,),^
		{
			//save the oparator
			switch (str[i])
			{
			case '(':
				push_back("(", leftBracket, low);
				break;
			case ')':
				push_back(")", rightBracket, low);
				break;
			case '+':
				push_back("+", oper, medium);
				break;
			case '-':
				push_back("-", oper, medium);
				break;
			case '*':
				push_back("*", oper, high);
				break;
			case '/':
				push_back("/", oper, high);
				break;
			case '^':
				push_back("^", oper, extra);
				break;
			}
		}
		else return i;
	}
	return checkForErrors();
}

int Expression::checkForErrors()
{
	node* cur = head; int poslastBracket = -1;
	size_t countFreeLBrackets = 0;
	for (int i = 0; i < countNodes; i++)
	{
		if (cur->type == digit)
		{
			// if digit is not a const
			if (cur->element != "pi" && cur->element != "e")
			{
				bool comma = 0;
				//searching errors in a digit
				for (int i = 0; i < cur->element.size(); i++)
				{
					if (cur->element[i] == ',')
						if (comma) return i;
						else if (i == cur->element.size() - 1) return i;
						else comma = 1;
				}
			}
			// if there is a next
			if (cur->next != NULL)
			{
				if (cur->next->type == function) return i;
				if (cur->next->type == leftBracket) return i;
				if (cur->next->type == digit) return i;
			}
		}
		else if (cur->type == function)
		{
			// if there is a next
			if (cur->next != NULL)
			{
				if (cur->next->type != leftBracket) return i;
			}
			else return i;
		}
		else if (cur->type == leftBracket)
		{
			if (cur->next != NULL)
			{
				if (cur->next->type == rightBracket) return i;
				if (cur->next->type == oper && cur->next->element != "-") return i;
			}
			// if left bracket is last then return position of error
			else return i;
			if (countFreeLBrackets == 0) poslastBracket = i;
			countFreeLBrackets++;
		}
		else if (cur->type == rightBracket)
		{
			if (cur->next != NULL)
			{
				if (cur->next->type == leftBracket) return i;
				if (cur->next->type == digit) return i;
				if (cur->next->type == function) return i;
			}
			// if right bracket is first then return pos of error
			if (i == 0) return i;
			if (countFreeLBrackets == 0) return i;
			countFreeLBrackets--;
		}
		else if (cur->type == oper)
		{
			if (cur->next != NULL)
			{
				if (cur->next->type == rightBracket) return i;
				if (cur->next->type == oper) return i;
			}
			// if operator is last
			else return i;

			// if operator is unary minus
			if (cur->element == "-")
			{
				if (cur->prev != NULL)
				{
					if (cur->prev->type == leftBracket)
					{
						cur->prior = extra;
						cur->type = function;
					}
				}
				else
				{
					cur->prior = extra;
					cur->type = function;
				}
			}
			// if operator is first ans it is not unary minus
			if (i == 0 && cur->type != function) return i;
		}
		cur = cur -> next;
	}

	if (countFreeLBrackets != 0) return poslastBracket;
	// if there are not errors return -1
	return -1;
}

void Expression::postfix(Expression* pfExpression)
{
	Stack <node*> stack; node* cur = head;
	for (int i = 0; i < countNodes; i++)
	{
		if (cur->type == leftBracket)
		{
			stack.push(cur);
		}
		else if (cur->type == rightBracket)
		{
			while (!stack.isEmpty())
			{
				if (stack.top()->type == leftBracket)
				{
					stack.pop();
					break;
				}
				else
				{
					pfExpression->push_back(stack.top()->element, stack.top()->type, stack.top()->prior);
					stack.pop();
				}
			}
		}
		else if (cur->type == digit)
		{
			pfExpression->push_back(cur->element, digit, low);
		}
		else
		{
			while (!stack.isEmpty())
			{
				if (stack.top()->type == digit)
					break;
				else
				{
					if (stack.top()->prior >= cur->prior)
					{
						pfExpression->push_back(stack.top()->element, stack.top()->type, stack.top()->prior);
						stack.pop();
					}
					else break;
				}
			}
			stack.push(cur);
		}
		cur = cur->next;
	}
	while (!stack.isEmpty())
	{
		pfExpression->push_back(stack.top()->element, stack.top()->type, stack.top()->prior);
		stack.pop();
	}
}

double Expression::string_to_double(string digit)
{
	if (digit.size() == 0) throw out_of_range("string is empty");
	if (digit == "pi") return pi;
	if (digit == "e") return e;
	size_t posComma = 0; double dDigit = 0; int exp;
	// search for a comma
	for ( posComma; posComma < digit.size(); posComma++)
		if (digit[posComma] == ',') break;
	exp = 0;
	// if there is not a comma
	if (posComma == digit.size() - 1)
	{
		for (int i = digit.size() - 1; i >= 0; i--)
		{
			dDigit += (digit[i] - '0')*exponent(10, exp);
			exp++;
		}
	}
	//if there is a comma
	else
	{
		for (int i = posComma - 1; i >= 0; i--)
		{
			dDigit += (digit[i] - '0') * exponent(10, exp);
			exp++;
		}
		exp = -1;
		for (int i = posComma + 1; i < digit.size(); i++)
		{
			dDigit += (digit[i] - '0') * exponent(10, exp);
			exp--;
		}
	}
	return dDigit;
}

double Expression::result()
{
	if (countNodes == 0) throw out_of_range("Expression is empty");
	node* cur = head; Stack <double> stack;
	do
	{
		if (cur->type == digit)
		{
			stack.push(string_to_double(cur->element));
		}
		if (cur->type == oper)
		{
			double A = stack.pop();
			double B = stack.pop();
			if (cur->element == "+") A = B + A;
			else if (cur->element == "-") A = B - A;
			else if (cur->element == "*") A = B * A;
			else if (cur->element == "/") A = B / A;
			else if (cur->element == "^") A = exponent(B, A);
			stack.push(A);
		}
		if (cur->type == function)
		{
			double A = stack.pop();
			if (cur->element == "cos") A = cos(A);
			else if (cur->element == "sin") A = sin(A);
			else if (cur->element == "tg") A = tg(A);
			else if (cur->element == "ctg") A = ctg(A);
			else if (cur->element == "sh") A = sh(A);
			else if (cur->element == "ln") A = ln(A);
			else if (cur->element == "log") A = log(A);
			else if (cur->element == "sqrt") A = sqrt(A);
			else if (cur->element == "-") A = -A;
			stack.push(A);
		}
		cur = cur->next;
	} while (cur != NULL);
	return stack.pop();
}

// natural logarithm
double Expression::ln(double x)
{
	if (x <= 0) throw out_of_range("x is no more than zero");
	double f = 0;
	double t = (x - 1) / (x + 1);
	size_t exp = 1;
	for (int i = 0; i < 20; i++)
	{
		f += 2 * exponent(t, exp) / exp;
		exp += 2;
	}
	return f;
}

double Expression::log(double x)
{
	if (x <= 0) throw out_of_range("x is no more than zero");
	return (ln(x)/ln(10));
}

double Expression::exponent(double basis, double exp)
{
	bool sign = 0;
	if (exp < 0)
	{
		exp *= -1;
		sign = 1;
	}
	size_t denominator = 1; 
	double f1 = 1; double f0;
	do
	{
		f0 = f1;
		double x = 1;
		if (exp == 0) break;
		for (int i = 0; i < (int)exp; i++)
			x *= basis;
		if (denominator == 1) f1 *= x;
		else f1 *= root(x, denominator);
		exp -= (int)exp;
		exp *= 10;
		denominator *= 10;
	} while ( ( (f1 - f0) >= 0.00001) || ((f1 - f0) <= -0.00001));
	if (sign) f1 = 1 / f1;
	return f1;
}

double Expression::root(double basis, size_t exp)
{
	if (exp % 2 == 0 && basis < 0) throw out_of_range("basis is negative");
	double x0; double x1 = 1;
	do
	{
		x0 = x1;
		x1 = ((exp - 1) * x0 + basis / (exponent(x0, exp - 1))) / exp;
	} while (((x1 - x0) >= 0.000001) || ((x1 - x0) <= -0.000001));
	return x1;
}

double Expression::sqrt(double basis)
{
	if (basis < 0) throw out_of_range("basis is negative");
	return root(basis, 2);
}

double Expression::cos(double x)
{
	double f = 0;
	if (x > 0)  while (x >= 2*pi) x -= 2*pi;
	else while (x <= -2*pi) x += 2*pi;
	if ((x - pi / 2 <= 0.00001) && (x - pi / 2 >= -0.00001)) return 0;
	if ((x + pi / 2 <= 0.00001) && (x + pi / 2 >= -0.00001)) return 0;
	for (size_t i = 0; i < 50; i++)
	{
		if (i % 2 == 0)
			f += exponent(x, 2 * i) / factorial(2 * i);
		else
			f -= exponent(x, 2 * i) / factorial(2 * i);
	}
	return f;
}

double Expression::sin(double x)
{
	double f = 0;
	if (x > 0)  while (x >= 2*pi) x -= 2*pi;
	else while (x <= -2*pi) x += 2*pi;
	if ((x - pi <= 0.00001) && (x - pi >= -0.00001)) return 0;
	if ((x + pi <= 0.00001) && (x + pi >= -0.00001)) return 0;
	for (size_t i = 0; i < 50; i++)
	{
		if (i % 2 == 0)
			f += exponent(x, 2 * i + 1) / factorial(2 * i + 1);
		else
			f -= exponent(x, 2 * i + 1) / factorial(2 * i + 1);
	}
	return f;
}

double Expression::tg(double x)
{
	return sin(x)/cos(x);
}

double Expression::ctg(double x)
{
	return cos(x)/sin(x);
}

double Expression::sh(double x)
{
	return (exponent(e, x) + exponent(e, -x))/2;
}

double Expression::factorial(size_t x)
{
	double fact = 1;
	for (size_t i = 1; i <= x; i++)
	{
		fact *= i;
	}
	return fact;
}
