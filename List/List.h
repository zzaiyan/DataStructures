#pragma once
#include "ListNode.h"

template <typename T> class List {
  int _size;
  ListNode<T> *header, *trailer;

protected:
  void _init();

public:
  List() { _init(); }
  List(ListNode<T> *p, int n);
  List(const List<T> &L);
  ~List();
  // ���ظ�ֵ
  List<T> &operator=(const List<T> &L);
  // ������ĩ�ڵ�
  ListNode<T> *first() const { return header->succ; }
  ListNode<T> *last() const { return trailer->pred; }
  ListNode<T> *begin() const { return header->succ; }
  ListNode<T> *end() const { return trailer; }
  // ����Ԫ�ظ���
  int size() { return _size; }
  // ����p��n����ǰ�������һ��ֵΪe�Ľڵ�
  ListNode<T> *find(const T &e, int n, ListNode<T> *p);
  // ����p��n�����������һ��ֵΪe�Ľڵ�
  ListNode<T> *find(const T &e, ListNode<T> *p, int n);
  // ����p��n����ǰ�������һ��������e�Ľڵ�
  ListNode<T> *search(const T &e, int n, ListNode<T> *p);
  // ����p��n�����������һ��������e�Ľڵ�
  ListNode<T> *search(const T &e, ListNode<T> *p, int n);
  // ǰ��
  ListNode<T> *insertBefore(ListNode<T> *p, const T &e);
  // ���
  ListNode<T> *insertAfter(ListNode<T> *p, const T &e);
  // ��β
  ListNode<T> *pushFront(const T &e);
  // β��
  ListNode<T> *pushBack(const T &e);
  // ��ɾ
  T &popFront() { return remove(0); }
  // ĩɾ
  T &popBack() { return remove(_size - 1); }
  // ѭ�ȷ���
  T &operator[](int r);
  // ���ƽڵ�(���ڿ�������or��ֵ)
  void copyNodes(ListNode<T> *p, int n);
  // ɾ���ڵ� ������ֵ
  const T &remove(ListNode<T> *p);
  // �������
  int clear();
  // Ψһ��
  int deduplicate();
  // Ψһ�� - ����
  int uniquify();
  // ���� (ʼ��p��n������Ԫ��)
  void selSort(ListNode<T> *p, int n);
  void selSort();
  void insSort(ListNode<T> *p, int n);
  void insSort();
  // �������ֵ
  ListNode<T> *selMax(ListNode<T> *p, int n);
  ListNode<T> *selMax();
};

template <typename T> List<T>::List(ListNode<T> *p, int n) {
  _init();
  copyNodes(p, n);
}

template <typename T> List<T>::List(const List<T> &L) {
  _init();
  copyNodes(L.header->succ, L._size);
}

template <typename T> List<T>::~List() {
  clear();
  delete header;
  delete trailer;
}

template <typename T> List<T> &List<T>::operator=(const List<T> &L) {
  clear();
  copyNodes(L.header->succ, L._size);
  return *this;
}

template <typename T> void List<T>::_init() {
  header = new ListNode<T>;
  trailer = new ListNode<T>;
  header->succ = trailer;
  trailer->pred = header;
  _size = 0;
}

template <typename T> T &List<T>::operator[](int r) {
  ListNode<T> *p = first();
  while (r-- > 0)
    p = p->succ;
  return p->data;
}

template <typename T> void List<T>::copyNodes(ListNode<T> *p, int n) {
  while (n--) {
    pushBack(p->data);
    p = p->succ;
  }
}

template <typename T>
ListNode<T> *List<T>::find(const T &e, int n, ListNode<T> *p) {
  while (n-- > 0) {
    p = p->pred;
    if (e == p->data)
      return p;
  }
  return nullptr;
}

template <typename T>
ListNode<T> *List<T>::find(const T &e, ListNode<T> *p, int n) {
  while (n-- > 0) {
    p = p->succ;
    if (e == p->data)
      return p;
  }
  return nullptr;
}

