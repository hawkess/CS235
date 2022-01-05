#ifndef BNODE_H_
#define BNODE_H_

#include <iostream>

template <typename T>
class BNode
{
public:
   BNode(const T& t = T{});
   T data;
   BNode<T>* pLeft;
   BNode<T>* pParent;
   BNode<T>* pRight;
};

template <typename T>
BNode<T>::BNode(const T& t) :
   data(t),
   pLeft(nullptr),
   pParent(nullptr),
   pRight(nullptr)
{
}

template <typename T>
void addLeft(BNode<T>* pos, const T& t)
{
   try
   {
      auto node = new BNode<T>(t);
      addLeft(pos, node);
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

template <typename T>
void addLeft(BNode<T>* pos, BNode<T>* node)
{
   if (node != nullptr)
      node->pParent = pos;
   if (pos != nullptr)
      pos->pLeft = node;
}

template <typename T>
void addRight(BNode<T>* pos, const T& t)
{
   try
   {
      auto node = new BNode<T>(t);
      addRight(pos, node);
   }
   catch (std::bad_alloc&)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

template <typename T>
void addRight(BNode<T>* pos, BNode<T>* node)
{
   if (node != nullptr)
      node->pParent = pos;
   if (pos != nullptr)
      pos->pRight = node;
}

template <typename T>
BNode<T>* copyBTree(BNode<T>* source)
{
   if (source == nullptr)
      return source;
   auto copyNode = new BNode<T>(source->data);
   copyNode->pLeft = copyBTree(source->pLeft);
   copyNode->pRight = copyBTree(source->pRight);
   return copyNode;
}

template <typename T>
void deleteBTree(BNode<T>*& root)
{
   if (root == nullptr)
      return;
   deleteBTree(root->pLeft);
   deleteBTree(root->pRight);
   delete root;
   root = nullptr;
}

template <typename T>
int sizeBTree(const BNode<T>* root)
{
   if (root == nullptr)
      return 0;
   else
      return(sizeBTree(root->pLeft) + sizeBTree(root->pRight) + 1);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const BNode<T>* node)
{
   if (node == nullptr)
      return out;
   if (node->pLeft != nullptr)
      out << node->pLeft;
   out << node->data << " ";
   if (node->pRight != nullptr)
      out << node->pRight;
   return out;
}

#endif // BNODE_H_
