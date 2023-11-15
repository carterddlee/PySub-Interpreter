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
    LexicalAnalyzer::tokenLineType infixToPostfix(LexicalAnalyzer::tokenLineType tokenLine, symbolTableType symbolTable);

    int PostfixEvaluator(LexicalAnalyzer::tokenLineType postFix);

    void clearSymbolTable()
    {
        return symbolTable.clear();
    }

    void AddtoSymbolTable(std::map<std::string, std::string>& symbolTableType, string key, string value)
    {
        symbolTableType[key] = value;
    }

    string findValueinTable(std::map<std::string, std::string>& symbolTableType, string key) 
    {
        auto it = symbolTableType.find(key);

        if (it != symbolTableType.end()) {
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

    bool IsaDigit(string value);


    int assigningPrecedence(string);


    int operandEvaluation(int operand1, int operand2, string sym);

    typedef std::map<std::string, std::string> symbolTableType;

    symbolTableType symbolTable;
};



#endif EXPEVALUATOR_H