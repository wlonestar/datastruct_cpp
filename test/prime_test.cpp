//
// Created by wjl on 2022/7/14.
//

#include <bitmap.h>

namespace jtd {

#define PRIME_1048576 "../../prime-1048576-bitmap.txt"

void eratosthenes(int n, const char *file) {
  bitmap b(n);
  b.set(0);
  b.set(1);
  for (int i = 2; i * i < n; i++) {
    if (!b.test(i)) {
      for (int j = i * i; j < n; j += i) {
        b.set(j);
      }
    }
  }
  b.dump(file);
}

}

int main() {
  jtd::eratosthenes(1048576, PRIME_1048576);
  return 0;
}

