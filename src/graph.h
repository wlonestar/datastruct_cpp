//
// Created by wjl on 2022/7/10.
//

#ifndef GRAPH_H
#define GRAPH_H

#pragma once

#include <queue.h>
#include <stack.h>

namespace jtd {

using VSTATUS = enum {
  UNDISCOVERED,
  DISCOVERED,
  VISITED,
};

using ETYPE = enum {
  UNDETERMINED,
  TREE,
  CROSS,
  FORWARD,
  BACKWARD,
};

template<class Tv, class Te>
class Graph {
private:
  void reset();

public:
  int n{};

  virtual Tv &vertex(int i) = 0;
  virtual int in_degree(int i) const = 0;
  virtual int out_degree(int i) const = 0;
  virtual int first_nbr(int i) const = 0;
  virtual int next_nbr(int i, int j) const = 0;
  virtual VSTATUS &status(int i) = 0;
  virtual const VSTATUS &status(int i) const = 0;
  virtual int &dtime(int i) = 0;
  virtual int &ftime(int i) = 0;
  virtual int &parent(int i) = 0;
  virtual const int &parent(int i) const = 0;
  virtual int &priority(int i) = 0;
  virtual const int &priority(int i) const = 0;

  virtual int insert(const Tv &vertex) = 0;
  virtual Tv remove(int i) = 0;

  int e{};
  virtual ETYPE &type(int i, int j) = 0;
  virtual Te &edge(int i, int j) = 0;
  virtual const Te &edge(int i, int j) const = 0;
  virtual int &weight(int i, int j) = 0;

