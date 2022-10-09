//
// Created by wjl15 on 2022/6/20.
//

#ifndef VECTOR_H
#define VECTOR_H

#pragma once

#include <fibonacci.h>
#include <util.h>

namespace jtd {

#define VECTOR_CAPACITY 10

template<class T>
class Vector {
protected:
  T *_elem;
  int _capacity{};
  int _size{};

  void copyfrom(const T *a, int lo, int hi);
  void expand();
  void shrink();
  int max(int lo, int hi);
  void merge(int lo, int mi, int hi);
  int partition(int lo, int hi);

public:
  explicit Vector();
  Vector(int c, int s, T v);
  Vector(const T *a, int n);
  Vector(const T *a, int lo, int hi);
  Vector(const Vector<T> &v);
  Vector(const Vector<T> &v, int lo, int hi);
  ~Vector();

  int size() const;
  bool empty() const;
  int find(const T &e, int lo, int hi) const;
  int find(const T &e) const;
  int binsearch(const T &e, int lo, int hi) const;
  int binsearch(const T &e) const;
  int fibsearch(const T &e, int lo, int hi) const;
  int fibsearch(const T &e) const;
  int search(const T &e, int lo, int hi) const;
  int search(const T &e) const;

  T &operator[](int i);
  const T &operator[](int i) const;
  Vector<T> &operator=(const Vector<T> &v);
  int remove(int lo, int hi);
  T remove(int i);
  int insert(int i, const T &e);
  int insert(const T &e);
  void bubblesort(int lo, int hi);
  void bubblesort();
  void selectsort(int lo, int hi);
  void selectsort();
  void mergesort(int lo, int hi);
  void mergesort();
  void heapsort(int lo, int hi);
  void heapsort();
  void quicksort(int lo, int hi);
  void quicksort();
  void shellsort(int lo, int hi);
  void shellsort();
  void sort(int lo, int hi);
  void sort();
  void unsort(int lo, int hi);
  void unsort();
  int deduplicate();
  int uniquify();
};

template<class T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &v) {
  os << typeid(v).name() << " : ";
  for (int i = 0; i < v.size(); i++) {
    os << v[i] << " ";
  }
  os << "\n";
  return os;
}

template<class T>
void print(const Vector<T> &v) {
  print("{} : ", typeid(v).name());
  for (int i = 0; i < v.size(); i++) {
    print("{} ", tostr(v[i]).c_str());
  }
  print("\n");
}

template<class T>
void Vector<T>::copyfrom(const T *a, int lo, int hi) {
  _elem = new T[_capacity = 2 * (hi - lo)];
  for (_size = 0; lo < hi; _size++, lo++) {
    _elem[_size] = a[lo];
  }
}

template<class T>
void Vector<T>::expand() {
  if (_size < _capacity) {
    return;
  }
  if (_capacity < VECTOR_CAPACITY) {
    _capacity = VECTOR_CAPACITY;
  }
  T *old = _elem;
  _elem = new T[_capacity <<= 1];
  for (int i = 0; i < _size; i++) {
    _elem[i] = old[i];
  }
  delete[] old;
}

template<class T>
void Vector<T>::shrink() {
  if (_capacity < VECTOR_CAPACITY << 1) {
    return;
  }
  if (_size << 2 > _capacity) {
    return;
  }
  T *old = _elem;
  _elem = new T[_capacity >>= 1];
  for (int i = 0; i < _size; i++) {
    _elem[i] = old[i];
  }
  delete[] old;
}

template<class T>
int Vector<T>::max(int lo, int hi) {
  int max = hi;
  while (lo < hi--) {
    if (_elem[hi] > _elem[max]) {
      max = hi;
    }
  }
  return max;
}

template<class T>
void Vector<T>::merge(int lo, int mi, int hi) {
  T *a = _elem + lo;
  T *b = new T[mi - lo];
  for (int i = 0; i < mi - lo; i++) {
    b[i] = a[i];
  }
  T *c = _elem + mi;
  int i = 0, j = 0, k = 0;
  while (j < mi - lo && k < hi - mi) {
    a[i++] = ((b[j] <= c[k]) ? b[j++] : c[k++]);
  }
  while (j < mi - lo) {
    a[i++] = b[j++];
  }
  while (k < hi - mi) {
    a[i++] = c[k++];
  }
  delete[] b;
}

