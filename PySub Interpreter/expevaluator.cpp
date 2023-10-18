#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "interface.h"
#include "lexanalyzer.h"
#include "expevaluator.h"

using namespace std;

bool expEvaluator:: isOperand(categoryType operand)
{
	
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

expEvaluator::infixToPostfix(tokenLineType tokenLine)
{
	int precedence;
	
	vector<pair<string, categoryType>> inFix;
	inFix = tokenLine;

	vector<pair<string, categoryType>> stackVect;

	vector<pair<string, categoryType>> postFix;

	for (auto i : inFix)
	{
		if (isdigit(i.first))
		{
			postFix.push_back(i.first);
			continue;
		}
		
		if (i.first == "(")
			stackVect.push_back(i.first);

		if (i.first == ")")
		{
			while (stackVect.first != "(")
			{
				for (auto it = stackVect.rbegin(); it != stackVect.rend(); ++it)
					stackVect.push_back(it.first);

			}
			stackVect.pop_back();
		}

				stackVect.push_back(i.first)

		if (i.second == ASSIGNMENT_OP || i.second == ARITH_OP || i.second == LOGICAL_OP || i.second == RELATIONAL_OP)
		{
			precedence = assigningPrecedence(i.first);
			if (!stackVect.empty() || isOperand(stackVect.back().second) || )
		}

	}

}