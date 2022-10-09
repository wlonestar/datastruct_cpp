//
// Created by wjl on 2022/7/12.
//

#ifndef SKIPLIST_H
#define SKIPLIST_H

#pragma once

#include <dictionary.h>
#include <entry.h>
#include <list.h>
#include <quadlist.h>

namespace jtd {

template<class K, class V>
class Skiplist : public Dictionary<K, V>, public List<Quadlist<Entry<K, V>> *> {
protected:
  bool skip_search(ListNode<Quadlist<Entry<K, V>> *> *&qlist,
                   QuadlistNode<Entry<K, V>> *&p, K &k);

public:
  int size() const;
  int level();
  bool put(K k, V v);
  V *get(K k);
  bool remove(K k);
};

//template<class K, class V>
//void print(Skiplist<K, V> &s) {
//
//}

template<class K, class V>
bool Skiplist<K, V>::skip_search(ListNode<Quadlist<Entry<K, V>> *> *&qlist,
                                 QuadlistNode<Entry<K, V>> *&p, K &k) {
  while (true) {
    while (p->succ && (p->entry.key <= k)) {
      p = p->succ;
    }
    p = p->pred;
    if (p->pred && (k == p->entry.key)) {
      return true;
    }
    qlist = qlist->succ;
    if (!qlist->succ) {
      return false;
    }
    p = (p->pred) ? p->below : qlist->data->first();
  }
}

template<class K, class V>
int Skiplist<K, V>::size() const {
  return this->empty() ? 0 : this->size();
}

template<class K, class V>
int Skiplist<K, V>::level() {
  return List<Quadlist<Entry<K, V>> *>::size();
}

template<class K, class V>
bool Skiplist<K, V>::put(K k, V v) {
  Entry<K, V> e = Entry<K, V>(k, v);
  if (this->empty()) {
    this->insertfirst(new Quadlist<Entry<K, V>>);
  }
  ListNode<Quadlist<Entry<K, V>> *> *qlist = this->first();
  QuadlistNode<Entry<K, V>> *p = qlist->data->first();
  if (skip_search(qlist, p, k)) {
    while (p->below) {
      p = p->below;
    }
  }
  qlist = this->last();
  QuadlistNode<Entry<K, V>> *b = qlist->data->insertafterabove(e, p);
  while (rand() & 1) {
    while (qlist->data->valid(p) && !p->above) {
      p = p->pred;
    }
    if (!qlist->data->valid(p)) {
      if (qlist == this->first()) {
        this->insertfirst(new Quadlist<Entry<K, V>>);
      }
      p = qlist->pred->data->first()->pred;
    } else {
      p = p->above;
    }
    qlist = qlist->pred;
    b = qlist->data->insertafterabove(e, p, b);
  }
  return true;
}

template<class K, class V>
V *Skiplist<K, V>::get(K k) {
  if (this->empty()) {
    return NULL;
  }
  ListNode<Quadlist<Entry<K, V>> *> *qlist = this->first();
  QuadlistNode<Entry<K, V>> *p = qlist->data->first();
  return skip_search(qlist, p, k) ? &(p->entry.value) : NULL;
}

template<class K, class V>
bool Skiplist<K, V>::remove(K k) {
  if (this->empty()) {
    return false;
  }
  ListNode<Quadlist<Entry<K, V>> *> *qlist = this->first();
  QuadlistNode<Entry<K, V>> *p = qlist->data->first();
  if (!skip_search(qlist, p, k)) {
    return false;
  }
  do {
    QuadlistNode<Entry<K, V>> *lower = p->below;
    qlist->data->remove(p);
    p = lower;
    qlist = qlist->succ;
  } while (qlist->succ);
  while (!this->empty() && this->first()->data->empty()) {
    List<Quadlist<Entry<K, V>> *>::remove(this->first());
  }
  return true;
}

}// namespace jtd

#endif//SKIPLIST_H
