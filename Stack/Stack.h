#pragma once
#include <iostream>
#include <vector>
#define vec std::vector<T>

template <typename T> class Stack : public std::vector<T> {
public:
  template <typename Re> void push(Re &&e) {
    vec::push_back(std::forward<Re>(e));
  } // Perfect Forward

  const T &pop() {
    T temp = vec::operator[](vec::size() - 1);
    std::vector<T>::pop_back();
    return temp;
  }

  T &top() { return vec::operator[](vec::size() - 1); }
};
