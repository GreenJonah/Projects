/***********************************************************************
 * Header:
 *    STOCK
 * Summary:
 *    This will contain just the prototype for stocksBuySell(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Jonah Green, Jared Garcia, Jacob Bogdan
 ************************************************************************/

#ifndef STOCK_H
#define STOCK_H

#include "dollars.h"   // for Dollars defined in StockTransaction
#include "queue.h"     // for QUEUE
#include <iostream>    // for ISTREAM and OSTREAM

// the interactive stock buy/sell function
void stocksBuySell();

void buy();

void sell();

void display();

#endif // STOCK_H

