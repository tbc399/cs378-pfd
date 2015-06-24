#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>

#include "PFD.h"

using namespace std;

Task::Task (unsigned int task_id) {
    id = task_id;
}

bool Task::precedes (const Task& t1, const Task& t2) {
    if (t1.dependents.size() == 0)
        return false;
    for (const pair<const unsigned int, Task*>& kv : t1.dependents) {
        if (*(kv.second) == t2) {
            return true;
        } else {
            if (precedes(*(kv.second), t2))
                return true;
        }
    }
    return false;
}

void Task::addDependent (Task& t) {
    this->dependents[t.id] = &t;
}

bool Task::operator> (const Task& t) {
    if (precedes(*this, t))
        return true;
    else if (precedes(t, *this))
        return false;
    else
        return id < t.id;
}

bool Task::operator== (const Task& t) {
    return id == t.id;
}

void pfd_read (const string& line, map<unsigned int, Task>& tasks) {
    istringstream iss(line);
    unsigned int target_id;
    iss >> target_id;
    //Task t(target_id);
    if (find(tasks.begin(), tasks.end(), target_id) == tasks.end()) {
        Task target(target_id);
        tasks[target_id] = target;
    }
    unsigned int ibuf;
    iss >> ibuf;
    for (int i = ibuf; i > 0; --i) {
        iss >> ibuf;
        //Task dep(ibuf);
        if (find(tasks.begin(), tasks.end(), ibuf) == tasks.end()) {
            Task dep(ibuf);
            tasks[ibuf] = dep;
        }
        tasks[target_id].addDependent(tasks[ibuf]);
        //tasks.push_back(dep);
    }
}

void pfd_solve (istream& in, ostream& out) {
    string s;
    in >> s;
    istringstream iss(s); // need to get the input dimensions
    int num_tasks;
    iss >> num_tasks;
    int num_targets;
    iss >> num_targets;
    map<unsigned int, Task> tasks_m;
    for (int i = 0; i < num_targets; ++i) {
        in >> s;
        pfd_read(s, tasks_m);
    }
    vector<Task> tasks_v(tasks_m.size());
    copy(tasks_m.begin(), tasks_m.end(), tasks_v.begin());
    sort(tasks_v.begin(), tasks_v.end());
    out << (tasks_v.begin())->id << " ";
    for (auto it = (tasks_v.begin() + 1); it != (tasks_v.end() - 1); ++it) {
        out << it->id << " ";
    }
    out << (tasks_v.end() - 1)->id << "\n";
}