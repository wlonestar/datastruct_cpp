//
// Created by wjl on 2022/7/3.
//

#include <bstree.h>

namespace jtd {

template<class T>
void test_bstree(int n) {
  BSTree<T> bst;
  while (bst.size() < n) {
    bst.insert(random(n * 3));
  }
  print(bst);
  bst.stretch2lpath();
  print(bst);
  while (!bst.empty()) {
    bst.remove(bst.root()->data);
  }

  while (bst.size() < n) {
    bst.insert(random(n * 3));
  }
  print(bst);
  bst.stretch2rpath();
  print(bst);
  while (!bst.empty()) {
    bst.remove(bst.root()->data);
  }

  while (bst.size() < n) {
    T e = random((T) n * 3);
    switch (random(3)) {
      case 0: {
        print("Searching for ");
        print("{}", tostr(e).c_str());
        printf(" ... ");
        BinNodePos<T> &p = bst.search(e);
        p ? print("Found with {}\n", tostr(p->data).c_str()) : print("not found\n");
        break;
      }
      case 1: {
        print("Removing ");
        print("{}", tostr(e).c_str());
        printf(" ... ");
        bst.remove(e) ? print("Done\n"), print(bst) : print("not exists\n");
        break;
      }
      default: {
        print("Inserting ");
        print("{}", tostr(e).c_str());
        print(" ... ");
        print("Done with {}\n", tostr(bst.insert(e)->data).c_str());
        print(bst);
        break;
      }
    }
  }
}

}// namespace jtd

int main() {
  std::locale::global(std::locale("zh_CN.UTF-8"));
  jtd::test_bstree<int>(15);
  return 0;
}
