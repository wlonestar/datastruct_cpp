//
// Created by wjl on 2022/7/14.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

#pragma once

#include <bitmap.h>
#include <dictionary.h>
#include <entry.h>

namespace jtd {

#define PRIME_1048576 "../../prime-1048576-bitmap.txt"

template<class K, class V>
class Hashtable : public Dictionary<K, V> {
private:
  int N, L;

protected:
  int probe4hit(const K &k);
  int probe4free(const K &k);
  void rehash();

public:
  int M;
  Entry<K, V> **ht;
  bitmap *removed;

  explicit Hashtable(int c = 5);
  ~Hashtable();
  int size() const;
  bool put(K k, V v);
  V *get(K k);
  bool remove(K k);
};

template<class K, class V>
void print(Hashtable<K, V> &ht) {
  for (int i = 0; i < ht.M; i++) {
    print("  {}  ", tostr(i).c_str());
  }
  print("\n");
  for (int i = 0; i < ht.M; i++) {
    if (ht.ht[i]) {
      print("-<{}>-", tostr(ht.ht[i]->key).c_str());
    } else if (ht.removed->test(i)) {
      print("-<****>-");
    } else {
      print("--------");
    }
  }
  print("\n");
  for (int i = 0; i < ht.M; i++) {
    if (ht.ht[i]) {
      print("    {}   ", tostr(ht.ht[i]->value).c_str());
    } else if (ht.removed->test(i)) {
      print("    *   ");
    } else {
      print("        ");
    }
  }
  print("\n");
}

static size_t hashcode(char c) {
  return (size_t) c;
}

static size_t hashcode(int k) {
  return (size_t) k;
}

static size_t hashcode(long long i) {
  return (size_t) ((i >> 32) + (int) i);
}

static size_t hashcode(char s[]) {
  unsigned int h = 0;
  for (size_t n = strlen(s), i = 0; i < n; i++) {
    h = (h << 5) | (h >> 27);
    h += (int) s[i];
  }
  return (size_t) h;
}

int prime_nlt(int c, int n, const char *file) {
  bitmap b(file, n);
  while (c < n) {
    if (b.test(c)) {
      c++;
    } else {
      return c;
    }
  }
  return c;
}

template<class K, class V>
int Hashtable<K, V>::probe4hit(const K &k) {
  int r = hashcode(k) % M;
  while ((ht[r] && (k != ht[r]->key)) || removed->test(r)) {
    r = (r + 1) % M;
  }
  return r;
}

template<class K, class V>
int Hashtable<K, V>::probe4free(const K &k) {
  int r = hashcode(k) % M;
  while (ht[r]) {
    r = (r + 1) % M;
  }
  return r;
}

template<class K, class V>
void Hashtable<K, V>::rehash() {
  int oldm = M;
  Entry<K, V> **oldht = ht;
  M = prime_nlt(4 * N, 1048576, PRIME_1048576);
  ht = new Entry<K, V> *[M];
  N = 0;
  memset(ht, 0, sizeof(Entry<K, V> *) * M);
  release(removed);
  removed = new bitmap(M);
  L = 0;
  for (int i = 0; i < oldm; i++) {
    if (oldht[i]) {
      put(oldht[i]->key, oldht[i]->value);
    }
  }
  release(oldht);
}

template<class K, class V>
Hashtable<K, V>::Hashtable(int c) {
  M = prime_nlt(c, 1048576, PRIME_1048576);
  N = 0;
  ht = new Entry<K, V> *[M];
  memset(ht, 0, sizeof(Entry<K, V> *) * M);
  removed = new bitmap(M);
  L = 0;
}

template<class K, class V>
Hashtable<K, V>::~Hashtable() {
  for (int i = 0; i < M; i++) {
    if (ht[i]) {
      release(ht[i]);
    }
  }
  release(ht);
  release(removed);
}

template<class K, class V>
int Hashtable<K, V>::size() const {
  return N;
}

template<class K, class V>
bool Hashtable<K, V>::put(K k, V v) {
  if (ht[probe4hit(k)]) {
    return false;
  }
  int r = probe4free(k);
  ht[r] = new Entry<K, V>(k, v);
  ++N;
  if (removed->test(r)) {
    removed->clear(r);
    --L;
  }
  if ((N + L) * 2 > M) {
    rehash();
  }
  return true;
}

template<class K, class V>
V *Hashtable<K, V>::get(K k) {
  int r = probe4hit(k);
  return ht[r] ? &(ht[r]->value) : NULL;
}

template<class K, class V>
bool Hashtable<K, V>::remove(K k) {
  int r = probe4hit(k);
  if (!ht[r]) {
    return false;
  }
  release(ht[r]);
  ht[r] = NULL;
  removed->set(r);
  --N;
  ++L;
  if (3 * N < L) {
    rehash();
  }
  return true;
}

}// namespace jtd

#endif//HASHTABLE_H
