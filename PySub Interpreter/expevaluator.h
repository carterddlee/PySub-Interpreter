#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H
#include <vector>
#include <string>
#include <map>
#include "lexanalyzer.h"


using namespace std;

class expEvaluator {
    friend class interface;
public:
    LexicalAnalyzer::tokenLineType infixToPostfix(LexicalAnalyzer::tokenLineType tokenLine);

private:
    bool isOperand(LexicalAnalyzer::pairType);

    bool IsaDigit(string value);


    int assigningPrecedence(string);

    typedef std::map<std::string, std::string> symbolTableType;
    symbolTableType symbolTable;
};


#endif EXPEVALUATOR_H