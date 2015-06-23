#ifndef PFD_H
#define PFD_H

class Task {
  
    private:
        
        map<int, Task*> dependents;
        
        const unsigned int id;
        
        int compare (const Task& that);
        
    public:
        
        Task (int id);
        
        void addDependent (Task& t);
        
        bool operator> (const Task& that);
    
};

void pfd_read (const string& line, vector<shared_ptr<Task>>& tasks);

void pfd_solve (istream& in, ostream& out);

#endif