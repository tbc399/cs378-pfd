#ifndef PFD_H
#define PFD_H

#include <map>
#include <memory>
#include <vector>
#include <queue>
#include <list>
#include <iostream>
#include <string>

using namespace std;

class Task {
  
    private:
        
        bool still_good;
        
        unsigned int id;
        
        static vector<Task> all_tasks;
        
        //static vector<bool> done;
        
        void setId (unsigned int task_id);
        
        void setStillGood (bool b);
        
    public:
        
        Task ();
        
        static Task& getInstance (unsigned int task_id);
        
        explicit operator bool () const;
        
        void completed ();
        
        unsigned int getId ();
    
};

void pfd_read (const string& line, vector<list<int>>& tasks);

void pfd_eval (vector<list<int>>& tasks,
               vector<bool>& tasks_completed,
               vector<int>& ordered_ids);

void pfd_eval_help (int index,
                    vector<list<int>>& tasks,
                    vector<bool>& tasks_completed,
                    vector<int>& ordered_ids,
                    priority_queue<int, vector<int>, greater<int>>& pq);

void pfd_print (ostream& out, vector<int>& ordered_ids);

void pfd_solve (istream& in, ostream& out);

#endif