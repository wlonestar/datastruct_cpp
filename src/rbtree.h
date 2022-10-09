//
// Created by wjl on 2022/7/12.
//

#ifndef RBTREE_H
#define RBTREE_H

#pragma once

#include <bstree.h>

namespace jtd {

template<class T>
class Rbtree : public BSTree<T> {
protected:
  void solve_doublered(BinNodePos<T> x);
  void solve_doubleblack(BinNodePos<T> x);
  int updateheight(BinNodePos<T> x);

public:
  BinNodePos<T> insert(const T &e);
  bool remove(const T &e);
};

template<class T>
void print(Rbtree<T> &bt) {
  auto *branchtype = new bitmap;
  print(bt.root(), -1, ROOT, branchtype);
  release(branchtype);
  print("\n");
}

template<class T>
void Rbtree<T>::solve_doublered(BinNodePos<T> x) {
  if (ISROOT(*x)) {
    this->_root->color = RB_BLACK;
    this->_root->height++;
    return;
  }
  BinNodePos<T> p = x->parent;
  if (ISBLACK(p)) {
    return;
  }
  BinNodePos<T> g = p->parent;
  BinNodePos<T> u = UNCLE(x);
  if (ISBLACK(u)) {
    if (ISLC(*x) == ISLC(*p)) {
      p->color = RB_BLACK;
    } else {
      x->color = RB_BLACK;
    }
    g->color = RB_RED;
    BinNodePos<T> gg = g->parent;
    BinNodePos<T> r = FROM_PARENT_TO(*g) = this->rotate_at(x);
    r->parent = gg;
  } else {
    p->color = RB_BLACK;
    p->height++;
    u->color = RB_BLACK;
    u->height++;
    if (!ISROOT(*g)) {
      g->color = RB_RED;
    }
    solve_doublered(g);
  }
}

template<class T>
void Rbtree<T>::solve_doubleblack(BinNodePos<T> x) {
  BinNodePos<T> p = x ? x->parent : this->_hot;
  if (!p) {
    return;
  }
  BinNodePos<T> s = (x == p->lc) ? p->rc : p->lc;
  if (ISBLACK(s)) {
    BinNodePos<T> t = NULL;
    if (ISRED(s->rc)) {
      t = s->rc;
    }
    if (ISRED(s->lc)) {
      t = s->lc;
    }
    if (t) {
      RBColor old = p->color;
      BinNodePos<T> b = FROM_PARENT_TO(*p) = this->rotate_at(t);
      if (HASLC(*b)) {
        b->lc->color = RB_BLACK;
        updateheight(b->lc);
      }
      if (HASRC(*b)) {
        b->rc->color = RB_BLACK;
        updateheight(b->rc);
      }
      b->color = old;
      updateheight(b);
    } else {
      s->color = RB_RED;
      s->height--;
      if (ISRED(p)) {
        p->color = RB_BLACK;
      } else {
        p->height--;
        solve_doubleblack(p);
      }
    }
  } else {
    s->color = RB_BLACK;
    p->color = RB_RED;
    BinNodePos<T> t = ISLC(*s) ? s->lc : s->rc;
    this->_hot = p;
    FROM_PARENT_TO(*p) = this->rotate_at(t);
    solve_doubleblack(x);
  }
}

template<class T>
int Rbtree<T>::updateheight(BinNodePos<T> x) {
  return x->height = ISBLACK(x) + MAX(STATURE(x->lc), STATURE(x->rc));
}

template<class T>
BinNodePos<T> Rbtree<T>::insert(const T &e) {
  BinNodePos<T> &x = this->search(e);
  if (x) {
    return x;
  }
  x = new BinNode<T>(e, this->_hot, NULL, NULL, 0);
  this->_size++;
  BinNodePos<T> old = x;
  solve_doublered(x);
  return old;
}

template<class T>
bool Rbtree<T>::remove(const T &e) {
  BinNodePos<T> &x = this->search(e);
  if (!x) {
    return false;
  }
  BinNodePos<T> r = remove_at(x, this->_hot);
  if (!(--this->_size)) {
    return true;
  }
  if (!this->_hot) {
    this->_root->color = RB_BLACK;
    updateheight(this->_root);
    return true;
  }
  if (BLACK_HEIGHT_UPDATED(*this->_hot)) {
    return true;
  }
  if (ISRED(r)) {
    r->color = RB_BLACK;
    r->height++;
    return true;
  }
  solve_doubleblack(r);
  return true;
}

}// namespace jtd

#endif//RBTREE_H
