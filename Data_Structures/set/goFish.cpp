/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    Jacob Bogdan, Jonah Green, Jared Garcia
* Summary: 
*    This is all the functions necessary to play Go Fish! This program 
*    implements our set class, iterator class, and card class.
*
*    Estimated:  2.0 hrs   
*    Actual:     1.5 hrs
*      The hardest part of this assignment was trying to get the last
*      item in the hand to display without a comma. We eventually figured
*      out, that we needed to use a the decrement operator which solved
*      our problem. 
************************************************************************/

#include <iostream>
#include <fstream>
#include "set.h"
#include "card.h"
#include "goFish.h"
//using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::ios;
using std::cerr;
using std::ifstream;


using namespace custom;

/**********************************************************************
 * GO FISH
 * This function implements the go fish game!
 ***********************************************************************/
void goFish()
{
   Card card;
   set <Card> hand;
   set <Card> :: iterator it;
   set <Card> :: iterator i;
   int count = 1;
   int match = 0;

   ifstream fin("/home/cs235/week05/hand.txt");
   if(fin.fail())
   {
      cout << "Failed to read file\n";
   }
   
   while(fin >> card)
   {
      hand.insert(card);
   }

   cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand\n";
   while (count != 6)
   { 
 
     cout << "round " << count << ": ";
     cin  >> card;

     // If a card is found you have a match
     if (hand.find(card) != hand.end())
     {
        cout << "\tYou got a match!\n";
        it = hand.find(card); 
        hand.erase(it);
        match++;
     }

     // if the card is not found go fish
     else
       cout << "\tGo Fish!\n";

     count++;
   }
   fin.close();

   cout << "You have " << match << " matches!\n";
   cout << "The remaining cards: ";

   for (it = hand.begin(); it != hand.end(); ++it)
   {
      if (it != hand.end()--)
      {
        cout << *it << ", ";
      }
      else 
        cout << *it;
   }
   cout << "\n";
   return ;
}

