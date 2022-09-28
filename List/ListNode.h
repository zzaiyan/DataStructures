#pragma once
#include <iostream>

template <typename T> struct ListNode {
  T data;
  ListNode<T> *pred, *succ;

  ListNode() : pred(nullptr), succ(nullptr) { data = std::move(T{}); }
  ListNode(const T &e, ListNode<T> *p = nullptr, ListNode<T> *s = nullptr)
      : data(e), pred(p), succ(s) {}
  // ~ListNode() { std::cout << "ListNode Distruction Called\n"; }
  ListNode<T> *insertAsPred(const T &e);
  ListNode<T> *insertAsSucc(const T &e);
  static const T &remove(ListNode<T> *p);
  static void posSwap(ListNode<T> *p1, ListNode<T> *p2);
};

template <typename T> ListNode<T> *ListNode<T>::insertAsPred(const T &e) {
  ListNode<T> *x = new ListNode<T>(e, pred, this);
  pred->succ = x, pred = x;
  return x;
}

template <typename T> ListNode<T> *ListNode<T>::insertAsSucc(const T &e) {
  ListNode<T> *x = new ListNode<T>(e, this, succ);
  succ->pred = x, succ = x;
  return x;
}

template <typename T> const T &ListNode<T>::remove(ListNode<T> *p) {
  p->pred->succ = p->succ;
  p->succ->pred = p->pred;
  T temp = p->data;
  delete p;
  return temp;
}

template <typename T>
void ListNode<T>::posSwap(ListNode<T> *p1, ListNode<T> *p2) {
  bool isNear = p1->succ == p2;
  ListNode<T> *oldSucc = p1->succ;
  p1->pred->succ = p1->succ, p1->succ->pred = p1->pred; // short p1
  p1->pred = p2, p1->succ = p2->succ;       // insert p1 as p2's succ
  p1->pred->succ = p1, p1->succ->pred = p1; // too

  if (!isNear) {
    p2->pred->succ = p2->succ, p2->succ->pred = p2->pred; // short p2
    p2->succ = oldSucc, p2->pred = oldSucc->pred;         // insert p2 to oldP1
    p2->pred->succ = p2, p2->succ->pred = p2;             // too
  }
}