#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "interface.h"
#include "lexanalyzer.h"
#include "expevaluator.h"
#include "interpreter.h"


using namespace std;


void Interface::startInterface()
{
    cout << "PySUB Interpreter 1.0 on Windows (September 2023)" << endl;
    cout << "Enter program lines or read(<filename>.py) at command line interface" << endl;
    cout << "Type 'help' for more information or 'quit' to exit" << endl << endl;
    cout << ">>> ";

    LexicalAnalyzer lexAnalysis;

     expEvaluator expEvaluation;

     Interpreter pysubi;

     string input;
     string commandName = "";
     string argumentName = "";

     input.clear();
     commandName.clear();
     argumentName.clear();

    while (keepGoing)
    {
        string input;
        getline(cin, input);
        string commandName = "";
        string argumentName = "";

        bool addToCommand = true;
        bool isEquation = false;
        for (auto ch : input)
        {
            if (input[0]==isdigit(ch) || input[0] == '(')
            {
                isEquation = true;
                break;
            }
            if (ch == ')')
                break;
            else if (ch == '(')
                addToCommand = false;
            else if (addToCommand)
                commandName += ch;
            else
                argumentName += ch;
        }
        getInput(commandName, argumentName, lexAnalysis, isEquation, input, lexAnalysis, expEvaluation, pysubi);
    }
}

void Interface::getInput(string com, string arg, LexicalAnalyzer& token, bool isEquation, string input, LexicalAnalyzer lexAnalysis, expEvaluator& expEvaluation, Interpreter& pysubi)
{
    if (com == "quit")
        keepGoing = false;

    if (com == "help" && arg == "")
        helpUtility();

    if (com == "help" && arg != "")
    {
        cout << endl;
        cout << helpMap[arg] << endl;
        cout << ">>> ";
    }


    if (com == "read")
        read(arg, token);

    if (com == "show" && arg == "")
        show(programCode);

    if (com == "show" && arg == "variables")
    {
        cout << "Showing variables" << endl;
        for (auto i : expEvaluation.symbolTable)
            cout << "This value of " << i.second << "is " << i.first << endl;
        
    }


    if (com == "show" && arg == "tokens")
    {
        token.displayTokens();
        cout << "This is displaying the tokens"<< endl<<endl<<endl<< "<<< ";
    }


    if (com == "clear")
    {
        clear();    
       expEvaluation.clearSymbolTable();

    }
    
   if (com == "run")
    {
        for(auto i: lexAnalysis.tokenInfo)
        pysubi.run(i, expEvaluation);
        
        lexAnalysis.tokenInfo.clear();
        cout << endl << endl;
        cout << ">>>";
    }


    if (isEquation)
    {
        auto tokenLine=token.readTokenLine(input);
        auto PostfixEvaluator = expEvaluation.infixToPostfix(tokenLine);
        int result=expEvaluation.PostfixEvaluator(PostfixEvaluator);
        cout << "The answer to the equation is " << result << endl;
    }

}


void Interface::read(string argName, LexicalAnalyzer& token)
{
    clear();
    ifstream file;
    string line = "";
    file.open(argName);
    while (getline(file, line))
        programCode.push_back(line);
    token.readTokens(programCode);
}

void Interface::show(const vector<string> programCode)
{
    cout << endl;
    int i = 0;
    for (auto line : programCode)
        cout << "[" << i++ << "]" << line << endl;
    cout << endl << ">>> ";
}

void Interface::clear()
{
    programCode.clear();
    cout << endl << ">>> ";
}



void Interface::commands()
{
    cout << endl;
    cout << "Below is a list of commands. Enter any command at the prompt to get more help" << endl << endl;
    cout << "clear" << "   " << "help" << "  " << "quit" << endl;
    cout << "read" << "   " << "show" << endl << endl;
    cout << "NOTE: All commands can also be entered as functions:" << endl << endl;
    cout << "clear()" << "   " << "help()" << "  " << "quit()" << endl;
    cout << "read()" << "   " << "show()" << endl << endl;





}


void Interface::helpUtility()
{
    cout << endl;
    cout << "Welcome to the help utility!" << endl;
    cout << "* To exit and return to the interpreter, type 'exit" << endl;
    cout << "* To get a list of commands, type 'commands'" << endl << endl;
    bool inHelp = true;
    while (inHelp)
    {
        cout << "help> ";
        string command;
        cin >> command;
        if (command == "commands")
            commands();
        else if (command == "exit")
        {
            cout << endl << endl << endl;
            cout << ">>> ";
            inHelp = false;
        }

        else
            cout << helpMap[command] << endl;


    }
}



