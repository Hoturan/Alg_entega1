#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

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

int main(int nargs, char* args[]) {
	ofstream myfile;
  	myfile.open ("claus.txt");
	if (nargs != 3 and nargs != 4) {
		cout << "usage: ./string_generator num_strings length (1..2)" << endl;
		cout << "1 generates strings with only letters, 2 with only numbers." << endl;
	}
	
	else {
		srand(time(0));
		int num_strings = atoi(args[1]);
		int length = atoi(args[2]);
		int option;
		if (nargs == 4) option = atoi(args[3]);
		else option = 3;

		for (int i = 0; i < num_strings; i++) {
			string p;
			for (int j = 0; j < length; j++) {
				if (option == 1) p+=getRandomletter();
				else if (option == 2) p+=getRandomnumber();
				else if (option == 3) p+=getRandom();
				else return 0;
			}
  			myfile << p << "\n";
  			
			cout << p << endl;
		}
	}
	myfile.close();
}
