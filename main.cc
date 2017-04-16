#include <iostream>
#include <vector>
#include "bloom.h"
#include "sha256.h"

using namespace std;

int main () {

	struct bloom bloom;
	bool finished = false;

	while(!finished){
		int entries, size_bloom, length;
		double error;
		cout << "-------------------------------------------" << endl;
		cout << "Number of entries: ";
		cin >> entries;
		cout << "Length of entries: ";
		cin >> length;
		cout << "Press 1 to create a Bloom filter by defining the size" << endl;
		cout << "Press 2 to create a Bloom filter by defining the error" << endl;

		bool done = false;
		while(!done){
			int choice;
			cout << "	Command: ";
			cin >> choice;
			if (choice == 1){
				cout << "Size of the Bloom Filter: ";
				done = true;
				cin >> size_bloom;
				error = -1;
			}
			else if (choice == 2){
				cout << "Error of the Bloom Filter (double from 0 to 1): ";
				double aux;
				cin >> aux;
				if (0 < aux and aux < 1) {done = true; error = aux;}
				else cout << "Not a valid error, please try again" << endl;
			}
			else cout << "Not a vaild command, please type 1 or 2" << endl;
		}

		if (error == -1)  bloom_init(&bloom, entries, size_bloom); //number of entries/size
		else bloom_init(&bloom, entries, error);
		cout << "Press 1 to create a Bloom filter without using sha256" << endl;
		cout << "Press 2 to create a Bloom filter using sha256" << endl;

		done = false;
		bool sha; 
		while (!done){
			int choice;
			cout << "	Command: ";
			cin >> choice;
			if (choice == 1) {sha = false; done = true;}
			else if (choice == 2) {sha = true; done = true;}
			else cout << "Not a vaild command, please type 1 or 2" << endl;
		}

		if (sha){
			//Must codify entries with sha256 "MARCANGEL AL RESCATE"
		}

	}
}
