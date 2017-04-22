#include <iostream>
#include <vector>
#include "bloom.h"
#include "sha256.h"
#include <fstream>
#include <set>

using namespace std;


int main () {
    set <string> S;
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

        if (error == -1) {bloom_init_m(&bloom, entries, size_bloom); } //number of entries/size
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

        string line;
        ifstream myfile ("claus.txt");
        bool entry_error = false;
        if (myfile.is_open()){
            while (getline (myfile,line)){
                if (sha) line = sha256(line);
                //cout << line << " size is " << line.size() << endl;
                S.insert(line);
                bloom_add(&bloom, &line, line.size());
                if (!bloom_check(&bloom, &line, line.size())) entry_error = true;
            }
        }
        if (entry_error) cout << "One or more of the strings hasn't been added succesfully" << endl;
        
        int num_falsepositive = 0;
        int num_queries = 0;
        ifstream testfile ("test1.txt");
        if (testfile.is_open()){
            while (getline (testfile,line)){
                ++num_queries;
                if (sha) line = sha256(line);
                if (bloom_check(&bloom, &line, line.size())) {
                    if (S.find(line) == S.end()){ //list is found in bloom but is not in S, false positive
                        ++num_falsepositive;
                    }
                }
            }
        }
        
        cout << "Total number of queries: " << num_queries << endl;
        cout << "Total number of false positives: " << num_falsepositive << endl;
        cout << "Experimental error: " << (double)num_falsepositive/num_queries << endl;
        cout << "Theoretical error: " << bloom.error << endl;
    }
    
    
}
