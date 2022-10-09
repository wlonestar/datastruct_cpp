//
// Created by wjl on 2022/7/3.
//

#ifndef BSTREE_H
#define BSTREE_H

#pragma once

#include <bintree.h>

namespace jtd {

template<class T>
class BSTree : public BinTree<T> {
protected:
  BinNodePos<T> _hot;
  BinNodePos<T> connect34(BinNodePos<T> a, BinNodePos<T> b, BinNodePos<T> c,
                          BinNodePos<T> t0, BinNodePos<T> t1,
                          BinNodePos<T> t2, BinNodePos<T> t3);
  BinNodePos<T> rotate_at(BinNodePos<T> v);

public:
  virtual BinNodePos<T> &search(const T &e);
  virtual BinNodePos<T> insert(const T &e);
  virtual bool remove(const T &e);

  void stretch2lpath();
  void stretch2rpath();
  void stretch();
  void balance();
  void imitate(BSTree<T> y);
};

template<class T>
void print(BSTree<T> &bt) {
  auto *branchtype = new bitmap;
  print(bt.root(), -1, ROOT, branchtype);
  release(branchtype);
  print("\n");
}

template<class T>
BinNodePos<T> BSTree<T>::connect34(
  BinNodePos<T> a, BinNodePos<T> b, BinNodePos<T> c,
  BinNodePos<T> t0, BinNodePos<T> t1, BinNodePos<T> t2, BinNodePos<T> t3) {
  a->lc = t0;
  if (t0) {
    t0->parent = a;
  }
  a->rc = t1;
  if (t1) {
    t1->parent = a;
  }
  this->updateheight(a);
  c->lc = t2;
  if (t2) {
    t2->parent = c;
  }
  c->rc = t3;
  if (t3) {
    t3->parent = c;
  }
  this->updateheight(c);
  b->lc = a;
  a->parent = b;
  b->rc = c;
  c->parent = b;
  this->updateheight(b);
  return b;
}

template<class T>
BinNodePos<T> BSTree<T>::rotate_at(BinNodePos<T> v) {
  if (!v) {
    print("Fail to rotate a null node\n");
    exit(-1);
  }
  BinNodePos<T> p = v->parent;
  BinNodePos<T> g = p->parent;
  if (ISLC(*p)) {
    if (ISLC(*v)) {
      p->parent = g->parent;
      return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
    } else {
      v->parent = g->parent;
      return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
    }
  } else {
    if (ISRC(*v)) {
      p->parent = g->parent;
      return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
    } else {
      v->parent = g->parent;
      return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
    }
  }
}

template<class T>
BinNodePos<T> &BSTree<T>::search(const T &e) {
  if (!this->_root || e == this->_root->data) {
    _hot = NULL;
    return this->_root;
  }
  for (_hot = this->_root;;) {
    BinNodePos<T> &v = (e < _hot->data) ? _hot->lc : _hot->rc;
    if (!v || e == v->data) {
      return v;
    }
    _hot = v;
  }
}

template<class T>
BinNodePos<T> BSTree<T>::insert(const T &e) {
  BinNodePos<T> &x = search(e);
  if (x) {
    return x;
  }
  x = new BinNode<T>(e, _hot);
  this->_size++;
  this->updateheight_above(x);
  return x;
}

template<typename T>
static BinNodePos<T> remove_at(BinNodePos<T> &x, BinNodePos<T> &hot) {
  BinNodePos<T> w = x;
  BinNodePos<T> succ = NULL;
  if (!HASLC(*x)) {
    succ = x = x->rc;
  } else if (!HASRC(*x)) {
    succ = x = x->lc;
  } else {
    w = w->succ();
    swap(x->data, w->data);
    BinNodePos<T> u = w->parent;
    ((u == x) ? u->rc : u->lc) = succ = w->rc;
  }
  hot = w->parent;
  if (succ) {
    succ->parent = hot;
  }
  release(w->data);
  release(w);
  return succ;
}

template<class T>
bool BSTree<T>::remove(const T &e) {
  BinNodePos<T> &x = search(e);
  if (!x) {
    return false;
  }
  remove_at(x, _hot);
  this->_size--;
  this->updateheight_above(_hot);
  return true;
}

template<class T>
void BSTree<T>::stretch2lpath() {
  stretch_byzag(this->_root);
}

template<class T>
void BSTree<T>::stretch2rpath() {
  stretch_byzig(this->_root);
}

template<class T>
void BSTree<T>::stretch() {
}

template<class T>
void BSTree<T>::balance() {
  this->_root = this->_root->balance();
}

template<class T>
void BSTree<T>::imitate(BSTree<T> y) {
  this->_root = this->_root->imitate(y._root);
}

}// namespace jtd

#endif//BSTREE_H
