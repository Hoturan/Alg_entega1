#include <iostream>
#include "sha256.h"
 
using namespace std;
using std::string;
using std::cout;
using std::endl;
 
int main(int argc, char *argv[])
{
    string input;
    while (cin >> input) {
    	input = "hola em dic marc";
		string output1 = sha256(input);
    	cout << "sha256('"<< input << "'):" << output1 << endl;
    }
    
    return 0;
}