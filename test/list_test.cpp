//
// Created by wjl15 on 2022/6/20.
//

#include <list.h>

namespace jtd {

template<class T>
void create_list(List<T> &l, int size) {
  auto p = (random(2))
             ? l.insertlast((T) random(100))
             : l.insertfirst((T) random(100));
  for (int i = 0; i < size - 1; i++) {
    T e = (T) random(100);
    p = (random(2)) ? l.insert(p, e) : l.insert(e, p);
  }
}

template<class T>
void test_sort(List<T> &l) {
  timer t;
  print(l);
  t.start();
  l.mergesort();
  auto val1 = t.stop();
  print(l);
  log("== merge sort: {} micro seconds\n", tostr(val1).c_str());
  List<T> l1;
  create_list(l1, l.size());
  print(l1);
  t.start();
  l1.selectsort();
  auto val2 = t.stop();
  print(l1);
  log("== select sort: {} micro seconds\n", tostr(val2).c_str());
  List<T> l2;
  create_list(l2, l.size());
  print(l2);
  t.start();
  l2.insertsort();
  auto val3 = t.stop();
  print(l);
  log("== insert sort: {} micro seconds\n", tostr(val3).c_str());
  List<T> l3;
  create_list(l3, l.size());
  print(l3);
  t.start();
  l3.radixsort();
  auto val4 = t.stop();
  print(l3);
  log("== radix sort: {} micro seconds\n", tostr(val4).c_str());
}

template<class T>
void merge_test() {
  List<T> l1;
  create_list(l1, 15);
  l1.sort();
  print(l1);
  List<T> l2;
  create_list(l2, 12);
  l2.sort();
  print(l2);
  l1.merge(l2);
  print(l1);
}

template<class T>
void test_find(List<T> &l) {
  for (int i = 0; i <= l.size(); i++) {
    ListNodePos<T> p = l.find((T) i);
    log("Looking for {} : ", tostr((T) i).c_str());
    if (p) {
      log("found with {}", tostr(p->data).c_str());
    } else {
      log("not found");
    }
    log("\n");
  }
}

template<class T>
void test_search(List<T> &l) {
  for (int i = 0; i <= l.size(); i++) {
    ListNodePos<T> p = l.search((T) i);
    log("Looking for {} : stopped at {} ", tostr((T) i).c_str(), tostr(p->data).c_str());
    if ((T) i == p->data) {
      log("and found");
    }
    log("\n");
  }
}

template<class T>
void test_redundancy() {
  List<T> l;
  create_list(l, 20);
  log("== remove redundancy in unsorted\n");
  print(l);
  l.deduplicate();
  print(l);
  log("== remove redundancy in sorted\n");
  List<T> l1;
  create_list(l1, 20);
  l1.sort();
  print(l1);
  l1.uniquify();
  print(l1);
}

template<class T>
void test_list(int size) {
  log("=== generate a random list\n");
  List<T> l;
  create_list(l, size);
  log("=== test sort\n");
  test_sort(l);
  log("=== merge two sorted list into a single list\n");
  merge_test<T>();
  log("=== reverse list\n");
  print(l);
  l.reverse();
  print(l);
  log("=== test find in\n");
  print(l);
  test_find(l);
  log("=== test search in\n");
  l.sort();
  print(l);
  test_search(l);
  log("=== test redundancy\n");
  test_redundancy<T>();
}

}// namespace jtd

int main() {
  jtd::test_list<int>(20);
  return 0;
}
