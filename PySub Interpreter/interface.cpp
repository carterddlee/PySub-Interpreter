#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "interface.h"
#include "lexanalyzer.h"
using namespace std;


void Interface::startInterface()
{
    cout << "PySUB Interpreter 1.0 on Windows (September 2023)" << endl;
    cout << "Enter program lines or read(<filename>.py) at command line interface" << endl;
    cout << "Type 'help' for more information or 'quit' to exit" << endl << endl;
    cout << ">>> ";

    LexicalAnalyzer lexAnalysis;

    while (keepGoing)
    {
        string input;
        getline(cin, input);
        string commandName = "";
        string argumentName = "";

        bool addToCommand = true;
        for (auto ch : input)
        {
            if (ch == ')')
                break;
            else if (ch == '(')
                addToCommand = false;
            else if (addToCommand)
                commandName += ch;
            else
                argumentName += ch;
        }
        getInput(commandName, argumentName, lexAnalysis);
    }
}

void Interface::getInput(string com, string arg, LexicalAnalyzer& token)
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

    if (com == "show" && arg != "")
    {
        token.displayTokens();
        cout << "This is displaying the tokens";
    }


    if (com == "clear")
        clear();


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











