//
// Created by wjl on 2022/7/10.
//

#include <avl.h>

namespace jtd {

template<class T>
void test_avl(int n) {
  Avl<T> avl;
  while (avl.size() < n) {
    T e = random((T) n * 3);
    switch (random(3)) {
      case 0: {
        print("Searching for {} ...\n", tostr(e).c_str());
        BinNodePos<T> &p = avl.search(e);
        if (p) {
          print("Found with");
          print(*p);
          print("\n");
        } else {
          print("Not found\n");
        }
        break;
      }
      case 1: {
        print("Removing {} ...\n", tostr(e).c_str());
        if (avl.remove(e)) {
          print("Done\n");
          print(avl);
        } else {
          print("Not exists\n");
        }
        break;
      }
      default: {
        print("Inserting {} ...\n", tostr(e).c_str());
        BinNodePos<T> p = avl.insert(e);
        if (p->data != e) {
          print("{} <> {}\n", tostr(p->data).c_str(), tostr(e).c_str());
        }
        print("Done with");
        print(*p);
        print("\n");
        print(avl);
        break;
      }
    }
  }
  while (avl.size() > 0) {
    T e = random((T) n * 3);
    print("Removing {} ...\n", tostr(e).c_str());
    if (avl.remove(e)) {
      print("Done\n");
      print(avl);
    } else {
      print("Not exists\n");
    }
  }
}

}// namespace jtd

int main() {
  std::locale::global(std::locale("zh_CN.UTF-8"));
  jtd::test_avl<int>(10);
  return 0;
}