  virtual bool exists(int i, int j) const = 0;
  virtual void insert(const Te &edge, int w, int i, int j) = 0;
  virtual Te remove(int i, int j) = 0;

private:
  void _bfs(int v, int &clock);
  void _dfs(int v, int &clock);
  void _bcc(int v, int &clock, Stack<int> &s);
  bool _tsort(int v, int &clock, Stack<Tv> *stack);
  template<class Pu>
  void _pfs(int s, Pu p);

public:
  void bfs(int s);
  void dfs(int s);
  void bcc(int s);
  Stack<Tv> *tsort(int s);
  void prim(int s);
  void dijkstra(int s);
  template<class Pu>
  void pfs(int s, Pu p);
};

template<class Tv, class Te>
void Graph<Tv, Te>::reset() {
  for (int i = 0; i < n; i++) {
    status(i) = UNDISCOVERED;
    dtime(i) = ftime(i) = -1;
    parent(i) = -1;
    priority(i) = INT_MAX;
    for (int j = 0; j < n; j++) {
      if (exists(i, j)) {
        type(i, j) = UNDETERMINED;
      }
    }
  }
}

template<class Tv, class Te>
void Graph<Tv, Te>::_bfs(int v, int &clock) {
  Queue<int> q;
  status(v) = DISCOVERED;
  q.enque(v);
  while (!q.empty()) {
    v = q.deque();
    dtime(v) = ++clock;
    for (int u = first_nbr(v); - 1 < u; u = next_nbr(v, u)) {
      if (UNDISCOVERED == status(u)) {
        status(u) = DISCOVERED;
        q.enque(u);
        type(v, u) = TREE;
        parent(u) = v;
      } else {
        type(v, u) = CROSS;
      }
    }
    status(v) = VISITED;
  }
}

template<class Tv, class Te>
void Graph<Tv, Te>::_dfs(int v, int &clock) {
  dtime(v) = ++clock;
  status(v) = DISCOVERED;
  for (int u = first_nbr(v); - 1 < u; u = next_nbr(v, u)) {
    switch (status(u)) {
      case UNDISCOVERED:
        type(v, u) = TREE;
        parent(u) = v;
        _dfs(u, clock);
        break;
      case DISCOVERED:
        type(v, u) = BACKWARD;
        break;
      default:
        type(v, u) = (dtime(v) < dtime(u)) ? FORWARD : CROSS;
        break;
    }
  }
  status(v) = VISITED;
  ftime(v) = ++clock;
}

template<class Tv, class Te>
void Graph<Tv, Te>::_bcc(int v, int &clock, Stack<int> &s) {
  ftime(v) = dtime(v) = ++clock;
  status(v) = DISCOVERED;
  s.push(v);
  for (int u = first_nbr(v); - 1 < u; u = next_nbr(v, u)) {
    switch (status(u)) {
      case UNDISCOVERED:
        parent(u) = v;
        type(v, u) = TREE;
        _bcc(u, clock, s);
        if (ftime(u) < dtime(v)) {
          ftime(v) = MIN(ftime(v), ftime(u));
        } else {
          // printf("BCC rooted at %c:", vertex(v));
          Stack<int> temp;
          do {
            temp.push(s.pop());
            // print(vertex(temp.top()));
          } while (u != temp.top());
          // print(vertex(parent(u)));
          while (!temp.empty()) {
            s.push(temp.pop());
          }
          while (u != s.pop())
            ;
          // printf("\n");
        }
        break;
      case DISCOVERED:
        type(v, u) = BACKWARD;
        if (u != parent(v)) {
          ftime(v) = MIN(ftime(v), dtime(u));
        }
        break;
      default:
        type(v, u) = (dtime(v) < dtime(u)) ? FORWARD : CROSS;
        break;
    }
  }
  status(v) = VISITED;
}

template<class Tv, class Te>
bool Graph<Tv, Te>::_tsort(int v, int &clock, Stack<Tv> *stack) {
  dtime(v) = ++clock;
  status(v) = DISCOVERED;
  for (int u = first_nbr(v); - 1 < u; u = next_nbr(v, u)) {
    switch (status(u)) {
      case UNDISCOVERED:
        parent(u) = v;
        type(v, u) = TREE;
        if (!_tsort(u, clock, stack)) {
          return false;
        }
        break;
      case DISCOVERED:
        type(v, u) = BACKWARD;
        return false;
      default:
        type(v, u) = (dtime(v) < dtime(u)) ? FORWARD : CROSS;
        break;
    }
  }
  status(v) = VISITED;
  stack->push(vertex(v));
  return true;
}

template<class Tv, class Te>
template<class Pu>
void Graph<Tv, Te>::_pfs(int s, Pu p) {
  priority(s) = 0;
  status(s) = VISITED;
  parent(s) = -1;
  while (true) {
    for (int w = first_nbr(s); - 1 < w; w = next_nbr(s, w)) {
      p(this, s, w);
    }
    for (int shortest = INT_MAX, w = 0; w < n; w++) {
      if (UNDISCOVERED == status(w))
        if (shortest > priority(w)) {
          shortest = priority(w);
          s = w;
        }
    }
    if (VISITED == status(s)) {
      break;
    }
    status(s) = VISITED;
    type(parent(s), s) = TREE;
  }
}

template<class Tv, class Te>
void Graph<Tv, Te>::bfs(int s) {
  reset();
  int clock = 0;
  int v = s;
  do {
    if (UNDISCOVERED == status(v)) {
      _bfs(v, clock);
    }
  } while (s != (v = ((v + 1) % n)));
}

template<class Tv, class Te>
void Graph<Tv, Te>::dfs(int s) {
  reset();
  int clock = 0;
  int v = s;
  do {
    if (UNDISCOVERED == status(v)) {
      _dfs(v, clock);
    }
  } while (s != (v = ((v + 1) % n)));
}

template<class Tv, class Te>
void Graph<Tv, Te>::bcc(int s) {
  reset();
  int clock = 0;
  int v = s;
  Stack<int> stack;
  do {
    if (UNDISCOVERED == status(v)) {
      _bcc(v, clock, stack);
      stack.pop();
    }
  } while (s != (v = (++v % n)));
}

template<class Tv, class Te>
Stack<Tv> *Graph<Tv, Te>::tsort(int s) {
  reset();
  int clock = 0;
  int v = s;
  auto *stack = new Stack<Tv>;
  do {
    if (UNDISCOVERED == status(v))
      if (!_tsort(v, clock, stack)) {
        print(*stack);
        while (!stack->empty()) {
          stack->pop();
        }
        break;
      }
  } while (s != (v = (++v % n)));
  return stack;
}

template<class Tv, class Te>
void Graph<Tv, Te>::prim(int s) {
  reset();
  priority(s) = 0;
  for (int i = 0; i < n; i++) {
    status(s) = VISITED;
    if (-1 < parent(s)) {
      type(parent(s), s) = TREE;
    }
    for (int j = first_nbr(s); - 1 < j; j = next_nbr(s, j)) {
      if ((status(j) == UNDISCOVERED) && (priority(j) > weight(s, j))) {
        priority(j) = weight(s, j);
        parent(j) = s;
      }
    }
    for (int shortest = INT_MAX, j = 0; j < n; j++) {
      if ((status(j) == UNDISCOVERED) && (shortest > priority(j))) {
        shortest = priority(j);
        s = j;
      }
    }
  }
}

template<class Tv, class Te>
void Graph<Tv, Te>::dijkstra(int s) {
  reset();
  priority(s) = 0;
  for (int i = 0; i < n; i++) {
    status(s) = VISITED;
    if (-1 < parent(s)) type(parent(s), s) = TREE;
    for (int j = first_nbr(s); - 1 < j; j = next_nbr(s, j)) {
      if ((status(j) == UNDISCOVERED) && (priority(j) > priority(s) + weight(s, j))) {
        priority(j) = priority(s) + weight(s, j);
        parent(j) = s;
      }
    }
    for (int shortest = INT_MAX, j = 0; j < n; j++) {
      if ((status(j) == UNDISCOVERED) && (shortest > priority(j))) {
        shortest = priority(j);
        s = j;
      }
    }
  }
}

template<class Tv, class Te>
template<class Pu>
void Graph<Tv, Te>::pfs(int s, Pu p) {
  reset();
  int v = s;
  do {
    if (UNDISCOVERED == status(v)) {
      _pfs(v, p);
    }
  } while (s != (v = ((v + 1) % n)));
}

template<class Tv, class Te>
struct bfs_pu {
  virtual void operator()(Graph<Tv, Te> *g, int uk, int v) {
    if (g->status(v) == UNDISCOVERED) {
      if (g->priority(v) > g->priority(uk) + 1) {
        g->priority(v) = g->priority(uk) + 1;
        g->parent(v) = uk;
      }
    }
  }
};

template<class Tv, class Te>
struct dfs_pu {
  virtual void operator()(Graph<Tv, Te> *g, int uk, int v) {
    if (g->status(v) == UNDISCOVERED) {
      if (g->priority(v) > g->priority(uk) - 1) {
        g->priority(v) = g->priority(uk) - 1;
        g->parent(v) = uk;
        return;
      }
    }
  }
};

template<class Tv, class Te>
struct prim_pu {
  virtual void operator()(Graph<Tv, Te> *g, int s, int w) {
    if (g->status(w) == UNDISCOVERED) {
      if (g->priority(w) > g->weight(s, w)) {
        g->priority(w) = g->weight(s, w);
        g->parent(w) = s;
      }
    }
  }
};

template<class Tv, class Te>
struct dijik_pu {
  virtual void operator()(Graph<Tv, Te> *g, int s, int w) {
    if (g->status(w) == UNDISCOVERED) {
      if (g->priority(w) > g->priority(s) + g->weight(s, w)) {
        g->priority(w) = g->priority(s) + g->weight(s, w);
        g->parent(w) = s;
      }
    }
  }
};

}// namespace jtd

#endif//GRAPH_H
