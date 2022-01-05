/***********************************************************************
 * Module:
 *    Assignment 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Sean Hawkes 
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include "spellCheck.h"
#include "hash.h"
#include "vector.h"
using namespace std;


// Helper function to test for primality
bool isPrime(int num)
{
   if (num > 1 && num < 4)
      return true;
   if (num % 2 == 0 || num % 3 == 0)
      return false;
   auto divisor = 6;
   while (divisor * divisor - 2 * divisor + 1 <= num)
   {
      if (num % (divisor - 1) == 0)
         return false;
      if (num % (divisor + 1) == 0)
         return false;

      divisor += 6;
   }
   return true;
}


// Helper function to find next highest prime number past a given int
int nextPrime(int num)
{
   while (!isPrime(++num))
   {}
   return num;
}

class SHash : public Hash <std::string>
{
public:
   SHash(int numBuckets) : Hash<std::string>(numBuckets) {}
   SHash(const SHash& rhs) : Hash<std::string>(rhs) {}

   int hash(const std::string& value) const
   {
      // avoid collisions by using primes
      auto hash = uint32_t{11};
      for (auto i = 0; i < value.length(); ++i)
      {
         // add a bit shift to further increase entropy
         hash = ((hash * 31) ^ value[i]);
      }

      return hash % capacity();
   }
};


/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
   ifstream fs;
   fs.open("/home/cs235/week12/dictionary.txt");
   auto dict = vector::custom::vector<std::string>{};
   auto word = std::string{};
   auto stringToLower = [](const std::string& word) {
      auto word_lower = word;
      for (auto it = word_lower.begin(); it != word_lower.end(); ++it)
         *it = std::tolower(*it);
      return word_lower;
   };
   while (fs >> word)
      dict.push_back(stringToLower(word));
   fs.close();
   // Pick a size so hash load is < 70%, striking balance between
   // size and collisions
   // Also preserve primality to prevent loss of entropy
   // during modulo operations
   auto dict_hash = SHash{nextPrime(dict.size() * 1.6)};
   for (auto i = 0; i < dict.size(); ++i)
   {
      dict_hash.insert(dict[i]);
   }
   auto filename = std::string{};
   std::cout << "What file do you want to check? ";
   std::cin >> filename;
   try
   {
      fs.open(filename);
   }
   catch (const std::ifstream::failure& e)
   {
      std::cout << "Error opening file.\n";
   }
   cin.ignore();
   auto misspelled = vector::custom::vector<std::string>{};
   while (fs >> word)
   {
      if (!(dict_hash.find(stringToLower(word))))
         misspelled.push_back(word);
   }
   if (misspelled.empty())
   {
      std::cout << "File contains no spelling errors.\n";
   }
   else
   {
      auto separator = "";
      std::cout << "Misspelled: ";
      for (auto it = misspelled.begin(); it != misspelled.end(); ++it)
      {
         std::cout << separator << *it;
         separator = ", ";
      }
      std::cout << '\n';
   }
}
