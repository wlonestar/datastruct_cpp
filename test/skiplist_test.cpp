//
// Created by wjl on 2022/7/12.
//

#include <skiplist.h>

namespace jtd {

template<class K, class V>
void test_skiplist(int n) {
  Skiplist<K, V> l;
  while (l.size() < n)
    switch (random(3)) {
      case 0: {                
        K key = random((K) n * 3);
        print("Searching for {} ... ", tostr(key).c_str());
        V *pValue = l.get(key);
        if (pValue) {
          print("found with {}", tostr(*pValue).c_str());
        } else {
          print("Not found");
        }
        print("\n");
        break;
      }
      case 1: {                 
        K key = random((K) n * 3);
        print("Removing {} ... ", tostr(key).c_str());
        if (l.remove(key)) {
          print("Done\n");
        } else {
          print("Entry not exists\n");
        }
        print(l);
        break;
      }
      default: {
        K k = random((K) n * 3);
        V v = (V) 'A' + random(26);
        print("Inserting <{},{}> ... ", tostr(k).c_str(), tostr(v).c_str());
        l.put(k, v);
        print("Done\n");
        print(l);
        break;
      }
    }
  while (l.size() > 0) {
    K key = random((K) n * 3);
    print("Removing {} ... ", tostr(key).c_str());
    if (l.remove(key)) {
      print("Done\n");
    } else {
      print("Entry not exists\n");
    }
    print(l);
  }
}

}// namespace jtd

int main() {
  jtd::test_skiplist<int, char>(10);
  return 0;
}
