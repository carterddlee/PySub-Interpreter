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
	for (auto i = line.begin(); i !=line.end(); i++)
	{
		
		 if (i->second == LexicalAnalyzer::categoryType::COMMENT)
			 break;

		 if (i->second == LexicalAnalyzer::categoryType::KEYWORD && i->first == "print")
		 {
			 for (i = i + 2; i++ != line.end(); i++)
			 {
				 if (i->second == LexicalAnalyzer::categoryType::STRING_LITERAL)
					 cout << i->first;
				 if
			 }
		 }


		
		if(i->second == LexicalAnalyzer::categoryType::IDENTIFIER || i+1->second )


	}
	cout << endl;
	return;
 }
