//
// Created by wjl on 2022/7/14.
//

#include <hashtable.h>

namespace jtd {

template<typename K, typename V>
void test_hashtable(int n) {
  Hashtable<K, V> ht(n);
  print(ht);
  while (ht.size() < 4 * n) {
    print("\n");
    switch (random(3)) {
      case 0: {
        K key = (K) random(n * 12);
        print("Searching {}({}) :\n", tostr(key).c_str(), tostr(hashcode(key)).c_str());
        V *pValue = ht.get(key);
        if (pValue) {
          print("Found with {}", tostr(*pValue).c_str());
        } else {
          print("Not found");
        }
        print("\n");
        break;
      }
      case 1: {
        K key = random((K) n * 12);
        print("Removing {}({}) :\n", tostr(key).c_str(), tostr(hashcode(key)).c_str());
        if (ht.remove(key)) {
          print("Done\n");
          print(ht);
        } else {
          print("Entry not exists\n");
        }
        break;
      }
      default: {
        K key = random((K) n * 12);
        V v = (V) 'A' + random(26);
        print("Inserting <{}(),()>\n", tostr(key).c_str(), tostr(hashcode(key)).c_str(), tostr(v).c_str());
        if (ht.put(key, v)) {
          print("Done\n");
          print(ht);
        } else {
          print("Dup key\n");
        }
        break;
      }
    }
  }
  while (ht.size() > 0) {
    print("\n");
    K key = random((K) n * 12);
    print("Removing {} :\n", tostr(key).c_str());
    if (ht.remove(key)) {
      print("Done\n");
      print(ht);
    } else {
      print("Entry not exists\n");
    }
  }
}

}// namespace jtd

int main() {
  jtd::test_hashtable<int, char>(10);
  return 0;
}
