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

int main() {
  string str;
  cin >> str;
  cout << (pareMatch(str) ? "Yes\n" : "No\n");

  return 0;
}