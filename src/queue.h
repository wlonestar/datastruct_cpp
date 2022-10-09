//
// Created by wjl15 on 2022/6/20.
//

#ifndef QUEUE_H
#define QUEUE_H

#pragma once

#include <list.h>

namespace jtd {

template<class T>
class Queue : public List<T> {
public:
  void enque(const T &e);
  T deque();
  T &front();
};

template<class T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &q) {
  os << typeid(q).name() << " : ";
  for (int i = 0; i < q.size(); i++) {
    os << q[i] << " ";
  }
  os << "\n";
  return os;
}

template<class T>
void print(const Queue<T> &q) {
  print("{} : ", typeid(q).name());
  for (int i = 0; i < q.size(); i++) {
    print("{} ", tostr(q[i]).c_str());
  }
  print("\n");
}

template<class T>
void Queue<T>::enque(const T &e) {
  this->insertlast(e);
}

template<class T>
T Queue<T>::deque() {
  return this->remove(this->first());
}

template<class T>
T &Queue<T>::front() {
  return this->first()->data;
}

}

#endif//QUEUE_H
