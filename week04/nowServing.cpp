/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Sean Hawkes 
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include <sstream>      // for std::stringstream
#include <vector>       // for std::vector
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
#include "task.h"       // for TASK
using namespace std;

enum class Option { NONE, REGULAR, EMERGENCY, QUIT };


Option classifyRequest(std::string request);
Task createRequest(std::vector<std::string> tokens, bool emergency);
void printCurrent(Task currentlyServing);
/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   custom::deque<Task> requests;
   auto elapsedTime = 0;
   auto simRunning = true;
   auto currentlyServing = Task{};

   std::cin.ignore();
   while (simRunning == true)
   {
      std::cout << '<' << elapsedTime << "> ";
      std::vector<std::string> tokens;
      std::string line;
      // Reads in entire line and converts it into a vector of std::string
      // tokens to allow access to individual elements of data
      std::getline(std::cin, line);
      std::stringstream ls(line);
      std::string token;
      while (ls >> token)
      {
         tokens.emplace_back(token);
      }
      auto requestType = classifyRequest(tokens.front());
      // Switch to handle behavior based on the user input
      switch (requestType)
      {
         case Option::NONE:
            break;
         case Option::REGULAR:
            // Go to the back of the line
            requests.push_back(createRequest(tokens, false));
            break;
         case Option::EMERGENCY:
            // You're special, go to the front of the line
            tokens.erase(tokens.begin());
            requests.push_front(createRequest(tokens, true));
            break;
         case Option::QUIT:
            simRunning = false;
            break;
         default:
            break;
      }
      // If the previous patron has been served for the full duration
      // and another one is in the deque, get a new task
      if (currentlyServing.duration_ == 0 && !requests.empty())
      {
         currentlyServing = requests.front();
         requests.pop_front();
      }

      // If there is remaining time in the duration for the current task
      if (currentlyServing.duration_ > 0)
      {
         printCurrent(currentlyServing);
         --currentlyServing.duration_;
      }
      ++elapsedTime;
   }
   // end
   cout << "End of simulation\n";
}

/*************************************************************************
 classifyRequest()
 Input: std::string - tokenized string to specify request type
 Output:
 Returns an enum corresponding to the option selected
**************************************************************************/
Option classifyRequest(std::string request)
{
   if (request == "!!")
      return Option::EMERGENCY;
   else if (request == "none")
      return Option::NONE;
   else if (request == "finished")
      return Option::QUIT;
   return Option::REGULAR;
}

/*************************************************************************
 createRequest()
 Input: std::vector<std::string>, bool - vector of tokenized strings from
        std::getline, bool flag signifying emergency request
 Output:
 Forms and returns a Task object based on the input to be pushed to the deque
**************************************************************************/
Task createRequest(std::vector<std::string> tokens, bool emergency)
{
   auto duration = int();
   stringstream minutes(tokens.back());
   minutes >> duration;
   return Task(tokens[0], tokens[1], duration, emergency);
}

/*************************************************************************
 printCurrent()
 Input: Task - current task to be printed
 Output:
 Prints the current task information
**************************************************************************/
void printCurrent(Task currentlyServing)
{
   auto output = std::stringstream();
   if (currentlyServing.emergency_)
      output << "\tEmergency for ";
   else
      output << "\tCurrently serving ";
   output << currentlyServing.name_ << " for class " <<
      currentlyServing.course_ << ". Time left: " <<
      currentlyServing.duration_ << "\n";
   std::cout << output.str();
}
