//
// Created by wjl on 2022/7/2.
//

#ifndef BITMAP_H
#define BITMAP_H

#pragma once

#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <util.h>

namespace jtd {

class bitmap {
private:
  unsigned char *M{};
  int N{};

protected:
  void init(int n);

public:
  explicit bitmap(int n = 8);
  explicit bitmap(const char *file, int n = 8);
  ~bitmap();

  void set(int k);
  void clear(int k);
  bool test(int k);

  void dump(const char *file);
  char *bits2string(int n);
  void expand(int k);
  void print(int n);
};

void bitmap::init(int n) {
  M = new unsigned char[N = (n + 7) / 8];
  memset(M, 0, N);
}

bitmap::bitmap(int n) {
  init(n);
}

bitmap::bitmap(const char *file, int n) {
  init(n);
  FILE *fp = fopen(file, "r");
  fread(M, sizeof(char), N, fp);
  fclose(fp);
}

bitmap::~bitmap() {
  delete[] M;
  M = nullptr;
}

void bitmap::set(int k) {
  expand(k);
  M[k >> 3] |= (0x80 >> (k & 0x07));
}

void bitmap::clear(int k) {
  expand(k);
  M[k >> 3] &= ~(0x80 >> (k & 0x07));
}

bool bitmap::test(int k) {
  expand(k);
  return M[k >> 3] & (0x80 >> (k & 0x07));
}

void bitmap::dump(const char *file) {
  FILE *fp = fopen(file, "w");
  fwrite(M, sizeof(char), N, fp);
  fclose(fp);
}

char *bitmap::bits2string(int n) {
  expand(n - 1);
  char *s = new char[n + 1];
  s[n] = '\0';
  for (int i = 0; i < n; i++) s[i] = test(i) ? '1' : '0';
  return s;
}

void bitmap::expand(int k) {
  if (k < 8 * N) return;
  int oldN = N;
  unsigned char *oldM = M;
  init(2 * k);
  memcpy_s(M, N, oldM, oldN);
  delete[] oldM;
}

void bitmap::print(int n) {
  expand(n);
  for (int i = 0; i < n; i++) printf(test(i) ? "1" : "0");
}

}// namespace jtd

#endif//BITMAP_H
