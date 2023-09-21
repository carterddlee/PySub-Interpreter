#ifndef LEXANALYZER_H
#define LEXANALYZER_H
#include <vector>
#include <string>
#include <map>
//Test
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

private:


    typedef vector<vector<pair<string, categoryType>>> tokenType;

    typedef vector<pair<string, categoryType>> tokenLineType;

    typedef pair<string, categoryType> pairType;

    tokenType tokenInfo;


public:
    void readTokens(vector<string> programCode);




};

#endif LEXANALYZER_H