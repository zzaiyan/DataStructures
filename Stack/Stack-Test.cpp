#include "Stack.h"
#include <iostream>
using namespace std;

int cnt = 0;

class Test {
public:
  int val;

  ~Test() { cout << "----------------desruction, val = " << val << endl; }
  Test() : val(0) {
    cout << "default construct with ";
    cout << "val = " << val << endl;
  }
  Test(const int &e) : val(e) {
    cout << "common construct with ";
    cout << "val = " << val << endl;
  }
  Test(const Test &T) : val(T.val) {
    cout << "& copy consruct with ";
    cout << "val = " << val << endl;
    cout << "copy time: " << ++cnt << endl;
  }
};

int main() {
  Stack<Test> S;
  // vector<Test> S;
  int n;
  cin >> n;
  S.reserve(n);
  cout << S.capacity() << endl;
  for (int i = 0; i < n; i++) {
    int t = i + 1;
    S.push(t);
    // cout << t << " ";
  }
  cout << "----------------------ending build\n";
  // while (S.size())
  //   S.pop();

  cout << endl;
  return 0;
}