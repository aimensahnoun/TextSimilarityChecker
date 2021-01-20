#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <vector>
#include <map>
#include <sstream>
#include <locale>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct SentenceIndex
{
    int sentenceStart;
    int sentenceEnd;
};

struct DocumentOutput
{
    vector<string> wordList;
    string newText;
    int wordCount;
};

struct MainDocumentOutput
{
    DocumentOutput props;
    map<string, SentenceIndex> sentencesHashMap;
};

void swap(string *xp, string *yp)
{
    string temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(vector<string> &arr)
{
    int i, j;
    for (i = 0; i < arr.size(); i++)
        for (j = 0; j < arr.size() - i - 1; j++)
            if (arr[j].size() < arr[j + 1].size())
                swap(&arr[j], &arr[j + 1]);
}

DocumentOutput splitIntoWords(string text)
{
    DocumentOutput result;
    vector<string> textWords;
    string newText;
    istringstream iss(text);
    for (string word; iss >> word;) //Iterate through text word by word
    {
        textWords.push_back(word);
        newText += word + " ";
    }
    result.wordList = textWords;
    result.newText = newText;
    result.wordCount = textWords.size();
    return result;
}

string toLowerCase(string input)
{
    locale loc;
    string lowerCaseString;
    for (int i = 0; i < input.length(); i++)
    {
        lowerCaseString += tolower(input[i], loc);
    }
    return lowerCaseString;
}

string readFile(string location)
{
    string fileString;
    ifstream mainFile(location);

    if (!mainFile.is_open())
    {
        return "Couldnt find file";
    }

    while (mainFile.peek() != EOF)
    {
        string newSentence;
        getline(mainFile, newSentence, '.');
        fileString += newSentence + " ";
    }
    mainFile.close();
    return fileString;
}

unsigned long DJB2HASH(string str)
{
    int hash = 5381;
    unsigned int length = str.length();
    for (int i = 0; i < length; i++)
    {
        hash = ((hash << 5) + hash) + (str[i]);
    }

    return hash;
}

MainDocumentOutput processMainDocument()
{
    MainDocumentOutput output;
    map<string, SentenceIndex> hashMap;
    string fileName;

    string mainFileString = readFile("./main_doc.txt"  );

    if (mainFileString == "Couldnt find file")
    {
        cout << "Couldnt find main document, please try again";
        exit(1);
    }

    mainFileString = toLowerCase(mainFileString);

    //Remove all punctuation from text
    mainFileString.erase(
            remove_if(mainFileString.begin(), mainFileString.end(), ::ispunct), mainFileString.end());

    DocumentOutput result = splitIntoWords(mainFileString);

    int sentenceStart = 0;
    for (int i = 0; i < result.wordList.size(); i++)
    {
        string hashableText;
        for (int j = i; j < i + 3; j++)
        {
            hashableText += result.wordList[j];
        }
        int sentenceEnd = sentenceStart + hashableText.length() + 2;

        string hashValue = to_string(DJB2HASH(hashableText));

        SentenceIndex tempIndex;
        tempIndex.sentenceStart = sentenceStart;
        tempIndex.sentenceEnd = sentenceEnd;
        sentenceStart += result.wordList[i].length() + 1;

        hashMap[hashValue] = tempIndex;
    }

    output.sentencesHashMap = hashMap;
    output.props.newText = result.newText;
    output.props.wordCount = result.wordList.size();

    return output;
}

vector<DocumentOutput> processFiles()
{
    DIR *dir;
    struct dirent *diread;

    string folderName;
    vector<DocumentOutput> fileOutputs;

    string folderPath = "./files" ;

    if ((dir = opendir(folderPath.c_str())) != nullptr)
    {
        while ((diread = readdir(dir)) != nullptr)
        {
            if (diread->d_name[0] == '.') //Skipping hidden files
            {
                continue;
            }

            string fileText = "";
            fileText = readFile(folderPath + "/" + diread->d_name);

            string lowerCaseText = toLowerCase(fileText);

            //Remove all punctuation from text
            lowerCaseText.erase(
                    remove_if(lowerCaseText.begin(), lowerCaseText.end(), ::ispunct), lowerCaseText.end());

            DocumentOutput result = splitIntoWords(lowerCaseText);
            DocumentOutput documentOutput;

            documentOutput.wordCount = result.wordList.size();
            documentOutput.wordList = result.wordList;
            documentOutput.newText = result.newText;
            fileOutputs.push_back(documentOutput);
        }

        closedir(dir);
    }
    return fileOutputs;
}

void compareFiles(MainDocumentOutput mainFile, vector<DocumentOutput> filesOutputs)
{

    for (int i = 0; i < filesOutputs.size(); i++) //Iterating through files vector
    {

        if (filesOutputs[i].wordCount > 0) //Skipping empty files
        {

            long totalSimilarWordCount = 0;
            vector<string> similarSentences;
            int sentenceStart = 0;

            for (int j = 0; j < filesOutputs[i].wordCount; j++) // Iterating through text
            {

                string hashableText = "";
                int similarWordCount = 0;

                for (int k = j; k < j + 3; k++)
                {
                    hashableText += filesOutputs[i].wordList[k];
                }

                string hashValue = to_string(DJB2HASH(hashableText));
                int currentSentenceStart = sentenceStart;

                if (mainFile.sentencesHashMap.count(hashValue) > 0) //Checking if sentence already exist in hash map
                {

                    SentenceIndex mainIndex = mainFile.sentencesHashMap[hashValue];
                    int mainSentenceStart = mainIndex.sentenceStart;
                    bool isMismatch = false;

                    while (!isMismatch)
                    {
                        if (filesOutputs[i].newText[currentSentenceStart] == mainFile.props.newText[mainSentenceStart])
                        {
                            mainSentenceStart++;
                            currentSentenceStart++;
                        }
                        else
                        {
                            isMismatch = true;
                        }
                        if (filesOutputs[i].newText[currentSentenceStart] == ' ') //Checking if iterators are moving into a new word
                        {
                            similarWordCount++;
                        }
                    }

                    if (similarWordCount > 3)
                    {
                        string commonString = filesOutputs[i].newText.substr(sentenceStart, (currentSentenceStart - sentenceStart));
                        similarSentences.push_back(commonString);
                        totalSimilarWordCount += similarWordCount;
                    }
                }

                if (similarWordCount > 0)
                {
                    sentenceStart = currentSentenceStart;
                    j += similarWordCount - 1;
                }
                else
                {
                    sentenceStart += filesOutputs[i].wordList[j].length() + 1;
                }
            }

            double similarity = (double)totalSimilarWordCount / (double)filesOutputs[i].wordCount;

            double similarityPercentage = similarity * 100;

            cout << "Main file and compared file " + to_string(i + 1) + " are "<<fixed<<setprecision(1)<<similarityPercentage<<"% similar"<<endl;

           bubbleSort(similarSentences);
            for (int a = 0; a < similarSentences.size(); a++) {
                 if (a > 4) {
                     break;
                 } else {
                     cout << to_string(a + 1) + ") " + similarSentences[a] << endl;
                 }
             }
        }
    }
}

#endif
