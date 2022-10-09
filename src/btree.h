//
// Created by wjl on 2022/7/10.
//

#ifndef BTREE_H
#define BTREE_H

#pragma once

#include <util.h>
#include <vector.h>

namespace jtd {

template<class T>
class Btnode;

template<class T>
using BtnodePos = Btnode<T> *;

template<class T>
class Btnode {
public:
  BtnodePos<T> parent;
  Vector<T> key;
  Vector<BtnodePos<T>> child;

  Btnode();
  Btnode(T e, BtnodePos<T> lc, BtnodePos<T> rc);
};

template<class T>
Btnode<T>::Btnode() {
  parent = NULL;
  child.insert(NULL);
}

template<class T>
Btnode<T>::Btnode(T e, BtnodePos<T> lc, BtnodePos<T> rc) {
  parent = NULL;
  key.insert(e);
  child.insert(lc);
  if (lc) {
    lc->parent = this;
  }
  child.insert(rc);
  if (rc) {
    rc->parent = this;
  }
}

template<class T>
class Btree {
protected:
  int _size;
  int _m;
  BtnodePos<T> _root;
  BtnodePos<T> _hot;
  void solve_overflow(BtnodePos<T> v);
  void solve_underflow(BtnodePos<T> v);

public:
  explicit Btree(int m = 3);
  ~Btree();

  int order();
  int size();
  BtnodePos<T> &root();
  bool empty() const;
  BtnodePos<T> search(const T &e);
  bool insert(const T &e);
  bool remove(const T &e);
};

template<class T>
void Btree<T>::solve_overflow(BtnodePos<T> v) {
  if (_m > v->key.size()) {
    return;
  }
  int s = _m / 2;
  auto u = new Btnode<T>();
  for (int j = 0; j < _m - s - 1; j++) {
    u->child.insert(j, v->child.remove(s + 1));
    u->key.insert(j, v->key.remove(s + 1));
  }
  u->child[_m - s - 1] = v->child.remove(s + 1);
  if (u->child[0]) {
    for (int j = 0; j < _m - s; j++) {
      u->child[j]->parent = u;
    }
  }
  BtnodePos<T> p = v->parent;
  if (!p) {
    _root = p = new Btnode<T>();
    p->child[0] = v;
    v->parent = p;
  }
  int r = 1 + p->key.search(v->key[0]);
  p->key.insert(r, v->key.remove(s));
  p->child.insert(r + 1, u);
  u->parent = p;
  solve_overflow(p);
}

template<class T>
void Btree<T>::solve_underflow(BtnodePos<T> v) {
  if ((_m + 1) / 2 <= v->child.size()) {
    return;
  }
  BtnodePos<T> p = v->parent;
  if (!p) {
    if (!v->key.size() && v->child[0]) {
      printf("collapse\n");
      _root = v->child[0];
      _root->parent = NULL;
      v->child[0] = NULL;
      release(v);
    }
    return;
  }
  int r = 0;
  while (p->child[r] != v) {
    r++;
  }
  printf("\nint = %d", r);
  if (0 < r) {
    BtnodePos<T> ls = p->child[r - 1];
    if ((_m + 1) / 2 < ls->child.size()) {
      printf(" ... case 1\n");
      v->key.insert(0, p->key[r - 1]);
      p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
      v->child.insert(0, ls->child.remove(ls->child.size() - 1));
      if (v->child[0]) {
        v->child[0]->parent = v;
      }
      return;
    }
  }
  if (p->child.size() - 1 > r) {
    BtnodePos<T> rs = p->child[r + 1];
    if ((_m + 1) / 2 < rs->child.size()) {
      printf(" ... case 2\n");
      v->key.insert(v->key.size(), p->key[r]);
      p->key[r] = rs->key.remove(0);
      v->child.insert(v->child.size(), rs->child.remove(0));
      if (v->child[v->child.size() - 1]) {
        v->child[v->child.size() - 1]->parent = v;
      }
      return;
    }
  }
  if (0 < r) {
    printf(" ... case 3L\n");
    BtnodePos<T> ls = p->child[r - 1];
    ls->key.insert(ls->key.size(), p->key.remove(r - 1));
    p->child.remove(r);
    ls->child.insert(ls->child.size(), v->child.remove(0));
    if (ls->child[ls->child.size() - 1]) {
      ls->child[ls->child.size() - 1]->parent = ls;
    }
    while (!v->key.empty()) {
      ls->key.insert(ls->key.size(), v->key.remove(0));
      ls->child.insert(ls->child.size(), v->child.remove(0));
      if (ls->child[ls->child.size() - 1]) {
        ls->child[ls->child.size() - 1]->parent = ls;
      }
    }
    release(v);
  } else {
    printf(" ... case 3R\n");
    BtnodePos<T> rs = p->child[r + 1];
    rs->key.insert(0, p->key.remove(r));
    p->child.remove(r);
    rs->child.insert(0, v->child.remove(v->child.size() - 1));
    if (rs->child[0]) {
      rs->child[0]->parent = rs;
    }
    while (!v->key.empty()) {
      rs->key.insert(0, v->key.remove(v->key.size() - 1));
      rs->child.insert(0, v->child.remove(v->child.size() - 1));
      if (rs->child[0]) {
        rs->child[0]->parent = rs;
      }
    }
    release(v);
  }
  solve_underflow(p);
  return;
}

template<class T>
Btree<T>::Btree(int m) : _m(m), _size(0) {
  _root = new Btnode<T>();
}

template<class T>
Btree<T>::~Btree() {
  if (_root) {
    release(_root);
  }
}

template<class T>
int Btree<T>::order() {
  return _m;
}

template<class T>
int Btree<T>::size() {
  return _size;
}

template<class T>
BtnodePos<T> &Btree<T>::root() {
  return _root;
}

template<class T>
bool Btree<T>::empty() const {
  return !_root;
}

template<class T>
BtnodePos<T> Btree<T>::search(const T &e) {
  BtnodePos<T> v = _root;
  _hot = NULL;
  while (v) {
    int r = v->key.search(e);
    if ((0 <= r) && (e == v->key[r])) {
      return v;
    }
    _hot = v;
    v = v->child[r + 1];
  }
  return NULL;
}

template<class T>
bool Btree<T>::insert(const T &e) {
  BtnodePos<T> v = search(e);
  if (v) {
    return false;
  }
  int r = _hot->key.search(e);
  _hot->key.insert(r + 1, e);
  _hot->child.insert(r + 2, NULL);
  _size++;
  solve_overflow(_hot);
  return true;
}

template<class T>
bool Btree<T>::remove(const T &e) {
  BtnodePos<T> v = search(e);
  if (!v) {
    return false;
  }
  int r = v->key.search(e);
  if (v->child[0]) {
    BtnodePos<T> u = v->child[r + 1];
    while (u->child[0]) {
      u = u->child[0];
    }
    v->key[r] = u->key[0];
    v = u;
    r = 0;
  }
  v->key.remove(r);
  v->child.remove(r + 1);
  _size--;
  solve_underflow(v);
  return true;
}

}// namespace jtd

#endif//BTREE_H
