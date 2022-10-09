//
// Created by wjl15 on 2022/6/20.
//

#include <queue.h>

namespace jtd {

template<class T>
void test_queue(int size) {
  Queue<T> q;
  for (int i = 0; i < size; i++) {
    q.enque((T) random(100));
  }
  print(q);
  while (!q.empty()) {
    log("queue front : {}\n", tostr(q.front()).c_str());
    log("== dequeue last\n");
    q.deque();
    print(q);
  }
}

}// namespace jtd

int main() {
  jtd::test_queue<int>(15);
  return 0;
}
