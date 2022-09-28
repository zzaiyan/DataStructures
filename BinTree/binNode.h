#pragma once

#define TT template <typename T>
#define Node BinNode<T>
#define Tree BinTree<T>

TT struct BinNode {
  Node *parent, *lChild, *rChild;
  T data;
  int height;
  BinNode()
      : parent(nullptr), lChild(nullptr), rChild(nullptr), height(0),
        data(T{}) {}
  BinNode(const T &e, Node *p = nullptr)
      : data(e), parent(p), lChild(nullptr), rChild(nullptr), height(0) {}
  int size();
  Node *insertAsLC(const T &x);
  Node *insertAsRC(const T &x);
};

TT int Node::size() {
  int cnt = 1;
  if (lChild)
    cnt += lChild->size();
  if (rChild)
    cnt += rChild->size();
  return cnt;
}

TT Node *Node::insertAsLC(const T &x) {
  lChild = new Node(x, this);
  return lChild;
}

TT Node *Node::insertAsRC(const T &x) {
  rChild = new Node(x, this);
  return rChild;
}

#undef TT
#undef Node
#undef Tree