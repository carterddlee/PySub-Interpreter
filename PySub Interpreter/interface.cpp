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
        bool skipElse = false;
        bool inWhile = false;
        bool conditional = false;
        bool ifStatementExecuted = false;

        for(int i=0; i< token.tokenInfo.size(); i++)
        {
            if (token.tokenInfo[i].size() == 0)
                continue;
            if (conditional == true && token.tokenInfo[i][0].second == LexicalAnalyzer::categoryType::INDENT) //If the if statement is true
            {
                pysubi.run(token.tokenInfo[i], expEvaluation, conditional, skipElse, inWhile);
                skipElse = true;
                continue;
            }

            if (conditional == false && inWhile == false && token.tokenInfo[i][0].second == LexicalAnalyzer::categoryType::INDENT)//If if statement is false
            {
                //skipElse = false;
                continue;
            }


            if (skipElse == true && token.tokenInfo[i][0].first == "else")//Encounter an else statement and the if statement was true
            {
               int j = 1;
                while (i+j < token.tokenInfo.size()&& token.tokenInfo[i + j].size() != 0 &&token.tokenInfo[i + j][0].second == LexicalAnalyzer::categoryType::INDENT)
                {
                    j++;
                }
                i=i+j;
                skipElse = false;
            }
            if (skipElse == false && i < token.tokenInfo.size() && token.tokenInfo[i].size() != 0 && token.tokenInfo[i][0].first == "else")//Encounter an else statement and the if statement was false
            {
                int j = 1;
                while (i + j < token.tokenInfo.size() && token.tokenInfo[i + j][0].second == LexicalAnalyzer::categoryType::INDENT)
                {
                    pysubi.run(token.tokenInfo[i + j], expEvaluation, conditional, skipElse, inWhile);
                    j++;
                }
                i=i + j;
            }

            if (inWhile==true)
          {
              int j = 0;
              while (inWhile)
              {
                  j = 0;
                  while (i + j < token.tokenInfo.size() && token.tokenInfo[i+j].size() != 0 && token.tokenInfo[i + j][0].second == LexicalAnalyzer::categoryType::INDENT)
                  {

                       pysubi.run(token.tokenInfo[i + j], expEvaluation, conditional, skipElse, inWhile);
                      j++;
                  }
                  inWhile = false;
                  pysubi.run(token.tokenInfo[i-1], expEvaluation, conditional, skipElse, inWhile);
              }
              i = i + j;
          }

            if(i < token.tokenInfo.size())
            pysubi.run(token.tokenInfo[i], expEvaluation, conditional, skipElse, inWhile);

        }

        

        
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

void Interface:: interactive(LexicalAnalyzer::tokenType& tokenInfo, expEvaluator& expEvaluation, Interpreter& pysubi)
{
    bool skipElse = false;
    bool inWhile;
    bool conditional = false;
    bool ifStatementExecuted = false;

    for (int i = 0; i < tokenInfo.size(); i++)
    {
        if (conditional == true && tokenInfo[i][0].second == LexicalAnalyzer::categoryType::INDENT) //If the if statement is true
        {
            pysubi.run(tokenInfo[i], expEvaluation, conditional, skipElse, inWhile);
            skipElse = true;
            continue;
        }

        if (conditional == false && tokenInfo[i][0].second == LexicalAnalyzer::categoryType::INDENT)//If if statement is false
        {
            //skipElse = false;
            continue;
        }


        if (skipElse == true && tokenInfo[i][0].first == "else")//Encounter an else statement and the if statement was true
        {
            int j = 1;
            while (i + j < tokenInfo.size() && tokenInfo[i + j][0].second == LexicalAnalyzer::categoryType::INDENT)
            {
                j++;
                continue;
            }
            i = i + j;
            skipElse = false;
        }
        if (skipElse == false && tokenInfo[i][0].first == "else")//Encounter an else statement and the if statement was false
        {
            int j = 1;
            while (i + j < tokenInfo.size() && tokenInfo[i + j][0].second == LexicalAnalyzer::categoryType::INDENT)
            {
                pysubi.run(tokenInfo[i + j], expEvaluation, conditional, skipElse, inWhile);
                j++;
            }
            i = i + j;
        }


        pysubi.run(tokenInfo[i], expEvaluation, conditional, skipElse, inWhile);

    }

    cout << endl << endl;
    cout << ">>>";
}


/*if (inWhile==true)
          {
              int j = 1;
              while (inWhile)
              {
                  while (i + j < token.tokenInfo.size() && token.tokenInfo[i + j][0].second == LexicalAnalyzer::categoryType::INDENT)
                  {
                      pysubi.run(token.tokenInfo[i + j], expEvaluation, conditional, inWhile);
                      j++;
                  }
                  pysubi.run(token.tokenInfo[i], expEvaluation, conditional, inWhile);
              }
              i = i + j;
          }
          pysubi.run(token.tokenInfo[i], expEvaluation, conditional, inWhile);*/
