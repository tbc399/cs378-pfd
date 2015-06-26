// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <vector>
#include <queue>
#include <list>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

class TaskCompare {
    private:
        vector<pair<int, int>>& relations;
        bool precedes (int lhs, int rhs);
    public:
        TaskCompare (vector<pair<int, int>>& relations);
        bool operator() (int lhs, int rhs);
};

TaskCompare::TaskCompare (vector<pair<int, int>>& task_relations) :
                          relations(task_relations) {}
    

bool TaskCompare::operator() (int lhs, int rhs) {
    if (precedes(lhs, rhs))
        return false;
    else if (precedes(rhs, lhs))
        return true;
    else
        return lhs > rhs;
}

bool TaskCompare::precedes (int lhs, int rhs) {
    for (pair<int, int>& p : relations) {
        if (p.first == lhs) {
            if (p.second == rhs) {
                return true;
            } else {
                if (precedes(p.second, rhs))
                    return true;
            }
        }
    }
    return false;
}

void pfd_read (const string& line, vector<pair<int, int>>& relations) {
    istringstream iss(line);
    unsigned int target_id;
    iss >> target_id;
    unsigned int ibuf;
    iss >> ibuf;
    for (int i = ibuf; i > 0; --i) {
        iss >> ibuf;
        relations.push_back(make_pair(ibuf, target_id));
    }
}

void pfd_eval (int num_tasks, vector<pair<int,int>>& relations, vector<int>& ordered_tasks) {
    TaskCompare tc(relations);
    priority_queue<int,vector<int>,TaskCompare> pq(tc);
    for (int i = 1; i <= num_tasks; ++i) {
        pq.push(i);
    }
    while (!pq.empty()) {
            ordered_tasks.push_back(pq.top());
            pq.pop();
    }
}

void pfd_print (ostream& out, vector<int>& ordered_tasks) {
    if (ordered_tasks.size() == 1){ // for whatever weird reason
        out << ordered_tasks[0] << "\n";
    } else {
        vector<int>::iterator it;
        for (it = ordered_tasks.begin(); it < ordered_tasks.end() - 1; ++it)
            out << *it << " ";
        out << *it << "\n";
    }
}

void pfd_solve (istream& in, ostream& out) {
    string s;
    getline(in, s);
    istringstream iss(s); // need to get the input dimensions  
    int num_tasks = 0;
    iss >> num_tasks;
    int num_targets = 0;
    iss >> num_targets;
    vector<pair<int,int>> relations;
    for (int i = 0; i < num_targets; ++i) {
        getline(in, s);
        pfd_read(s, relations);
    }
    vector<int> ordered_tasks;
    pfd_eval(num_tasks, relations, ordered_tasks);
    pfd_print(out, ordered_tasks);
}

// ----
// main
// ----

int main () {
    using namespace std;
    pfd_solve(cin, cout);
    return 0;}