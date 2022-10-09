//
// Created by wjl15 on 2022/6/20.
//

#include <stack.h>

namespace jtd {

template<class T>
void test_stack(int size) {
  Stack<T> s;
  for (int i = 0; i < size; i++) {
    s.push((T) random(100));
  }
  print(s);
  while (!s.empty()) {
    log("stack top : {}\n", tostr(s.top()).c_str());
    log("== pop top\n");
    s.pop();
    print(s);
  }
}

}

int main() {
  jtd::test_stack<int>(10);
  return 0;
}
