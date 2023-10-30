#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <stack>
#include "interface.h"
#include "lexanalyzer.h"
#include "expevaluator.h"

using namespace std;

bool expEvaluator:: isOperator(LexicalAnalyzer::pairType i)
{
	return i.second == LexicalAnalyzer::categoryType::ASSIGNMENT_OP || i.second == LexicalAnalyzer::categoryType::ARITH_OP || i.second == LexicalAnalyzer::categoryType::LOGICAL_OP || i.second == LexicalAnalyzer::categoryType::RELATIONAL_OP;
}

bool expEvaluator:: IsaDigit(string value)
{
	return value == "0" || value == "1" || value == "2" || value == "3" || value == "4" || value == "5" || value == "6" || value == "7" || value == "8" || value == "9";
}

int expEvaluator::assigningPrecedence(string symbol)
{
	if (symbol == "*" || symbol == "/" || symbol == "%")
		return 5;
	else if (symbol == "+" || symbol == "-")
		return 4;
	else if (symbol == "<" || symbol == "<=" || symbol == ">" || symbol == ">=" || symbol == "!=" || symbol == "==")
		return 3;
	else if (symbol == "not")
		return 2;
	else if (symbol == "and")
		return 1;
	else if (symbol == "or")
		return 0;

	else
	{
		cout << "Error, invalid expression.";
		return 0;
	}
}



int expEvaluator::operandEvaluation(int operand1, int operand2, string sym)
{
	if (sym == "*")
		return operand1 * operand2;
	if (sym == "/")
		return operand1 / operand2;
	if (sym == "%")
		return operand1 % operand2;
	if (sym == "+")
		return operand1 + operand2;
	if (sym == "-")
		return operand1 - operand2;
	if (sym == "<")
		return operand1 < operand2;
	if (sym == "<=")
		return operand1 <= operand2;
	if (sym == ">")
		return operand1 > operand2;
	if (sym == ">=")
		return operand1 >= operand2;
	if (sym == "!=")
		return operand1 != operand2;
	if (sym == "==")
		return operand1 == operand2;
	if (sym == "not")
			return 0; // operand1 not operand2 is false
	if (sym == "and")
		return operand1 && operand2;
	if (sym == "||")
		return operand1 || operand2;

	else
	{
		cout << "Error, invalid expression." << endl;
		return 0;
	}
		
}



LexicalAnalyzer:: tokenLineType expEvaluator::infixToPostfix(LexicalAnalyzer::tokenLineType inFix)
{
	int precedence;
	
	stack<pair<string, LexicalAnalyzer ::categoryType>> stackVect;

	vector<pair<string, LexicalAnalyzer:: categoryType>> postFix;

	for (auto i : inFix)
	{
		if ((i.second == LexicalAnalyzer::categoryType::NUMERIC_LITERAL))
		{
			postFix.push_back(i);
			continue;
		}
		
		else if (i.first == "(")
			stackVect.push(i);

		else if (i.first == ")")
		{
			while (!stackVect.empty() && stackVect.top().first != "(")
			{
				stackVect.pop();
			}
			stackVect.pop();
		}


		else if (isOperator(i))
		{
			precedence = assigningPrecedence(i.first);
			while (!stackVect.empty() && isOperator(stackVect.top()) &&  assigningPrecedence(stackVect.top().first) >= precedence)
			{
				postFix.push_back(stackVect.top());
					stackVect.pop();
			}
			stackVect.push(i);
		}



	}
	while (!stackVect.empty())
	{
		postFix.push_back(stackVect.top());
		stackVect.pop();
	}
	cout << "This is the PostFix Expression: ";

	for (auto i : postFix)
	{
		cout << i.first << " ";
	}
	cout << endl;

	return postFix;
}



int expEvaluator::PostfixEvaluator(LexicalAnalyzer::tokenLineType postFix)
{
	stack<int> stackVect;

	for (auto i : postFix)
	{
		if (i.second== LexicalAnalyzer::categoryType::NUMERIC_LITERAL)
		{
			stackVect.push(stoi(i.first));
		}

		else if (i.second == LexicalAnalyzer::categoryType::ASSIGNMENT_OP || i.second == LexicalAnalyzer::categoryType::ARITH_OP || i.second == LexicalAnalyzer::categoryType::LOGICAL_OP || i.second == LexicalAnalyzer::categoryType::RELATIONAL_OP)
		{
			int operand2 = stackVect.top();
			stackVect.pop();
			int operand1 = stackVect.top();
			stackVect.pop();

			int result= expEvaluator::operandEvaluation(operand1, operand2, i.first);

			stackVect.push(result);
		}
		
		else if (i.first == "++")
		{
			int operand = stackVect.top();
			stackVect.pop();
			operand++;
			stackVect.push(operand);

		}

		else if (i.first == "--")
		{
			int operand = stackVect.top();
			stackVect.pop();
			operand--;
			stackVect.push(operand);

		}
	}
	return 	stackVect.top();

}
	