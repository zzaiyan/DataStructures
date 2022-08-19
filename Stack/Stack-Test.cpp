#include "Stack.h"
#include <iostream>
#include <string>
using namespace std;

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
  return s.size() == 0;
}

int main() {
  string str;
  cin >> str;
  cout << (pareMatch(str) ? "Yes\n" : "No\n");
  return 0;
}