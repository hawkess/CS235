/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include <cassert>         // for ASSERT
#include <sstream>
#include <string>          // for STRING: binary representation of codes
#include "bnode.h"         // for BINARY_NODE class definition
#include "huffman.h"       // for HUFFMAN() prototype
#include "pair.h"
#include "vector.h"

using std::cout;
using std::cin;
using std::ifstream;
using std::endl;
using std::string;
using std::bad_alloc;

using huff_pair = custom::pair<std::string, double>;
using bnode = BNode<huff_pair>*;
using node_vec = custom::vector<bnode>;
using node_vec_it = custom::vector<bnode>::iterator;
using str_pair = custom::pair<std::string, std::string>;


void generateCodes(std::string code, bnode node,
                   custom::vector<custom::pair
                   <std::string, std::string>>& vec);
custom::pair<int, int> findSmallest(node_vec& vec);
bool isLeaf(bnode node);
void mergeNodes(node_vec& vec, custom::pair<int, int> index);
void sortInsertion(custom::vector<str_pair>& vec);

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(const string & fileName)
{
   std::ifstream fs;
   try
   {
      fs.open(fileName, std::ios::in);
      auto nodes = node_vec{};
      auto tokens = custom::vector<str_pair>{};
      auto str = std::string{};
      auto freq = double{};

      while (fs >> str >> freq)
      {
         auto newPair = huff_pair{str, freq};
         auto node = new BNode<huff_pair>{newPair};
         auto tokenPair = str_pair(str, " ");
         tokens.push_back(tokenPair);
         nodes.push_back(node);
      }

      fs.close();

      while (nodes.size() > 1)
      {
         auto min = findSmallest(nodes);
         mergeNodes(nodes, min);
      }

      auto codes = custom::vector<str_pair>{};
      auto code = std::string{};
      auto node = nodes[0];
      assert(node != nullptr);
      generateCodes(code, node, codes);

      sortInsertion(codes);
      for (auto it = codes.begin(); it != codes.end(); ++it)
         std::cout << (*it).first << " = " << (*it).second << '\n';
      return;
   }
   catch (std::exception)
   {
      throw "ERROR: Could not open file";
   }
}

void generateCodes(std::string code, bnode node,
                   custom::vector<custom::pair
                   <std::string, std::string>>& vec)
{
   if (node == nullptr)
      return;
   if (node->pLeft)
   {
      generateCodes(code + '0', node->pLeft, vec);
   }
   if (node->pRight)
   {
      generateCodes(code + '1', node->pRight, vec);
   }
   if (isLeaf(node))
   {
      vec.push_back(str_pair{node->data.first,
               code});
   }
}

void sortInsertion(custom::vector<str_pair>& vec)
{
   auto i = 1;
   while (i < vec.size())
   {
      auto sortee = vec[i];
      auto j = i - 1;
      while ((j >= 0) && (vec[j].first > sortee.first))
      {
         vec[j + 1] = vec[j];
         --j;
      }
      vec[j + 1] = sortee;
      ++i;
   }
}

bool isLeaf(bnode node)
{
   return (node->pLeft == nullptr) && (node->pRight == nullptr);
}

void mergeNodes(node_vec& vec, custom::pair<int, int> index)
{
   auto parent = new BNode<huff_pair>{};
   auto totalfreq = vec[index.getFirst()]->data.getSecond();
   addLeft(parent, vec[index.getFirst()]);
   totalfreq += vec[index.getSecond()]->data.getSecond();
   addRight(parent, vec[index.getSecond()]);
   parent->data.second = totalfreq;
   vec[index.getFirst()] = parent;
   vec[index.getSecond()] = vec[vec.size() - 1];
   auto newVec = node_vec{};
   for (auto i = 0; i < vec.size() - 1; ++i)
      newVec.push_back(vec[i]);
   vec = newVec;
}

custom::pair<int, int> findSmallest(node_vec& vec)
{
   auto twoSmallest = custom::pair<int, int>{0, 1};
   auto smallest = vec[0]->data.getSecond();
   auto second = vec[1]->data.getSecond();

   for (auto i = 1; i < vec.size(); ++i)
   {
      if (vec[i]->data.getSecond() <
          vec[twoSmallest.getFirst()]->data.getSecond())
      {
         second = smallest;
         smallest = vec[i]->data.getSecond();
         twoSmallest.second = twoSmallest.first;
         twoSmallest.first = i;
      }
      else if ((vec[i]->data.getSecond() <
                vec[twoSmallest.getSecond()]->data.getSecond()))
      {
         second = vec[i]->data.getSecond();
         twoSmallest.second = i;
      }
   }
   return twoSmallest;
}

