//
// Created by wjl15 on 2022/6/20.
//

#include <vector.h>

namespace jtd {

template<class T>
void create_vector(Vector<T> &v, int n, int range = 20, bool ordered = true) {
  while (v.size() < n) {
    T e = (T) random(range);
    if (ordered) {
      v.insert(v.search(e) + 1, e);
    } else {
      v.insert(e);
    }
  }
}

template<class T>
void test_find(Vector<T> &v) {
  for (int i = 0; i < v.size(); i++) {
    T e = v[i];
    log("{}", tostr(e).c_str());
    int r = v.find(e);
    if (-1 < r) {
      log(" : found at rank v[{}] = {}\n", tostr(r).c_str(), tostr(v[r]).c_str());
    } else {
      log(" : not found until rank v[{}] <> {}\n", tostr(r).c_str(), tostr(e).c_str());
    }
  }
  for (int i = 0; i <= v.size(); i++) {
    T a = (0 < i) ? v[i - 1] : v[0] - 4;
    T b = (i < v.size()) ? v[i] : v[v.size() - 1] - 4;
    T e = (a + b) / 2;
    log("{}", tostr(e).c_str());
    int r = v.find(e);
    if (-1 < r) {
      log(" : found at rank v[{}] = {}\n", tostr(r).c_str(), tostr(v[r]).c_str());
    } else {
      log(" : not found until rank v[{}] <> {}\n", tostr(r).c_str(), tostr(e).c_str());
    }
  }
}

template<class T>
void test_sort(Vector<T> &v) {
  timer t;
  v.unsort();
  print(v);
  t.start();
  v.bubblesort();
  auto val1 = t.stop();
  print(v);
  log("== bubble sort: {} micro seconds\n", tostr(val1).c_str());
  v.unsort();
  print(v);
  t.start();
  v.selectsort();
  auto val2 = t.stop();
  print(v);
  log("== select sort: {} micro seconds\n", tostr(val2).c_str());
  v.unsort();
  print(v);
  t.start();
  v.mergesort();
  auto val3 = t.stop();
  print(v);
  log("== merge sort: {} micro seconds\n", tostr(val3).c_str());
  v.unsort();
  print(v);
  t.start();
  v.heapsort();
  auto val4 = t.stop();
  print(v);
  log("== heap sort: {} micro seconds\n", tostr(val4).c_str());
  v.unsort();
  print(v);
  t.start();
  v.quicksort();
  auto val5 = t.stop();
  print(v);
  log("== quick sort: {} micro seconds\n", tostr(val5).c_str());
  v.unsort();
  print(v);
  t.start();
  v.shellsort();
  auto val6 = t.stop();
  print(v);
  log("== shell sort: {} micro seconds\n", tostr(val6).c_str());
}

template<class T>
void test_search(Vector<T> &v) {
  timer t;
  log("== binary search: \n");
  t.start();
  for (int i = 0; i < v.size(); i++) {
    T e = v[i];
    log("{}: by ", tostr(e).c_str());
    int r = v.binsearch(e);
    if (v[r] == e) {
      log("found at rank v[{}] = {}\n", tostr(r).c_str(), tostr(v[r]).c_str());
    } else {
      log("found at rank v[{}] = <> {}\a\a\n", tostr(r).c_str(), tostr(v[r]).c_str(), tostr(e).c_str());
    }
  }
  auto val1 = t.stop();
  log("binary search cost {} micro seconds\n", tostr(val1).c_str());
  log("== fibonacci search: \n");
  t.start();
  for (int i = 0; i < v.size(); i++) {
    T e = v[i];
    log("{}: by ", tostr(e).c_str());
    int r = v.fibsearch(e);
    if (v[r] == e) {
      log("found at rank v[{}] = {}\n", tostr(r).c_str(), tostr(v[r]).c_str());
    } else {
      log("found at rank v[{}] = <> {}\a\a\n", tostr(r).c_str(), tostr(v[r]).c_str(), tostr(e).c_str());
    }
  }
  auto val2 = t.stop();
  log("fibonacci search cost {} micro seconds\n", tostr(val2).c_str());
}

template<class T>
void test_copy(Vector<T> &v) {
  T *e = new T[random(10)];
  for (int i = 0; i < 10; i++) {
    e[i] = random(100);
  }
  log("generate random array:\n");
  for (int i = 0; i < 10; i++) {
    log("{} ", tostr(e[i]).c_str());
  }
  log("\n");
  log("== test copy from entire array\n");
  Vector<T> v1(e, 10);
  print(v1);
  log("== test copy from interval array [{}, {})\n", tostr(1).c_str(), tostr(5).c_str());
  Vector<T> v2(e, 1, 5);
  print(v2);
  log("== test copy from entire vector\n");
  print(v);
  Vector<T> v3(v);
  print(v3);
  log("== test copy from interval vector [{}, {})\n", tostr(v.size() / 4).c_str(), tostr(3 * v.size() / 4).c_str());
  print(v);
  Vector<T> v4(v, v.size() / 4, 3 * v.size() / 4);
  print(v4);
  log("== test clone from\n");
  print(v);
  Vector<T> v5 = v;
  print(v5);
}

template<class T>
void test_redundancy() {
  Vector<T> v;
  create_vector(v, 10, 10, false);
  print(v);
  log("=== remove redundancy in unsorted\n");
  print(v);
  v.deduplicate();
  print(v);
  log("=== remove redundancy in sorted\n");
  Vector<T> u;
  create_vector(u, 10, 10, true);
  v = u;
  v.sort();
  print(v);
  v.uniquify();
  print(v);
}

template<class T>
void test_vector(int size) {
  log("=== generate a random vector\n");
  Vector<T> v;
  create_vector(v, size, 100, false);
  log("=== test find in\n");
  print(v);
  test_find(v);
  log("=== test sort entire vector\n");
  test_sort(v);
  log("=== test search in\n");
  print(v);
  test_search(v);
  log("=== test copy construction\n");
  test_copy(v);
  log("=== test redundancy\n");
  test_redundancy<T>();
}

}// namespace jtd

int main() {
  jtd::test_vector<int>(20);
  return 0;
}
