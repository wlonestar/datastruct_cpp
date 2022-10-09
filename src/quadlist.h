//
// Created by wjl on 2022/7/12.
//

#ifndef QUADLIST_H
#define QUADLIST_H

#pragma once

#include <entry.h>

namespace jtd {

template<class T>
class QuadlistNode;

template<class T>
using QlistNodePos = QuadlistNode<T> *;

template<class T>
class QuadlistNode {
public:
  T entry;
  QlistNodePos<T> pred;
  QlistNodePos<T> succ;
  QlistNodePos<T> above;
  QlistNodePos<T> below;

  explicit QuadlistNode(T e = T(), QlistNodePos<T> p = NULL, QlistNodePos<T> s = NULL,
                        QlistNodePos<T> a = NULL, QlistNodePos<T> b = NULL);

  QlistNodePos<T> insertsuccabove(const T &e, QlistNodePos<T> b = NULL);
};

template<class T>
QuadlistNode<T>::QuadlistNode(T e, QlistNodePos<T> p, QlistNodePos<T> s,
                              QlistNodePos<T> a, QlistNodePos<T> b)
    : entry(e), pred(p), succ(s), above(a), below(b) {}

template<class T>
QlistNodePos<T> QuadlistNode<T>::insertsuccabove(const T &e, QlistNodePos<T> b) {
  auto x = new QuadlistNode<T>(e, this, succ, NULL, b);
  succ->pred = x;
  succ = x;
  if (b) {
    b->above = x;
  }
  return x;
}

template<class T>
class Quadlist {
private:
  int _size{};
  QlistNodePos<T> header;
  QlistNodePos<T> trailer;

protected:
  void init();
  int clear();

public:
  Quadlist();
  ~Quadlist();

  int size() const;
  bool empty() const;
  QlistNodePos<T> first() const;
  QlistNodePos<T> last() const;
  bool valid(QlistNodePos<T> p);
  T remove(QlistNodePos<T> p);
  QlistNodePos<T> insertafterabove(const T &e, QlistNodePos<T> p, QlistNodePos<T> b = NULL);
};

template<class T>
void print(Quadlist<T> &q) {
  if (q.empty()) {
    printf("\n");
    return;
  }
  QuadlistNode<T> *curr = q.first()->pred;
  QuadlistNode<T> *base = q.first();
  while (base->below) base = base->below;
  while (base->pred) base = base->pred;
  for (int i = 0; i < q.size(); i++) {
    curr = curr->succ;
    QuadlistNode<T> *proj = curr;
    while (proj->below) proj = proj->below;
    while ((base = base->succ) != proj) {
      print("------------");
    }
    print(curr->entry);
  }
  print("\n");
}

template<class T>
void Quadlist<T>::init() {
  header = new QuadlistNode<T>;
  trailer = new QuadlistNode<T>;
  header->succ = trailer;
  header->pred = NULL;
  trailer->pred = header;
  trailer->succ = NULL;
  header->above = trailer->above = NULL;
  header->below = trailer->below = NULL;
  _size = 0;
}

template<class T>
int Quadlist<T>::clear() {
  int old = _size;
  while (0 < _size) {
    remove(header->succ);
  }
  return old;
}

template<class T>
Quadlist<T>::Quadlist() {
  init();
}

template<class T>
Quadlist<T>::~Quadlist() {
  clear();
  delete header;
  delete trailer;
}

template<class T>
int Quadlist<T>::size() const {
  return _size;
}

template<class T>
bool Quadlist<T>::empty() const {
  return _size <= 0;
}

template<class T>
QlistNodePos<T> Quadlist<T>::first() const {
  return header->succ;
}

template<class T>
QlistNodePos<T> Quadlist<T>::last() const {
  return trailer->pred;
}

template<class T>
bool Quadlist<T>::valid(QlistNodePos<T> p) {
  return p && (trailer != p) && (header != p);
}

template<class T>
T Quadlist<T>::remove(QlistNodePos<T> p) {
  p->pred->succ = p->succ;
  p->succ->pred = p->pred;
  _size--;
  T e = p->entry;
  delete p;
  return e;
}

template<class T>
QlistNodePos<T> Quadlist<T>::insertafterabove(const T &e, QlistNodePos<T> p, QlistNodePos<T> b) {
  _size++;
  return p->insertsuccabove(e, b);
}

}// namespace jtd

#endif//QUADLIST_H
