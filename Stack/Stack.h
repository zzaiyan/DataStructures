#pragma once
#include <iostream>
#include <vector>

template <typename T> class Stack : public std::vector<T> {
public:
  void push(T &&e) {
    // std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~&& push.\n";
    std::vector<T>::emplace_back(std::forward<T>(e));
  }
  const T &pop() {
    T temp = std::vector<T>[std::vector<T>::size() - 1];
    std::vector<T>::pop_back();
    return temp;
  }
};