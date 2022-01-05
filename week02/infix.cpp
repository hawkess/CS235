/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Sean Hawkes
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <locale>
#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include <vector>
#include "stack.h"     // for STACK
using namespace std;


int onStackPrecedence(char input);
int offStackPrecedence(char input);
std::string getOperInstruction(char input);
bool isOperand(char input);
bool isOperator(char input);
bool isVariable(char input);
std::vector<std::string> tokenify (const std::string& input);
/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string& infix)
{
   auto postfix = std::string();
   auto space = std::string();
   auto opStack = custom::stack<std::string>{};

   auto tokens = tokenify(infix);

   auto appendToPostfix = [&space, &postfix](const auto& appendee)
      {
         postfix.append(space);
         postfix.append(appendee);
         space = " ";
      };

   for (auto token : tokens)
   {
      //If character is an operand
      if (isOperand(token[0]))
         appendToPostfix(token);

      //If character is an operator
      else if (isOperator(token[0]))
      {
         //If the stack is empty or precedence off stack is higher
         if (opStack.empty() ||
             offStackPrecedence(token[0]) > onStackPrecedence(opStack.top()[0]))
         {
            opStack.push(token);
         }
         //If stack isn't empty of precedence on stack is higher
         else
         {
            //Empty stack
            while (!opStack.empty() &&
                   offStackPrecedence(token[0]) <
                   onStackPrecedence(opStack.top()[0]))
            {
               appendToPostfix(opStack.top());
               opStack.pop();
            }
            opStack.push(token);
         }
      }

      //Opening bracket
      else if (token == ")")
      {
         //Pop up to opening bracket
         while (opStack.top() != "(")
         {
            appendToPostfix(opStack.top());
            opStack.pop();

            if (opStack.empty())
               throw "ERROR: Invalid expression";
         }
         //Pop opening bracket
         opStack.pop();
      }
   }

   while (!opStack.empty())
   {
      if (opStack.top() == "(")
         throw "ERROR: Invalid expression";
      appendToPostfix(opStack.top());
      opStack.pop();
   }

   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }

      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix:  " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   auto assembly = std::string();
   auto opStack = custom::stack<std::string>{};
   auto tokens = tokenify(postfix);
   auto reg = char('A');

   for (auto token : tokens)
   {
      auto rhs = std::string();
      auto lhs = std::string();
      auto oper = std::string();

      if (isOperand(token[0]))
          opStack.push(token);
      else
      {
         rhs = opStack.top();
         opStack.pop();
         lhs = opStack.top();
         opStack.pop();
         if (isVariable(lhs[0]))
            assembly += "\tLOD " + lhs + "\n";
         else
            assembly += "\tSET " + lhs + "\n";
         oper = getOperInstruction(token[0]);
         assembly += "\t" +  oper + rhs + "\n";
         assembly += "\tSAV " + std::string(1, reg) + "\n";
         opStack.push(std::string(1, reg));
         reg++;
      }
   }
   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }

      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");

}

int onStackPrecedence(char input)
{
   switch (input)
   {
      case '+':
      case '-':
         return 10;
      case '*':
      case '%':
      case '/':
         return 100;
      case '^':
         return 101;
      case '(':
         return 0;
      default:
         return -1;
   }
}

int offStackPrecedence(char input)
{
   switch (input)
   {
      case '+':
      case '-':
         return 1;
      case '*':
      case '%':
      case '/':
         return 11;
      case '^':
         return 111;
      case '(':
         return 1000;
      default:
         return -1;
   }
}

std::string getOperInstruction(char input)
{
   auto oper = std::string();
   switch (input)
   {
      case '+':
         oper = "ADD ";
         break;
      case '-':
         oper = "SUB ";
         break;
      case '*':
         oper = "MUL ";
         break;
      case '%':
         oper = "MOD ";
         break;
      case '/':
         oper = "DIV ";
         break;
      case '^':
         oper = "EXP ";
         break;
      default:
         oper = "";
         break;
   }

   return oper;
}

bool isOperator(char input)
{
   switch (input)
   {
      case '+':
      case '-':
      case '*':
      case '%':
      case '/':
      case '^':
      case '(':
         return true;
      default:
         return false;
   }
}

bool isOperand(char input)
{
   return (std::isalnum(input, std::locale("")) || input == '.');
}

bool isVariable(char input)
{
   return (std::isalpha(input, std::locale("")));
}

std::vector<std::string> tokenify(const std::string& input)
{
   auto output = std::vector<std::string>{};
   auto token = std::string{};
   for (auto c : input)
   {
      if (isOperand(c))
         token.push_back(c);
      else
      {
         if (!token.empty())
         {
            output.push_back(token);
            token = "";
         }
         if (c != ' ')
            output.push_back(std::string(1, c));
      }
   }
   if (!token.empty())
   {
      output.push_back(token);
      token = "";
   }
   return output;
}
