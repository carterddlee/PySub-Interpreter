#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H
#include <vector>
#include <string>
#include <map>
#include "lexanalyzer.h"


using namespace std;

class expEvaluator {
public:

private:
    bool isOperand(LexicalAnalyzer::pairType);

    int assigningPrecedence(string);

    typedef std::map<std::string, std::string> symbolTableType;
    symbolTableType symbolTable;
    LexicalAnalyzer :: tokenLineType infixToPostfix(LexicalAnalyzer::tokenLineType tokenLine);

};


#endif EXPEVALUATOR_H