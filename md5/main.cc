#include <iostream>
#include "md5.h"
 
using std::cout; using std::endl;
 
int main(int argc, char *argv[])
{
	if (argc != 2) {
		cout << "usage: ./md5 stringtoconvert" << endl;
	}
	else cout << md5(argv[1]) << endl;
}