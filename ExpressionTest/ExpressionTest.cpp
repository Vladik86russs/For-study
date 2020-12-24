#include "pch.h"
#include "CppUnitTest.h"
#include "../kursach/Expression.h"
#include "../kursach/Expression.cpp"
#include <cmath>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ExpressionTest
{
	TEST_CLASS(ExpressionTest)
	{
	public:
		
		TEST_METHOD(atTest)
		{
			Expression expression;
			string str = "(1+2)*4";
			expression.createExp(str);
			for (int i = 0; i < expression.get_size(); i++)
				Assert::AreEqual(expression.at(i), { str[i] });
		}

		TEST_METHOD(backTest)
		{
			Expression expression;
			string str = "(1+2)*4";
			expression.createExp(str);
			Assert::AreEqual(expression.back(), {'4'});
		}

		TEST_METHOD(checkTest)
		{
			Expression expression;
			string str = "2*cas(pi)";
			Assert::AreEqual(expression.createExp(str), 2);
		}

		TEST_METHOD(cosTest)
		{
			Expression expression, pfExpression;
			string str = "cos(1,5)";
			expression.createExp(str);
			expression.postfix(&pfExpression);
			double res;
			pfExpression.result(res);
			Assert::AreEqual( abs(std::cos(1.5) - res) <= 0.001, true);
		}

		TEST_METHOD(ctgTest)
		{
			Expression expression, pfExpression;
			string str = "ctg(1,5)";
			expression.createExp(str);
			expression.postfix(&pfExpression);
			double res;
			pfExpression.result(res);
			Assert::AreEqual(abs(std::cos(1.5)/std::sin(1.5) - res) <= 0.001, true);
		}


		TEST_METHOD(tgTest)
		{
			Expression expression, pfExpression;
			string str = "tg(1,5)";
			expression.createExp(str);
			expression.postfix(&pfExpression);
			double res;
			pfExpression.result(res);
			Assert::AreEqual(abs(std::sin(1.5) / std::cos(1.5) - res) <= 0.001, true);
		}


		TEST_METHOD(exponentTest)
		{
			Expression expression, pfExpression;
			string str = "1,5^3,6";
			expression.createExp(str);
			expression.postfix(&pfExpression);
			double res;
			pfExpression.result(res);
			Assert::AreEqual(abs(pow(1.5, 3.6) - res) <= 0.001, true);
		}


		TEST_METHOD(lnTest)
		{
			Expression expression, pfExpression;
			string str = "ln(14,6)";
			expression.createExp(str);
			expression.postfix(&pfExpression);
			double res;
			pfExpression.result(res);
			Assert::AreEqual(abs(std::log(14.6) - res) <= 0.001, true);
		}


		TEST_METHOD(logTest)
		{
			Expression expression, pfExpression;
			string str = "log(14,6)";
			expression.createExp(str);
			expression.postfix(&pfExpression);
			double res;
			pfExpression.result(res);
			Assert::AreEqual(abs(std::log10(14.6) - res) <= 0.001, true);
		}


		TEST_METHOD(postfixTest)
		{
			Expression expression, pfExpression;
			string infix = "((1-(2+3))*4)^(5+6)";
			string postfix = "123+-4*56+^";
			expression.createExp(infix);
			expression.postfix(&pfExpression);
			for(int i = 0; i < pfExpression.get_size(); i++)
				Assert::AreEqual(pfExpression.at(i), { postfix[i] });
		}

		TEST_METHOD(resultTest)
		{
			Expression expression, pfExpression;
			string infix = "3*4^2+(-2+6*7)";
			expression.createExp(infix);
			expression.postfix(&pfExpression);
			double res;
			pfExpression.result(res);
			Assert::AreEqual(res, 88.0);
		}

		TEST_METHOD(sinTest)
		{
			Expression expression, pfExpression;
			string str = "sin(1,5)";
			expression.createExp(str);
			expression.postfix(&pfExpression);
			double res;
			pfExpression.result(res);
			Assert::AreEqual(abs(std::sin(1.5) - res) <= 0.001, true);
		}
	};
}
