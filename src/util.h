//
// Created by wjl15 on 2022/6/19.
//

#ifndef UTIL_H
#define UTIL_H

#pragma once

#include <chrono>
#include <cstdarg>
#include <exception>
#include <iostream>
#include <random>
#include <string>

namespace jtd {

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

template<class T>
void swap(T &lhs, T &rhs) {
  auto tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}

void print(const char *format, ...) {
  std::string res(format);
  size_t count = 0;
  size_t pos = res.find("{}", 0);
  while (pos != std::string::npos) {
    count += 1;
    pos = res.find("{}", pos + 1);
  }
  va_list args;
  va_start(args, format);
  pos = res.find("{}", 0);
  for (int i = 0; i < count; i++) {
    res.replace(pos, 2, va_arg(args, char *));
    pos = res.find("{}", pos + 1);
  }
  va_end(args);
  std::cout << res;
}

void log(const char *format, ...) {
  std::string res(format);
  size_t count = 0;
  size_t pos = res.find("{}", 0);
  while (pos != std::string::npos) {
    count += 1;
    pos = res.find("{}", pos + 1);
  }
  try {
    va_list args;
    va_start(args, format);
    pos = res.find("{}", 0);
    for (int i = 0; i < count; i++) {
      res.replace(pos, 2, va_arg(args, char *));
      pos = res.find("{}", pos + 1);
    }
    va_end(args);
  } catch (const std::exception &e) {
    std::cout << e.what() << "\n";
  }
  std::cout << res;
}

std::string tostr(bool v) {
  std::string s = (v ? "true" : "false");
  return s;
}

std::string tostr(int val) {
  return std::to_string(val);
}

std::string tostr(unsigned int val) {
  return std::to_string(val);
}

std::string tostr(size_t val) {
  return std::to_string(val);
}

std::string tostr(long val) {
  return std::to_string(val);
}

std::string tostr(unsigned long val) {
  return std::to_string(val);
}

std::string tostr(float val) {
  return std::to_string(val);
}

std::string tostr(double val) {
  return std::to_string(val);
}

std::string tostr(long double val) {
  return std::to_string(val);
}

std::string tostr(char c) {
  std::string s(1, c);
  return s;
}

std::string tostr(char *c) {
  std::string s(c);
  return s;
}

// [0, 10)
int random() {
  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, 9.0);
  return dist(rd);
}

// [0, range - 1)
int random(int range) {
  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, range - 1);
  return dist(rd);
}

// [lo, hi)
int random(int lo, int hi) {
  std::random_device rd;
  std::uniform_int_distribution<int> dist(lo, hi - 1);
  return dist(rd);
}

// [0, 10)
template<typename T>
T random() {
  std::random_device rd;
  std::uniform_real_distribution<T> dist(0, 9.0);
  return dist(rd);
}

// [0, range - 1)
template<typename T>
T random(T range) {
  std::random_device rd;
  std::uniform_real_distribution<T> dist(0, range - 1);
  return dist(rd);
}

// [lo, hi)
template<class T>
T random(T lo, T hi) {
  std::random_device rd;
  std::uniform_real_distribution<T> dist(lo, hi - 1);
  return dist(rd);
}

class timer {
private:
  std::chrono::time_point<std::chrono::steady_clock> begin;
  std::chrono::time_point<std::chrono::steady_clock> end;

public:
  timer() = default;

  void start() {
    begin = std::chrono::steady_clock::now();
  }

  double stop() {
    end = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::micro>(end - begin).count();
  }
};

template<class T>
static bool lt(T &lhs, T &rhs) {
  return lhs < rhs;
}

template<class T>
static bool lt(T *lhs, T *rhs) {
  return lt(*lhs, *rhs);
}

template<class T>
static bool eq(T &lhs, T &rhs) {
  return lhs == rhs;
}

template<class T>
static bool eq(T *lhs, T *rhs) {
  return eq(*lhs, *rhs);
}

template<class T>
struct cleaner {
  static void clean(T t) {
  }
};

template<class T>
struct cleaner<T *> {
  static void clean(T *t) {
    delete t;
  }
};

template<class T>
void release(T x) {
  cleaner<T>::clean(x);
}

}// namespace jtd

#endif//UTIL_H
