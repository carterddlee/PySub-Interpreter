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
    bool isOperand(categoryType);

    int assigningPrecedence(string);

    typedef std::map<std::string, std::string> symbolTableType;
    symbolTableType symbolTable;
    void infixToPostfix(tokenLineType tokenLine);

};


#endif EXPEVALUATOR_H