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
        float **adjacency = nullptr;
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
    corpusSize = 0;
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
        corpus.adjacency = new float *[corpusSize];

        /* Initialize an adjacency matrix */
        for (int i = 0; i < corpusSize; i++)
        {
            corpus.adjacency[i] = new float[corpusSize];

            for (int j = 0; j < corpusSize; j++)
                corpus.adjacency[i][j] = 0;
        }

        while (i < corpusSize && getline(file, line, '\n'))
        {
            parser[i] << line;
            getline(parser[i], word, ',');
            corpus.buckets[word] = i;
            i++;
        }

        for (i = 0; i < corpusSize; i++)
        {
            while (getline(parser[i], word, ','))
            {
                splitter.clear();
                splitter.str(word);
                splitter >> word >> weight;

                /* Add weight into the matrix, with the first index as the starting
                   node and the second index at the destination node */
                map<string, int>::iterator destination = corpus.buckets.find(word);

                if (destination != corpus.buckets.end())
                    corpus.adjacency[i][destination->second] = weight;
            }
        }

        delete[] parser;
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
    if (corpusSize == 0 || corpus.buckets.empty() || length <= 0)
        return "";

    /* Initialize an iterator to find a random node in the next line */
    map<string, int>::iterator it = corpus.buckets.begin();

    /* This grabs a random node from your corpus as a starting point */
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
        index = -1;
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
