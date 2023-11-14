#include "markovMat.h"
using namespace std;

int main()
{
    /* DYNAMICALLY ALLOCATE A NEW CHAIN */
    markovMat *chain = new markovMat("corpus.txt");

    /* GENERATE STRING */
    cout << chain->generate(100) << "\n";

    /* DEALLOCATE CHAIN */
    delete chain;

    /* SUCCESSFUL EXIT FLAG */
    return 0;
}