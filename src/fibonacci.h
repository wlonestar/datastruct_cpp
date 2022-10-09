//
// Created by wjl15 on 2022/6/20.
//

#ifndef FIBONACCI_H
#define FIBONACCI_H

#pragma once

#include <cstddef>

namespace jtd {

class fib {
private:
  size_t f;
  size_t g;

public:
  explicit fib(int n);
  size_t get() const;
  size_t next();
  size_t prev();
};

fib::fib(int n) {
  f = 1;
  g = 0;
  while (g < n) {
    next();
  }
}

size_t fib::get() const {
  return g;
}

size_t fib::next() {
  g += f;
  f = g - f;
  return g;
}

size_t fib::prev() {
  f = g - f;
  g -= f;
  return g;
}

}// namespace jtd

#endif//FIBONACCI_H
