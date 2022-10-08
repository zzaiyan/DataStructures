#pragma once

#include <algorithm>
#include "../Queue/Queue.h"
#include "../Stack/Stack.h"
#include "binNode.h"

#define TT template <typename T>
#define Node BinNode<T>
#define Tree BinTree<T>

#define stature(p) ((p) ? (p)->height : -1)

TT class BinTree {
  Node* _root;
  int _size, _height;
  // 内部接口
  void destroy(Node*& p);
  void remove(Node* p) { delete p; }
  // void createBinTree();

 public:
  // 状态接口
  int size() const { return _size; }
  bool isEmpty() const { return root == nullptr; }
  int updateHeight(Node* p);
  void updateHAbove(Node* p);
  Node* root() const { return _root; }
  Node* parent(Node* p) { return p->parent; }

  BinTree() : _root(new Node), _size(1), _height(0) {}  // 默认构造
  BinTree(const Tree& t);                               // 拷贝构造
  ~BinTree() { destroy(_root); }                        // 析构

  // 操作接口
  Node* insertAsLC(Node* p, const T& e);  // 插入左节点
  Node* insertAsRC(Node* p, const T& e);  // 插入右节点

  void removeLT(Node* p);  // 移除左子树
  void removeRT(Node* p);  // 移除右子树
  void removeT(Node*& p);  // 移除子树
  // 递归遍历
  void preOrder(Node* p, void (*visit)(Node* t));
  void inOrder(Node* p, void (*visit)(Node* t));
  void postOrder(Node* p, void (*visit)(Node* t));
  // 迭代遍历
  void preOrderX(Node* p, void (*visit)(Node* t));
  void inOrderX(Node* p, void (*visit)(Node* t));
  void postOrderX(Node* p, void (*visit)(Node* t));
  // 层次遍历
  void levelOrder(Node* p, void (*visit)(Node* t));
};

TT void Tree::destroy(Node*& p) {
  if (p) {
    destroy(p->lChild);
    destroy(p->rChild);
    delete p;
    p = nullptr;
  }
}

TT int Tree::updateHeight(Node* p) {
  return p->height = 1 + std::max(stature(p->lChild), stature(p->rChild));
}

TT void Tree::updateHAbove(Node* p) {
  while (p) {
    // if (p->height == updateHeight(p))
    //   break;
    updateHeight(p);
    p = p->parent;
  }
}

TT Node* Tree::insertAsLC(Node* p, const T& e) {
  _size++;
  p->insertAsLC(e);
  updateHAbove(p);
  return p->lChild;
}

TT Node* Tree::insertAsRC(Node* p, const T& e) {
  _size++;
  p->insertAsRC(e);
  updateHAbove(p);
  return p->rChild;
}

TT void Tree::removeLT(Node* p) {
  destroy(p->lChild);
}

TT void Tree::removeRT(Node* p) {
  destroy(p->rlChild);
}

TT void Tree::removeT(Node*& p) {
  destroy(p);
}

TT void Tree::preOrder(Node* p, void (*visit)(Node* t)) {
  if (p) {
    visit(p);
    preOrder(p->lChild, visit);
    preOrder(p->rChild, visit);
  }
}

TT void Tree::inOrder(Node* p, void (*visit)(Node* t)) {
  if (p) {
    inOrder(p->lChild, visit);
    visit(p);
    inOrder(p->rChild, visit);
  }
}

TT void Tree::postOrder(Node* p, void (*visit)(Node* t)) {
  if (p) {
    postOrder(p->lChild, visit);
    postOrder(p->rChild, visit);
    visit(p);
  }
}

TT void Tree::preOrderX(Node* p, void (*visit)(Node* t)) {
  Stack<Node*> stk;
  if (p)
    stk.push(p);
  while (!stk.empty()) {
    p = stk.pop();
    visit(p);
    if (p->rChild)
      stk.push(p->rChild);
    if (p->lChild)
      stk.push(p->lChild);
  }
}

TT void Tree::inOrderX(Node* p, void (*visit)(Node* t)) {
  Stack<Node*> stk;
  while (1) {
    for (; p; p = p->lChild)
      stk.push(p);
    if (stk.empty())
      break;
    p = stk.pop();
    visit(p);
    p = p->rChild;
  }
}

TT void Tree::levelOrder(Node* p, void (*visit)(Node* t)) {
  Queue<Node*> que;
  que.enqueue(p);
  while (que.size()) {
    p = que.dequeue();
    visit(p);
    if (p->lChild)
      que.enqueue(p->lChild);
    if (p->rChild)
      que.enqueue(p->rChild);
  }
}

#undef TT
#undef Node
#undef Tree