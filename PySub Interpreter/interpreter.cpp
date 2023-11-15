#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include "interface.h"
#include "lexanalyzer.h"
#include "interpreter.h"

using namespace std;


void Interpreter::run(LexicalAnalyzer::tokenLineType line)
{
	vector<pair<string, LexicalAnalyzer::categoryType>> equation;
	expEvaluator printEvaluator;

	for (auto i = line.begin(); i !=line.end(); i++)
	{
		 if (i->second == LexicalAnalyzer::categoryType::COMMENT) //It's a comment
			 break;




		 if ((i->second == LexicalAnalyzer::categoryType::IDENTIFIER && i++->second == LexicalAnalyzer::categoryType::ASSIGNMENT_OP))//There is assigning
		 {
			 if (i->second == LexicalAnalyzer::categoryType::NUMERIC_LITERAL || i->second == LexicalAnalyzer::categoryType::LEFT_PAREN ||
				 (i->second == LexicalAnalyzer::categoryType::IDENTIFIER)) //If the conditions fulfill, it is an equation
			 {
				 for (i; i++ != line.end(); i++)
					 equation.push_back(i);

				 auto PostfixEquation = printEvaluator.infixToPostfix(equation, printEvaluator.symbolTable);

				 int number = printEvaluator.PostfixEvaluator(PostfixEquation);

				 printEvaluator.AddtoSymbolTable(printEvaluator.symbolTable, i = line.begin(), to_string(number))
			 }
		 }






		 if (i->second == LexicalAnalyzer::categoryType::KEYWORD && i->first == "print") //If it is a print statement
		 {
			 
			 for (i = i + 2; i++ != line.end(); i++)
			 {
				 if (i->second == LexicalAnalyzer::categoryType::STRING_LITERAL)
					 cout << i->first<< " ";

				 if (i->second == LexicalAnalyzer::categoryType::NUMERIC_LITERAL || i->second == LexicalAnalyzer::categoryType::LEFT_PAREN ||
					 (i->second == LexicalAnalyzer::categoryType::IDENTIFIER)) //If the conditions fulfill, it is an equation
				 {
					 for (i; i++ != line.end() || i++->second != LexicalAnalyzer::categoryType::COMMA; i++)
						 equation.push_back(i);
					 
					 auto PostfixEquation = printEvaluator.infixToPostfix(equation);

					 int number = printEvaluator.PostfixEvaluator(PostfixEquation);
					 cout << number << " ";
					 equation.clear();
				 }

			 }
			 
		 }



	


		if(i->second == LexicalAnalyzer::categoryType::IDENTIFIER || i+1->second )


	}
	cout << endl;
	return;
 }
