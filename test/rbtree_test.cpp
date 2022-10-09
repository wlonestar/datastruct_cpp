//
// Created by wjl on 2022/7/12.
//

#include <rbtree.h>

namespace jtd {

template<class T>
void test_rbtree(int n) {
  Rbtree<T> rb;
  while (rb.size() < n) {
    T e = random((T) n * 3);
    switch (random(6)) {
      case 0: {
        print("Searching for {} ...\n", tostr(e).c_str());
        BinNodePos<T> p = rb.search(e);
        if (p) {
          print("Found with");
          print(*p);
          print("\n");
        } else {
          print("Not found\n");
        }
        break;
      }
      case 1:
      case 2: {
        print("Removing {} ...\n", tostr(e).c_str());
        if (rb.remove(e)) {
          print("Done\n");
          print(rb);
        } else {
          print("Not exists\n");
        }
        break;
      }
      default: {
        print("Inserting {} ...\n", tostr(e).c_str());
        BinNodePos<T> p = rb.insert(e);
        if (p->data != e) {
          print("{} <> {}\n", tostr(p->data).c_str(), tostr(e).c_str());
        }
        print("Done with");
        print(*p);
        print("\n");
        print(rb);
        break;
      }
    }
  }
  while (rb.size() > 0) {
    T e = random((T) n * 3);
    print("Removing {} ...\n", tostr(e).c_str());
    if (rb.remove(e)) {
      print("Done\n");
      print(rb);
    } else {
      print("Not exists\n");
    }
  }
}

}// namespace jtd

int main() {
  std::locale::global(std::locale("zh_CN.UTF-8"));
  jtd::test_rbtree<int>(12);
  return 0;
}
