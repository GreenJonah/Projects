/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    Jacob Bogdan, Jonah Green, Jared Garcia
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype
#include <string>
#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ios;
using std::cerr;
using std::ostream;
using std::ifstream;
using std::string;

using namespace custom;

/**********************************************************
* READ FILE
* It is just as it sounds this function reads in a file
* then it places each word into a file and ups the count 
* each time the word is repeated
**********************************************************/
void readFile(map <string, int> & counts, const string & fileName)
{
   ifstream fin(fileName.c_str());
   if (fin.fail())
   {
      cout << "Cannot access that file\n";
      return;
   }
   
   string word;
   map <string, int> :: iterator it;
   while (fin >> word)
   {
	  //cout << word << endl;
	   int value = 1;
      string key;
	   // IF found set value to get second + 1
     // Pass value in with the [] operator 
	   it = counts.find(word);
	   if (it != counts.end())
	   {
	     value = (*it).getSecond() + 1;
        key = (*it).getFirst();
        counts[key] =  value;
	   }

	   // else insert the word
	   if (it == counts.end())
	      counts.insert(word, value);
    }
}

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
   string fileName;
   map <string, int> counts;

   cout << "What is the filename to be counted? ";
   cin  >> fileName;

   readFile(counts, fileName);

   string word;
   cout << "What word whose frequency is to be found. Type ! when done\n";

   while (word != "!")
   {
   	  cout << "> ";
   	  cin >> word;
   	  if (word != "!")
         cout << "\t" << word << " : " << counts[word]  << endl;
   }
}

