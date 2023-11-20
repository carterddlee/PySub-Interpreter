#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "interface.h"
#include "lexanalyzer.h"
using namespace std;

//Working version
void LexicalAnalyzer::displayTokens()
{
    int lineCount = 0; // Initialize line count

    for (const auto& tokenLine : tokenInfo)
    {
        int tokensInLine = 0; // Initialize token count for the current line
        cout << "Line[" << lineCount << "]" << endl;

        for (const auto& tokenPair : tokenLine)
        {
            cout << "Token " << ++tokensInLine << ": ";

            cout << "Token Value: " << tokenPair.first << " Token Category : ";

            switch (tokenPair.second)
            {
            case categoryType::KEYWORD:
                cout << "KEYWORD";
                break;
            case categoryType::IDENTIFIER:
                cout << "IDENTIFIER";
                break;
            case categoryType::STRING_LITERAL:
                cout << "STRING_LITERAL";
                break;
            case categoryType::NUMERIC_LITERAL:
                cout << "NUMERIC_LITERAL";
                break;
            case categoryType::ASSIGNMENT_OP:
                cout << "ASSIGNMENT_OP";
                break;
            case categoryType::ARITH_OP:
                cout << "ARITH_OP";
                break;
            case categoryType::LOGICAL_OP:
                cout << "LOGICAL_OP";
                break;
            case categoryType::RELATIONAL_OP:
                cout << "RELATIONAL_OP";
                break;
            case categoryType::LEFT_PAREN:
                cout << "LEFT_PAREN";
                break;
            case categoryType::RIGHT_PAREN:
                cout << "RIGHT_PAREN";
                break;
            case categoryType::COLON:
                cout << "COLON";
                break;
            case categoryType::COMMA:
                cout << "COMMA";
                break;
            case categoryType::COMMENT:
                cout << "COMMENT";
                break;
            case categoryType::INDENT:
                cout << "INDENT";
                break;
            case categoryType::UNKNOWN:
                cout << "UNKNOWN";
                break;
            default:
                cout << "UNKNOWN";
                break;
            }

            cout << endl;
        }
        cout << "--------------------------------------" << endl;
        lineCount++; // Move to the next line
    }
}

bool isKeyword(string word)
{
    vector<string> keywords = { "print", "if", "elif", "else", "while", "int", "input" };
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






bool isUnderScore(char c)
{
    return c == '_';
}


bool isIdentifierCharacter(char c)
{
    return isalpha(c) || isdigit(c) || isUnderScore(c);
}



LexicalAnalyzer::tokenLineType LexicalAnalyzer::readTokenLine(string programLine)
{

    vector<pairType> tokenLine; // Store tokens for each line
    string tokenValue = "";
    categoryType tokenCategory = categoryType::UNKNOWN;

    for (int i = 0; i < programLine.length(); i++)
    {
        char c = programLine[i];

        if (isdigit(c))
        {
            tokenValue = c; // Append digits to the existing tokenValue
            tokenCategory = categoryType::NUMERIC_LITERAL;
            while (isdigit(programLine[i + 1]))
            {
                c = programLine[++i];

                tokenValue += c; // Append digits to the existing tokenValue
            }
        }
        else if (isalpha(c))
        {
            while (i < programLine.length() && isIdentifierCharacter(programLine[i]))
            {
                tokenValue += programLine[i];
                i++;
            }
            i--; // Move back one character to account for the extra increment
            // Check if tokenValue is a keyword after collecting the identifier.
            if (isKeyword(tokenValue))
                tokenCategory = categoryType::KEYWORD;
            else if (isLogicalOperator(tokenValue))
                tokenCategory = categoryType::LOGICAL_OP;
            else
                tokenCategory = categoryType::IDENTIFIER;
        }
        else if (c == '\"' || c == '\'')
        {
            tokenValue += c;
            while (i + 1 < programLine.length() && programLine[i + 1] != c)
            {
                i++;
                tokenValue += programLine[i];
            }
            if (i + 1 < programLine.length() && programLine[i + 1] == c)
            {
                tokenValue += c;
                tokenCategory = categoryType::STRING_LITERAL;
                i++; // Move to the closing quote
            }
            else
            {
                // Handle unterminated string literal error.
                // Set tokenCategory to an appropriate error category.
            }
        }
        else if (c == '(')
        {
            tokenValue = c;
            tokenCategory = categoryType::LEFT_PAREN;
        }
        else if (c == ')')
        {
            tokenValue = c;
            tokenCategory = categoryType::RIGHT_PAREN;
        }
        else if (c == ',')
        {
            tokenValue = c;
            tokenCategory = categoryType::COMMA;
        }
        else if (c == ':')
        {
            tokenValue = c;
            tokenCategory = categoryType::COLON;
        }
        else if (c == '#')
        {
            while (i < programLine.length())
            {
                i++;
                tokenValue += programLine[i];
            }
            tokenCategory = categoryType::COMMENT;
        }
        else if (isspace(c))
        {
            if (tokenLine.size() == 0)
            {
                c = '\0';
                tokenValue = c; // Store one space character
                tokenCategory = categoryType::INDENT;
            }
            else
                continue;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '&')
        {
            tokenValue = c;
            tokenCategory = categoryType::ARITH_OP;
        }
        else if ((c == '<' && i + 1 < programLine.length() && programLine[i + 1] == '=')
            || (c == '>' && i + 1 < programLine.length() && programLine[i + 1] == '=')
            || (c == '=' && i + 1 < programLine.length() && programLine[i + 1] == '=')
            || (c == '!' && i + 1 < programLine.length() && programLine[i + 1] == '='))
        {
            tokenValue += c;
            tokenValue += programLine[i + 1];
            tokenCategory = categoryType::RELATIONAL_OP;
            i++; // Move to the second character of the operator
        }
        else if (c == '<' || c == '>')
        {
            tokenValue += c;
            tokenCategory = categoryType::RELATIONAL_OP;
        }
        else if (c == '=')
        {
            tokenValue = c;
            tokenCategory = categoryType::ASSIGNMENT_OP;
        }
        else
        {
            tokenValue = c;
            tokenCategory = categoryType::UNKNOWN;
        }

        pairType tokenPair = make_pair(tokenValue, tokenCategory);
        tokenLine.push_back(tokenPair);
        tokenValue = ""; // Reset tokenValue for the next token
    }
    return tokenLine;
}




void LexicalAnalyzer::readTokens(vector<string> programCode)
{
    for (auto programLine : programCode)
    {
        auto tokenLine = readTokenLine(programLine);

        tokenInfo.push_back(tokenLine);
    }
}
