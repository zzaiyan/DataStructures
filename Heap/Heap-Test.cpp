#include "heap.h"
#include <ctime>
#include <iostream>
using namespace std;

struct HNode {
  int num = 0, cnt = 0;
};

struct Cp {
  bool operator()(HNode& a, HNode& b) {
    return a.cnt < b.cnt || (a.cnt == b.cnt && a.num < b.num);
  }
};

HNode arr[1000];
int times_cnt[1000];

int main() {
  constexpr int n = 1e7;

  times_cnt[77] = 12345;

  srand(clock());

  for (int i = 0; i < n; i++) {  // 统计出现次数
    int r = rand();
    int x = r * r % 997;
    times_cnt[x]++;
  }

  for (int i = 0; i < 1000; i++) {  // 建立数组
    // cout << times_cnt[i] << " ";
    arr[i] = HNode{i, times_cnt[i]};
  }
  cout << "\nArray Created!\n";

  auto Mhp = new Heap<HNode, Cp>(arr, 1000);  // 建立堆

  cout << "Heap Created!\n";

  int k = 20;
  while (Mhp->size() && k--) {
    cout << Mhp->pop().num << " ";
    // Mhp->pop();
  }

  cout << "\nFinish!\n";

  delete Mhp;
  return 0;
}