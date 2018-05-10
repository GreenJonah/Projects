
/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Jonah Green, Jared Garcia, Jacob Bogdan
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include <cctype>      // for ISPUNCT
#include <sstream>     
#include "stack.h"     // for STACK
#include "infix.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;
using std::ios;
using std::cerr;
using namespace custom;
//using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix) 
{
  string postfix;
   string _infix;
   stack <char> s;
   postfix += " ";
   bool flag = false;

   int t = 0;
   for (int j = 0; j < infix.length(); j++)
   {
      if (infix[j] != ' ')
      {  
         _infix += infix[j];
         t++;
      }
   }
   
   try
   {
      for (int i = 0; i < _infix.length(); i++) 
      {
         switch(_infix[i])
         {      
            case '(':
                s.push(_infix[i]);
                break;
               
            case ')':
               while (s.top() != '(')
               {
                  postfix = postfix + s.top() + " ";
                  s.pop();
               }
               flag = true;
               s.pop();
               break;
               
            case '^':
               s.push(_infix[i]);
               break;
               
            case '*':
            case '/':
            case '%':
               if (!s.empty())
               {
                  if (s.top() != '(' && s.top() != '+' && s.top() != '-')
                  {
                    postfix = postfix + s.top() + " "; 
                    s.pop();
                    s.push(_infix[i]);
                  }
                  else 
                    s.push(_infix[i]);
               }
               else
                  s.push(_infix[i]);
               break;

            case '+':
            case '-':
               if (!s.empty())
               {
                  int firstTime = 0;
                  int size = s.size();
                  while (!s.empty() && s.top() != '(')
                  {
                     int endSize = s.size();
                     if (size == 1 )
                        // stack has one, takes care of single sybmol
                        postfix = postfix + s.top() + " ";
                     else if (size > 1 && endSize == 1)
                        // stack has more than 1, takes care of last symbol pulled
                        postfix = postfix + " " + s.top() + " "; 
                     else if (size > 1 && firstTime == 0)
                        // stack has more than 1, takes care of first symbol
                        postfix = postfix + s.top();
                     else
                        // stack has more than 1, takes care of middle symbol
                        postfix = postfix + " " + s.top();
                     s.pop();
                     firstTime++;
                     if (!s.empty() && s.top() == '(')
                        postfix += " ";
                  }
                  s.push(_infix[i]);
               }
               else
                  s.push(_infix[i]);
               
               break;
               
            default:
               postfix = postfix + _infix[i];
               if (i != _infix.length() - 1)
               {
                  if (ispunct(_infix[i + 1]) && _infix[i + 1] != '.')
                     postfix = postfix + " ";
               }   
               break;
         }
      }
      
      while (!s.empty())
      {
        if (flag == true)
          postfix = postfix + s.top();
        else
          postfix = postfix + " " + s.top();

        flag = false;
        s.pop();
      }
   }
   catch (const char * error)
   {
      cout << error;
   }
   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;
   stringstream ss;
   stack <string> t;
   int count = 1;
  
   for (int i = 0; i < postfix.length(); i++)
   {
      bool readValue = false;
      string token = "";
      string charHolder;
      switch(postfix[i])
      {
        // If postfix[i] is an operator set token to 
        // the string equivilent of the operator
        case '^':
           token = "EXPONENT ";
           break;
        case '*':
           token = "MULTIPLY ";
           break;
        case '/':
           token = "DIVIDE ";
           break;
        case '%':
           token = "MODULUS ";
           break;
        case '+':
           token = "ADD ";
           break;
        case '-':
           token = "SUBTRACT ";
           break;  
        // If not an operator add to the stack  
        default:
           while (postfix[i] != ' ')
           {
              ss << postfix[i];   
              i++;
              readValue = true;
           }
           
           // Do not read in a blank stream.
           if (readValue)
           {
             charHolder = ss.str();
             t.push(charHolder);
             ss.str(string());
             break;
           }
      } 
      
      // If token is not equal to "" pop twice from 
      //stack LOAD value1 from stack then do token 
      // + value2 from stack and STORE the new value
      if (token != "")
      {
         try
         {             
            // set values to ""
            string value1 = "";
            string value2 = "";
                    
            // Set value 1 and 2 and pop                  
            value2 = t.top();
            t.pop();
            value1 = t.top();
            t.pop(); 
             
            // Add assembly steps to ss and give those 
            // values to assembly string                 
            ss << "\tLOAD "  << value1   << endl;
            ss << "\t"       << token     << value2 << endl;
            ss << "\tSTORE " << "VALUE" << count  << endl;
            assembly += ss.str();
            
            // put value into the stack
            ss.str(string());
            string temp = "";
            ss << "VALUE" << count;
            temp += ss.str();
            t.push(temp);
            ss.str(string());  
            count++;
         } 
         catch (const char * error)
         {
           cout << error;
         }        
      }
   }

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
