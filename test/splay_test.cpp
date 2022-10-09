//
// Created by wjl on 2022/7/10.
//

#include <splay.h>

namespace jtd {

template<class T>
void test_splay(int n) {
  Splay<T> splay;
  while (splay.size() < n) {
    T e = random((T) n * 3);
    switch (random(3)) {
      case 0: {
        print("Searching for {} ...\n", tostr(e).c_str());
        if (splay.search(e)) {
          print("Found with");
          print(*splay.root());
          print("\n");
        } else {
          print("Not found\n");
        }
        break;
      }
      case 1: {
        print("Removing {} ...\n", tostr(e).c_str());
        if (splay.remove(e)) {
          print("Removal done\n");
        } else {
          print("{}", tostr(e).c_str());
          print(" not exists\n");
        }
        break;
      }
      default: {
        print("Inserting {} ...\n", tostr(e).c_str());
        splay.insert(e);
        if (e == splay.root()->data) {
          print("Insertion done with");
          print(*splay.root());
          print("\n");
        } else {
          print("{} duplicated", tostr(e).c_str());
        }
        break;
      }
    }
    print(splay);
  }
  while (splay.size() > 0) {
    T e = random((T) n * 3);
    print("Removing {} ...\n", tostr(e).c_str());
    if (splay.remove(e)) {
      print("Removal done\n");
      print(splay);
    } else {
      print("{} not exists\n", tostr(e).c_str());
    }
  }
}

}// namespace jtd

int main() {
  jtd::test_splay<int>(10);
  return 0;
}
