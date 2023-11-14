#include "markovList.h"
using namespace std;

int main()
{
    /* DYNAMICALLY ALLOCATE A NEW CHAIN */
    markovList *chain = new markovList("corpus.txt");

    /* GENERATE STRING */
    cout << chain->generate(100) << "\n";

    /* DEALLOCATE CHAIN */
    delete chain;

    /* SUCCESSFUL EXIT FLAG */
    return 0;
}