template<class T>
int Vector<T>::partition(int lo, int hi) {
  swap(_elem[lo], _elem[lo + random(hi - lo)]);
  T pivot = _elem[lo];
  int mi = lo;
  for (int k = lo + 1; k < hi; k++) {
    if (_elem[k] < pivot) {
      swap(_elem[++mi], _elem[k]);
    }
  }
  swap(_elem[lo], _elem[mi]);
  return mi;
}

template<class T>
Vector<T>::Vector() {
  _elem = new T[_capacity = VECTOR_CAPACITY];
  _size = 0;
}

template<class T>
Vector<T>::Vector(int c, int s, T v) {
  _elem = new T[_capacity = c];
  for (_size = 0; _size < s; _elem[_size++] = v)
    ;
}

template<class T>
Vector<T>::Vector(const T *a, int n) {
  copyfrom(a, 0, n);
}

template<class T>
Vector<T>::Vector(const T *a, int lo, int hi) {
  copyfrom(a, lo, hi);
}

template<class T>
Vector<T>::Vector(const Vector<T> &v) {
  copyfrom(v._elem, 0, v.size());
}

template<class T>
Vector<T>::Vector(const Vector<T> &v, int lo, int hi) {
  copyfrom(v._elem, lo, hi);
}

template<class T>
Vector<T>::~Vector() {
  delete[] _elem;
}

template<class T>
int Vector<T>::size() const {
  return _size;
}

template<class T>
bool Vector<T>::empty() const {
  return !_size;
}

template<class T>
int Vector<T>::find(const T &e, int lo, int hi) const {
  while ((lo < hi--) && (e != _elem[hi]))
    ;
  return hi;
}

template<class T>
int Vector<T>::find(const T &e) const {
  return find(e, 0, _size);
}

template<class T>
int Vector<T>::binsearch(const T &e, int lo, int hi) const {
  while (lo < hi) {
    int mi = (lo + hi) >> 1;
    (e < _elem[mi]) ? hi = mi : lo = mi + 1;
  }
  return lo - 1;
}

template<class T>
int Vector<T>::binsearch(const T &e) const {
  return binsearch(e, 0, _size);
}

template<class T>
int Vector<T>::fibsearch(const T &e, int lo, int hi) const {
  for (fib fib(hi - lo); lo < hi;) {
    while (hi - lo < fib.get()) {
      fib.prev();
    }
    int mi = lo + fib.get() - 1;
    (e < _elem[mi]) ? hi = mi : lo = mi + 1;
  }
  return --lo;
}

template<class T>
int Vector<T>::fibsearch(const T &e) const {
  return fibsearch(e, 0, _size);
}

template<class T>
int Vector<T>::search(const T &e, int lo, int hi) const {
  return binsearch(e, lo, hi);
}

template<class T>
int Vector<T>::search(const T &e) const {
  return (0 >= _size) ? -1 : search(e, 0, _size);
}

template<class T>
T &Vector<T>::operator[](int i) {
  return _elem[i];
}

template<class T>
const T &Vector<T>::operator[](int i) const {
  return _elem[i];
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &v) {
  if (_elem) {
    delete[] _elem;
  }
  copyfrom(v._elem, 0, v.size());
  return *this;
}

template<class T>
int Vector<T>::remove(int lo, int hi) {
  if (lo == hi) {
    return 0;
  }
  while (hi < _size) {
    _elem[lo++] = _elem[hi++];
  }
  _size = lo;
  shrink();
  return hi - lo;
}

template<class T>
T Vector<T>::remove(int i) {
  T e = _elem[i];
  remove(i, i + 1);
  return e;
}

template<class T>
int Vector<T>::insert(int i, const T &e) {
  expand();
  for (int k = _size; i < k; k--) {
    _elem[k] = _elem[k - 1];
  }
  _elem[i] = e;
  _size++;
  return i;
}

template<class T>
int Vector<T>::insert(const T &e) {
  return insert(_size, e);
}

template<class T>
void Vector<T>::bubblesort(int lo, int hi) {
  for (int last = --hi; lo < hi; hi = last) {
    for (int i = last = lo; i < hi; i++) {
      if (_elem[i] > _elem[i - 1]) {
        swap(_elem[last = i], _elem[i + 1]);
      }
    }
  }
}

template<class T>
void Vector<T>::bubblesort() {
  bubblesort(0, _size);
}

template<class T>
void Vector<T>::selectsort(int lo, int hi) {
  while (lo < --hi) {
    swap(_elem[max(lo, hi)], _elem[hi]);
  }
}

template<class T>
void Vector<T>::selectsort() {
  selectsort(0, _size);
}

