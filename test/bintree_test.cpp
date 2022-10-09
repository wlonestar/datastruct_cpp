//
// Created by wjl15 on 2022/6/20.
//

#include <bintree.h>

namespace jtd {

template<class T>
bool create_bintree(BinTree<T> &bt, BinNodePos<T> x, int h) {
  if (h <= 0) {
    return false;
  }
  if (random(h) > 0) {
    create_bintree(bt, bt.insert(x, (T) random<double>(h * h * h)), h - 1);
  }
  if (random(h) > 0) {
    create_bintree(bt, bt.insert((T) random<double>(h * h * h), x), h - 1);
  }
  return true;
}

template<class T>
BinNodePos<T> random_pos(BinNodePos<T> root) {
  if (!HASCHILD(*root)) {
    return root;
  }
  if (!HASLC(*root)) {
    return random(6) ? random_pos(root->rc) : root;
  }
  if (!HASRC(*root)) {
    return random(6) ? random_pos(root->lc) : root;
  }
  return random(2) ? random_pos(root->lc) : random_pos(root->rc);
}

template<class T>
void test_bintree(int h) {
  log("=== generate a random list\n");
  BinTree<T> bt;
  print(bt);
  bt.insert((T) random(h * h * h));
  print(bt);
  create_bintree(bt, bt.root(), h);
  print(bt);
  bt.trav_prer();
  bt.trav_pre();
  bt.trav_inr();
  bt.trav_in();
  bt.trav_postr();
  bt.trav_post();
  bt.trav_level();
}

}// namespace jtd

int main() {
//  std::locale::global(std::locale("zh_CN"));
  jtd::test_bintree<int>(5);
  return 0;
}
