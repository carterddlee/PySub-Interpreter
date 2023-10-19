#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "interface.h"
#include "lexanalyzer.h"
#include "expevaluator.h"
#include "stack"

using namespace std;

bool expEvaluator:: isOperand(LexicalAnalyzer::pairType i)
{
	return i.second == LexicalAnalyzer::categoryType::ASSIGNMENT_OP || i.second == LexicalAnalyzer::categoryType::ARITH_OP || i.second == LexicalAnalyzer::categoryType::LOGICAL_OP || i.second == LexicalAnalyzer::categoryType::RELATIONAL_OP;
}

bool expEvaluator:: IsaDigit(string value)
{
	return value == "0" || value == "1" || value == "3" || value == "4" || value == "5" || value == "6" || value == "7" || value == "8" || value == "9";
}

int expEvaluator::assigningPrecedence(string symbol)
{
	if (symbol == "*" || symbol == "/" || symbol == "%")
		return 5;
	if (symbol == "+" || symbol == "-")
		return 4;
	if (symbol == "<" || symbol == "<=" || symbol == ">" || symbol == ">=" || symbol == "!=" || symbol == "==")
		return 3;
	if (symbol == "not")
		return 2;
	if (symbol == "and")
		return 1;
	if (symbol == "or")
		return 0;
}


int expEvaluator::StringtoDigit(string element)
{
	if (element == "0")
		return 0;
	if(element=="1")
		return 1;
	if (element == "2")
		return 2;
	if (element == "3")
		return 3;
	if (element == "4")
		return 4;
	if (element == "5")
		return 5;
	if (element == "6")
		return 6;
	if (element == "7")
		return 7;
	if (element == "8")
		return 8;
	if (element == "9")
		return 9;

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
	if (sym == "and")
		return operand1 || operand2;
}



LexicalAnalyzer:: tokenLineType expEvaluator::infixToPostfix(LexicalAnalyzer::tokenLineType inFix)
{
	int precedence;
	
	stack<pair<string, LexicalAnalyzer ::categoryType>> stackVect;

	vector<pair<string, LexicalAnalyzer:: categoryType>> postFix;

	for (auto i : inFix)
	{
		if (IsaDigit(i.first))
		{
			postFix.push_back(i);
			continue;
		}
		
		else if (i.first == "(")
			stackVect.push(i);

		else if (i.first == ")")
		{
			while (stackVect.top().first != "(")
			{
				stackVect.pop();

			}
			stackVect.pop();
		}


		else if (isOperand(i))
		{
			precedence = assigningPrecedence(i.first);
			while (!stackVect.empty() && isOperand(stackVect.top()) ||  assigningPrecedence(stackVect.top().first) >= precedence)
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
		stackVect.top();
	}
	return postFix;
}



int expEvaluator::PostfixEvaluator(LexicalAnalyzer::tokenLineType postFix)
{
	stack<pair<string, LexicalAnalyzer::categoryType>> stackVect;

	for (auto i : postFix)
	{
		if (isOperand(i))
			stackVect.push(i);

		else if (i.second == LexicalAnalyzer::categoryType::ASSIGNMENT_OP || i.second == LexicalAnalyzer::categoryType::ARITH_OP || i.second == LexicalAnalyzer::categoryType::LOGICAL_OP || i.second == LexicalAnalyzer::categoryType::RELATIONAL_OP)
		{
			int operand2 = StringtoDigit(stackVect.top().first);
			stackVect.pop();
			int operand1 = StringtoDigit(stackVect.top().first);
			stackVect.pop();

			stackVect.push(expEvaluator::operandEvaluation(operand1, operand2, i.first));
			postFix.pop_back();

		}



	}
	return 0;
}
	