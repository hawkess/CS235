/***********************************************************************
 * Header:
 *    TASK
 * Summary:
 *    Contains implementation for a task to be used by nowServing
  * Author
 *    Sean Hawkes 
 ************************************************************************/

#include <string>

#ifndef TASK_H_
#define TASK_H_

struct Task
{
   explicit Task(const std::string& course = {},
        const std::string& name = {},
        int duration = 0, bool emergency = false);

   std::string course_;
   int duration_;
   bool emergency_;
   std::string name_;
};

Task::Task(const std::string& course, const std::string& name,
     int duration, bool emergency) :
   course_(course),
   duration_(duration),
   emergency_(emergency),
   name_(name)
{
}

#endif // TASK_H_
