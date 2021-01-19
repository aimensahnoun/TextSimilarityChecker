#include <vector>
#include "helperFunctions.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main()
{
    auto programStart = high_resolution_clock::now();

    MainDocumentOutput mainDocumentOutput = processMainDocument();
    vector<DocumentOutput> filesOutputs = processFiles();

    auto compareStart = high_resolution_clock::now();

    compareFiles(mainDocumentOutput, filesOutputs);

    auto programEnd = high_resolution_clock::now();
    auto programDuration = duration_cast<milliseconds>(programEnd - programStart);
    auto functionDuration = duration_cast<milliseconds>(programEnd - compareStart);

    cout<<"Program ran in : "<<programDuration.count()<<" milliseconds."<<endl;
    cout<<"Compare function ran in : "<<functionDuration.count()<<" milliseconds."<<endl;
}
