MurmurHash2.o: murmurhash2.h MurmurHash2.c
	g++ -c murmurhash2.h MurmurHash2.c

bloom.o: bloom.h bloom.c
	g++ -c bloom.h bloom.c

sha256.o: sha256.h sha256.cpp
	g++ -c sha256.h sha256.cpp

main: bloom.o MurmurHash2.o sha256.o
	g++ -o main main.cc bloom.o MurmurHash2.o sha256.o
