#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H
#include <vector>
#include <string>
#include <map>
#include "lexanalyzer.h"


using namespace std;

class expEvaluator {

public:
    LexicalAnalyzer::tokenLineType infixToPostfix(LexicalAnalyzer::tokenLineType tokenLine);

    int PostfixEvaluator(LexicalAnalyzer::tokenLineType postFix);


private:
    bool isOperand(LexicalAnalyzer::pairType);

    bool IsaDigit(string value);


    int assigningPrecedence(string);

    int StringtoDigit(string element);


    int operandEvaluation(int operand1, int operand2, string sym);


    typedef std::map<std::string, std::string> symbolTableType;
    symbolTableType symbolTable;
};


#endif EXPEVALUATOR_H