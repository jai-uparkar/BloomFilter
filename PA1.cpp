#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "BloomFilter.h"
using namespace std;

vector<std::string> CreatingBloomFilter(const std::string& filename)
{
    std::ifstream source;
    source.open(filename);
    std::string line;
    vector<std::string> var;
    //unsigned int linesRead = 0;
    while (/*(linesRead <) &&*/ std::getline(source, line))
    {
        var.push_back(line);
        //linesRead++;
    }
    source.close();
    return var;
}


int main(int argc,  char **argv)
{
    std::string line;
    std::string setUp(argv[1]); // corresponds to setup.txt
    std::string inputVal(argv[2]); // corresponds to input.txt
    std::string successSearch(argv[3]); // corresponds to successfulSearch.txt
    std::string FailedSearch(argv[4]); // corresponds to failedSearch.txt
    std::string removeTable(argv[5]); // corresponds to remove.txt

    std::ifstream input(inputVal); // creating file to input.txt
    std::ifstream success(successSearch); // creating file to successfulSearch.txt
    std::ifstream failed(FailedSearch); // creating file to failedSearch.txt
    std::ifstream removeT(removeTable); // creating file to remove.txt


    // Creating the Bloom Filter
    vector<std::string> bfVar =  CreatingBloomFilter(setUp);
    BloomFilter bf1(std::stof(bfVar[0]),std::stoi(bfVar[1]), std::stof(bfVar[2]), std::stof(bfVar[3]));

    // Creating name for output file
    std::string outName = "output<" + bfVar[2] + "_" + bfVar[3] + ">.txt"; 
    //Creating output file
    std::ofstream outputFile(outName);

    // Printing out experiment values
    cout << "\nExperiment for values of : " << endl; 
    cout << "p = " << bfVar[0]<< endl; 
    cout << "m = " << bfVar[1] << endl;  
    cout << "c = " << bfVar[2] << endl; 
    cout << "d = " << bfVar[3] << endl; 
    
    int linesRead = 0;

    // 10 Phases of Testing
    for(int i = 0; i < 10; i++){
        cout << "\n\nPhase " << i+1 << ": " <<endl;

        // intserting 1000 element into filter
        if (input.is_open()){
            while ((linesRead <1000) && std::getline(input, line)){
                bf1.insert(line);
                linesRead++;
            }
        }
        linesRead  = 0; // reset counter for next file read

        // 100 elements successful Search
        if (success.is_open()){
            while (linesRead < 100 && getline (success,line) ){
                bf1.TrackingFalseNeg(line);
                linesRead++;
            }
        }
        linesRead  = 0; // reset counter 

         // 100 elements failed Search
        if (failed.is_open()){
            while (linesRead < 100 && getline (failed,line) ){
                bf1.TrackingFalsePos(line);
                linesRead++;
            }
        }
        linesRead  = 0; // reset counter 

         // 100 elements removal
        if (removeT.is_open()){
            while (linesRead < 100 && getline (removeT,line) ){
                bf1.remove(line);
                linesRead++;
            }
        }
        bf1.print();
        linesRead  = 0; // reset counter 
    }
    // close the 
    bf1.Endprint();
    outputFile << bf1.EndprintS(); // send final summary of phase to the ouput file
    outputFile.close();
    input.close();
    success.close();
    failed.close();
    removeT.close();
    return 0;
}