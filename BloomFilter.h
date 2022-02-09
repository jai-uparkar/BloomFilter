// BloomFilter.h

#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath> 
#include <time.h>
#include <stdlib.h> // random num
#include "HashTable3.h"

class BloomFilter {
public:
   
    // p := probability of a false positive
    // m := expected number of strings to be inserted
    // c := scale factor of bloom filter size
    // d := scale factor of number of hash functions
    BloomFilter(float p, int m, float c, float d);

    // Insert a string into the bloom filter.
    void insert(std::string element);

    // Delete an element from the bloom filter.
    // This will use an auxiliary hash table . defined below .
    void remove(std::string element);

    // Return true if the element is in the bloom filter ,
    // otherwise return false .
    bool find(std::string element);

    // Compute the bloom filter size based on the false positive probability desired ,
    // and the expected number of strings to be inserted.
    // Scale the computed size by ’c ’ ( for experimental purposes ).
    // p := probability of a false positive
    // m := expected number of strings to be inserted
    // c := scale factor of bloom filter size
    int bloomFilterSize(float p, int m, int c);

    // Compute the number of hash functions to use based on the bloom filter size ,
    // and the expected number of strings to be inserted.
    // Scale the computed size by ’d ’ ( for experimental purposes ).
    // n := bloom filter size
    // m := expected number of strings to be inserted
    // d := scale factor of bloom filter size
    int numHashFunctions(int n , int m, int d) ;

    // Family of hash functions
    // The index specifies which hash function should be used
    int hash(unsigned int element, int index);

    // String to integer conversion
    // Needed for running the elements on the above hash function
    unsigned int strToInt(std::string element);

    // generates 2 random numbers to create a family of k independent hash functions
    // l := number of hashFunctions needed
    void generatingRandInt(int l);

    // checks for false positive by checking if element exists in table and filter
    // existsF : = whether word exists in the filter
    // existsT : = whether word exists in the table
    // word : = element you are trying to find
    void TrackingFalsePos(std::string word);

    void TrackingFalseNeg(std::string word);

    // calculates the probability of false positive in each phase
    double ProbFalsePositive();

    void displayFalsePosWords(std::vector<std::string>);

    // Local Phase Testing Results
    void print();

    // End of Experiment Results
    std::string EndprintS();

    void Endprint();

    // prints the bloomfilter
    void printFilter();

private:
    // probability of false positive
    float falsePos;

    // espected number of strings to be inserted
	int numOfStrings;

	// scale factor of bloom filter size
	float scaleBloom;

    // scale factor of number of hash functions
	float scaleHash;

    //size of the bloom filter
    int filterSize;

    // number of elements currently in bloom filter
	int dataSize;

    // number of hash functions needed
    int numofHashFunc;

    // total number of false positives in a phase
    int numofFalsePos;

    // total number of false negatives in a phase
    int numofFalseNeg;

        // total number of false positives in a phase
    int totalNumofFalsePos;

    // total number of false negatives in a phase
    int totalNumofFalseNeg;

    // bloom filter with n bits 
    std::vector<bool> filter;

    // keeps track of all the false positive words
    std::vector<std::string> falsePosString;

    // keeps track of all the false positive words
    std::vector<std::string> totalFalsePosString;

    // vector of random numbers for hash function
    std::vector<std::pair<int, int>> randomNumbers; 

    // auxilirary table that contains all the removed elements
    HashTable auxTable;
};


#endif // BLOOMFILTER_H


