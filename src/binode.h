//
// Created by wjl15 on 2022/6/20.
//

#ifndef BINODE_H
#define BINODE_H

#pragma once

#include <queue.h>
#include <stack.h>
#include <util.h>

namespace jtd {

#if defined(RBTREE_H)
#define STATURE(p) ((p) ? (p)->height : 0)
#else
#define STATURE(p) ((p) ? (p)->height : -1)
#endif

using RBColor = enum {
  RB_RED,
  RB_BLACK
};

template<class T>
class BinNode;

template<class T>
using BinNodePos = BinNode<T> *;

#define ISROOT(x) (!(x).parent)
#define ISLC(x) (!ISROOT(x) && (&(x) == (x).parent->lc))
#define ISRC(x) (!ISROOT(x) && (&(x) == (x).parent->rc))
#define HASPARENT(x) (!ISROOT(x))
#define HASLC(x) ((x).lc)
#define HASRC(x) ((x).rc)
#define HASCHILD(x) (HASLC(x) || HASRC(x))
#define HASBOTHCHILD(x) (HASLC(x) && HASRC(x))
#define ISLEAF(x) (!HASCHILD(x))
#define SIBLING(p) (ISLC(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define UNCLE(x) (SIBLING((x)->parent))
#define FROM_PARENT_TO(x) (ISROOT(x) ? this->_root : (ISLC(x) ? (x).parent->lc : (x).parent->rc))

#define HEIGHT_UPDATED(x) ((x).height == 1 + MAX(STATURE((x).lc), STATURE((x).rc)))
#define BALANCED(x) (STATURE((x).lc) == STATURE((x).rc))
#define BALFAC(x) (STATURE((x).lc) - STATURE((x).rc))
#define AVL_BALANCED(x) ((-2 < BALFAC(x)) && (BALFAC(x) < 2))

#define ISBLACK(p) (!(p) || (jtd::RB_BLACK == (p)->color))
#define ISRED(p) (!ISBLACK(p))
#define BLACK_HEIGHT_UPDATED(x) ((STATURE((x).lc) == STATURE((x).rc)) && ((x).height == (ISRED(&x) ? STATURE((x).lc) : STATURE((x).rc) + 1)))

template<class T>
class BinNode {
public:
  T data;
  BinNodePos<T> parent;
  BinNodePos<T> lc;
  BinNodePos<T> rc;
  int height;
  int npl;
  RBColor color;

  BinNode();
  explicit BinNode(T e, BinNodePos<T> p = nullptr,
                   BinNodePos<T> lc = nullptr, BinNodePos<T> rc = nullptr,
                   int h = 0, int l = 1, RBColor c = RB_RED);

  int size();
  BinNodePos<T> insertlc(const T &e);
  BinNodePos<T> insertrc(const T &e);
  BinNodePos<T> succ();

  void trav_level();
  void trav_prer(BinNodePos<T> x);
  void trav_prei(BinNodePos<T> x);
  void trav_pre();
  void trav_inr(BinNodePos<T> x);
  void trav_ini(BinNodePos<T> x);
  void trav_in();
  void trav_postr(BinNodePos<T> x);
  void trav_posti(BinNodePos<T> x);
  void trav_post();

  bool operator<(const BinNode &bn);
  bool operator==(const BinNode &bn);

