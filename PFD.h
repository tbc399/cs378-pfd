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

/**
 * A function object that defines a binary predicate that is used to determine
 * an ordering between pairs of tasks.
 */
class TaskCompare {
    
    private:
        
        /**
         * the container to hold the relationships between tasks
         */
        vector<pair<int, int>>& relations;
        
        /**
         * Used by operator() to determine if one task precedes another
         * @param lhs
         * @param rhs
         * @return returns true if rhs preceds lhs
         */
        bool precedes (int lhs, int rhs);
        
    public:
        
        /**
         * The only constructor for this function object
         * @param relations the predefined relationships between tasks
         */
        TaskCompare (vector<pair<int, int>>& relations);
        
        /**
         * Used to test two tasks against each other
         * @param lhs
         * @param rhs
         * @return returns true if rhs precedes lhs in the defined ordering
         */
        bool operator() (int lhs, int rhs);
};

/**
 * Reads in a single line describing a target and it's dependencies
 * @param line a single line from the input file
 * @param relations an output vector to put list of pairs of tasks
 * that defines the ordering between them
 */
void pfd_read (const string& line, vector<pair<int,int>>& relations);

/**
 *  Handles the ordering of the tasks based on the task relationships
 *  specified in the relations vector
 *  @param num_tasks the number of tasks to be ordered within [1, 100]
 *  @param relations the list of pairs of tasks that defines the
 *  ordering between them
 *  @param ordered_tasks the output vector to store the sorted tasks in
 */
void pfd_eval (int num_tasks, vector<pair<int,int>>& relations, vector<int>& ordered_tasks);

/**
 * Writes out all the elements from ordered_tasks into
 * the ostream reference starting from the beginning of the
 * vector
 * @param out an output stream to write to
 * @param ordered_tasks the elements to write out to the stream
 */
void pfd_print (ostream& out, vector<int>& ordered_tasks);

/**
 * Calls pfd_read(), pfd_eval() and pfd_print()
 * using the input it receives from istream
 * @param in the input stream for the dependencies
 * @param out the output stream to write the task orders to
 */
void pfd_solve (istream& in, ostream& out);

#endif