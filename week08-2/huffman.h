#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <fstream>
#include <algorithm>
#include "bnode.h"
#include "pair.h"
#include <vector>
#include <string>



using namespace std;

typedef Pair<string, float> PAIR;
typedef Pair<string, string> PAIR_STRING;
typedef BNode<PAIR> TREE;
typedef vector<TREE*> VEC_TREE;
typedef vector<PAIR_STRING> VEC_PAIR;

void huffman(string fileName);
bool sortGreater(TREE* lhs, TREE * rhs);
bool sortLesser(PAIR_STRING lhs, PAIR_STRING rhs);
void encodeHuffman(TREE * root, string huffman, VEC_PAIR & huff);

#endif // HUFFMAN_h