  BinNodePos<T> zig();
  BinNodePos<T> zag();
  BinNodePos<T> balance();
  BinNodePos<T> imitate(const BinNodePos<T> &bn);
};

template<class T>
void print(const BinNode<T> &node) {
  print("{}", tostr(node.data).c_str());
#if defined(LEFTHEAP_H)
  print("({})", tostr(node.npl).c_str());
#elif defined(BSTREE_H)
  print("({})", tostr(node.height).c_str());
#elif defined(AVL_H)
  print("({})", tostr(node.height).c_str());
#elif defined(RBTREE_H)
  print("({})", tostr(node.height).c_str());
#elif defined(SPLAY_H)
  print("({})", tostr(node.height).c_str());
#endif

  print((node.lc && &node != node.lc->parent) || (node.rc && &node != node.rc->parent) ? "@" : " ");

#if defined(RBTREE_H)
  print(node.color == RB_BLACK ? "B" : " ");
#endif

#if defined(PQ_COMPHEAP_H)
#elif defined(PQ_LEFTHEAP_H)
  print((node.rc && (node.npl != 1 + node.rc->npl)) || (node.lc && (node.npl > 1 + node.lc->npl)) ? "%%" : " ");
#elif defined(RBTREE_H)
  print(BLACK_HEIGHT_UPDATED(node) ? " " : "!");
#else
  print(HEIGHT_UPDATED(node) ? " " : "!");
#endif

#if defined(AVL_H)
  if (!AVL_BALANCED(node)) {
    print("X");
  } else if (0 < BALFAC(node)) {
    print("\\");
  } else if (BALFAC(node) < 0) {
    print("/");
  } else {
    print("-");
  }
#elif defined(RBTREE_H)
  if (!BALANCED(node)) {
    print("X");
  } else if (0 < BALFAC(node)) {
    print("\\");
  } else if (BALFAC(node) < 0) {
    print("/");
  } else {
    print("-");
  }
#else
#endif
}

template<class T>
BinNode<T>::BinNode() : parent(nullptr), lc(nullptr), rc(nullptr),
                        height(0), npl(0), color(RB_RED) {}

template<class T>
BinNode<T>::BinNode(T e, BinNodePos<T> p, BinNodePos<T> lc, BinNodePos<T> rc,
                    int h, int l, RBColor c)
    : data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

template<class T>
int BinNode<T>::size() {
  int s = 1;
  if (lc) {
    s += lc->size();
  }
  if (rc) {
    s += rc->size();
  }
  return s;
}

template<class T>
BinNodePos<T> BinNode<T>::insertlc(const T &e) {
  return lc = new BinNode(e, this);
}

template<class T>
BinNodePos<T> BinNode<T>::insertrc(const T &e) {
  return rc = new BinNode(e, this);
}

template<class T>
BinNodePos<T> BinNode<T>::succ() {
  BinNodePos<T> s = this;
  if (rc) {
    s = rc;
    while (HASLC(*s)) {
      s = s->lc;
    }
  } else {
    while (ISRC(*s)) {
      s = s->parent;
    }
    s = s->parent;
  }
  return s;
}

template<class T>
void BinNode<T>::trav_level() {
  Queue<BinNodePos<T>> q;
  q.enque(this);
  while (!q.empty()) {
    BinNodePos<T> x = q.deque();
    log("{} ", tostr(x->data).c_str());
    if (HASLC(*x)) {
      q.enque(x->lc);
    }
    if (HASRC(*x)) {
      q.enque(x->rc);
    }
  }
}

template<class T>
void BinNode<T>::trav_prer(BinNodePos<T> x) {
  if (!x) {
    return;
  }
  print("{} ", tostr(x->data).c_str());
  trav_prer(x->lc);
  trav_prer(x->rc);
}

template<class T>
void BinNode<T>::trav_prei(BinNodePos<T> x) {
  Stack<BinNodePos<T>> s;
  if (x) {
    s.push(x);
  }
  while (!s.empty()) {
    x = s.pop();
    print("{} ", tostr(x->data).c_str());
    if (HASRC(*x)) {
      s.push(x->rc);
    }
    if (HASLC(*x)) {
      s.push(x->lc);
    }
  }
}

template<class T>
void BinNode<T>::trav_pre() {
  trav_prei(this);
}

template<class T>
void BinNode<T>::trav_inr(BinNodePos<T> x) {
  if (!x) {
    return;
  }
  trav_inr(x->lc);
  print("{} ", tostr(x->data).c_str());
  trav_inr(x->rc);
}

template<class T>
void BinNode<T>::trav_ini(BinNodePos<T> x) {
  while (true) {
    if (HASLC(*x)) {
      x = x->lc;
    } else {
      print("{} ", tostr(x->data).c_str());
      while (!HASRC(*x)) {
        if (!(x = x->succ())) {
          return;
        } else {
          print("{} ", tostr(x->data).c_str());
        }
      }
      x = x->rc;
    }
  }
}

template<class T>
void BinNode<T>::trav_in() {
  trav_ini(this);
}

template<class T>
void BinNode<T>::trav_postr(BinNodePos<T> x) {
  if (!x) {
    return;
  }
  trav_postr(x->lc);
  trav_postr(x->rc);
  print("{} ", tostr(x->data).c_str());
}

template<class T>
static void goto_leftmost_leaf(Stack<BinNodePos<T>> &s) {
  while (BinNodePos<T> x = s.top()) {
    if (HASLC(*x)) {
      if (HASRC(*x)) {
        s.push(x->rc);
      }
      s.push(x->lc);
    } else {
      s.push(x->rc);
    }
  }
  s.pop();
}

template<class T>
void BinNode<T>::trav_posti(BinNodePos<T> x) {
  Stack<BinNodePos<T>> s;
  if (x) {
    s.push(x);
  }
  while (!s.empty()) {
    if (s.top() != x->parent) {
      goto_leftmost_leaf(s);
    }
    x = s.pop();
    print("{} ", tostr(x->data).c_str());
  }
}

template<class T>
void BinNode<T>::trav_post() {
  trav_posti(this);
}

template<class T>
bool BinNode<T>::operator<(const BinNode &bn) {
  return data < bn.data;
}

template<class T>
bool BinNode<T>::operator==(const BinNode &bn) {
  return data == bn.data;
}

template<class T>
BinNodePos<T> BinNode<T>::zig() {
  BinNodePos<T> lchild = lc;
  lchild->parent = this->parent;
  if (lchild->parent) {
    ((this == lchild->parent->rc) ? lchild->parent->rc : lc->parent->lc) = lchild;
  }
  lc = lchild->rc;
  if (lc) {
    lc->parent = this;
  }
  lchild->rc = this;
  this->parent = lchild;
  height = 1 + MAX(STATURE(lc), STATURE(rc));
  lchild->height = 1 + MAX(STATURE(lchild->lc), STATURE(lchild->rc));
  for (BinNodePos<T> x = lchild->parent; x; x = x->parent) {
    if (HEIGHT_UPDATED(*x)) {
      break;
    } else {
      x->height = 1 + MAX(STATURE(x->lc), STATURE(x->rc));
    }
  }
  return lchild;
}

template<class T>
BinNodePos<T> BinNode<T>::zag() {
  BinNodePos<T> rchild = rc;
  rchild->parent = this->parent;
  if (rchild->parent) {
    ((this == rchild->parent->lc) ? rchild->parent->lc : rchild->parent->rc) = rchild;
  }
  rc = rchild->lc;
  if (rc) {
    rc->parent = this;
  }
  rchild->lc = this;
  this->parent = rchild;
  height = 1 + MAX(STATURE(lc), STATURE(rc));
  rchild->height = 1 + MAX(STATURE(rchild->lc), STATURE(rchild->rc));
  for (BinNodePos<T> x = rchild->parent; x; x = x->parent) {
    if (HEIGHT_UPDATED(*x)) {
      break;
    } else {
      x->height = 1 + MAX(STATURE(x->lc), STATURE(x->rc));
    }
  }
  return rchild;
}

template<class T>
void stretch_byzig(BinNodePos<T> &x) {
  int c = 0;
  BinNodePos<T> v = x;
  while (x->lc) {
    x = x->lc;
  }
  for (; v; v = v->rc) {
    while (v->lc) {
      v = v->zig();
      c++;
    }
  }
  printf("\nsize = %d, height = %d, #zig = %d\n\n", x->size(), x->height, c);
}

template<class T>
void stretch_byzag(BinNodePos<T> &x) {
  int c = 0;
  BinNodePos<T> p = x;
  while (p->rc) {
    p = p->rc;
  }
  while (x->lc) {
    x = x->lc;
  }
  for (; x != p; x = x->parent) {
    while (x->rc) {
      x->zag();
      c++;
    }
  }
  printf("\nsize = %d, height = %d, #zag = %d\n\n", x->size(), x->height, c);
}

template<class T>
BinNodePos<T> BinNode<T>::balance() {
  return nullptr;
}

template<class T>
BinNodePos<T> BinNode<T>::imitate(const BinNodePos<T> &bn) {
}

}// namespace jtd

#endif//BINODE_H
