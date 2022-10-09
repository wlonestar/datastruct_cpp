//
// Created by wjl on 2022/7/2.
//

#include <bitmap.h>

namespace jtd {

#define PRIME_FILE "../prime-bitmap.txt"

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
  auto val = b.bits2string(n);
  print("{}\n", tostr(val).c_str());
}

int prime_nlt(int c, int n, const char *file) {
  bitmap b(file, n);
  while (c < n) {
    if (b.test(c)) {
      c++;
    } else {
      return c;
    }
  }
  return c;
}

void test_bitmap(int n) {
  eratosthenes(n, PRIME_FILE);
  for (int i = 0; i <= 13; i++) {
    int lo = random(n);
    print("the smallest prime number no less then {} is {}\n",
          tostr(lo).c_str(),
          tostr(prime_nlt(lo, n, PRIME_FILE)).c_str());
  }
  for (int i = 0; i < 13; i++) {
    print("the smallest prime number no less then {} is {}\n",
          tostr(n * i / 11).c_str(),
          tostr(prime_nlt(n * i / 11, n, PRIME_FILE)).c_str());
  }
}

}// namespace jtd

int main() {
  jtd::test_bitmap(10);
  return 0;
}
