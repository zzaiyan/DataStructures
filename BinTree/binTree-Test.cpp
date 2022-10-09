#include "binTree.h"
#include <iostream>
using namespace std;

void pr(BinNode<char>* p) {
  cout << p->data << " " << p->height << endl;
}

int main() {
  auto tree = new BinTree<char>;
  // cout << tree->root()->data << endl;
  tree->root()->data = 'A';
  auto l = tree->insertAsLC(tree->root(), 'B');
  auto r = tree->insertAsRC(tree->root(), 'C');
  tree->insertAsRC(l, 'D');
  tree->insertAsLC(r, 'E');
  tree->preOrderX(tree->root(), pr);
  // auto d = tree->insertAsLC(l, 'D');
  //// tree->insertAsLC(d, 'X');

  // tree->insertAsRC(l, 'E');
  // tree->insertAsLC(r, 'F');
  // tree->insertAsRC(r, 'G');
  // cout << "size = " << tree->size() << endl;

  //// tree->inOrder(tree->root(), pr);
  //// cout << endl;
  //// tree->inOrderX(tree->root(), pr);
  //// cout << endl;
  // tree->levelOrder(tree->root(), pr);
  // cout << "height = " << tree->getHeight(tree->root()) << endl;
  // tree->removeLT(tree->root());
  // tree->removeT(r->lChild);
  // tree->removeT(r->rChild);
  // cout << endl;

  // tree->levelOrder(tree->root(), pr);

  // cout << "height = " << tree->getHeight(tree->root()) << endl;

  cout << "Finish!\n";

  return 0;
}