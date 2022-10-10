#pragma once

#include "../Vector/vector.h"

#define TTC template <typename T, typename _Cp>
#define hp Heap<T, _Cp>
#define vec Vector<T>

#define _data vec::_data
#define _size vec::_size
#define _capacity vec::_capacity

#define MinHeap(T) Heap<T, std::greater<T>>
#define MaxHeap(T) Heap<T, std::less<T>>

template <typename T, typename _Cp = std::greater<T>>
class Heap : public Vector<T> {
 protected:
  // T* _data;
  // int _size, _capacity;
  _Cp _cp;  // �ȽϺ���

  void _init(int cp = DEFAULT_SIZE, int sz = 0) { vec::_init(cp, sz); }
  void siftDown(int start, int m);  // �����㷨
  void siftUp(int start);           // �����㷨

 public:
  Heap() : vec() {}
  Heap(T* arr, int n);

  const T& top() { return _data[0]; }  // ��ȡ����Ԫ��
  T pop();                             // ɾ����СԪ��
  void push(const T& x);
};

TTC hp::Heap(T* arr, int n) : Vector<T>(arr, n) {
  // Copy from Array
  for (int i = (_size - 2) / 2; i >= 0; i--)  // �����������
    siftDown(i, _size - 1);                   // �ֲ����������»�����
}

TTC void hp::siftDown(int start, int m) {
  // printf("\nstart=%d, m=%d\n", start, m);
  int i = start, j = 2 * i + 1;  // j��i������Ůλ��
  T temp = _data[i];
  while (j <= m) {  // ����Ƿ����λ��
    if (j < m && _cp(_data[j], _data[j + 1]))
      j++;  // ��jָ������Ů�е�С��
    if (!_cp(temp, _data[j]))
      break;  // С��������
    else {    // ����С������, i, j�½�
      // printf("%d <- %d\n", _data[i], _data[j]);
      _data[i] = _data[j];
      i = j, j = 2 * j + 1;
      // printf("i=%d, j=%d\n", i, j);
    }
  }
  _data[i] = temp;  // �ط�temp���ݴ��Ԫ��
}

TTC void hp::siftUp(int start) {
  int j = start, i = (j - 1) / 2;
  T temp = _data[j];
  while (j > 0) {  // �ظ����·������ֱ���
    if (!_cp(_data[i], temp))
      break;  // �����ֵС, ������
    else {    // �������ֵ��, ����
      _data[j] = _data[i];
      j = i, i = (i - 1) / 2;
    }
  }
  _data[j] = temp;  // ����
}

TTC T hp::pop() {
  T ret = _data[0];
  _data[0] = _data[--_size];
  siftDown(0, _size);  // �������µ���Ϊ��
  return ret;          // ������СԪ��
}

TTC void hp::push(const T& x) {
  vec::push_back(x);
  siftUp(_size - 1);  // ���ϵ���
}

#undef TTC
#undef hp
#undef vec

#undef _data
#undef _size
#undef _capacity
