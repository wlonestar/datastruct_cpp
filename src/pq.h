//
// Created by wjl on 2022/7/14.
//

#ifndef PQ_H
#define PQ_H

#pragma once

namespace jtd {

template<class T>
class PQ {
public:
  virtual void insert(T e) = 0;
  virtual T get_max() = 0;
  virtual T del_max() = 0;
};

}// namespace jtd

#endif//PQ_H
