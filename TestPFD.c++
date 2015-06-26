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

TEST(PFDFixture, TaskCompare_operator_1) {
    vector<pair<int,int>> v;
    v.push_back(make_pair(3,2));
    v.push_back(make_pair(5,2));
    v.push_back(make_pair(5,3));
    v.push_back(make_pair(1,3));
    v.push_back(make_pair(3,4));
    v.push_back(make_pair(1,5));
    TaskCompare comes_after(v);
    ASSERT_TRUE(comes_after(5,1));
}

TEST(PFDFixture, TaskCompare_operator_2) {
    vector<pair<int,int>> v;
    v.push_back(make_pair(3,2));
    v.push_back(make_pair(5,2));
    v.push_back(make_pair(5,3));
    v.push_back(make_pair(1,3));
    v.push_back(make_pair(3,4));
    v.push_back(make_pair(1,5));
    TaskCompare comes_after(v);
    ASSERT_FALSE(comes_after(1,2));
}

TEST(PFDFixture, TaskCompare_operator_3) {
    vector<pair<int,int>> v;
    v.push_back(make_pair(3,2));
    v.push_back(make_pair(5,2));
    v.push_back(make_pair(5,3));
    v.push_back(make_pair(1,3));
    v.push_back(make_pair(3,4));
    v.push_back(make_pair(1,5));
    TaskCompare comes_after(v);
    ASSERT_TRUE(comes_after(4,2));
}

TEST(PFDFixture, read_1) {
    string s("3 2 1 5\n");
    vector<pair<int,int>> v;
    pfd_read(s, v);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v[0], make_pair(1, 3));
    ASSERT_EQ(v[1], make_pair(5, 3));
}

TEST(PFDFixture, read_2) {
    string s("2 2 5 3\n");
    vector<pair<int,int>> v;
    pfd_read(s, v);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v[0], make_pair(5, 2));
    ASSERT_EQ(v[1], make_pair(3, 2));
}

TEST(PFDFixture, read_3) {
    string s("5 1 1\n");
    vector<pair<int,int>> v;
    pfd_read(s, v);
    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(v[0], make_pair(1, 5));
}

TEST(PFDFixture, eval_1) {
    vector<pair<int,int>> v;
    v.push_back(make_pair(3,2));
    v.push_back(make_pair(5,2));
    v.push_back(make_pair(5,3));
    v.push_back(make_pair(1,3));
    v.push_back(make_pair(3,4));
    v.push_back(make_pair(1,5));
    vector<int> o;
    pfd_eval(5, v, o);
    vector<int> real_o{1, 5, 3, 2, 4};
    ASSERT_TRUE(equal(o.begin(), o.end(), real_o.begin()));
}

TEST(PFDFixture, eval_2) {
    vector<pair<int,int>> v;
    v.push_back(make_pair(3,2));
    v.push_back(make_pair(5,2));
    v.push_back(make_pair(5,3));
    v.push_back(make_pair(1,3));
    v.push_back(make_pair(3,4));
    v.push_back(make_pair(1,5));
    v.push_back(make_pair(6,5));
    vector<int> o;
    pfd_eval(6, v, o);
    vector<int> real_o{1, 6, 5, 3, 2, 4};
    ASSERT_TRUE(equal(o.begin(), o.end(), real_o.begin()));
}

TEST(PFDFixture, eval_3) {
    vector<pair<int,int>> v;
    v.push_back(make_pair(3,2));
    v.push_back(make_pair(5,2));
    v.push_back(make_pair(5,3));
    v.push_back(make_pair(1,3));
    v.push_back(make_pair(3,4));
    v.push_back(make_pair(1,5));
    v.push_back(make_pair(6,4));
    vector<int> o;
    pfd_eval(6, v, o);
    vector<int> real_o{1, 5, 3, 2, 6, 4};
    ASSERT_TRUE(equal(o.begin(), o.end(), real_o.begin()));
}

TEST(PFDFixture, print_1) {
    ostringstream out;
    vector<int> o{99, 12, 7, 3};
    pfd_print(out, o);
    ASSERT_EQ("99 12 7 3\n", out.str());
}

TEST(PFDFixture, print_2) {
    ostringstream out;
    vector<int> o{99};
    pfd_print(out, o);
    ASSERT_EQ("99\n", out.str());
}

TEST(PFDFixture, print_3) {
    ostringstream out;
    vector<int> o{3, 7};
    pfd_print(out, o);
    ASSERT_EQ("3 7\n", out.str());
}

TEST(PFDFixture, solve_1) {
    string s("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    istringstream iss(s);
    ostringstream oss;
    pfd_solve(iss, oss);
    ASSERT_EQ("1 5 3 2 4\n", oss.str());
}

TEST(PFDFixture, solve_2) {
    string s("6 4\n3 2 1 5\n2 2 5 3\n4 2 3 6\n5 1 1\n");
    istringstream iss(s);
    ostringstream oss;
    pfd_solve(iss, oss);
    ASSERT_EQ("1 5 3 2 6 4\n", oss.str());
}

TEST(PFDFixture, solve_3) {
    string s("6 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 2 6 1\n");
    istringstream iss(s);
    ostringstream oss;
    pfd_solve(iss, oss);
    ASSERT_EQ("1 6 5 3 2 4\n", oss.str());
}