/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    Jonah Green, Jared Garcia, Jacob Bogdan
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "dollars.h"
#include <sstream> 

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ios;
using std::cerr;
using std::stringstream;
using namespace custom;

/**********************************************************
* BUY
* Pushs in all shares purchased in the buy(b) queue which 
* represents a batch of shares purchased. 
**********************************************************/
void buy(int & quantity, Dollars & price,  queue <Dollars> & b)
{
   // Push number of stock prices onto q
   for (int i = 0; i < quantity; i++)
      b.push(price);
}

/**********************************************************
* SELL
* Gets the gain received from sell price and purchase price
* placing the gains and the price inside of the sell(s) queue
* representing a batch of shares sold.  
**********************************************************/
void sell(int & quantity, Dollars & price, queue <Dollars> & b, 
          queue <Dollars> & s, Dollars & proceeds)
{ 
   // sell will be be 
   //(current sell price - purchase price) X number of stocks
   Dollars profit = 0;
   Dollars gain = 0;
   Dollars previous = b.front();
   for(int i = 0; i < quantity; i++)
   {
      if (b.front() != previous)
      {
        s.push(price);
        previous = b.front();
      }
      gain = price - b.front();
      s.push(gain);
      proceeds += gain;
      b.pop();  
   }
   // Push on our three factors for sell
   s.push(price);
}

/**********************************************************
* DISPLAY
* Displays both the batches of shares bought from the buy(b) 
* queue and the batches of sold shares from the sell(s) queue.
* Lastly, the proceeds from the portfolio are displayed. 
**********************************************************/
void display(queue <Dollars>  b, queue <Dollars>  s, 
            Dollars & proceeds)
{

  // Displays batches of shares from the buy(b) queue. 
  if (!b.empty())
  {
    cout << "Currently held:\n";
    Dollars previous = b.front();
    int batch = 0; 
    while (!b.empty())
    {
      if (b.front() != previous)
      {
         cout << "\tBought " << batch << " shares at " << previous << endl;
         previous = b.front();
         batch = 0;
      }
      b.pop();
      batch++;
    }
     // Display our last batch or single batch
    cout << "\tBought " << batch << " shares at " << previous << endl; 
  }
  
  // Displays batches of shares from the sell(s) queue
  if (!s.empty())
  {
    cout << "Sell History:\n";
    
    Dollars previousSell = s.front();
    int batchSell = 0;
    Dollars profit = 0;
    while (!s.empty())
    { 
      if (s.front() != previousSell)
      {
        cout << "\tSold " << batchSell << " shares at ";
        cout << s.front()  << " for a profit of ";
        cout << profit << endl;
        s.pop();
        if (!s.empty())
          previousSell = s.front();
        profit = 0;
        batchSell = 0;
      }

      if (!s.empty())
      {
        profit += s.front();
        s.pop();
        batchSell++;
      }
    } 
  }
  cout << "Proceeds: " << proceeds << endl;
}

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   queue <Dollars> b;
   queue <Dollars> s;
   string instruction;
   int quantity       = 0;
   Dollars price    = 0.00;
   Dollars proceeds = 0.00;
   
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";
      

   do 
   {
      cout << "> ";
      cin  >> instruction;
      // If quit or display is typed ignore the other two entries 
      if (instruction == "quit" || instruction == "Quit"
          || instruction == "display" || instruction == "Display")
      {
          cin.ignore();
          cin.clear();
      }
      else
          cin >> quantity >> price; 
  
      if (instruction == "buy" || instruction == "Buy")
        buy(quantity, price, b);
      else if (instruction == "sell" || instruction == "Sell" )
        sell(quantity, price, b, s, proceeds);
      else if (instruction == "display" || instruction == "Display")
        display(b, s, proceeds);
      else if (instruction == "quit" || instruction == "Quit")
        break;
      else
        cout << "Invalid Command\n";
   }
   while(instruction != "quit" || instruction != "Quit"); 
}