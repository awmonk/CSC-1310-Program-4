/*
    Title:          driver.cpp
    Author:         Austin Monk
    Date:           11/30/2023
    Section:        CSC 1310-001
    Purpose:        Driver for the adjacency list
*/

#include "markovList.h"
using namespace std;

int main()
{
    /* DYNAMICALLY ALLOCATE A NEW CHAIN */
    markovList *chain = new markovList("corpus.txt");

    /* GENERATE STRING */
    cout << "\nGENERATING TEXT BASED ON CORPUS (corpus.txt):\n\n";
    cout << chain->generate(100) << "\n";

    /* DEALLOCATE CHAIN */
    delete chain;

    cout << "\nGOODBYE!\n\n";

    /* SUCCESSFUL EXIT FLAG */
    return 0;
}