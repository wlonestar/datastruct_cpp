//
// Created by wjl on 2022/7/12.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

#pragma once

namespace jtd {

template<class K, class V>
class Dictionary {
public:
  virtual int size() const = 0;
  virtual bool put(K k, V v) = 0;
  virtual V *get(K k) = 0;
  virtual bool remove(K k) = 0;
};

}// namespace jtd

#endif//DICTIONARY_H
