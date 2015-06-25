#include <vector>
#include <queue>
#include <list>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>

#include "PFD.h"

using namespace std;

vector<Task> Task::all_tasks;
//vector<bool> Task::all_tasks

Task::Task () {
    id = 0;
    still_good = true;
}

Task& Task::getInstance (unsigned int task_id) {
    //cout << "getting instance for: " << task_id << "\n";
    if (task_id >= all_tasks.size()) {
        all_tasks.resize(task_id + 1);
        all_tasks[task_id].setId(task_id);
        //all_tasks[task_id].setStillGood(true);
    } else if (all_tasks[task_id].getId() == 0) {
        all_tasks[task_id].setId(task_id);
        //all_tasks[task_id].setStillGood(true);
    }
    return all_tasks[task_id];
}

Task::operator bool () const {
    return still_good;
}

unsigned int Task::getId () {
    return id;
}

void Task::setId (unsigned int task_id) {
    id = task_id;
}

void Task::setStillGood (bool b) {
    still_good = b;
}

void Task::completed () {
    //cout << "complete() called on id: " << id << "\n";
    still_good = false;
}

void pfd_read (const string& line, vector<list<int>>& tasks) {
    istringstream iss(line);
    unsigned int target_id;
    iss >> target_id;
    unsigned int ibuf;
    iss >> ibuf;
    for (int i = ibuf; i > 0; --i) {
        iss >> ibuf;
        tasks[target_id].push_back(ibuf);
    }
}

void pfd_eval (vector<list<int>>& tasks, vector<bool>& tasks_completed, vector<int>& ordered_ids) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i < (int)(tasks.size()); ++i) {
        cout << i << " -> " << tasks_completed[i] << "\n";
        //if (!Task::getInstance(i))
        if (tasks_completed[i])
            continue;
        //cout << "tasks["<<i<<"].size(): " << tasks[i].size() << "\n";
        /*
        if (tasks[i].size() == 0) {
            pq.push(i);
            tasks_completed[i] = true;
            cout << "PUSHING " << i << " ONTO QUEUE\n";
        } else {*/
            pfd_eval_help(i, tasks, tasks_completed, ordered_ids, pq);
            //pq.push(i);
            //cout << "PUSHING "<<i<<" TO THE QUEUE\n";
            /*
            while (pq.size() > 0) {
                ordered_ids.push_back(pq.top());
                //tasks_completed[pq.top()] = true;
                pq.pop();
            }
            pq.push(i);
            tasks_completed[i] = true;
            */
        //}
    }
    while (!pq.empty()) {
        ordered_ids.push_back(pq.top());
        cout << "POPING "<<pq.top()<<" FROM THE QUEUE\n";
        pq.pop();
    }
}

void pfd_eval_help (int index,
                    vector<list<int>>& tasks,
                    vector<bool>& tasks_completed,
                    vector<int>& ordered_ids,
                    priority_queue<int, vector<int>, greater<int>>& pq) {
    if (tasks_completed[index])
        return;
    list<int>& deps = tasks[index];
    if (deps.size() == 0) {
        pq.push(index);
        cout << "PUSHING "<<index<<" TO THE QUEUE 3\n";
        tasks_completed[index] = true;
    } else {
        for (auto it = deps.begin(); it != deps.end(); ++it) {
            if (tasks_completed[*it])
                continue;
            /*
            if (pq.top() == *it) {
                ordered_ids.push_back(pq.top());
                pq.pop();
                cout << "POPING "<<*it<<" FROM THE QUEUE\n";
                tasks_completed[*it] = true;
                continue;
            }*/
            pfd_eval_help(*it, tasks, tasks_completed, ordered_ids, pq);
            tasks_completed[*it] = true;
            if (pq.top() == *it) {
                ordered_ids.push_back(pq.top());
                pq.pop();
                cout << "POPING "<<*it<<" FROM THE QUEUE\n";
                //tasks_completed[*it] = true;
                continue;
            }
            /*
            while (pq.size() > 0) {
                ordered_ids.push_back(pq.top());
                //tasks_completed[pq.top()] = true;
                pq.pop();
            }
            */
            if (pq.empty() || pq.top() != *it) {
                pq.push(*it);
                cout << "PUSHING "<<*it<<" TO THE QUEUE 1\n";
                cout << "TOP = " << pq.top() << "\n";
            }
            //tasks_completed[*it] = true;
        }
        if (pq.empty() || pq.top() != index) {
            pq.push(index);
            cout << "PUSHING "<<index<<" TO THE QUEUE 2\n";
        }
    }
}

void pfd_print (ostream& out, vector<int>& ordered_ids) {
    if (ordered_ids.size() == 1) // for whatever weird reason
        out << ordered_ids[0] << "\n";
    else {
        out << *(ordered_ids.begin()) << " ";
        for (auto it = ordered_ids.begin() + 1; it != ordered_ids.end() - 1; ++it) {
            out << *it << " ";
        }
        out << *(ordered_ids.end() - 1) << "\n";
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
    vector<list<int>> tasks(num_tasks+1); // + 1 since we have no 0th task
    for (int i = 0; i < num_targets; ++i) {
        in >> s;
        pfd_read(s, tasks);
    }
    vector<int> ordered_ids;
    vector<bool> tasks_completed(num_tasks+1, false);
    pfd_eval(tasks, tasks_completed, ordered_ids);
    pfd_print(out, ordered_ids);
}