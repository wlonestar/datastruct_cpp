//
// Created by wjl on 2022/7/14.
//

#ifndef PQ_COMPHEAP_H
#define PQ_COMPHEAP_H

#pragma once

#include <vector.h>
#include <pq.h>

namespace jtd {

template<class T>
class PQ_compheap : public PQ<T>, public Vector<T> {
public:
  PQ_compheap() = default;
  PQ_compheap(T *a, int n);
  void insert(T e);
  T get_max();
  T del_max();
};

template<class T>
PQ_compheap<T>::PQ_compheap(T *a, int n) {
  this->copyfrom(a, 0, n);
  heapify(this->_elem, n);
}

template<class T>
void PQ_compheap<T>::insert(T e) {
  Vector<T>::insert(e);
  percolate_up(this->_elem, this->_size - 1);
}

template<class T>
T PQ_compheap<T>::get_max() {
  return this->_elem[0];
}

template<class T>
T PQ_compheap<T>::del_max() {
  T max = this->_elem[0];
  this->_elem[0] = this->_elem[--this->_size];
  percolate_down(this->_elem, this->_size, 0);
  return max;
}

};

#endif//PQ_COMPHEAP_H
