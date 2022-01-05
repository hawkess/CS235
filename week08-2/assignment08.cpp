/***********************************************************************
* Program:
*    Week 08, Binary Trees 
*    Brother Helfrich, CS 235
* Author:
*    Br. Helfrich
* Summary: 
*    This is a driver program to exercise the BinaryNode class.  When you
*    submit your program, this should not be changed in any way.  That being
*    said, you may need to modify this once or twice to get it to work.
************************************************************************/

#include <iostream>    // for CIN and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "bnode.h"     // your BinaryNode class should be in bnode.h
#include "huffman.h"   // for huffman()
using namespace std;


// prototypes for our four test functions
void testSimple();
void testAdd();
void testDisplay();
void testMerge();

// To get your program to compile, you might need to comment out a few
// of these. The idea is to help you avoid too many compile errors at once.
// I suggest first commenting out all of these tests, then try to use only
// TEST1.  Then, when TEST1 works, try TEST2 and so on.
#define TEST1   // for testSimple()
#define TEST2   // for testAdd()
#define TEST3   // for testDisplay()
#define TEST4   // for testMerge()

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
   // menu
   cout << "Select the test you want to run:\n";
   cout << "\t1. Just create and destroy a BinaryNode\n";
   cout << "\t2. The above plus add a few nodes to create a Binary Tree\n";
   cout << "\t3. The above plus display the contents of a Binary Tree\n";
   cout << "\t4. The above plus merge Binary Trees\n";
   cout << "\ta. To generate Huffman codes\n";

   // select
   char choice;
   cout << "> ";
   cin  >> choice;
   switch (choice)
   {
      case 'a':
      {
         // get the filename
         string fileName;
         cout << "Enter the filename containing the value frequencies.\n";
         cout << "Enter \"quit\" when done.\n";

         cout << "> ";
         cin  >> fileName;

         while (fileName != "quit")
         {
            huffman(fileName);
            cout << "> ";
            cin  >> fileName;
         }
         break;
      }
      case '1':
         testSimple();
         cout << "Test 1 complete\n";
         break;
      case '2':
         testAdd();
         cout << "Test 2 complete\n";
         break;
      case '3':
         testDisplay();
         cout << "Test 3 complete\n";
         break;
      case '4':
         testMerge();
         cout << "Test 4 complete\n";
         break;
      default:
         cout << "Unrecognized command, exiting...\n";
   }

   return 0;
}

/*******************************************
 * TEST SIMPLE
 * Very simple test for a BinaryNode: create and destroy
 ******************************************/
