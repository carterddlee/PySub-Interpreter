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

    LexicalAnalyzer token;

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
            if (isdigit(input[0]) || input[0] == '(' || input[1]== '=')
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
        getInput(commandName, argumentName, token, isEquation, input, expEvaluation, pysubi);
    }
}

void Interface::getInput(string com, string arg, LexicalAnalyzer& token, bool isEquation, string input, expEvaluator& expEvaluation, Interpreter& pysubi)
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
    {
        token.tokenInfo.clear();
        read(arg, token);
    }

    if (com == "show" && arg == "")
        show(programCode);

    if (com == "show" && arg == "variables")
    {
        cout << endl << "Showing variables:" << endl;
        for (auto i : expEvaluation.symbolTable)
            cout << "The value of " << i.first << " is " << i.second << endl;

        cout << endl << ">>>";
        expEvaluation.symbolTable.clear();
    }


    if (com == "show" && arg == "tokens")
    {
        token.displayTokens();
        cout << "This is displaying the tokens" << endl << endl << endl << "<<< ";
    }


    if (com == "clear")
    {
        clear();
        expEvaluation.clearSymbolTable();

    }

    if (com == "run")
    {
        bool inWhile;
        bool conditional = false;

        vector<pair<string, LexicalAnalyzer::categoryType>> whileCondition;

        for(int i=0; i< token.tokenInfo.size(); i++)
        {
            if (conditional == true && token.tokenInfo[i][0].second == LexicalAnalyzer::categoryType::INDENT)
            {
                pysubi.run(token.tokenInfo[i], expEvaluation, conditional, inWhile);
                continue;

            }

            if (conditional == false && token.tokenInfo[i][0].second == LexicalAnalyzer::categoryType::INDENT)
                continue;


            //if (i[0][0].second == LexicalAnalyzer::categoryType::INDENT && i[0].second == i + 1[0].second)
            //{
            //    if (conditional == false && inWhile == false)
            //        continue;

            //    if (conditional == true)
            //        pysubi.run(i, expEvaluation, conditional, inWhile);

            //    if (inWhile == true)
            //    {
            //        for (auto i : token.tokenInfo)
            //            while (i[0].second == LexicalAnalyzer::categoryType::INDENT)
            //                pysubi.run(i, expEvaluation, conditional, inWhile);
            //    
            //    }
            //}
            pysubi.run(token.tokenInfo[i], expEvaluation, conditional, inWhile);

        }

        /*    if (conditional == false && i[0].second == LexicalAnalyzer::categoryType::INDENT)
                continue;

            if (conditional == true && i[0].second == LexicalAnalyzer::categoryType::INDENT)
            {
                pysubi.run(i, expEvaluation, conditional, whileCondition);
            }

            if (inWhile == false && i[0].second == LexicalAnalyzer::categoryType::INDENT)
                continue;

            else if (inWhile == true)
            {
                pysubi.run(i, expEvaluation, conditional);

            }*/

        
        cout << endl << endl;
        cout << ">>>";

    }

    if (isEquation)
    {
        auto tokenLine = token.readTokenLine(input);
        auto PostfixEvaluator = expEvaluation.infixToPostfix(tokenLine);
        int result = expEvaluation.PostfixEvaluator(PostfixEvaluator);
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
//
//int Interface::ctoi(char value)
//{
//    if (value == '0')
//        return 0;
//    else if (value == '1')
//        return 1;
//    else if (value == '2')
//        return 2;
//    else if (value == '3')
//        return 3;
//    else if (value == '4')
//        return 4;
//    else if (value == '5')
//        return 5;
//    else if (value == '6')
//        return 6;
//    else if (value == '7')
//        return 7;
//    else if (value == '8')
//        return 8;
//    else if (value == '9')
//        return 9;
//}
//
