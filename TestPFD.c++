#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <queue>
#include <algorithm>
#include <map>

#include <gtest/gtest.h>

#include "PFD.h"

using namespace std;

TEST(PFDFixture, task_getInstance_1) {
    Task& t1 = Task::getInstance(5);
    ASSERT_EQ(t1.getId(), 5);
}

TEST(PFDFixture, task_getInstance_2) {
    Task& t1 = Task::getInstance(5);
    Task& t2 = Task::getInstance(5);
    ASSERT_EQ(&t1, &t2);
}

TEST(PFDFixture, task_getInstance_3) {
    Task& t1 = Task::getInstance(5);
    t1.completed();
    Task& t2 = Task::getInstance(5);
    ASSERT_TRUE(!t2);
}

TEST(PFDFixture, task_bool_1) {
    Task& t1 = Task::getInstance(3);
    ASSERT_TRUE(!!t1);
}

TEST(PFDFixture, task_bool_2) {
    Task& t1 = Task::getInstance(3);
    t1.completed();
    ASSERT_TRUE(!t1);
}

TEST(PFDFixture, task_completed_1) {
    Task& t = Task::getInstance(2);
    t.completed();
    ASSERT_TRUE(!t);
}

TEST(PFDFixture, task_completed_2) {
    Task& t = Task::getInstance(2);
    Task::getInstance(2).completed();
    ASSERT_TRUE(!t);
}

TEST(PFDFixture, task_completed_3) {
    Task& t1 = Task::getInstance(2);
    Task& t2 = Task::getInstance(2);
    t1.completed();
    ASSERT_TRUE(!t2);
}

TEST(PFDFixture, task_getId_1) {
    Task& t = Task::getInstance(1);
    ASSERT_EQ(t.getId(), 1);
}

TEST(PFDFixture, task_getId_2) {
    Task t;
    ASSERT_EQ(t.getId(), 0);
}

TEST(PFDFixture, task_getId_3) {
    ASSERT_EQ(Task::getInstance(67).getId(), 67);
}

TEST(PFDFixture, read_1) {
    string s("3 2 1 5\n");
    vector<list<int>> v(4);
    pfd_read(s, v);
    ASSERT_EQ(v[3].size(), 2);
    list<int>::iterator it = v[3].begin();
    ASSERT_EQ(*it, 1);
    ASSERT_EQ(*(++it), 5);
}

TEST(PFDFixture, read_2) {
    string s("2 2 5 3\n");
    vector<list<int>> v(3);
    pfd_read(s, v);
    ASSERT_EQ(v[2].size(), 2);
    list<int>::iterator it = v[2].begin();
    ASSERT_EQ(*it, 5);
    ASSERT_EQ(*(++it), 3);
}

TEST(PFDFixture, read_3) {
    string s("5 1 1\n");
    vector<list<int>> v(6);
    pfd_read(s, v);
    ASSERT_EQ(v[5].size(), 1);
    list<int>::iterator it = v[5].begin();
    ASSERT_EQ(*it, 1);
}

TEST(PFDFixture, eval_1) {
    vector<list<int>> v(6);
    list<int> l1{1, 5};
    v[3] = l1;
    list<int> l2{5, 3};
    v[2] = l2;
    list<int> l3{3};
    v[4] = l3;
    list<int> l4{1};
    v[5] = l4;
    vector<int> o;
    vector<bool> vb(6, false);
    pfd_eval(v, vb, o);
    vector<int> real_o{1, 5, 3, 2, 4};
    copy(o.begin(), o.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    ASSERT_TRUE(equal(o.begin(), o.end(), real_o.begin()));
}

TEST(PFDFixture, eval_2) {
    vector<list<int>> v(7);
    list<int> l1{6, 1};
    v[5] = l1;
    list<int> l2{1, 5};
    v[3] = l2;
    list<int> l4{5, 3};
    v[2] = l4;
    list<int> l3{3};
    v[4] = l3;
    vector<int> o;
    vector<bool> vb(7, false);
    pfd_eval(v, vb, o);
    vector<int> real_o{1, 6, 5, 3, 2, 4};
    copy(o.begin(), o.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    ASSERT_TRUE(equal(o.begin(), o.end(), real_o.begin()));
}

TEST(PFDFixture, eval_3) {
    vector<list<int>> v(7);
    list<int> l2{1, 5};
    v[3] = l2;
    list<int> l1{1};
    v[5] = l1;
    list<int> l4{5, 3};
    v[2] = l4;
    list<int> l3{3, 6};
    v[4] = l3;
    vector<int> o;
    vector<bool> vb(7, false);
    pfd_eval(v, vb, o);
    vector<int> real_o{1, 5, 3, 2, 6, 4};
    copy(o.begin(), o.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    ASSERT_TRUE(equal(o.begin(), o.end(), real_o.begin()));
}
/*
TEST(PFDFixture, eval_help_1) {
    vector<list<int>> v(7);
    priority_queue<int, vector<int>, greater<int>> pq;
    list<int> l2{1, 5};
    v[3] = l2;
    list<int> l1{1};
    v[5] = l1;
    list<int> l4{5, 3};
    v[2] = l4;
    list<int> l3{3, 6};
    v[4] = l3;
    pfd_eval_help(1, v, pq);
    
}

TEST(PFDFixture, eval_help_2) {
    
}

TEST(PFDFixture, eval_help_3) {
    
}
*/
TEST(PFDFixture, print_1) {
    ostringstream out;
    vector<int> v{1, 2, 5, 4, 2};
    pfd_print(out, v);
    ASSERT_EQ("1 2 5 4 2\n", out.str());
}

TEST(PFDFixture, print_2) {
    ostringstream out;
    vector<int> v{1, 2};
    pfd_print(out, v);
    ASSERT_EQ("1 2\n", out.str());
}

TEST(PFDFixture, print_3) {
    ostringstream out;
    vector<int> v{1};
    pfd_print(out, v);
    ASSERT_EQ("1\n", out.str());
}

TEST(PFDFixture, solve_1) {
    string s("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    istringstream iss(s);
    ostringstream oss;
    pfd_solve(iss, oss);
    ASSERT_EQ(oss.str(), "1 5 3 2 4\n");
}

TEST(PFDFixture, solve_2) {
    string s("6 4\n3 2 1 5\n2 2 5 3\n4 2 3 6\n5 1 1\n");
    istringstream iss(s);
    ostringstream oss;
    pfd_solve(iss, oss);
    ASSERT_EQ(oss.str(), "1 5 3 2 6 4\n");
}

TEST(PFDFixture, solve_3) {
    string s("6 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 2 6 1\n");
    istringstream iss(s);
    ostringstream oss;
    pfd_solve(iss, oss);
    ASSERT_EQ(oss.str(), "1 6 5 3 2 4\n");
}