template<class T>
void Vector<T>::mergesort(int lo, int hi) {
  if (hi - lo < 2) {
    return;
  }
  int mi = (lo + hi) / 2;
  mergesort(lo, mi);
  mergesort(mi, hi);
  merge(lo, mi, hi);
}

template<class T>
void Vector<T>::mergesort() {
  mergesort(0, _size);
}

#define PARENT(i) (((i) -1) >> 1)
#define LC(i) (1 + ((i) << 1))
#define RC(i) ((1 + (i)) << 1)
#define IN_HEAP(n, i) (((-1) < (i)) && ((i) < (n)))
#define LC_VALID(n, i) IN_HEAP(n, LC(i))
#define RC_VALID(n, i) IN_HEAP(n, RC(i))
#define BIGGER(a, i, j) (lt(a[i], a[j]) ? (j) : (i))
#define PROPER_PARENT(a, n, i)                              \
  (RC_VALID(n, i) ? BIGGER(a, BIGGER(a, (i), LC(i)), RC(i)) \
                  : (LC_VALID(n, i) ? BIGGER(a, (i), LC(i)) : (i)))

template<class T>
int percolate_up(T *a, int i) {
  while (0 < i) {
    int j = PARENT(i);
    if (lt(a[i], a[j])) {
      break;
    }
    swap(a[i], a[j]);
    i = j;
  }
  return i;
}

template<class T>
int percolate_down(T *a, int n, int i) {
  int j;
  while (i != (j = PROPER_PARENT(a, n, i))) {
    swap(a[i], a[j]);
    i = j;
  }
  return i;
}

template<class T>
void heapify(T *a, const int n) {
  for (int i = n / 2 - 1; 0 <= i; i--) {
    percolate_down(a, n, i);
  }
}

template<class T>
void Vector<T>::heapsort(int lo, int hi) {
  T *a = _elem + lo;
  int n = hi - lo;
  heapify(a, n);
  while (0 < --n) {
    swap(a[0], a[n]);
    percolate_down(a, n, 0);
  }
}

template<class T>
void Vector<T>::heapsort() {
  heapsort(0, _size);
}

template<class T>
void Vector<T>::quicksort(int lo, int hi) {
  if (hi - lo < 2) {
    return;
  }
  int mi = partition(lo, hi);
  quicksort(lo, mi);
  quicksort(mi + 1, hi);
}

template<class T>
void Vector<T>::quicksort() {
  quicksort(0, _size);
}

template<class T>
void Vector<T>::shellsort(int lo, int hi) {
  for (int d = 0x3FFFFFFF; 0 < d; d >>= 1) {
    for (int j = lo + d; j < hi; j++) {
      T x = _elem[j];
      int i = j - d;
      while (lo <= i && _elem[i] > x) {
        _elem[i + d] = _elem[i];
        i -= d;
      }
      _elem[i + d] = x;
    }
  }
}

template<class T>
void Vector<T>::shellsort() {
  shellsort(0, _size);
}

template<class T>
void Vector<T>::sort(int lo, int hi) {
  quicksort(lo, hi);
}

template<class T>
void Vector<T>::sort() {
  sort(0, _size);
}

template<class T>
void Vector<T>::unsort(int lo, int hi) {
  T *v = _elem + lo;
  for (int i = hi - lo; i > 0; i--) {
    swap(v[i - 1], v[random(i)]);
  }
}

template<class T>
void Vector<T>::unsort() {
  unsort(0, _size);
}

template<class T>
int Vector<T>::deduplicate() {
  int old = _size;
  for (int i = 1; i < _size;) {
    if (find(_elem[i], 0, i) < 0) {
      i++;
    } else {
      remove(i);
    }
  }
  return old - _size;
}

template<class T>
int Vector<T>::uniquify() {
  int i = 0, j = 0;
  while (++j < _size) {
    if (_elem[i] != _elem[j]) {
      _elem[++i] = _elem[j];
    }
  }
  _size = ++i;
  shrink();
  return j - i;
}

template<class T>
void random_vector(Vector<T> &v, int n, T range, bool sorted) {
  for (int i = 0; i < n; i++) {
    v.insert((T) random<double>(range));
  }
  if (sorted) {
    v.sort();
  }
}

template<class T>
void init2dvector(Vector<Vector<T>> &v, int n) {
  for (int i = 0; i < n; i++) {
    v.insert(Vector<T>(i + 1, i + 1, NULL));
  }
}

}// namespace jtd

#endif//VECTOR_H
