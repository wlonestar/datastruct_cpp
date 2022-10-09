//
// Created by wjl15 on 2022/6/20.
//

#ifndef BINTREE_H
#define BINTREE_H

#pragma once

#include <binode.h>
#include <bitmap.h>

namespace jtd {

#define ROOT 0
#define L_C 1
#define R_C (-1 * L_C)

template<class T>
class BinTree {
protected:
  int _size;
  BinNodePos<T> _root;

  virtual int updateheight(BinNodePos<T> x);
  void updateheight_above(BinNodePos<T> x);

public:
  BinTree();
  ~BinTree();

  int size() const;
  bool empty() const;
  BinNodePos<T> root() const;

  virtual BinNodePos<T> insert(const T &e);
  BinNodePos<T> insert(const T &e, BinNodePos<T> x);
  BinNodePos<T> insert(BinNodePos<T> x, const T &e);
  BinNodePos<T> attach(BinTree<T> *&bt, BinNodePos<T> x);
  BinNodePos<T> attach(BinNodePos<T> x, BinTree<T> *&bt);
  int remove(BinNodePos<T> x);
  BinTree<T> *secede(BinNodePos<T> x);

  void trav_level();
  void trav_prer();
  void trav_prei();
  void trav_pre();
  void trav_inr();
  void trav_ini();
  void trav_in();
  void trav_postr();
  void trav_posti();
  void trav_post();

  bool operator<(const BinTree<T> &bt);
  bool operator==(const BinTree<T> &bt);
};

template<class T>
void print(BinNodePos<T> bt, int depth, int type, bitmap *btype) {
  if (!bt) {
    return;
  }
  if (-1 < depth) {
    R_C == type ? btype->set(depth) : btype->clear(depth);
  }
  print(bt->rc, depth + 1, R_C, btype);
  print(*bt);
  print(" *");
  for (int i = -1; i < depth; i++) {
    if ((0 > i) || btype->test(i) == btype->test(i + 1)) {
      print("      ");
    } else {
      print("│    ");
    }
  }
  switch (type) {
    case R_C:
      print("┌─");
      break;
    case L_C:
      print("└─");
      break;
    default:
      print("──");
      break;
  }
  print(*bt);
#if defined(HUFFMAN)
  if (ISLEAF(*bt)) {
    btype->print(depth + 1);
  }
#endif
  print("\n");
  print(bt->lc, depth + 1, L_C, btype);
}

template<class T>
void print(BinTree<T> &bt) {
  auto *branchtype = new bitmap;
  print(bt.root(), -1, ROOT, branchtype);
  release(branchtype);
  print("\n");
}

template<class T>
int BinTree<T>::updateheight(BinNodePos<T> x) {
  return x->height = 1 + MAX(STATURE(x->lc), STATURE(x->rc));
}

template<class T>
void BinTree<T>::updateheight_above(BinNodePos<T> x) {
  while (x) {
    updateheight(x);
    x = x->parent;
  }
}

template<class T>
BinTree<T>::BinTree() : _size(0), _root(nullptr) {}

template<class T>
BinTree<T>::~BinTree() {
  if (0 < _size) {
    remove(_root);
  }
}

template<class T>
int BinTree<T>::size() const {
  return _size;
}

template<class T>
bool BinTree<T>::empty() const {
  return !_size;
}

template<class T>
BinNodePos<T> BinTree<T>::root() const {
  return _root;
}

template<class T>
BinNodePos<T> BinTree<T>::insert(const T &e) {
  _size = 1;
  return _root = new BinNode<T>(e);
}

template<class T>
BinNodePos<T> BinTree<T>::insert(const T &e, BinNodePos<T> x) {
  _size++;
  x->insertlc(e);
  updateheight_above(x);
  return x->lc;
}

template<class T>
BinNodePos<T> BinTree<T>::insert(BinNodePos<T> x, const T &e) {
  _size++;
  x->insertrc(e);
  updateheight_above(x);
  return x->rc;
}

template<class T>
BinNodePos<T> BinTree<T>::attach(BinTree<T> *&bt, BinNodePos<T> x) {
  x->lc = bt->_root;
  if (x->lc) {
    x->lc->parent = x;
  }
  _size += bt->_size;
  updateheight_above(x);
  bt->_root = nullptr;
  bt->_size = 0;
  release(bt);
  bt = nullptr;
  return x;
}

template<class T>
BinNodePos<T> BinTree<T>::attach(BinNodePos<T> x, BinTree<T> *&bt) {
  x->rc = bt->_root;
  if (x->rc) {
    x->rc->parent = x;
  }
  _size += bt->_size;
  updateheight_above(x);
  bt->_root = nullptr;
  bt->_size = 0;
  release(bt);
  bt = nullptr;
  return x;
}

template<class T>
static int remove_at(BinNodePos<T> x) {
  if (!x) {
    return 0;
  }
  int n = 1 + remove_at(x->lc) + remove_at(x->rc);
  release(x->data);
  release(x);
  return n;
}

template<class T>
int BinTree<T>::remove(BinNodePos<T> x) {
  FROM_PARENT_TO(*x) = nullptr;
  updateheight_above(x->parent);
  int n = remove_at(x);
  _size -= n;
  return n;
}

template<class T>
BinTree<T> *BinTree<T>::secede(BinNodePos<T> x) {
  FROM_PARENT_TO(*x) = nullptr;
  updateheight_above(x->parent);
  auto *bt = new BinTree<T>;
  bt->_root = x;
  x->parent = nullptr;
  bt->_size = x->size();
  _size = bt->_size;
  return bt;
}

template<class T>
void BinTree<T>::trav_level() {
  if (_root) {
    _root->trav_level();
  }
}

template<class T>
void BinTree<T>::trav_prer() {
  if (_root) {
    _root->trav_prer(_root);
    print("\n");
  }
}

template<class T>
void BinTree<T>::trav_prei() {
  if (_root) {
    _root->trav_pre();
    print("\n");
  }
}

template<class T>
void BinTree<T>::trav_pre() {
  trav_prei();
}

template<class T>
void BinTree<T>::trav_inr() {
  if (_root) {
    _root->trav_inr(_root);
    print("\n");
  }
}

template<class T>
void BinTree<T>::trav_ini() {
  if (_root) {
    _root->trav_in();
    print("\n");
  }
}

template<class T>
void BinTree<T>::trav_in() {
  trav_ini();
}

template<class T>
void BinTree<T>::trav_postr() {
  if (_root) {
    _root->trav_postr(_root);
    print("\n");
  }
}

template<class T>
void BinTree<T>::trav_posti() {
  if (_root) {
    _root->trav_post();
    print("\n");
  }
}

template<class T>
void BinTree<T>::trav_post() {
  trav_posti();
}

template<class T>
bool BinTree<T>::operator<(const BinTree<T> &bt) {
  return _root && bt._root && lt(_root, bt._root);
}

template<class T>
bool BinTree<T>::operator==(const BinTree<T> &bt) {
  return _root && bt._root && eq(_root, bt._root);
}

}// namespace jtd

#endif//BINTREE_H
