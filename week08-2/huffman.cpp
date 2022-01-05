#include "huffman.h"

using namespace std;

// Driver function

void huffman(string fileName)
{
    ifstream fin(fileName.c_str());
    
    PAIR pair;
	// bnodes of pairs
    TREE * tree;
	// vector of 3 pointers 
    VEC_TREE data; 
    
    // read the file into a vector
    while(fin >> pair)
    {
       tree = new TREE(pair);
       data.push_back(tree);
    }
    // close the stream
    fin.close();
    
    // sort the data
    sort(data.begin(), data.end(), sortGreater);
    
    // sort the pairs with bnode (tree)
    while (data.size() > 1)
    {
       int size = data.size();
       
       // bnode will hold the result of two nodes
       TREE * combined;
       
     
       // combine two pairs to end of the vector
       combined = new TREE(*(new PAIR(data[size - 1]->data.first +
          data[size - 2]->data.first, data[size - 1]->data.second +
          data[size - 2]->data.second)));
       
       // push greater to right
       combined->addLeft(data[size - 1]);
       // push lesser to left
       combined->addRight(data[size - 2]);
       // pop off vector
       data.pop_back();
       data.pop_back();
       // push in place
       data.push_back(combined);
       // sort
       sort(data.begin(), data.end(), sortGreater);
    }
    
    VEC_PAIR huff;
    
    
    // encode
    encodeHuffman(data[0], "", huff);
    
    // sort first pair down
    sort(huff.begin(), huff.end(), sortLesser);
    
    for(int i = 0; i < huff.size(); i++)
    {
       cout << huff[i].first << " = " << huff[i].second << endl;
    }
    
   return;
}


 bool sortGreater(TREE * lhs, TREE * rhs)
 {
    if (lhs->data.second == rhs->data.second)
       return (lhs->data >= rhs->data);
    else
       return (lhs->data.second > rhs->data.second);
 }
 

 bool sortLesser(PAIR_STRING lhs, PAIR_STRING rhs)
 {
    return (lhs < rhs);
 }
 

 void encodeHuffman(TREE * root, string huffman, VEC_PAIR & huff)
 {
    
    // push back to vector if leaf
    if ((root->pLeft == NULL) && (root->pRight == NULL))
    {
       //First
       huff.push_back(PAIR_STRING(root->data.first, huffman));
       return;
    }
    
    // Check the tree if its not a leaf
    else
    {
	   // Add left
       if (root->pLeft != NULL)
       {
          encodeHuffman(root->pLeft, huffman + "0", huff);
       }
       
       // Add right
       if (root->pRight != NULL)
          encodeHuffman(root->pRight, huffman + "1", huff);
       return;
    }
 }
 
 
