#include <iostream>
#include <stdio.h>
#include <string>
#include "city.h"
#include "citycrc.h"
#include <inttypes.h>
using namespace std;



int main() {
	string p = "hola!";
	cout << "hasheo " << p << ": ";
	uint64 res = CityHash64(p.c_str(), p.size());
	unsigned int pres = res;
	cout << pres << endl;
}