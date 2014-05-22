//============================================================================
// Name        : BST_analysis.cpp
// Author      : Fernando Gonzalez
// Date        : May 15, 2014
// Description : BST analysis for measuring time to execute various operations.
//               Data is saved to plot size of input vs time in Matlab.
//				 Part of HW2 for CS 130A at UCSB.
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "BST.h"
using namespace std;

int main() {
	// Save time results in a MATLAB friendly format for plotting
	ofstream f;

	// Increasing
	f.open("bst_increasing.txt");
	f << "inc_times = [" << endl;
	BST<int> *b1 = new BST<int>();
	for (int N = 1000; N <= 10000; N += 500) {
		clock_t start, end;
		float delta;
		start = clock();

		// Insert in increasing order
		for (int k = 1; k <= N; k++) {
			b1->insert(k);
		}

		// Access in increasing order
		for (int k = 1; k <= N; k++) {
			b1->access(k);
		}

		// Remove in increasing order
		for (int k = 1; k <= N; k++) {
			b1->remove(k);
		}

		end = clock();
		delta = (float) (end - start) / CLOCKS_PER_SEC;
		f << delta << ";" << endl;
	}
	f << "];";
	f.close();
	delete b1;

	// Increasing insert and access, Reverse delete
	f.open("bst_inc_reverse.txt");
	f << "inc_dec_times = [" << endl;
	BST<int> *b2 = new BST<int>();
	for (int N = 1000; N <= 10000; N += 500) {
		clock_t start, end;
		float delta;
		start = clock();

		// Insert in increasing order
		for (int k = 1; k <= N; k++) {
			b2->insert(k);
		}

		// Access in increasing order
		for (int k = 1; k <= N; k++) {
			b2->access(k);
		}

		// Remove in reverse order
		for (int k = N; k > 0; k--) {
			b2->remove(k);
		}

		end = clock();
		delta = (float) (end - start) / CLOCKS_PER_SEC;
		f << delta << ";" << endl;
	}
	f << "];";
	f.close();
	delete b2;

	// Random insert, access, and delete
	f.open("bst_random.txt");
	f << "rand_times = [" << endl;
	BST<int> *b3 = new BST<int>();
	for (int N = 1000; N <= 10000; N += 500) {

		vector<int> nums_in, nums_acc, nums_rem;
		vector<int>::iterator it;
		// Populate vector with numbers in order
		for (int i = 1; i <= N; i++) {
			nums_in.push_back(i);
		}

		// Make 2 more copies
		nums_rem = nums_acc = nums_in;

		// Shuffle vectors so that order is random
		// We can iterate through in order and elements will be random!
		random_shuffle(nums_in.begin(), nums_in.end());
		random_shuffle(nums_acc.begin(), nums_acc.end());
		random_shuffle(nums_rem.begin(), nums_rem.end());

		clock_t start, end;
		float delta;
		start = clock();

		// Insert in random order
		for (it = nums_in.begin(); it != nums_in.end(); it++) {
			b3->insert(*it);
		}

		// Access in random order
		for (it = nums_acc.begin(); it != nums_acc.end(); it++) {
			b3->access(*it);
		}

		// Remove in random order
		for (it = nums_rem.begin(); it != nums_rem.end(); it++) {
			b3->remove(*it);
		}

		end = clock();
		delta = (float) (end - start) / CLOCKS_PER_SEC;
		f << delta << ";" << endl;
	}
	f << "];";
	f.close();
	delete b3;

	return 0;
}

