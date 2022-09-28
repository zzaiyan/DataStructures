#include "Queue.h"
#include <iostream>
using namespace std;

int main() {
  Queue<int> que;
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
    que.enqueue(i);
  for (int i = 1; i <= n; i++)
    cout << que.dequeue() << ' ';
}