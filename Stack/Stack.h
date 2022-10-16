#pragma once
#include <iostream>
#include <vector>

#define vec std::vector<T>

template <typename T>
class Stack : public vec {
 public:
  template <typename Re>
  void push(Re&& e) {
    vec::push_back(std::forward<Re>(e));
  }  // Perfect Forward
  int size() { return vec::size(); }
  T pop() {
    T temp = vec::back();
    vec::pop_back();
    return temp;
  }

  T& top() { return vec::back(); }
};

#undef vec