# CSC 1310 Program 4: Markov Chain Text Generator

A C++ text generator that models a corpus as weighted word transitions and uses a first-order Markov chain to produce stochastic text. The project implements the same model with two graph representations: an adjacency list and an adjacency matrix.

## How it works

1. `generateCorpus.py` removes punctuation from a training document and counts adjacent word pairs.
2. Each outgoing count is converted into a transition probability.
3. The generated `corpus.txt` maps every source word to its possible successors and their weights.
4. The C++ program selects an initial word and repeatedly samples the next word from the weighted transitions.

Because selection is probabilistic, every run can produce different text.

## Implementations

### Adjacency list

`adjacency list/markovList.h` stores only transitions that occur in the corpus. This is memory-efficient for sparse word graphs.

### Adjacency matrix

`adjacency matrix/markovMat.h` assigns each source word an integer index and stores transition weights in a two-dimensional array. This provides direct indexed access at the cost of allocating space for every possible word pair.

Each directory includes its own driver, corpus generator, generated corpus, and sample source text.

## Requirements

- A C++ compiler with C++11 or later support
- Python 3 only when regenerating a corpus

## Build and run

### Adjacency-list version

```bash
cd "adjacency list"
g++ -std=c++11 driver.cpp -o markov-list
./markov-list
```

### Adjacency-matrix version

```bash
cd "adjacency matrix"
g++ -std=c++11 driver.cpp -o markov-matrix
./markov-matrix
```

On Windows, run the corresponding `.exe` file instead.

Both drivers expect `corpus.txt` in their working directory and currently generate approximately 100 words.

## Regenerating the corpus

Run the Python script from either implementation directory:

```bash
python generateCorpus.py
```

When prompted, enter the path to a training text such as `pirates.txt`. The script replaces `corpus.txt`, after which the C++ program can be rebuilt or run against the new data.

## Concepts demonstrated

- Markov chains and weighted random selection
- Directed graph representations
- Adjacency-list versus adjacency-matrix tradeoffs
- Maps, linked structures, and dynamic arrays
- Text preprocessing with Python
