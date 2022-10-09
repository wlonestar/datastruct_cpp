//
// Created by wjl on 2022/7/14.
//

#include <util.h>
#include <pq_compheap.h>
#include <pq_leftheap.h>

namespace jtd {

template<class PQ, class T>
void test_heap(int n) {
  T *A = new T[2 * n / 3];
  for (int i = 0; i < 2 * n / 3; i++) {
    A[i] = random((T) 3 * n);
  }
  print("{} random keys created:\n", tostr(2 * n / 3).c_str());
  for (int i = 0; i < 2 * n / 3; i++) {
    print("{}", tostr(A[i]).c_str());
  }
  print("\n");
  PQ heap(A + n / 6, n / 3);
  delete[] A;
  print(heap);
  while (heap.size() < n) {
    if (random(100) < 70) {
      T e = random((T) 3 * n);
      print("Inserting {} ...\n", tostr(e).c_str());
      heap.insert(e);
      print("Insertion done\n");
    } else {
      if (!heap.empty()) {
        print("Deleting max ...\n");
        T e = heap.del_max();
        print("Deletion done with {}\n", tostr(e).c_str());
      }
    }
    print(heap);
  }
  while (!heap.empty()) {
    T e = heap.del_max();
    print("Deletion done with {}\n", tostr(e).c_str());
    print(heap);
  }
}

}// namespace jtd

int main() {
  std::locale::global(std::locale("zh_CN.UTF-8"));
  jtd::test_heap<jtd::PQ_compheap<int>, int>(10);
  jtd::test_heap<jtd::PQ_leftheap<int>, int>(10);
  return 0;
}
