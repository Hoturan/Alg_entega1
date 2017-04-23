#include <iostream>
#include <vector>
#include "libs/bloom/bloom.h"
#include "libs/sha256/sha256.h"
#include <fstream>
#include <set>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "libs/md5/md5.h"

using namespace std;

static const char let[] = "abcdefghijklmnopqrstuvwxyz";
static const char num[] = "0123456789";
static const char l[] = "abcdefghijklmnopqrstuvwxyz0123456789";
int stringLength = sizeof(l) - 1;
int numLength = sizeof(num) - 1;
int letLength = sizeof(let) - 1;

char getRandomletter() {
    return let[rand() % letLength];
}

char getRandomnumber() {
    return num[rand() % numLength];
}

char getRandom() {
    return l[rand() % stringLength];
}

void create_claus(int num_strings, int length, int option) {
    ofstream myfile;
    myfile.open ("claus.txt");
    
    srand(time(0));

    for (int i = 0; i < num_strings; i++) {
        string p;
        for (int j = 0; j < length; j++) {
            if (option == 1) p+=getRandomletter();
            else if (option == 2) p+=getRandomnumber();
            else if (option == 3) p+=getRandom();
        }
        myfile << p << "\n";
        
    }
    myfile.close();
}

int main () {
    set <string> S;
	struct bloom bloom;
	bool finished = false;

    time_t timer;
    int entries, size_bloom, length;
    double error;
    cout << "-------------------------------------------" << endl;
    cout << "Number of entries: ";
    cin >> entries;
    cout << "Length of entries: ";
    cin >> length;
        
    create_claus(entries, length, 3); //generates random entries number of strings of length lenth
        
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
    else bloom_init(&bloom, entries, error); //number of entries/error

    cout << "Press 1 to create a Bloom filter" << endl;
    cout << "Press 2 to create a Bloom filter using sha256" << endl;
    cout << "Press 3 to create a Bloom filter using md5" << endl;

    done = false;
    int opt;
    while (!done){
        int choice;
        cout << "	Command: ";
        cin >> choice;
        if (choice == 1) {opt = 1; done = true;}
        else if (choice == 2) {opt = 2; done = true;}
        else if (choice == 3) {opt = 3; done = true;}
        else cout << "Not a vaild command, please type 1, 2 or 3" << endl;
    }
    string line;
    ifstream myfile ("claus.txt");
    time_t before_adding = clock();
    float time_to_add = 0;
    bool entry_error = false;
    if (myfile.is_open()){
        while (getline (myfile,line)){
            if (opt == 2) line = sha256(line);
            else if (opt == 3) line = md5(line);
            S.insert(line);
            
            time_t add = clock();
            bloom_add(&bloom, &line, line.size());
            time_to_add += float(clock() - add) / CLOCKS_PER_SEC;
            
            if (!bloom_check(&bloom, &line, line.size())) entry_error = true;
        }
    }
    if (entry_error) cout << "One or more of the strings hasn't been added succesfully" << endl;
    //time_to_add = float(clock() - before_query) / CLOCKS_PER_SEC;
        
    int n = 0;
    int num_falsepositive = 0;
    int num_queries = 0;
    
    cout << "Starting queries, might take a while..." << endl;
        
    time_t before_query;
    before_query = clock();
    float time_query;
    while (n < 10){
        ++n;
        string query;
        ifstream testfile ("tests/test" + to_string(n) + ".txt");
        if (testfile.is_open()){
            while (getline (testfile,query)){
                ++num_queries;
                if (opt == 2) query = sha256(query);
                else if (opt == 3) query = md5(query);
                if (bloom_check(&bloom, &query, query.size())) {
                    if (S.find(query) == S.end()){ //list is found in bloom but is not in S, false positive
                        ++num_falsepositive;
                    }
                }
            }
        }
    }
    time_query = float(clock() - before_query) / CLOCKS_PER_SEC;
        
    cout << endl;
    cout << "Number of hash functions used (optimal k): " << bloom.hashes << endl;
    cout << "Total number of queries: " << num_queries << endl;
    cout << "Total number of false positives: " << num_falsepositive << endl;
    cout << "Experimental error: " << (double)num_falsepositive/num_queries << endl;
    cout << "Theoretical error (without any encryption): " << bloom.error << endl;
    cout << endl;
    cout << "Time to add all strings to bloom filter: " << time_to_add << " seconds" << endl;
    cout << "Time to do all querys: " << time_query  <<  " seconds" << endl;
    bloom_free(&bloom); //free bloom for next use
    
}
