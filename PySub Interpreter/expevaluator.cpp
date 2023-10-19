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
			while (!stackVect.empty() && isOperand(stackVect.top()) || precedence > assigningPrecedence(stackVect.top().first))
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
	return postFix;
}