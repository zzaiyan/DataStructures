#include "Stack.h"
#include <iostream>
#include <string>
using namespace std;

template <typename T> void show(const Stack<T> &A) {
  for (auto i : A)
    cout << i << ' ';
  cout << endl;
}

bool match(char a, char b) {
  return (a == '(' && b == ')' || a == '[' && b == ']' ||
          a == '{' && b == '}' || a == '<' && b == '>');
}

bool pareMatch(string &str) {
  Stack<char> s;
  for (auto now : str) {
    if (s.size() && match(s.top(), now))
      s.pop();
    else
      s.push(now);
  }
  return s.empty();
}

string decToN(int base, string src) {
  Stack<int> stk;
  string ret;
  static char sign[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  auto snum = atoll(src.c_str());
  while (snum) {
    stk.push(snum % base);
    snum /= base;
  }
  while (stk.size())
    ret.push_back(sign[stk.pop()]);
  return ret;
}

bool isResonal(vector<int> vec) {
  Stack<int> stk;
  for (int i = 1, cnt = 0; i <= vec.size(); i++) {
    stk.push(i);
    while (stk.size() && stk.top() == vec[cnt])
      stk.pop(), cnt++;
  }
  return stk.size() == 0;
}

int main() {
  /*string str;
  cin >> str;
  cout << (pareMatch(str) ? "Yes\n" : "No\n");*/
  /*int base;
  string src;
  cin >> base >> src;
  cout << decToN(base, src) << endl;*/
  vector<int> vec{3, 2, 1, 4, 5, 6};
  cout << isResonal(vec) ? "Yes\n" : "No\n";
  return 0;
}