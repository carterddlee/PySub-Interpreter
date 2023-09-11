#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "interface.h"
using namespace std;


void Interface::startInterface()
{
    cout << "PySUB Interpreter 1.0 on Windows (September 2023)" << endl;
    cout << "Enter program lines or read(<filename>.py) at command line interface" << endl;
    cout << "Type 'help' for more information or 'quit' to exit" << endl << endl;
    cout << ">>> ";

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
        getInput(commandName, argumentName);
    }
}

void Interface::getInput(string com, string arg)
{
    if (com == "quit")
        keepGoing = false;

    if (com == "help" && arg == "")
        helpUtility();

    if (com == "help" && arg != "")
        immediateHelp(arg);

    if (com == "read")
        read(arg);

    if (com == "show")
        show(programCode);

    if (com == "clear")
        clear();


}


void Interface::read(string argName)
{
    ifstream file;
    string line = "";
    file.open(argName);
    while (getline(file, line))
    {
        programCode.push_back(line);
    }
    cout << endl << ">>> ";
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
    cout << endl << ">>>";
}



void Interface::immediateHelp(string key)
{
    map<string, string> help;
    help["clear"] = "\nClears out or deletes any lines that are stored in the program data structure.\n";
    help["help"] = "\nWhen no parameter is given, then help will enter the help utility.\n";
    help["read"] = "\nReads a Python file.\n";
    help["quit"] = "\nExits the interpreter interface\n";
    help["show"] = "\nShows the lines of the program that are stored in program data structure. Includes line number when displaying each line of code in the program\n";

    cout << help[key] << endl;
    cout << ">>> ";

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
    map<string, string> helpMap;
    helpMap["clear"] = "\nClears out or deletes any lines that are stored in the program data structure\n";
    helpMap["help"] = "\nWhen no parameter is given, then “help” will enter the help utility.\n";
    helpMap["read"] = "\nReads a Python file.\n";
    helpMap["quit"] = "\nExits the interpreter interface\n";
    helpMap["show"] = "\nShows the lines of the program that are stored in program data structure. Include line number when displaying each line of code in the program.\n";
    helpMap["clear()"] = "\nClears out or deletes any lines that are stored in the program data structure\n";
    helpMap["help()"] = "\nWhen no parameter is given, then “help” will enter the help utility. \n";
    helpMap["read()"] = "\nReads a Python file.\n";
    helpMap["quit()"] = "\nExits the interpreter interface\n";
    helpMap["show()"] = "\nShows the lines of the program that are stored in program data structure. Include line number when displaying each line of code in the program\n";
    cout << endl;
    cout << "Welcome to the help utility!" << endl;
    cout << "* To exit and return to the interpreter, type 'exit" << endl;
    cout << "* To get a list of commands, type 'commands'" << endl << endl;
    bool inHelp = true;
    while (inHelp)
    {
        cout << ">>> ";
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







