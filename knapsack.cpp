#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;

// knapsack problem for {0,1}
vector<vector<int> > knapsackHelperZeroOne(
  vector<int> w_vec,
  vector<int> v_vec,
  int max_weight) {
  vector<vector<int> > v;
  vector<int> temp;
  for(int i = 0; i <= max_weight; i++){
    temp.push_back(0);
  }
  for (int i = 0; i <= w_vec.size(); i++) {
    v.push_back(temp);
  }
  int w = 1;
  while (w <= max_weight) {
    int i = 1;
    while (i <= w_vec.size()) {
        int result = 0;
        if (w-w_vec[i-1] < 0) {
          result = max(v[i-1][w], 0);
        } else {
          result = max(v[i-1][w], v_vec[i-1]+v[i-1][w-w_vec[i-1]]);
        }
        v[i][w] = result;
        i++;
      }
    w++;
  }
  return v;
}

// knapsack problem for {0,1,2,...}
vector<vector<int> > knapsackHelperMulti(
  vector<int> w_vec,
  vector<int> v_vec,
  int max_weight) {
  vector<vector<int> > v;
  vector<int> temp;
  for (int i = 0; i <= max_weight; i++) {
    temp.push_back(0);
  }
  for (int i = 0; i <= w_vec.size(); i++) {
    v.push_back(temp);
  }
  int w = 1;
  while (w <= max_weight) {
    int i = 1;
    while (i <= w_vec.size()) {
      int max_result = -1000;
      for (int k = 0; k <= w/w_vec[i-1]; k++) {
        int rhs = v[i-1][w-(k*w_vec[i-1])];
        int lhs = k*v_vec[i-1];
        max_result = max(max_result, lhs+rhs);
      }
      v[i][w] = max_result;
      i++;
    }
    w++;
  }
  return v;
}

int main() {
  // 3.1 ------------------------------------------------------------------------
  // from midterm 2019
  // vector<int> v_i;
  // v_i.push_back(5); v_i.push_back(9); v_i.push_back(11); v_i.push_back(8);
  // vector<int> w_i;
  // w_i.push_back(2); w_i.push_back(4); w_i.push_back(5); w_i.push_back(3);
  // vector<vector<int> > res = knapsackHelperZeroOne(w_i, v_i,11);

  // from lecture 6_knapsack (29/39)
  // vector<int> v_i;
  // v_i.push_back(2); v_i.push_back(5); v_i.push_back(7); v_i.push_back(8); v_i.push_back(10);
  // vector<int> w_i;
  // w_i.push_back(1); w_i.push_back(3); w_i.push_back(4); w_i.push_back(7); w_i.push_back(8);
  // vector<vector<int> > res = knapsackHelperZeroOne(w_i, v_i,10);

  // assignment question 3.1
  // vector<int> v_i;
  // v_i.push_back(7); v_i.push_back(5); v_i.push_back(6); v_i.push_back(4);
  // vector<int> w_i;
  // w_i.push_back(6); w_i.push_back(7); w_i.push_back(4); w_i.push_back(3);
  // vector<vector<int> > res = knapsackHelperZeroOne(w_i, v_i,12);

  // ----------------------------------------------------------------------------
  // ----------------------------------------------------------------------------
  // 3.2 ------------------------------------------------------------------------

  // from lecture 6_knapsack (29/39)
  // vector<int> v_i;
  // v_i.push_back(2); v_i.push_back(5); v_i.push_back(9); v_i.push_back(1);
  // vector<int> w_i;
  // w_i.push_back(1); w_i.push_back(3); w_i.push_back(4); w_i.push_back(7);
  // vector<vector<int> > res = knapsackHelperMulti(w_i, v_i,10);

  // from midterm 2019
  // vector<int> v_i;
  // v_i.push_back(5); v_i.push_back(9); v_i.push_back(11); v_i.push_back(8);
  // vector<int> w_i;
  // w_i.push_back(2); w_i.push_back(4); w_i.push_back(5); w_i.push_back(3);
  // vector<vector<int> > res = knapsackHelperMulti(w_i, v_i,11);

  // assignment question 3.2
  vector<int> v_i;
  v_i.push_back(7); v_i.push_back(5); v_i.push_back(6); v_i.push_back(4);
  vector<int> w_i;
  w_i.push_back(6); w_i.push_back(7); w_i.push_back(4); w_i.push_back(3);
  vector<vector<int> > res = knapsackHelperMulti(w_i, v_i,12);

  for (int i = 0; i < res.size(); i++) {
    for (int j = 0; j < res[0].size(); j++) {
      cout << res[i][j] << "    ";
    }
    cout << endl;
  }
  return 0;
}
