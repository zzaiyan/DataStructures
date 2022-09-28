#pragma once
#include "../List/List.h"
#define TT template <typename T>

TT class Queue : public List<T> {
public:
  void enqueue(const T &e) { List<T>::pushBack(e); }
  T dequeue() { return List<T>::remove(List<T>::first()); }
};
