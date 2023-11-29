#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include "interface.h"
#include "lexanalyzer.h"
#include "interpreter.h"

using namespace std;


void Interpreter::run(LexicalAnalyzer::tokenLineType& line, expEvaluator& printEvaluator, bool& conditional, bool& inWhile)
{
	vector<pair<string, LexicalAnalyzer::categoryType>> equation;

	for (auto i = line.begin(); i != line.end(); i++)
	{
		if (i->second == LexicalAnalyzer::categoryType::COMMENT) //It's a comment
			break;


		if (i->second == LexicalAnalyzer::categoryType::IDENTIFIER && i + 1 != line.end() && (i + 1)->second == LexicalAnalyzer::categoryType::ASSIGNMENT_OP)//There is assigning for an integer
		{
			if ((i + 2)->second == LexicalAnalyzer::categoryType::NUMERIC_LITERAL || (i + 2)->second == LexicalAnalyzer::categoryType::LEFT_PAREN ||
				(i + 2)->second == LexicalAnalyzer::categoryType::IDENTIFIER) //If the conditions fullfill, it is an equation
			{
				/* cout << " In the assigning integer function" << endl;*/
				for (i = i + 2; i != line.end(); i++)
					equation.push_back(*i);

				auto PostfixEquation = printEvaluator.infixToPostfix(equation);

				int number = printEvaluator.PostfixEvaluator(PostfixEquation);

				printEvaluator.AddtoSymbolTable(line.begin()->first, to_string(number));
				break;
			}
		}


		if (i->second == LexicalAnalyzer::categoryType::IDENTIFIER && i + 1 != line.end() && (i + 1)->second == LexicalAnalyzer::categoryType::ASSIGNMENT_OP
			&& (i + 2)->second == LexicalAnalyzer::categoryType::KEYWORD && (i + 2)->first == "int" && (i + 3)->second == LexicalAnalyzer::categoryType::LEFT_PAREN &&
			(i + 4)->second == LexicalAnalyzer::categoryType::KEYWORD && (i + 4)->first == "input" && (i + 5)->second == LexicalAnalyzer::categoryType::LEFT_PAREN)
			//Checking to see if it is going to take input
		{
			if ((i + 6)->second == LexicalAnalyzer::categoryType::STRING_LITERAL)
			{
				vector<char> parsedString((i + 6)->first.begin(), (i + 6)->first.end());

				for (int j = 1; j < parsedString.size() - 1; j++)
					cout << parsedString[j];

				cout << " ";
				parsedString.clear();
			}

			int inputNumber;
			cin >> inputNumber;
			printEvaluator.AddtoSymbolTable(line.begin()->first, to_string(inputNumber));

		}



		else if (i->second == LexicalAnalyzer::categoryType::KEYWORD && i->first == "print") //If there is a print statement
		{

			for (i = i + 2; i + 1 != line.end(); i++) //Here
			{
				if (i->second == LexicalAnalyzer::categoryType::STRING_LITERAL)
				{
					vector<char> parsedString(i->first.begin(), i->first.end());

					for (int j = 1; j < parsedString.size() - 1; j++)
						cout << parsedString[j];

					cout << " ";
					parsedString.clear();
				}

				else if (i->second == LexicalAnalyzer::categoryType::NUMERIC_LITERAL || i->second == LexicalAnalyzer::categoryType::LEFT_PAREN ||
					(i->second == LexicalAnalyzer::categoryType::IDENTIFIER)) //If the conditions fulfill, it is an equation
				{
					for (i; i + 1 != line.end() && (i)->second != LexicalAnalyzer::categoryType::COMMA; i++)
						equation.push_back(*i);

					if (equation.size() == 1)
					{
						if (equation[0].second == LexicalAnalyzer::categoryType::IDENTIFIER)
						{
							string num = printEvaluator.findValueinTable(equation[0].first);
							cout << num;
							break;
						}
						else
						{
							cout << equation[0].first;
							break;
						}
					}
					auto PostfixEquation = printEvaluator.infixToPostfix(equation);

					int number = printEvaluator.PostfixEvaluator(PostfixEquation);
					cout << number << " ";
					equation.clear();

					if (i + 1 == line.end())
						break;
				}

			}
			cout << endl;

		}

		else if (i->second == LexicalAnalyzer::categoryType::KEYWORD && i->first == "if"|| i->first == "elif")
		{
			for (i = i + 1; i->first != ":"; i++)
				equation.push_back(*i);

			auto PostfixEquation = printEvaluator.infixToPostfix(equation);

			conditional = printEvaluator.PostfixEvaluator(PostfixEquation);
			break;
		}

		//else if (i->second == LexicalAnalyzer::categoryType::KEYWORD && i->first == "else")
		//{
		//	break;
		//}

		/*else if (i->second == LexicalAnalyzer::categoryType::KEYWORD && i->first == "while")
		{
			for (i = i + 1; i->first != ":"; i++)
				equation.push_back(*i);

			auto PostfixEquation = printEvaluator.infixToPostfix(equation);

			inWhile = printEvaluator.PostfixEvaluator(PostfixEquation);
			equation.clear();
			break;
		}*/

	}
	equation.clear();

	return;
}
