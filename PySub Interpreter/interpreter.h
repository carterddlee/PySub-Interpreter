#pragma once
#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <vector>
#include <string>
#include <map>

using namespace std;


class Interpreter
{
	void run(LexicalAnalyzer::tokenLineType line);
};

#endif INTERPRETER_H