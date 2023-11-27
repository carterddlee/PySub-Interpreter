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
    typedef std::map<std::string, std::string> symbolTableType;

    symbolTableType symbolTable;

    LexicalAnalyzer::tokenLineType infixToPostfix(LexicalAnalyzer::tokenLineType tokenLine);

    int PostfixEvaluator(LexicalAnalyzer::tokenLineType postFix);

    void clearSymbolTable()
    {
        return symbolTable.clear();
    }

    void AddtoSymbolTable(string key, string value)
    {
        symbolTable[key] = value;
    }

    string findValueinTable(string key)
    {
        auto it = symbolTable.find(key);

        if (it != symbolTable.end()) {
            // Key found in the map, return the associated value
            return it->second;
        }
        else {
            // Key not found in the map, return a default value or an error message
            return "Key not found";
        }
    }

private:
    bool isOperator(LexicalAnalyzer::pairType);


    int assigningPrecedence(string);


    int operandEvaluation(int operand1, int operand2, string sym);


};



#endif EXPEVALUATOR_H