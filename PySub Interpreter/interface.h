#ifndef INTERFACE_H
#define INTERFACE_H
#include <vector>
#include <string>
//Test
using namespace std;

class Interface {
public:
	void startInterface();

private:

	typedef vector<string> programType;

	programType programCode;

	void getInput(string command, string argument);

	void read(string argument);

	void show(const vector <string> v);

	void clear();


	void helpUtility();

	void commands();

	void immediateHelp(string argument);

	bool keepGoing = true;

};







#endif INTERFACE_H

