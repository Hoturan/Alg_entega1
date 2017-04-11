#include <iostream>
#include <vector>

using namespace std;

class BloomFilter{

	vector <bool> HashMap;
	uint8_t kfunc; //numer of hash functions to use
	uint64_t m_bits; //size of BloomFilter
	double fp; //probability of a false positive
	array <uint64_t, 2> hash(const uint8_t *data, size_t len);
	uint64_t nthHash(uint8_t n, uint64_t hashA, uint64_t hashB, uint64_t m_bits);
public:
	BloomFilter (uint64_t size);
	void setNumberFunctions (uint8_t nf);
	void add (const uint8_t *data, size_t len);
	bool possiblyCointains(const uint8_t data);
};