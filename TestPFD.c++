#define private public // to get at the private members of Task

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <map>

#include <gtest/gtest.h>

#include "PFD.h"

using namespace std;

TEST(PFDFixture, task_precedes_1) {
    Task t1(3);
    Task t2(2);
    Task t3(7);
    t2.addDependent(t3);
    t1.addDependent(t2);
    Task t4(4);
    ASSERT_TRUE(Task::precedes(t1,t4));
}

TEST(PFDFixture, task_precedes_2) {
    Task t1(3);
    Task t2(2);
    Task t3(7);
    t2.addDependent(t3);
    t1.addDependent(t2);
    ASSERT_TRUE(Task::precedes(t1,t3));
}

TEST(PFDFixture, task_precedes_3) {
    Task t1(3);
    Task t2(2);
    Task t3(7);
    t2.addDependent(t3);
    t1.addDependent(t2);
    ASSERT_FALSE(Task::precedes(t3,t1));
}

TEST(PFDFixture, task_addDependent_1) {
    Task t1(3);
    Task t2(9);
    t1.addDependent(t2);
    bool success = true;
    try {
        t1.dependents.at(9);
    } catch (out_of_range& oor) {
        success = false;
    }
    ASSERT_TRUE(success);
}

TEST(PFDFixture, task_addDependent_2) {
    Task t1(3);
    Task t2(9);
    Task t3(45);
    t1.addDependent(t2);
    t1.addDependent(t3);
    bool success = true;
    try {
        t1.dependents.at(9);
        t1.dependents.at(45);
    } catch (out_of_range& oor) {
        success = false;
    }
    ASSERT_TRUE(success);
}

TEST(PFDFixture, task_addDependent_3) {
    Task t1(3);
    Task t2(9);
    Task t3(45);
    t1.addDependent(t2);
    t2.addDependent(t3);
    bool success = true;
    try {
        t1.dependents.at(9);
        t2.dependents.at(45);
    } catch (out_of_range& oor) {
        success = false;
    }
    ASSERT_TRUE(success);
}

TEST(PFDFixture, task_greater_1) {
    Task t1(3);
    Task t2(2);
    Task t3(7);
    t2.addDependent(t3);
    t1.addDependent(t2);
    Task t4(4);
    ASSERT_TRUE(t1 > t4);
}

TEST(PFDFixture, task_greater_2) {
    Task t1(3);
    Task t2(2);
    Task t3(7);
    t2.addDependent(t3);
    t1.addDependent(t2);
    ASSERT_TRUE(t1 > t3);
}

TEST(PFDFixture, task_greater_3) {
    Task t1(3);
    Task t2(2);
    Task t3(7);
    t2.addDependent(t3);
    t1.addDependent(t2);
    Task t4(1);
    ASSERT_FALSE(t1 > t4);
}

TEST(PFDFixture, task_equals_1) {
    Task t1(4);
    Task t2(7);
    ASSERT_FALSE(t1 == t2);
}

TEST(PFDFixture, task_equals_2) {
    Task t1(4);
    Task t2(4);
    ASSERT_TRUE(t1 == t2);
}

TEST(PFDFixture, task_equals_3) {
    Task t1(4);
    ASSERT_TRUE(t1 == t1);
}

TEST(PFDFixture, read_1) {
    string s("3 2 1 5\n");
    map<unsigned int, Task> v;
    pfd_read(s, v);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[0].id, 3);
    ASSERT_EQ(v[1].id, 1);
    ASSERT_EQ(v[2].id, 5);
}

TEST(PFDFixture, read_2) {
    string s("2 2 5 3\n");
    map<unsigned int, Task> v;
    pfd_read(s, v);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[0].id, 2);
    ASSERT_EQ(v[1].id, 5);
    ASSERT_EQ(v[2].id, 3);
}

TEST(PFDFixture, read_3) {
    string s("5 1 1\n");
    map<unsigned int, Task> v;
    pfd_read(s, v);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v[0].id, 5);
    ASSERT_EQ(v[1].id, 1);
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