#ifndef MARKOVMAT_H
#define MARKOVMAT_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdlib.h>
using namespace std;

class markovMat
{
private:
    struct matrix
    {
        map<string, int> buckets;
        float **adjacency;
    };

    matrix corpus;
    int corpusSize;

public:
    markovMat(const char *);
    ~markovMat();

    string generate(int);
};

markovMat::markovMat(const char *filename)
{
    ifstream file(filename);
    stringstream *parser;
    stringstream splitter;

    string line;
    string word;
    float weight;

    srand(time(0));

    int i = 0;

    if (file.good())
    {
        file >> corpusSize;
        file.ignore(1, '\n');

        parser = new stringstream[corpusSize];

        /* Initialize an adjacency matrix */
        for (int i = 0; i < corpusSize; i++)
        {
            corpus.adjacency[i] = new float[corpusSize];

            for (int j = 0; j < corpusSize; j++)
                corpus.adjacency[i][j] = 0;
        }

        while (getline(file, line, '\n'))
        {
            parser[i] << line;
            getline(parser[i], word, ',');
            i++;
        }

        for (i = 0; i < corpusSize; i++)
        {
            while (getline(parser[i], word, ','))
            {
                splitter.clear();
                splitter.str(word);
                splitter >> word >> weight;

                /* add weight into the matrix, with the first index as the starting
                   node and the second index at the destination node */
                corpus.adjacency[i][corpus.buckets[word]] = weight;
            }
        }
    }
}

markovMat::~markovMat()
{
    for (int i = 0; i < corpusSize; ++i)
        delete[] corpus.adjacency[i];

    delete[] corpus.adjacency;
}

string markovMat::generate(int length)
{
    // initialize an iterator to find a random node in the next line
    map<string, int>::iterator it = corpus.buckets.begin();

    // this grabs a random node from your corpus as a starting point
    advance(it, rand() % corpusSize);

    /* Initialize return string and matrix indices */
    string result = it->first;
    int curr = corpus.buckets[result];
    int index = -1;

    /* Initialize random value and cumulative weight */
    float randV;
    float weight;

    for (int i = 0; i < length - 1; i++)
    {
        randV = (float)rand() / RAND_MAX;
        weight = 0;

        for (int j = 0; j < corpusSize; j++)
        {
            weight += corpus.adjacency[curr][j];

            if (randV <= weight)
            {
                index = j;
                break;
            }
        }

        if (index != -1)
        {
            for (map<string, int>::iterator it = corpus.buckets.begin();
                 it != corpus.buckets.end(); it++)
            {
                if (it->second == index)
                {
                    result += " " + it->first;
                    curr = index;
                    break;
                }
            }
        }
        else
        {
            curr = rand() % corpusSize;

            for (map<string, int>::iterator it = corpus.buckets.begin();
                 it != corpus.buckets.end(); it++)
            {
                if (it->second == curr)
                {
                    result += " " + it->first;
                    break;
                }
            }
        }
    }

    return result;
}

#endif