void testSimple()
{
#ifdef TEST1
   try
   {
      // Test1: a bool Stack with defeault constructor
      cout << "Create a bool BinaryNode using the default constructor\n";
      BNode <bool> tree;
      cout << "\tSize:    " << tree.size() << endl;

      // Test2: double Stack with non-default constructor
      cout << "Create a double BinaryNode using the non-default constructor\n";
      BNode <double> *pTree = new BNode <double>(3.14159);
      cout << "\tSize:    " << pTree->size() << endl;
      delete pTree;
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif //TEST1
}

/*******************************************
 * TEST ADD
 * Add a few nodes together to create a tree, then
 * destroy it when done
 *****************************************/
void testAdd()
{
#ifdef TEST2
   try
   {
      // create
      BNode <int> * pTree = new BNode <int> (1);

      // add 2 to the left and 3 to the right
      pTree->addLeft(2);
      pTree->addRight(3);

      // add 4 and 5 off the left node
      pTree->pLeft->addLeft(4);
      pTree->pLeft->addRight(new BNode<int>(5));  // add one node using the other version of addRight()

      // add 6 and 7 to the right node
      pTree->pRight->addLeft(6);
      pTree->pRight->addRight(7);

      // now display the results:
      cout << "The elements in the binary tree:\n";
      cout << "\tRoot......... " << pTree->data                 << endl;
      cout << "\tLeft......... " << pTree->pLeft->data          << endl;
      cout << "\tRight........ " << pTree->pRight->data         << endl;
      cout << "\tLeft-Left.... " << pTree->pLeft->pLeft->data   << endl;
      cout << "\tLeft-Right... " << pTree->pLeft->pRight->data  << endl;
      cout << "\tRight-Left... " << pTree->pRight->pLeft->data  << endl;
      cout << "\tRight-Right.. " << pTree->pRight->pRight->data << endl;
      cout << "\tSize: "         << pTree->size()               << endl;

      // double-check the parents
      assert(pTree->pLeft->pParent  ==  pTree);
      assert(pTree->pRight->pParent ==  pTree);
      assert(pTree->pLeft ->pLeft ->pParent  ==  pTree->pLeft);
      assert(pTree->pLeft ->pRight->pParent  ==  pTree->pLeft);
      assert(pTree->pRight->pLeft ->pParent  ==  pTree->pRight);
      assert(pTree->pRight->pRight->pParent  ==  pTree->pRight);
      assert(pTree->pLeft ->pLeft ->pParent->pParent  ==  pTree);
      assert(pTree->pLeft ->pRight->pParent->pParent  ==  pTree);
      assert(pTree->pRight->pLeft ->pParent->pParent  ==  pTree);
      assert(pTree->pRight->pRight->pParent->pParent  ==  pTree);
      cout << "All the parent nodes are correctly set\n";
      
      // move some nodes around
      BNode <int> * pSix   = pTree->pRight->pLeft;
      BNode <int> * pSeven = pTree->pRight->pRight;
      pTree->pRight->addRight(pSix);
      pTree->pRight->addLeft(pSeven);
      assert(pTree->pRight->pRight->data == 6);
      assert(pTree->pRight->pLeft->data == 7);
      cout << "Was able to move the '6' and '7' nodes\n";
   
      // delete the left half of the tree
      BNode <int> * pTemp = pTree->pLeft;
      pTree->addLeft((BNode <int> *)NULL);
      assert(pTree->pLeft == NULL);
      deleteBinaryTree(pTemp);
      cout << "Size after deleting half the nodes: " << pTree->size() << endl;
   
      // finally, delete everything else
      deleteBinaryTree(pTree);
      cout << "Was able to delete the rest of the binary tree\n";
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif // TEST2   
}

/*******************************************
 * TEST Display
 * We will build a binary tree and display the
 * results on the screen
 ******************************************/
void testDisplay()
{
#ifdef TEST3
   try
   {
      // create
      BNode <string> *pTree = NULL;

      // prompt for seven words
      string word;
      cout << "Enter seven words\n";
      cout << "\tRoot node:         ";
      cin  >> word;
      pTree = new BNode <string> (word);

      cout << "\tLeft child:        ";
      cin  >> word;
      pTree->addLeft(new BNode <string> (word));

      cout << "\tRight child:       ";
      cin  >> word;
      pTree->addRight(new BNode <string> (word));
      
      cout << "\tLeft-Left child:   ";
      cin  >> word;
      pTree->pLeft->addLeft(new BNode <string> (word));
      
      cout << "\tLeft-Right child:  ";
      cin  >> word;
      pTree->pLeft->addRight(new BNode <string> (word));
      
      cout << "\tRight-Left child:  ";
      cin  >> word;
      pTree->pRight->addLeft(new BNode <string> (word));
      
      cout << "\tRight-Right child: ";
      cin  >> word;
      pTree->pRight->addRight(new BNode <string> (word));

      // when we are adding nothing, we should just return
      pTree->pLeft->pLeft->addLeft(NULL);
      pTree->pRight->pRight->addRight(NULL);
   
      // display the results
      cout << "Completed tree: { " << pTree << "}\n";

      // delete the tree
      deleteBinaryTree(pTree);
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif // TEST3
}

/*******************************************
 * TEST MERGE
 * Create three binary trees and merge them
 *******************************************/
void testMerge()
{
#ifdef TEST4
   try
   {
      // create the middle tree
      BNode <char> * pMiddle = new BNode <char> ('m');
      pMiddle->addLeft ('l');
      pMiddle->addRight('n');
      cout << "Middle tree: { " << pMiddle << "}"
           << " size = " << pMiddle->size() << endl;

      // create lower tree
      BNode <char> * pLower  = new BNode <char> ('b');
      pLower->addLeft  ('a');
      pLower->addRight ('c');
      cout << "Lower tree: { " << pLower << "}"
           << " size = " << pLower->size() << endl;
      

      // create upper tree
      BNode <char> * pUpper  = new BNode <char> ('y');
      pUpper->addLeft  ('x');
      pUpper->addRight ('z');
      cout << "Upper tree: { " << pUpper << "}"
           << " size = " << pUpper->size() << endl;
      
   
      // add Lower to the left of Middle, and Upper to the right of Middle
      pMiddle->pLeft->addLeft(pLower);
      pMiddle->pRight->addRight(pUpper);
      cout << "Merged tree: { " << pMiddle << "}"
           << " size = " << pMiddle->size() << endl;
      
	  // copy the tree
	  BNode <char> * pCopy = copyBTree(pMiddle);

      // delete the tree
      deleteBinaryTree(pMiddle);
	  assert(pMiddle == NULL);

	  // display the copied tree
	  cout << "Copied tree: { " << pCopy << "}"
		  << " size = " << pCopy->size() << endl;
	  deleteBinaryTree(pCopy);
	  assert(pCopy == NULL);

   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif // TEST4
}
