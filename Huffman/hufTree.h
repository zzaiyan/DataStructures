#pragma once

#include "../Heap/heap.h"

#define TTC template <typename T, typename _Cp>
#define hp Heap<T, _Cp>

struct Cp {
  bool operator()() {}
};

TTC class HufTree : public MinHeap(T) {
 public:
  int a;
};