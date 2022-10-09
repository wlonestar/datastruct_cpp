//
// Created by wjl15 on 2022/6/20.
//

#ifndef STACK_H
#define STACK_H

#pragma once

#include <list.h>

namespace jtd {

template<class T>
class Stack : public List<T> {
public:
  void push(const T &e);
  T pop();
  T &top();
};

template<class T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &s) {
  os << typeid(s).name() << " : ";
  for (int i = 0; i < s.size(); i++) {
    os << s[i] << " ";
  }
  os << "\n";
  return os;
}

template<class T>
void print(const Stack<T> &s) {
  print("{} : ", typeid(s).name());
  for (int i = 0; i < s.size(); i++) {
    print("{} ", tostr(s[i]).c_str());
  }
  print("\n");
}

template<class T>
void Stack<T>::push(const T &e) {
  this->insertlast(e);
}

template<class T>
T Stack<T>::pop() {
  return this->remove(this->last());
}

template<class T>
T &Stack<T>::top() {
  return this->last()->data;
}

}// namespace jtd

#endif//STACK_H
