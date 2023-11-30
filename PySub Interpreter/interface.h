#ifndef INTERFACE_H
#define INTERFACE_H
#include <vector>
#include <string>
#include <map>
#include "lexanalyzer.h"
#include "expevaluator.h"
#include "interpreter.h"



using namespace std;

class Interface {
public:
	Interface()
	{
		helpMap["clear"] = "\nClears out or deletes any lines that are stored in the program data structure\n";
		helpMap["help"] = "\nWhen no parameter is given, then the help command will enter the help utility.\n";
		helpMap["read"] = "\nReads a Python file.\n";
		helpMap["quit"] = "\nExits the interpreter interface\n";
		helpMap["show"] = "\nShows the lines of the program that are stored in program data structure. Includes line number when displaying each line of code in the program.\n";
		helpMap["clear()"] = "\nClears out or deletes any lines that are stored in the program data structure\n";
		helpMap["help()"] = "\nWhen no parameter is given, then the help command will enter the help utility. \n";
		helpMap["read()"] = "\nReads a Python file.\n";
		helpMap["quit()"] = "\nExits the interpreter interface\n";
		helpMap["show()"] = "\nShows the lines of the program that are stored in program data structure. Include line number when displaying each line of code in the program\n";
	}

	void startInterface();

	int ctoi(char value);

	void scriptRun(LexicalAnalyzer::tokenType& tokenInfo, expEvaluator& expEvaluation, Interpreter& pysubi);
	void interactiveRun(LexicalAnalyzer::tokenType& tokenInfo, expEvaluator& expEvaluation, Interpreter& pysubi);


private:
	map<string, string> helpMap;


	typedef vector<string> programType;

	programType programCode;

	void getInput(string com, string arg, LexicalAnalyzer& token, bool isEquation, string input, expEvaluator& expEvaluation, Interpreter& pysubi);

	void read(string argument, LexicalAnalyzer& token);

	void show(const vector <string> v);

	void clear();

	void helpUtility();

	void commands();

	void immediateHelp(string argument);

	bool keepGoing = true;

};




#endif INTERFACE_H