template <typename T>
ListNode<T> *List<T>::search(const T &e, int n, ListNode<T> *p) {
  do {
    p = p->pred, n--;
  }                                  // R -> L
  while ((-1 < n) && (e < p->data)); // compare until Hit or Range-out
  return p;
}

template <typename T>
ListNode<T> *List<T>::search(const T &e, ListNode<T> *p, int n) {
  for (int i = 0; i < n; i++)
    p = p->succ;
  return search(e, n, p);
}

template <typename T>
ListNode<T> *List<T>::insertBefore(ListNode<T> *p, const T &e) {
  _size++;
  return p->insertAsPred(e);
}

template <typename T>
ListNode<T> *List<T>::insertAfter(ListNode<T> *p, const T &e) {
  _size++;
  return p->insertAsSucc(e);
}

template <typename T> ListNode<T> *List<T>::pushFront(const T &e) {
  return insertAfter(header, e);
}

template <typename T> ListNode<T> *List<T>::pushBack(const T &e) {
  return insertBefore(trailer, e);
}

template <typename T> const T &List<T>::remove(ListNode<T> *p) {
  _size--;
  return std::move(ListNode<T>::remove(p));
}

template <typename T> int List<T>::clear() {
  int oldSize = _size;
  while (_size > 0)
    remove(header->succ);
  return oldSize;
}

template <typename T> int List<T>::deduplicate() {
  if (_size < 2)
    return 0;
  int oldSize = _size, r = 1;
  auto p = first();
  while (p->succ != trailer) {
    p = p->succ;
    auto q = find(p->data, r, p);
    q ? remove(q) : r++;
  }
  return oldSize - _size;
}

template <typename T> int List<T>::uniquify() {
  if (_size < 2)
    return 0;
  int oldSize = _size;
  ListNode<T> *p = first(), *q;
  while (p->succ != trailer) {
    q = p->succ;
    if (q->data != p->data)
      p = q; // if diff, continue
    else
      remove(q); // if same, remove(q)
  }
  return oldSize - _size;
}

template <typename T> void List<T>::selSort(ListNode<T> *p, int n) {
  if (n < 2) // skip the plain cases
    return;
  ListNode<T> *head = p->pred, *tail = p;
  for (int i = 0; i < n; i++)
    tail = tail->succ;
  for (; n > 1; n--) {
    // Type 1:
    // delete and rebuild the Nodes
    //
    // insertBefore(tail, remove(selMax(head->succ, n)));

    // Type 2:
    // swap the two's value
    //
    // auto m = selMax(head->succ, n);
    // T temp = tail->pred->data;
    // tail->pred->data = m->data;
    // m->data = temp;

    // Type 3:  Optimal Sln
    // swap the Nodes via reconnect their lines
    //
    ListNode<T>::posSwap(tail->pred, selMax(head->succ, n));

    tail = tail->pred;
  }
}

template <typename T> ListNode<T> *List<T>::selMax(ListNode<T> *p, int n) {
  ListNode<T> *m = p;
  while (--n) {
    p = p->succ;
    // once Greater or Equal, update m.
    if (!(p->data < m->data))
      m = p;
  }
  return m;
}

template <typename T> void List<T>::selSort() { selSort(header->succ, _size); }

template <typename T> ListNode<T> *List<T>::selMax() {
  return selMax(header->succ, _size);
}

template <typename T> void List<T>::insSort(ListNode<T> *p, int n) {
  if (n < 2) // skip the plain cases
    return;
  for (int r = 0; r < n; r++) {
    // Just reconnect the lines to move the Node,
    // which is most Efficient.
    ListNode<T> *pos = search(p->data, r, p);
    auto now = p;
    p = p->succ;
    now->pred->succ = now->succ, now->succ->pred = now->pred; // short now
    now->pred = pos, now->succ = pos->succ;       // insert now as pos's succ
    now->pred->succ = now, now->succ->pred = now; // too
  }
}

template <typename T> void List<T>::insSort() { insSort(header->succ, _size); }