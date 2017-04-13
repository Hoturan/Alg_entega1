#include "bloom.h"
#include <iostream>

using namespace std;

void ini_bloom (int ent, double error, int bits, int bytes, int k) {
	
}

int main(){
	struct bloom bloom;
	bloom_init(&bloom, 20, 0.1); //number of entries/error
	cout << "with bloom 20 entries and 0.1 error: " << endl;
	cout << "optimal number of hashes is: " << bloom.hashes << endl;
	cout << "expected error is: " << bloom.error << endl; 
	bloom_add(&bloom, "hello world", 11);
	if (bloom_check(&bloom, "hello world", 11) == 1) cout << "is included" << endl;
        if (bloom_check(&bloom, "hello korld", 11) == 1)  cout << "should not be included" << endl;
	bloom_free(&bloom);

	if (bloom_init_m(&bloom, 20, 100) == 1) cout << "something went wrong" << endl; //number of entries/bits
	else {
		cout << "with bloom 20 entries and 100 bits: " << endl;
		cout << "optimal number of hashes is: " << bloom.hashes << endl;
		cout << "expected error is: " << bloom.error << endl; 
	}
}
