//============================================================================
// Name        : AVL_driver.cpp
// Author      : Fernando Gonzalez
// Date        : May 20, 2014
// Description : Driver program for AVL Tree implementation.
//               Part of HW2 for CS 130A at UCSB.
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include "AVL.h"
using namespace std;

int main() {

	size_t npos = string::npos;
	AVL<int> *avl = new AVL<int>();

	while (!cin.eof()) {
		string command;
		getline(cin, command);

		if (command.find("insert") != npos) {
			int pos, param;
			string raw_param;
			pos = command.find(" ");
			raw_param = command.substr(pos + 1, command.length());
			stringstream(raw_param) >> param;
			avl->insert(param);
		}

		else if (command.find("access") != npos) {
			int pos, param;
			string raw_param;
			pos = command.find(" ");
			raw_param = command.substr(pos + 1, command.length());
			stringstream(raw_param) >> param;
			avl->access(param);
		}

		else if (command.find("delete") != npos) {
			int pos, param;
			string raw_param;
			pos = command.find(" ");
			raw_param = command.substr(pos + 1, command.length());
			stringstream(raw_param) >> param;
			avl->remove(param);
		}

		else if (command.find("print") != npos) {
			int pos;
			string param;
			pos = command.find(" ");
			param = command.substr(pos + 1, command.length());
			if (param.compare("bfs") == 0) {
				avl->print_bfs();
			} else {
				avl->print();
			}
		}

		else if (cin.eof()) {
			break;
		}

		else {
			cout << "Invalid input. Try again." << endl;
		}
	}

	delete avl;
	return 0;
}

