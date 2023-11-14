/*
    Title:          markovList.h
    Author:         Austin Monk
    Date:           11/30/2023
    Section:        CSC 1310-001
    Purpose:        An adjacency list that parses a corpus of text and generates a
                    stochastic array of words based on the weight (probability) of
                    each word in a given text file
*/

#ifndef MARKOVLIST_H
#define MARKOVLIST_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdlib.h>
using namespace std;

class markovList
{
private:
    struct edge
    {
        /* EDGE ATTRIBUTES */
        string dest;
        float weight;
        edge *next;

        /* EDGE CONSTRUCTOR */
        edge(string d, float w, edge *n) : dest(d), weight(w), next(n){};
    };

    /* HEAD ARRAY AND SIZE */
    map<string, edge *> corpus;
    int corpusSize;

public:
    /* LIST ALLOCATION */
    markovList(const char *);
    ~markovList();

    /* OUTPUT GENERATOR */
    string generate(int);
};

markovList::markovList(const char *filename)
{
    /* INFILE STREAM TRAVERSAL VARIABLES */
    ifstream file(filename);
    stringstream parser;
    stringstream splitter;

    /* INFILE STORAGE VARIABLES */
    string line;
    string index;
    string word;
    float weight;

    /* LIST TRAVERSAL NODE POINTER */
    edge *newEdge;

    /* RANDOMIZATION SEED */
    srand(time(NULL));

    if (file.good())
    {
        file >> corpusSize;
        file.ignore(1, '\n');

        /* Map every word to a position in the matrix, keep the line in an array of
           buffers for later */
        while (getline(file, line, '\n'))
        {
            parser.clear();
            parser << line;

            getline(parser, index, ',');

            /* Initialize an empty list at the index */
            corpus[index] = nullptr;

            while (getline(parser, word, ','))
            {
                splitter.clear();
                splitter.str(word);
                splitter >> word >> weight;

                /* Stick the word and weight on the node you've just allocated and
                   make sure the new node is attached to the list */
                newEdge = new edge(word, weight, corpus[index]);
                corpus[index] = newEdge;
            }
        }
    }
}

markovList::~markovList()
{
    /* LIST TRAVERSAL NODE POINTERS */
    edge *next;
    edge *curr;

    /* Set the range of the loop to an iterator mapped to the beginning of the corpus
       to the end */
    for (map<string, edge *>::iterator it = corpus.begin(); it != corpus.end(); it++)
    {
        /* The current traversal node is assigned to the iterator using the edge
           mapped to the iterator as a key */
        curr = it->second;

        /* Begin the usual traversal and deletion loop */
        while (curr)
        {
            next = curr->next;
            delete curr;
            curr = next;
        }
    }

    /* Clear the map and remove all the entries */
    corpus.clear();
}

string markovList::generate(int length)
{
    /* Initialize a random value and a cumulative weight variable */
    float randV;
    float weight;

    /* Initialize an iterator to find a random node in the next line */
    map<string, edge *>::iterator it = corpus.begin();

    /* Grab a random node from the corpus as a starting point */
    advance(it, rand() % corpusSize);

    /* Initialize a string variable that will store the destination string throughout
       the traversal; strings are mapped to the first pointer of the iterator */
    string result = it->first;

    /* Initialize a traversal node */
    edge *curr;

    /* The range of the traversal is set to the length passed through to the function;
       in our test case this will be 100, but it can be any arbitrary value */
    for (int i = 0; i < length; i++)
    {
        /* This formula ensures that the random value is between 0.0 and 1.0 */
        randV = (float)rand() / RAND_MAX;

        /* Set the initial cumulative weight to zero for each pass of the for loop */
        weight = 0.0;

        /* The traversal node is initialized using the string mapped to the iterator
           as the key */
        curr = corpus[it->first];

        /* List traversal */
        while (curr)
        {
            /* The weight of the current node is added to the cumulative weight */
            weight += curr->weight;

            /* Check the weight against the random value */
            if (randV < weight)
            {
                /* Set the storage string to the string found at the current node
                   and use a space character as a parser */
                result += " " + curr->dest;

                /* Assign the iterator to the current edge and return to the beginning
                   of the for loop */
                it = corpus.find(curr->dest);
                break;
            }

            /* If the random value is greater than the cumulative weight, move on
               to the next node in the list */
            curr = curr->next;
        }
    }

    /* Return the storage string */
    return result;
}

#endif