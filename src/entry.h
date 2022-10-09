//
// Created by wjl on 2022/7/12.
//

#ifndef ENTRY_H
#define ENTRY_H

#pragma once

namespace jtd {

template<class K, class V>
class Entry {
public:
  K key;
  V value;

  explicit Entry(K k = K(), V v = V());
  Entry(const Entry<K, V> &e);

  bool operator<(const Entry<K, V> &e);
  bool operator>(const Entry<K, V> &e);
  bool operator==(const Entry<K, V> &e);
  bool operator!=(const Entry<K, V> &e);
};

template<class K, class V>
void print(Entry<K, V> &e) {
  print("-<{}:{}>-", tostr(e.key).clear(), tostr(e.value).clear());
}

template<class K, class V>
Entry<K, V>::Entry(K k, V v) : key(k), value(v) {}

template<class K, class V>
Entry<K, V>::Entry(const Entry<K, V> &e) : key(e.key), value(e.value) {}

template<class K, class V>
bool Entry<K, V>::operator<(const Entry<K, V> &e) {
  return key < e.key;
}

template<class K, class V>
bool Entry<K, V>::operator>(const Entry<K, V> &e) {
  return key > e.key;
}

template<class K, class V>
bool Entry<K, V>::operator==(const Entry<K, V> &e) {
  return key == e.key;
}

template<class K, class V>
bool Entry<K, V>::operator!=(const Entry<K, V> &e) {
  return key != e.key;
}

}// namespace jtd

#endif//ENTRY_H
