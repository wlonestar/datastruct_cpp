//
// Created by wjl on 2022/7/10.
//

#ifndef AVL_H
#define AVL_H

#pragma once

#include <bstree.h>

namespace jtd {

#define TALLER_CHILD(x) \
  (STATURE((x)->lc) > STATURE((x)->rc) ? (x)->lc : (STATURE((x)->lc) < STATURE((x)->rc) ? (x)->rc : (ISLC(*(x)) ? (x)->lc : (x)->rc)))

template<class T>
class Avl : public BSTree<T> {
public:
  BinNodePos<T> insert(const T &e);
  bool remove(const T &e);
};

template<class T>
void print(Avl<T> &avl) {
  auto *branchtype = new bitmap;
  print(avl.root(), -1, ROOT, branchtype);
  release(branchtype);
  print("\n");
}

template<class T>
BinNodePos<T> Avl<T>::insert(const T &e) {
  BinNodePos<T> &x = this->search(e);
  if (x) {
    return x;
  }
  BinNodePos<T> xx = x = new BinNode<T>(e, this->_hot);
  this->_size++;
  for (BinNodePos<T> g = this->_hot; g; g = g->parent) {
    if (!AVL_BALANCED(*g)) {
      FROM_PARENT_TO(*g) = this->rotate_at(TALLER_CHILD(TALLER_CHILD(g)));
      break;
    } else {
      this->updateheight(g);
    }
  }
  return xx;
}

template<class T>
bool Avl<T>::remove(const T &e) {
  BinNodePos<T> &x = this->search(e);
  if (!x) {
    return false;
  }
  remove_at(x, this->_hot);
  this->_size--;
  for (BinNodePos<T> g = this->_hot; g; g = g->parent) {
    if (!AVL_BALANCED(*g)) {
      g = FROM_PARENT_TO(*g) = this->rotate_at(TALLER_CHILD(TALLER_CHILD(g)));
    }
    this->updateheight(g);
  }
  return true;
}

}// namespace jtd

#endif//AVL_H
