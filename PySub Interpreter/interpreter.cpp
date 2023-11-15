#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "interface.h"
#include "lexanalyzer.h"
#include "interpreter.h"

using namespace std;


void Interpreter::run(LexicalAnalyzer::tokenLineType line)
{
	bool evenBraces;
	for (auto i = line.begin(); i !=line.end(); i++)
	{
		
		 if (i->second == LexicalAnalyzer::categoryType::COMMENT)
			 break;

		 if (i->second == LexicalAnalyzer::categoryType::KEYWORD && i->first == "print")
		 {
			 while (evenBraces)
			 {
				 for (i = i + 2; i++ != line.end(); i++)
				 {
					 if (i->second == LexicalAnalyzer::categoryType::STRING_LITERAL)
						 cout << i->first;
					 if(i->second== LexicalAnalyzer::categoryType::NUMERIC_LITERAL || i->second == LexicalAnalyzer::categoryType::LEFT_PAREN|| i->second == LexicalAnalyzer::categoryType::IDENTIFIER)
						 LexicalAnalyzer:: expEvaluator::infixToPostfix
				 }
			 }
		 }


		
		if(i->second == LexicalAnalyzer::categoryType::IDENTIFIER || i+1->second )


	}
	cout << endl;
	return;
 }
