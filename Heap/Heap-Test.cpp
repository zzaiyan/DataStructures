#include"heap.h"
#include<iostream>
using namespace std;

int main() {
  auto hp = new Heap<int>;
  int n;
  cin>>n;
  for (int i = 1; i <= n; i++)
    hp->push_back(i);

  for (int i = 0; i < hp->size(); i++)
    cout << (*hp)[i] << " ";

  cout << endl;
  

  return 0;
}