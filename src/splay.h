//
// Created by wjl on 2022/7/10.
//

#ifndef SPLAY_H
#define SPLAY_H

#pragma once

#include <bstree.h>

namespace jtd {

template<class T>
class Splay : public BSTree<T> {
protected:
  BinNodePos<T> splay(BinNodePos<T> v);

public:
  BinNodePos<T> &search(const T &e);
  BinNodePos<T> insert(const T &e);
  bool remove(const T &e);
};

template<class P>
inline void attachlc(P lc, P p) {
  p->lc = lc;
  if (lc) {
    lc->parent = p;
  }
}

template<class P>
inline void attachrc(P p, P rc) {
  p->rc = rc;
  if (rc) {
    rc->parent = p;
  }
}

template<class T>
BinNodePos<T> Splay<T>::splay(BinNodePos<T> v) {
  if (!v) {
    return NULL;
  }
  BinNodePos<T> p;
  BinNodePos<T> g;
  while ((p = v->parent) && (g = p->parent)) {
    BinNodePos<T> gg = g->parent;
    if (ISLC(*v)) {
      if (ISLC(*p)) {
        print(*g);
        print(*p);
        print(*v);
        print("\n");
        attachlc(p->rc, g);
        attachlc(v->rc, p);
        attachrc(p, g);
        attachrc(v, p);
      } else {
        print(*g);
        print(*p);
        print(*v);
        print("\n");
        attachlc(v->rc, p);
        attachrc(g, v->lc);
        attachlc(g, v);
        attachrc(v, p);
      }
    } else if (ISRC(*p)) {
      print(*g);
      print(*p);
      print(*v);
      print("\n");
      attachrc(g, p->lc);
      attachrc(p, v->lc);
      attachlc(g, p);
      attachlc(p, v);
    } else {
      print(*g);
      print(*p);
      print(*v);
      print("\n");
      attachrc(p, v->lc);
      attachlc(v->rc, g);
      attachrc(v, g);
      attachlc(p, v);
    }
    if (!gg) {
      v->parent = NULL;
    } else {
      (g == gg->lc) ? attachlc(v, gg) : attachrc(gg, v);
    }
    this->updateheight(g);
    this->updateheight(p);
    this->updateheight(v);
  }
  p = v->parent;
  if (p) {
    if (ISLC(*v)) {
      print(*p);
      print(*v);
      print("\n");
    } else {
      print(*p);
      print(*v);
      print("\n");
    }
    if (ISLC(*v)) {
      attachlc(v->rc, p);
      attachrc(v, p);
    } else {
      attachrc(p, v->lc);
      attachlc(p, v);
    }
    this->updateheight(p);
    this->updateheight(v);
  }
  v->parent = NULL;
  return v;
}

template<class T>
BinNodePos<T> &Splay<T>::search(const T &e) {
  BinNodePos<T> p = BSTree<T>::search(e);
  this->_root = splay(p ? p : this->_hot);
  return this->_root;
}

template<class T>
BinNodePos<T> Splay<T>::insert(const T &e) {
  if (!this->_root) {
    this->_size = 1;
    return this->_root = new BinNode<T>(e);
  }
  BinNodePos<T> t = search(e);
  if (e == t->data) {
    return t;
  }
  if (t->data < e) {
    t->parent = this->_root = new BinNode<T>(e, NULL, t, t->rc);
    if (t->rc) {
      t->rc->parent = this->_root;
      t->rc = NULL;
    }
  } else {
    t->parent = this->_root = new BinNode<T>(e, NULL, t->lc, t);
    if (t->lc) {
      t->lc->parent = this->_root;
      t->lc = NULL;
    }
  }
  this->_size++;
  this->updateheight_above(t);
  return this->_root;
}

template<class T>
bool Splay<T>::remove(const T &e) {
  if (!this->_root || (e != search(e)->data)) {
    return false;
  }
  BinNodePos<T> l = this->_root->lc, r = this->_root->rc;
  release(this->_root);
  if (!r) {
    if (l) {
      l->parent = NULL;
    }
    this->_root = l;
  } else {
    this->_root = r;
    r->parent = NULL;
    search(e);
    if (l) {
      l->parent = this->_root;
    }
    this->_root->lc = l;
  }
  if (--this->_size) {
    this->updateheight(this->_root);
  }
  return true;
}

}// namespace jtd

#endif//SPLAY_H
