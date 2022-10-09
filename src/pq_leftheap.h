//
// Created by wjl on 2022/7/14.
//

#ifndef PQ_LEFTHEAP_H
#define PQ_LEFTHEAP_H

#pragma once

#include <bintree.h>
#include <pq.h>

namespace jtd {

template<class T>
class PQ_leftheap : public PQ<T>, public BinTree<T> {
public:
  PQ_leftheap() = default;
  PQ_leftheap(T *a, int n);
  PQ_leftheap(PQ_leftheap &a, PQ_leftheap &b);
  void insert(T e);
  T get_max();
  T del_max();
};

template<class T>
PQ_leftheap<T>::PQ_leftheap(T *a, int n) {
  for (int i = 0; i < n; i++) {
    insert(a[i]);
  }
}

template<class T>
static BinNodePos<T> merge(BinNodePos<T> a, BinNodePos<T> b) {
  if (!a) {
    return b;
  }
  if (!b) {
    return a;
  }
  if (lt(a->data, b->data)) {
    swap(a, b);
  }
  (a->rc = merge(a->rc, b))->parent = a;
  if (!a->lc || a->lc->npl < a->rc->npl) {
    swap(a->lc, a->rc);
  }
  a->npl = a->rc ? a->rc->npl + 1 : 1;
  return a;
}

template<class T>
PQ_leftheap<T>::PQ_leftheap(PQ_leftheap &a, PQ_leftheap &b) {
  this->_root = merge(a._root, b._root);
  this->_size = a._size + b._size;
  a._root = b._root = NULL;
  a._size = b._size = 0;
}

template<class T>
void PQ_leftheap<T>::insert(T e) {
  this->_root = merge(this->_root, new BinNode<T>(e, NULL));
  this->_size++;
}

template<class T>
T PQ_leftheap<T>::get_max() {
  return this->_root->data;
}

template<class T>
T PQ_leftheap<T>::del_max() {
  BinNodePos<T> lh = this->_root->lc;
  if (lh) {
    lh->parent = NULL;
  }
  BinNodePos<T> rh = this->_root->rc;
  if (rh) {
    rh->parent = NULL;
  }
  T e = this->_root->data;
  delete this->_root;
  this->_size--;
  this->_root = merge(lh, rh);
  return e;
}

}// namespace jtd

#endif//PQ_LEFTHEAP_H
