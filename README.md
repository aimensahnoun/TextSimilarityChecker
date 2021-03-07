# C++ Text Similiraty Checker

This project checks the similarty between a main file ("main_doc.txt") that is in the same directory as the main.cpp file and an array of documents in the "files" directory in the same folder as main.cpp as well.

The programm wil give you the similarity percentage (Direct Plagiarism) between the texts as well as the top five similar sentences.


# Files

The program only has two code files the main.cpp that the user needs to run as well as the HelperFunctions header file that holds the main functionalities used by the program.

## Algorithms Used
The program uses multiple algorithms in order to be efficient and give reliable results.

 - DJB2 Hashing  (Closed Hashing/Key-Value) : Used in order to get the hash value of sentences, a Hash map is used in order to store all the possible sentence combinations found in the main file in order to make it easier to compare with the other files. If the hash value from a sentence in the compared files is not found in the hash map that means it does not exist in the main file.
 - Naive Text Matching : There can be more efficient algorithms found when it comes to string matching than naive text matching, but combined with the hash map the program becomes more efficient.
 - Bubble Sort : Even though it can be said that Bubble sort might be one of the most unefficient sorting algorithms available, this program is made with the asumption that there will not be a lot of similar sentences found that it would make much difference when it comes to sorting.



## Custom Structs 

Some structs have been defined in this program in order to make it easier to hold varialbes.

 - Sentence Index Struct : This struct holds the starting and ending index for a sentence found in the in the hash map, making easier to compare two sentences.
 - Document Output Struct : This struct holds the general output of the files after it is done processing. It holds three variables within it:
			 -Word List : A vector of words found in the text.
			 -New Text : A updated version of the given text (Lowercase and no punctuation).
			 -Word Count : The number of words found in the text.
- Main Document Output : This struct is only used by the main file after its done processing it has two variables, A DocumentOutput that holds the same variables as the other files within it, with the addition of the hash map.

## Program Steps

 1. Assuming that the main file is available, the program reads the content of that file, turns the text into lowercase as well as removes all punctuation, the new version of the text is then split into a vector of words and a new texts is created that removes all unnecessary use of white space. A hashmap is then created from the hash value of sentences made up of three words as well as staring/ending index of that sentence.
 2. The programm will do the first step except for the hash map creating for all of the files available under the "files" directory and returns a vector of DocumentOutput.
 3. The program iterates the DocumentOuput vector and hashes sentences made up of three words at a time, if the hash value is found within the main file hashmap the two sentences are compared and a similar word count is kept in a variable.
 4. After comparing the sentences the program will calculate the percentage by dividing the number of similar words found by the total number of words available in the text.
 5. The program outputs the percentage and top five(If found) similar sentences for each file.

## Exemplary outputs

 1. Comparing four movie scripts with repeating the main file 4 times for a total of 240,000 words.
**![](https://user-images.githubusercontent.com/62159014/110239806-ff7b0000-7f59-11eb-9b36-89fe73dc9bbd.jpg)**

2-Comaparing a direct plagiarism example and comparing it to an advanced plagiarism detection tool (Program does not check for related meanings)
**![](https://user-images.githubusercontent.com/62159014/110239821-233e4600-7f5a-11eb-84a8-36fa93a61986.jpg)****![](https://user-images.githubusercontent.com/62159014/110239841-381ad980-7f5a-11eb-923a-38be8e3261fa.jpg)**

3-Another direct plagiarism example
**![](https://user-images.githubusercontent.com/62159014/110239870-5680d500-7f5a-11eb-8d10-e4dbfb44f920.jpg)****![](https://user-images.githubusercontent.com/62159014/110239885-626c9700-7f5a-11eb-9ffd-dfaa5db9af3e.jpg)**

4-A mosaic plagiarism example (Out of scope of the program)**![](https://user-images.githubusercontent.com/62159014/110239898-6d272c00-7f5a-11eb-858f-4a3444c715e9.jpg)****![](https://user-images.githubusercontent.com/62159014/110239911-79ab8480-7f5a-11eb-8f70-8779f63721c9.jpg)**
