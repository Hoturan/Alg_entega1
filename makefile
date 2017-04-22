MurmurHash2.o: libs/bloom/murmurhash2.h libs/bloom/MurmurHash2.c
	g++ -c libs/bloom/murmurhash2.h libs/bloom/MurmurHash2.c

bloom.o: libs/bloom/bloom.h libs/bloom/bloom.c
	g++ -c libs/bloom/bloom.h libs/bloom/bloom.c

sha256.o: libs/sha256/sha256.h libs/sha256/sha256.cpp
	g++ -c libs/sha256/sha256.h libs/sha256/sha256.cpp

md5.o: libs/md5/md5.h libs/md5/md5.cc
	g++ -c libs/md5/md5.h libs/md5/md5.cc

main: bloom.o MurmurHash2.o sha256.o md5.o main.cc
	g++ -o main main.cc bloom.o md5.o MurmurHash2.o sha256.o
