#include "BloomFilter.h"
#include "MurmurHash3.h"
#include <array>

BloomFilter::BloomFilter(uint64_t size){
	vector <bool> a (size,0);
	HashMap = a;
	m_bits = size;
}

void BloomFilter::setNumberFunctions (uint8_t nf){
	kfunc = nf;
}

array <uint64_t, 2> BloomFilter::hash(const uint8_t *data, size_t len){
	array <uint64_t, 2> hashValue;
	MurmurHash3_x86_32(data, len, 0, hashValue.data());

	return hashValue;
}

uint64_t BloomFilter::nthHash(uint8_t n, uint64_t hashA, uint64_t hashB, uint64_t m_bits){
	return (hashA + n*hashB) % m_bits;
}

void BloomFilter::add (const uint8_t *data, size_t len){
	array <uint64_t, 2> hashValues;
	hashValues = hash(data, len);

	for (int n = 0; n < kfunc; ++n){
		HashMap[nthHash(n, hashValues[0], hashValues[1], m_bits)] = true;
	}
}