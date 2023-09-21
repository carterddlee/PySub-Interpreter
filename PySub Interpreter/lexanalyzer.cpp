#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "interface.h"
#include "lexanalyzer.h"
using namespace std;



bool isKeyword(string word)
	{
		vector<string> keywords = {"print", "if", "elif", "else", "while", "int", "input"};
		for (auto keyword : keywords)
			if (word == keyword) return true;

		return false;
	}




bool isLogicalOperator(string word)
{
	vector<string> operators = { "and", "or", "not" };
	for (auto op : operators)
		if (word == op) return true;

	return false;
}



bool isSpace(char c)
{
	return c;
}




bool isRelationalOperator(char c1, char c2)
{
	/*vector<string> operators = { "<=", "==", ">=", "!=", "<", ">" };
	for (auto op:operators)

		if (c1 == op && c2 == '=') return true;



		 if (isrelationaloperator(c, programline[i + 1]))
		{

		}*/
	return true;
}


bool isUnderScore(char c)
{
	return c == '_';
}


bool isIdentifierCharacter(char c)
{
	return isalpha(c) || isdigit(c) || isUnderScore(c);
}







void LexicalAnalyzer::readTokens(vector<string> programCode)
{
	string tokenValue;
	tokenLineType tokenLine;
	categoryType tokenCategory;
	for (auto programLine : programCode)
		for (int i = 0; programCode[i] < programLine; i++)
		{

			char c = programLine[i];
			
			if(isalpha(c))
				while (isIdentifierCharacter(programLine[i + 1]))
				{
					i++;
					tokenValue += programLine[i];
				}

			categoryType tokenCategory;
			if (isKeyword(tokenValue)) tokenCategory = categoryType::KEYWORD;

			else if (isLogicalOperator(tokenValue))tokenCategory = categoryType::LOGICAL_OP;

			else tokenCategory = categoryType::IDENTIFIER;


			if (isdigit(c))
			{
				tokenValue = c;
				tokenCategory = categoryType::NUMERIC_LITERAL;
			}

			


			else if (isRelationalOperator(c, programLine[i + 1]))
			{


					}

			else if (c == '(') // Check if c is an opening parenthesis
			{
				tokenValue = c;
				tokenCategory = categoryType::LEFT_PAREN;
			}

			else if (c == ')') // Check if is a clsoing parenthesis
			{
				tokenValue = c;
				tokenCategory = categoryType::RIGHT_PAREN;
			}

			else if (c == ',') // Check if c is an comma
			{
				tokenValue = c;
				tokenCategory = categoryType::COMMA;
			}

			else if (c == ':') // Check if c is a colon parenthesis
			{
				tokenValue = c;
				tokenCategory = categoryType::COLON;
			}


			else if (c == '\"' || c== '\'')
			{
				tokenValue += programLine[i];

				tokenCategory = categoryType::STRING_LITERAL;

			}

			else if (				
				(c == '<' && programLine[i + 1] != programLine.size() && programLine[i + 1] == '=')
				|| (c == '>' && programLine[i + 1] != programLine.size() && programLine[i + 1] == '=')
				|| (c == '=' && programLine[i + 1] != programLine.size() && programLine[i + 1] == '=')
				|| (c == '!' && programLine[i + 1] != programLine.size() && programLine[i + 1] == '=')
				)
			{
				tokenValue += programLine[i];
				tokenValue += programLine[i+1];

				tokenCategory = categoryType::RELATIONAL_OP;
			}

			else if( (c == '<')|| (c == '>'))
			{
				tokenValue += programLine[i];

					tokenCategory = categoryType::RELATIONAL_OP;
			}
			
			cout << "tokenValue: " << tokenValue << endl;
			pairType tokenPair = make_pair(tokenValue, tokenCategory);
			tokenLine.push_back(tokenPair);
		}

	tokenInfo.push_back(tokenLine);

}





