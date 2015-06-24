#ifndef PFD_H
#define PFD_H

#include <map>
#include <memory>
#include <iostream>
#include <string>

using namespace std;

class Task {
  
    private:
        
        map<unsigned int, Task*> dependents;
        
        static bool precedes (const Task& t1, const Task& t2);
        
    public:
        
        unsigned int id;
        
        Task (unsigned int task_id);
        
        void addDependent (Task& t);
        
        bool operator> (const Task& t);
        
        bool operator== (const Task& t);
    
};

void pfd_read (const string& line, map<unsigned int, Task>& tasks);

void pfd_solve (istream& in, ostream& out);

#endif