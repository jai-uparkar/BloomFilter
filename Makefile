# Makefile
CXX=clang++

CXXFLAGS = -g -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field

BINARIES = PA1.out
# BINARIES= testBloomFilter

all: ${BINARIES}

PA1.out : PA1.o BloomFilter.o HashTable3.o
	${CXX} $^ -o $@


tests: ${BINARIES}
	./PA1.out

clean:
	/bin/rm -f ${BINARIES} *.o
