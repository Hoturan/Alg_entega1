#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//static const char l[] = "abcdefghijklmnopqrstuvwxyz";
//static const char l[] = "0123456789";
static const char l[] = "abcdefghijklmnopqrstuvwxyz0123456789";
int stringLength = sizeof(l) - 1;

char getRandom() {
	return l[rand() % stringLength];
}

int main(int nargs, char* args[]) {
	ofstream myfile;
  	myfile.open ("test.txt");
	
	if (nargs != 3) {
		cout << "usage: ./string_generator num_strings length" << endl;
	}
	
	else {
		srand(time(0));
		int num_strings = atoi(args[1]);
		int length = atoi(args[2]);
		for (int i = 0; i < num_strings; i++) {
			string p;
			for (int j = 0; j < length; j++) {
				p+=getRandom();
			}
  			myfile << p << "\n";
  			
			cout << p << endl;
		}
	}
	myfile.close();
}
