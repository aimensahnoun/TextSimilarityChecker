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
**![](https://lh3.googleusercontent.com/fLUkhQFcVXnv2maNYyTSY_KEUFNaDFp1us6SrdyZJYBiXrznZWP8ezu7i5qW54YRbDCfNR6texpjA8K5CYcV8eFzDNbamZ2XZ8twVlC288k7d9G6Y3erkSja_83ZuLoE0NDIxMN6)**

2-Comaparing a direct plagiarism example and comparing it to an advanced plagiarism detection tool (Program does not check for related meanings)
**![](https://lh3.googleusercontent.com/lT2sz9weaouenGVMrS_DpBtO0MPRhcwYe1MlnDWhX1sp6DKK_RWZrokFWBIksludhd55UV_zDfa9Ceki8MyHrGGFrh2P53HQdJlpBzG5fnhh3MQx5UfMTQrAjPqPXZy5uoH1wC8F)****![](https://lh5.googleusercontent.com/cFfYEtFId6zNmaxDmjHCF40ZYnCWzZgaHoiDfDSV0XW8BHMeWlaXJVRuiPQiMKRfcJifFyLyJcpHONCWRoq_vpRD216HBdgfYLfAyMfAfx0yIMs7LEjS5s0BNY1vH0_Ml9tnFsU5)**

3-Another direct plagiarism example
**![](https://lh3.googleusercontent.com/6dtJDGYeH1hYXoH_OepFeb9iB-K3xlZLwOsF5Cq6ucePkjJ3uxzvQDPSYQ3P3_jySVS-OzM15Qz8GhMPYIhbRBjFp-XHFRvRZDWQ_QckotJiGDdCWA8QGeG7PvAIBePGtW5QKxkH)****![](https://lh3.googleusercontent.com/9VRJGChIO41GDQoS3tn8jmDGAfSSjYnRacNU-8DDZ_3DA2yLHhxHyjKQ2FYTI6VNfPG947e3rxfqaIQhET7fjXkw3WlR6KHLo0LhlEtQdFC7lRPIv-77RejB_H5rIj6_MD2QHAFb)**

4-A mosaic plagiarism example (Out of scope of the program)**![](https://lh6.googleusercontent.com/0vJIItWmSzvrjkj9dhOJsan-cTNE-XBied8k6O2_bWwXcpNG-7yFHBeq0FTfA_785N9HfeLMTFZn5AK9tnb6ykByfxmu-VbkV-2GaiytbuVRe6P-_jd3oOCuwP8C5f0sZLqAi1FY)****![](https://lh6.googleusercontent.com/ySPxeOEPPTE5gTtijYsaSmLuHZHz-SWcDV6bZmq7dEqHB5XmAZu2Z7TerapbsbTg6oColAVJ_AitUdskJFUjqAdDsZU1tnLRtJ8Ms72Nmfai0MVJtJTNxyVZz_npfteIbhcNLTjP)**
