//
// Created by wjl15 on 2022/6/20.
//

#ifndef LIST_H
#define LIST_H

#pragma once

#include <util.h>

namespace jtd {

template<class T>
class ListNode;

template<class T>
using ListNodePos = ListNode<T> *;

template<class T>
class ListNode {
public:
  T data;
  ListNodePos<T> pred;
  ListNodePos<T> succ;

  ListNode() = default;
  explicit ListNode(T e, ListNodePos<T> p = nullptr, ListNodePos<T> s = nullptr);

  ListNodePos<T> insertpred(const T &e);
  ListNodePos<T> insertsucc(const T &e);
};

template<class T>
ListNode<T>::ListNode(T e, ListNodePos<T> p, ListNodePos<T> s)
    : data(e), pred(p), succ(s) {}

template<class T>
ListNodePos<T> ListNode<T>::insertpred(const T &e) {
  auto x = new ListNode(e, pred, this);
  pred->succ = x;
  pred = x;
  return x;
}

template<class T>
ListNodePos<T> ListNode<T>::insertsucc(const T &e) {
  auto x = new ListNode(e, this, succ);
  succ->pred = x;
  succ = x;
  return x;
}

template<class T>
class List {
private:
  int _size{};
  ListNodePos<T> header;
  ListNodePos<T> trailer;

protected:
  void init();
  int clear();
  void copynodes(ListNodePos<T> p, int n);
  ListNodePos<T> merge(ListNodePos<T> p, int n, List<T> &l, ListNodePos<T> q, int m);

public:
  List();
  List(const List<T> &l);
  List(const List<T> &l, int i, int n);
  List(ListNodePos<T> p, int n);
  ~List();

  int size() const;
  bool empty() const;
  T &operator[](int i) const;
  ListNodePos<T> first() const;
  ListNodePos<T> last() const;
  bool valid(ListNodePos<T> p);
  ListNodePos<T> find(const T &e, int n, ListNodePos<T> p) const;
  ListNodePos<T> find(const T &e);
  ListNodePos<T> search(const T &e, int n, ListNodePos<T> p) const;
  ListNodePos<T> search(const T &e);
  ListNodePos<T> max(ListNodePos<T> p, int n);
  ListNodePos<T> max();

