#pragma once
#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <vector>
#include <string>
#include <map>

using namespace std;


class Interpreter
{
public:
	void run(LexicalAnalyzer::tokenLineType& line, expEvaluator& expEvaluation, bool& conditional, bool& ifStatementExecuted, bool& inWhile);
};

#endif INTERPRETER_H