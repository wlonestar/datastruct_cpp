//
// Created by wjl15 on 2022/6/19.
//

#include <util.h>
#include <utility>

void macro_test() {
  jtd::log("--- test macro: \n");
  int a = 2, b = 10;
  auto val1 = MAX(a, b);
  jtd::log("max in ({}, {}): {}\n",
           jtd::tostr(a).c_str(), jtd::tostr(b).c_str(),
           jtd::tostr(val1).c_str());
  auto val2 = MIN(a, b);
  jtd::log("min in ({}, {}): {}\n",
           jtd::tostr(a).c_str(), jtd::tostr(b).c_str(),
           jtd::tostr(val2).c_str());
}

void print_test() {
  jtd::log("--- test print function: \n");
  jtd::print("{}, {}\n", "12", "123");
}

void tostring_test() {
  jtd::log("--- test tostr function: \n");
  int val1 = -121;
  jtd::log("int: {}\n", jtd::tostr(val1).c_str());
  unsigned int val2 = 1;
  jtd::log("unsigned int: {}\n", jtd::tostr(val2).c_str());
  long val3 = -121211121;
  jtd::log("long: {}\n", jtd::tostr(val3).c_str());
  unsigned long val4 = 1;
  jtd::log("unsigned long: {}\n", jtd::tostr(val4).c_str());
  float val5 = 1.2;
  jtd::log("float: {}\n", jtd::tostr(val5).c_str());
  double val6 = 1.1211111111111;
  jtd::log("double: {}\n", jtd::tostr(val6).c_str());
  long double val7 = -12.121212121111111111;
  jtd::log("long double: {}\n", jtd::tostr(val7).c_str());
  char val8 = '1';
  jtd::log("char: {}\n", jtd::tostr(val8).c_str());
  char *val9 = "asar3211a2131";
  jtd::log("char*: {}\n", jtd::tostr(val9).c_str());
}

void timer_test() {
  jtd::log("--- test timer function: \n");
  jtd::timer t;
  t.start();
  for (int i = 0; i < 10000; i++) {
    for (int j = 0; j < 10000; j++) {
    }
  }
  auto val = t.stop();
  std::cout << val << "\n";
}

void random_test() {
  jtd::log("--- test random function: \n");
  int num = 10;
  jtd::log("--- int: \n");
  jtd::log("random(): ");
  for (int i = 0; i < num * 2; i++) {
    jtd::log("{} ", jtd::tostr(jtd::random()).c_str());
  }
  jtd::log("\n");
  jtd::log("random(0, range): ");
  for (int i = 0; i < num * 2; i++) {
    jtd::log("{} ", jtd::tostr(jtd::random(10)).c_str());
  }
  jtd::log("\n");
  jtd::log("random(lo, hi): ");
  for (int i = 0; i < num * 2; i++) {
    jtd::log("{} ", jtd::tostr(jtd::random(1, 12)).c_str());
  }
  jtd::log("\n");

  jtd::log("--- float: \n");
  jtd::log("random(): ");
  for (int i = 0; i < num; i++) {
    jtd::log("{} ", jtd::tostr(jtd::random<float>()).c_str());
  }
  jtd::log("\n");
  jtd::log("random(0, range): ");
  for (int i = 0; i < num; i++) {
    jtd::log("{} ", jtd::tostr(jtd::random<float>(10.5)).c_str());
  }
  jtd::log("\n");
  jtd::log("random(lo, hi): ");
  for (int i = 0; i < num; i++) {
    jtd::log("{} ", jtd::tostr(jtd::random<float>(1.5, 12.9)).c_str());
  }
  jtd::log("\n");

  jtd::log("--- double: \n");
  jtd::log("random(): ");
  for (int i = 0; i < num; i++) {
    jtd::log("{} ", jtd::tostr(jtd::random<double>()).c_str());
  }
  jtd::log("\n");
  jtd::log("random(0, range): ");
  for (int i = 0; i < num; i++) {
    jtd::log("{} ", jtd::tostr(jtd::random<double>(10)).c_str());
  }
  jtd::log("\n");
  jtd::log("random(lo, hi): ");
  for (int i = 0; i < num; i++) {
    jtd::log("{} ", jtd::tostr(jtd::random<double>(1, 12)).c_str());
  }
  jtd::log("\n");
}

void compare_test() {
  jtd::log("--- test compare template function: \n");
  int a = 1, b = 121;
  jtd::log("{} lt {}: {}\n", jtd::tostr(a).c_str(), jtd::tostr(b).c_str(),
           jtd::tostr(jtd::lt(a, b)).c_str());
  char *c = "12", *d = "12";
  jtd::log("{} eq {}: {}\n", jtd::tostr(c).c_str(), jtd::tostr(d).c_str(),
           jtd::tostr(jtd::eq(c, d)).c_str());
  std::string e = "6awa", f = "ewe23";
  jtd::log("{} lt {}: {}\n", e.c_str(), f.c_str(), jtd::tostr(jtd::lt(&e, &f)).c_str());
}

class user_test {
private:
  int id;
  std::string name;
public:
  user_test(int id, std::string name) : id(id), name(std::move(name)) {}
};

void release_test() {
  std::vector<int> v;
  for (int i = 0; i < 10; i++) {
    v.push_back(i);
  }
  jtd::release(v);
  int a = 12;
  jtd::release(a);
  user_test u(1, "wew");
  jtd::release(u);
}

int main() {
  macro_test();
  print_test();
  tostring_test();
  timer_test();
  random_test();
  compare_test();
  release_test();
  return 0;
}