  ListNodePos<T> insertfirst(const T &e);
  ListNodePos<T> insertlast(const T &e);
  ListNodePos<T> insert(ListNodePos<T> p, const T &e);
  ListNodePos<T> insert(const T &e, ListNodePos<T> p);
  T remove(ListNodePos<T> p);
  void merge(List<T> &l);
  void mergesort(ListNodePos<T> &p, int n);
  void mergesort();
  void selectsort(ListNodePos<T> p, int n);
  void selectsort();
  void insertsort(ListNodePos<T> p, int n);
  void insertsort();
  void radixsort(ListNodePos<T> p, int n);
  void radixsort();
  void sort(ListNodePos<T> p, int n);
  void sort();
  int deduplicate();
  int uniquify();
  void reverse();
};

template<class T>
std::ostream &operator<<(std::ostream &os, const List<T> &l) {
  os << typeid(l).name() << " : ";
  for (int i = 0; i < l.size(); i++) {
    os << l[i] << " ";
  }
  os << "\n";
  return os;
}

template<class T>
void print(const List<T> &l) {
  print("{} : ", typeid(l).name());
  for (int i = 0; i < l.size(); i++) {
    print("{} ", tostr(l[i]).c_str());
  }
  print("\n");
}

template<class T>
void List<T>::init() {
  header = new ListNode<T>;
  trailer = new ListNode<T>;
  header->succ = trailer;
  header->pred = nullptr;
  trailer->pred = header;
  trailer->succ = nullptr;
  _size = 0;
}

template<class T>
int List<T>::clear() {
  int old = _size;
  while (0 < _size) {
    remove(header->succ);
  }
  return old;
}

template<class T>
void List<T>::copynodes(ListNodePos<T> p, int n) {
  init();
  while (n--) {
    insertlast(p->data);
    p = p->succ;
  }
}

template<class T>
ListNodePos<T> List<T>::merge(ListNodePos<T> p, int n, List<T> &l, ListNodePos<T> q, int m) {
  ListNodePos<T> pp = p->pred;
  while (0 < m && q != p) {
    if (0 < n && p->data <= q->data) {
      p = p->succ;
      n--;
    } else {
      insert(l.remove((q = q->succ)->pred), p);
      m--;
    }
  }
  return pp->succ;
}

template<class T>
List<T>::List() {
  init();
}

template<class T>
List<T>::List(const List<T> &l) {
  copynodes(l.first(), l._size);
}

template<class T>
List<T>::List(const List<T> &l, int i, int n) {
  ListNodePos<T> p = l.first();
  while (0 < i--) {
    p = p->succ;
  }
  copynodes(p, n);
}

template<class T>
List<T>::List(ListNodePos<T> p, int n) {
  copynodes(p, n);
}

template<class T>
List<T>::~List() {
  clear();
  delete header;
  delete trailer;
}

template<class T>
int List<T>::size() const {
  return _size;
}

template<class T>
bool List<T>::empty() const {
  return _size <= 0;
}

template<class T>
T &List<T>::operator[](int i) const {
  ListNodePos<T> p = first();
  while (0 < i--) {
    p = p->succ;
  }
  return p->data;
}

template<class T>
ListNodePos<T> List<T>::first() const {
  return header->succ;
}

template<class T>
ListNodePos<T> List<T>::last() const {
  return trailer->pred;
}

template<class T>
bool List<T>::valid(ListNodePos<T> p) {
  return p && (trailer != p) && (header != p);
}

template<class T>
ListNodePos<T> List<T>::find(const T &e, int n, ListNodePos<T> p) const {
  while (0 < n--) {
    if (e == (p = p->pred)->data) {
      return p;
    }
  }
  return nullptr;
}

template<class T>
ListNodePos<T> List<T>::find(const T &e) {
  return find(e, _size, trailer);
}

template<class T>
ListNodePos<T> List<T>::search(const T &e, int n, ListNodePos<T> p) const {
  do {
    p = p->pred;
    n--;
  } while ((-1 < n) && (e < p->data));
  return p;
}

template<class T>
ListNodePos<T> List<T>::search(const T &e) {
  return search(e, _size, trailer);
}

template<class T>
ListNodePos<T> List<T>::max(ListNodePos<T> p, int n) {
  ListNodePos<T> max = p;
  for (ListNodePos<T> cur = p; 1 < n; n--) {
    if (!lt((cur = cur->succ)->data, max->data)) {
      max = cur;
    }
  }
  return max;
}

template<class T>
ListNodePos<T> List<T>::max() {
  return max(header->succ, _size);
}

template<class T>
ListNodePos<T> List<T>::insertfirst(const T &e) {
  _size++;
  return header->insertsucc(e);
}

template<class T>
ListNodePos<T> List<T>::insertlast(const T &e) {
  _size++;
  return trailer->insertpred(e);
}

template<class T>
ListNodePos<T> List<T>::insert(ListNodePos<T> p, const T &e) {
  _size++;
  return p->insertsucc(e);
}

template<class T>
ListNodePos<T> List<T>::insert(const T &e, ListNodePos<T> p) {
  _size++;
  return p->insertpred(e);
}

template<class T>
T List<T>::remove(ListNodePos<T> p) {
  T e = p->data;
  p->pred->succ = p->succ;
  p->succ->pred = p->pred;
  delete p;
  _size--;
  return e;
}

template<class T>
void List<T>::merge(List<T> &l) {
  merge(header->succ, _size, l, l.header->succ, l._size);
}

template<class T>
void List<T>::mergesort(ListNodePos<T> &p, int n) {
  if (n < 2) {
    return;
  }
  int m = n >> 1;
  ListNodePos<T> q = p;
  for (int i = 0; i < m; i++) {
    q = q->succ;
  }
  mergesort(p, m);
  mergesort(q, n - m);
  p = merge(p, m, *this, q, n - m);
}

template<class T>
void List<T>::mergesort() {
  ListNodePos<T> p = first();
  mergesort(p, _size);
}

template<class T>
void List<T>::selectsort(ListNodePos<T> p, int n) {
  ListNodePos<T> head = p->pred;
  ListNodePos<T> tail = p;
  for (int i = 0; i < n; i++) {
    tail = tail->succ;
  }
  while (1 < n) {
    ListNodePos<T> m = max(head->succ, n);
    insert(remove(m), tail);
    tail = tail->pred;
    n--;
  }
}

template<class T>
void List<T>::selectsort() {
  selectsort(first(), _size);
}

template<class T>
void List<T>::insertsort(ListNodePos<T> p, int n) {
  for (int r = 0; r < n; r++) {
    insert(search(p->data, r, p), p->data);
    p = p->succ;
    remove(p->pred);
  }
}

template<class T>
void List<T>::insertsort() {
  insertsort(first(), _size);
}

template<class T>
void List<T>::radixsort(ListNodePos<T> p, int n) {
  ListNodePos<T> head = p->pred;
  ListNodePos<T> tail = p;
  for (int i = 0; i < n; i++) {
    tail = tail->succ;
  }
  for (int radixBit = 0x1; radixBit && (p = head); radixBit <<= 1) {
    for (int i = 0; i < n; i++) {
      radixBit &int(p->succ->data)
        ? insert(remove(p->succ), tail)
        : p = p->succ;
    }
  }
}

template<class T>
void List<T>::radixsort() {
  radixsort(first(), _size);
}

template<class T>
void List<T>::sort(ListNodePos<T> p, int n) {
  mergesort(p, n);
}

template<class T>
void List<T>::sort() {
  sort(first(), _size);
}

template<class T>
int List<T>::deduplicate() {
  int old = _size;
  ListNodePos<T> p = first();
  for (int i = 0; p != trailer; p = p->succ) {
    if (ListNodePos<T> q = find(p->data, i, p)) {
      remove(q);
    } else {
      i++;
    }
  }
  return old - _size;
}

template<class T>
int List<T>::uniquify() {
  if (_size < 2) {
    return 0;
  }
  int old = _size;
  ListNodePos<T> p = first();
  ListNodePos<T> q;
  while (trailer != (q = p->succ)) {
    if (p->data != q->data) {
      p = q;
    } else {
      remove(q);
    }
  }
  return old - _size;
}

template<class T>
void List<T>::reverse() {
  ListNodePos<T> p = header;
  ListNodePos<T> q = trailer;
  for (int i = 1; i < _size; i += 2) {
    swap((p = p->succ)->data, (q = q->pred)->data);
  }
}

}// namespace jtd

#endif//LIST_H
