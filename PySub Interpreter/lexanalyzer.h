#ifndef LEXANALYZER_H
#define LEXANALYZER_H
#include <vector>
#include <string>
#include <map>

using namespace std;


class LexicalAnalyzer
{
public:
    enum class categoryType
    {
        KEYWORD,
        IDENTIFIER,
        STRING_LITERAL,
        NUMERIC_LITERAL,
        ASSIGNMENT_OP,
        ARITH_OP,
        LOGICAL_OP,
        RELATIONAL_OP,
        LEFT_PAREN,
        RIGHT_PAREN,
        COLON,
        COMMA,
        COMMENT,
        INDENT,
        UNKNOWN
    };


public:

    typedef vector<vector<pair<string, categoryType>>> tokenType;

    typedef vector<pair<string, categoryType>> tokenLineType;

    typedef pair<string, categoryType> pairType;

    void readTokens(vector<string> programCode);

    tokenLineType readTokenLine(string tokenLine);

    void displayTokens();



private:

    tokenType tokenInfo;
    tokenLineType tokenLine;
    pairType tokenPair;



};



#endif LEXANALYZER_H
