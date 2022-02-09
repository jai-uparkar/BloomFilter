// BloomFilter.cpp
#include "BloomFilter.h"
#include <string>
#include <iostream>
using namespace std;

// Constructor
BloomFilter::BloomFilter(float p, int m, float c, float d):auxTable(1009) {
    falsePos = p;
    numOfStrings = m;
    scaleBloom = c;
    scaleHash = d;
    dataSize = 0;
    numofFalsePos = 0;
    numofFalseNeg = 0;
    totalNumofFalsePos = 0;
    totalNumofFalseNeg = 0;
    filterSize = bloomFilterSize(p, m, c);
    filter.resize(this->filterSize);
    numofHashFunc = numHashFunctions(this->filterSize, m, d);
    generatingRandInt(this->numofHashFunc);
}

void BloomFilter::insert(std::string element){
    // coverting the string to an unsigned int
    unsigned int stringInt = strToInt(element);
    int hashValue = 0;
    // using the randomly generated k hash functions to set the corresponding bits to 1
    for (int i = 0; i <numofHashFunc; i++){
        hashValue = hash(stringInt, i); // calculcating the ith hash function
        filter[hashValue] = 1; // setting the bit
    }
    dataSize++;
}

void BloomFilter::remove(std::string element){
    // only remove elements that exist in the hash table
    bool exists = find(element);
    if (exists == true){
        auxTable.insertItem(element);
    }
    return;
}

bool BloomFilter::find(std::string element){
    unsigned int stringInt = strToInt(element);
    bool bloompresent = true;
    unsigned int hashValue = 0;
    for (int i = 0; i < numofHashFunc; i++){
         hashValue = hash(stringInt, i); // calculcating the hash function
         // if at any point the bool filter is not set, then we know the element
         // does not exist and we can break out of the loop
         if (filter[hashValue] == 0){
            bloompresent = false;
            break;
         }
    }
    return bloompresent;
}

int BloomFilter::bloomFilterSize(float p, int m, int c){
    return (int) ((-1*m*c*log(p)) / pow(log(2), 2));
}

int BloomFilter::numHashFunctions(int n, int m, int d){
    return (int)ceil(((n/m)*log(2)*d));
}

void BloomFilter::generatingRandInt(int l){
    srand(time(NULL)); // setting seed
    // generating k pairs of 2 random numbers (unif dist) and storing into vector
    for(int i = 0; i < l; i++){
        randomNumbers.push_back(make_pair(rand(), rand())); // random numbers will be coeff of hash func
    }
}

// generate k random integers at beginning of program 
// then access them via a loop when calculating each hash function
// same hash function with different elements. 
int BloomFilter::hash(unsigned int element , int index){
    // should I mod by another number too?
    return (element*randomNumbers[index].first + randomNumbers[index].second) % filterSize;
}

unsigned int BloomFilter::strToInt(std::string element){
    unsigned int num = 5381; // start out with large prime number
    for (int i = 0; i < (int)element.length(); i++){
        // bitwise shift operator is faster than multiplying by 33
        num = ((num<<5) + num) + element[i]; 
    }
    return num;
}

void BloomFilter::TrackingFalsePos(std::string word){
    // a false positive word is a word you know doesn't exists in the table but the 
    // bloom filter says that the word exists. 
    bool existsF = find(word);
    if (existsF == 1){
        numofFalsePos++;
        totalNumofFalsePos ++; 
        falsePosString.push_back(word);
        totalFalsePosString.push_back(word); // inserting into total count
    }
}

void BloomFilter::TrackingFalseNeg(std::string word){
    // false negative word is a word you know exists in the table but the 
    // bloom filter says it doesn't
    bool existsF = find(word);
    if (existsF == 0){
        numofFalseNeg++;
        totalNumofFalseNeg++;
    }
    //cout << "Total number of false pos " << numofFalsePos << endl;
}

double BloomFilter::ProbFalsePositive(){
    return (numofFalsePos*.01); // divide number by 100
}


void BloomFilter::displayFalsePosWords(std::vector<std::string> strList){
    std::vector<std::string>::iterator itr; // creating iterator to traverse list
    cout << "False Positive Elements: " << endl;
    for (itr = strList.begin(); itr != strList.end(); itr++){
        cout << *itr << endl;
    }
}

void BloomFilter::print(){
    cout << "Number of false negative:  " << numofFalseNeg << endl;
    cout << "Number of false positives:  "  <<  numofFalsePos << endl;
    cout << "Probability of false positives:  "  <<  (double)numofFalsePos/100 << endl;
    cout << "Total number of words  " << dataSize << endl;
    displayFalsePosWords(falsePosString);
    
    // reseting variables for next phase
    numofFalseNeg = 0;
    numofFalsePos = 0;
    falsePosString.clear();
}

string BloomFilter::EndprintS(){
    string output = "";
    output +=  "Total statistics: " ;
    output += "\nNumber of false negative:  " + std::to_string(totalNumofFalseNeg);
    output += "\nNumber of false positives:  "  + std::to_string(totalNumofFalsePos);
    output += "\nProbability of false positives:  "  + std::to_string(((double)totalNumofFalsePos/1000)) ;
    //output += "\nTotal number of words  " + dataSize;
    
    std::vector<std::string>::iterator itr; 
    output += "\nFalse Positive Elements:\n";
    for (itr = totalFalsePosString.begin(); itr !=  totalFalsePosString.end(); itr++){
        output += *itr + "\n";
    }

    return output;
}

void BloomFilter::Endprint(){
    cout<<  "\nTotal statistics: "  << endl;
    cout<< "\nNumber of false negative:  " << totalNumofFalseNeg;
    cout<< "\nNumber of false positives:  "  << totalNumofFalsePos;
    cout<< "\nProbability of false positives:  "  << ((double)totalNumofFalsePos/1000) ;
    
    std::vector<std::string>::iterator itr; 
    cout << "\nFalse Positive Elements:\n";
    for (itr = totalFalsePosString.begin(); itr !=  totalFalsePosString.end(); itr++){
        cout << *itr << "\n";
    }
   // auxTable.displayHash();
}

void BloomFilter::printFilter(){
    for (int i = 0; i < (int)filter.size(); i++){
        cout << filter[i];
    }
    cout << endl;  
}
