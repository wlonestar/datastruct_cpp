//
// Created by wjl on 2022/7/10.
//

#include <graphmatrix.h>
#include <util.h>

namespace jtd {

template<class Tv, class Te>
void create_graph(GraphMatrix<Tv, Te> &g, int n, int e) {
  while ((g.n < n) || (g.e < e)) {
    if (g.n < n) {
      if (random(100) < 65) {
        Tv vertex = (Tv) ('A' + random(26));
        print("Inserting vertex {} ...", tostr(vertex).c_str());
        g.insert(vertex);
        print("done\n");
      } else {
        if (1 > g.n) continue;
        int i = random(g.n);
        print("Removing vertex %d ...", i);
        Tv v = g.remove(i);
        print("done with {}\n", tostr(v).c_str());
      }
      print(g);
    }
    if ((1 < g.n) && (g.e < e)) {
      if (random(100) < 65) {
        int i = random(g.n), j = random(g.n);
        Te te = random((Te) 3 * n);
        print("Inserting edge ({}, {}) = {} ...", tostr(i).c_str(), tostr(j).c_str(), tostr(e).c_str());
        if (g.exists(i, j)) {
          print("already exists\n");
        } else {
          g.insert(te, te, i, j);
          print("done\n");
        }
      } else {
        int i = random(g.n), j = random(g.n);
        print("Removing edge (%d, %d) ...", i, j);
        if (g.exists(i, j)) {
          Te te = g.remove(i, j);
          print("done with {}\n", tostr(e).c_str());
        } else {
          print("not exists\n");
        }
      }
      print(g);
    }
  }
  for (int i = 0; i < n; i++) {
    g.vertex(i) = 'A' + i;
  }
  print(g);
}

template<class Tv, class Te>
void test_graph(int n, int e) {
  log("=== generate a graph\n");
  GraphMatrix<Tv, Te> g;
  create_graph(g, n, e);
  log("=== bfs\n");
  g.bfs(0);
  print(g);
  log("=== bfs (pfs)\n");
  g.pfs(0, bfs_pu<Tv, Te>());
  print(g);
  log("=== dfs\n");
  g.dfs(0);
  print(g);
  log("=== dfs (pfs)\n");
  g.pfs(0, dfs_pu<Tv, Te>());
  print(g);
  log("=== tsort\n");
  Stack<Tv> *s = g.tsort(0);
  print(*s);
  print(g);
  log("=== bcc\n");
  g.bcc(0);
  print(g);
  log("=== prim\n");
  g.prim(0);
  print(g);
  log("=== prim (pfs)\n");
  g.pfs(0, prim_pu<Tv, Te>());
  print(g);
  log("=== dijkstra\n");
  g.dijkstra(0);
  print(g);
  log("=== dijkstra (pfs)\n");
  g.pfs(0, dijik_pu<Tv, Te>());
  print(g);
}

}// namespace jtd

int main() {
  jtd::test_graph<char, int>(10, 20);
  return 0;
}
