//
// Created by wjl on 2022/7/10.
//

#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

#pragma once

#include <graph.h>
#include <vector.h>

namespace jtd {

template<class Tv>
class Vertex {
public:
  Tv data;
  int in_degree;
  int out_degree;
  VSTATUS status;
  int dtime;
  int ftime;
  int parent;
  int priority;

  explicit Vertex(const Tv &d = (Tv) 0);
};

template<class Tv>
Vertex<Tv>::Vertex(const Tv &d) : data(d), in_degree(0), out_degree(0),
                                  status(UNDISCOVERED), dtime(-1), ftime(-1),
                                  parent(-1), priority(INT_MAX) {}

template<class Te>
class Edge {
public:
  Te data;
  int weight;
  ETYPE type;

  Edge(const Te &d, int w);
};

template<class Te>
Edge<Te>::Edge(const Te &d, int w) : data(d), weight(w), type(UNDETERMINED) {}

template<class Tv, class Te>
class GraphMatrix : public Graph<Tv, Te> {
private:
  Vector<Vertex<Tv>> vertices;
  Vector<Vector<Edge<Te> *>> edges;

public:
  GraphMatrix();
  ~GraphMatrix();

  Tv &vertex(int i) override;
  int in_degree(int i) const override;
  int out_degree(int i) const override;
  int first_nbr(int i) const override;
  int next_nbr(int i, int j) const override;
  VSTATUS &status(int i) override;
  const VSTATUS &status(int i) const override;
  int &dtime(int i) override;
  int &ftime(int i) override;
  int &parent(int i) override;
  const int &parent(int i) const override;
  int &priority(int i) override;
  const int &priority(int i) const override;
  int insert(const Tv &vertex) override;
  Tv remove(int i) override;
  ETYPE &type(int i, int j) override;
  Te &edge(int i, int j) override;
  const Te &edge(int i, int j) const override;
  int &weight(int i, int j) override;
  bool exists(int i, int j) const override;
  void insert(const Te &edge, int w, int i, int j) override;
  Te remove(int i, int j) override;
};

template<class Tv, class Te>
void print(GraphMatrix<Tv, Te> &s) {
  int in_d = 0;
  int out_d = 0;
  for (int i = 0; i < s.n; i++) {
    in_d += s.in_degree(i);
    out_d += s.out_degree(i);
  }
  print("{}({}, {}):\n", typeid(s).name(), tostr(s.n).c_str(), tostr(s.e).c_str());
  print("{} {}|", tostr(s.n).c_str(), tostr(in_d).c_str());
  for (int i = 0; i < s.n; i++) {
    print("{}[{}]", tostr(s.vertex(i)).c_str(), tostr(s.status(i)).c_str());
  }
  print("\n");
  print("{} {}|", tostr(out_d).c_str(), tostr(s.e).c_str());
  for (int i = 0; i < s.n; i++) {
    print("{} ", tostr(s.in_degree(i)).c_str());
  }
  print("| dtime ftime Parent Weight\n");
  print("-----------+");
  for (int i = 0; i < s.n; i++) {
    print("------");
  }
  print("+----------------------------\n");
  for (int i = 0; i < s.n; i++) {
    print("{}[{}] {}|", tostr(s.vertex(i)).c_str(),
          tostr(s.status(i)).c_str(), tostr(s.out_degree(i)).c_str());
    for (int j = 0; j < s.n; j++) {
      if (s.exists(i, j)) {
        print("{} {}", tostr(s.edge(i, j)).c_str(), tostr(s.type(i, j)).c_str());
      } else {
        print("     .");
      }
    }
    print("| {} {}     ", tostr(s.dtime(i)).c_str(), tostr(s.ftime(i)).c_str());
    if (0 > s.parent(i)) {
      print("^");
    } else {
      print("{}", tostr(s.vertex(s.parent(i))).c_str());
    }
    print("  ");
    if (INT_MAX > s.priority(i)) {
      print("{}", tostr(s.priority(i)).c_str());
    } else {
      print(" INF");
    }
    print("\n");
  }
  print("\n");
}

template<class Tv, class Te>
GraphMatrix<Tv, Te>::GraphMatrix() {
  this->n = this->e = 0;
}

template<class Tv, class Te>
GraphMatrix<Tv, Te>::~GraphMatrix() {
  for (int j = 0; j < this->n; j++) {
    for (int k = 0; k < this->n; k++) {
      delete edges[j][k];
    }
  }
}

template<class Tv, class Te>
Tv &GraphMatrix<Tv, Te>::vertex(int i) {
  return vertices[i].data;
}

template<class Tv, class Te>
int GraphMatrix<Tv, Te>::in_degree(int i) const {
  return vertices[i].in_degree;
}

template<class Tv, class Te>
int GraphMatrix<Tv, Te>::out_degree(int i) const {
  return vertices[i].out_degree;
}

template<class Tv, class Te>
int GraphMatrix<Tv, Te>::first_nbr(int i) const {
  return next_nbr(i, this->n);
}

template<class Tv, class Te>
int GraphMatrix<Tv, Te>::next_nbr(int i, int j) const {
  while ((-1 < j) && (!exists(i, --j)))
    ;
  return j;
}

template<class Tv, class Te>
VSTATUS &GraphMatrix<Tv, Te>::status(int i) {
  return vertices[i].status;
}

template<class Tv, class Te>
const VSTATUS &GraphMatrix<Tv, Te>::status(int i) const {
  return vertices[i].status;
}

template<class Tv, class Te>
int &GraphMatrix<Tv, Te>::dtime(int i) {
  return vertices[i].dtime;
}

template<class Tv, class Te>
int &GraphMatrix<Tv, Te>::ftime(int i) {
  return vertices[i].ftime;
}

template<class Tv, class Te>
int &GraphMatrix<Tv, Te>::parent(int i) {
  return vertices[i].parent;
}

template<class Tv, class Te>
const int &GraphMatrix<Tv, Te>::parent(int i) const {
  return vertices[i].parent;
}

template<class Tv, class Te>
int &GraphMatrix<Tv, Te>::priority(int i) {
  return vertices[i].priority;
}

template<class Tv, class Te>
const int &GraphMatrix<Tv, Te>::priority(int i) const {
  return vertices[i].priority;
}

template<class Tv, class Te>
int GraphMatrix<Tv, Te>::insert(const Tv &vertex) {
  this->n++;
  edges.insert(Vector<Edge<Te> *>(this->n, this->n, (Edge<Te> *) NULL));
  for (int j = 0; j < this->n; j++) {
    for (int i = 0; i <= j; i++) {
      edges[j].insert(NULL);
    }
  }
  return vertices.insert(Vertex<Tv>(vertex));
}

template<class Tv, class Te>
Tv GraphMatrix<Tv, Te>::remove(int i) {
  for (int j = 0; j < this->n; j++) {
    if (exists(i, j)) {
      delete edges[i][j];
      vertices[j].in_degree--;
      this->e--;
    }
  }
  edges.remove(i);
  this->n--;
  Tv v = vertex(i);
  vertices.remove(i);
  for (int j = 0; j < this->n; j++) {
    if (Edge<Te> *x = edges[j].remove(i)) {
      delete x;
      vertices[j].out_degree--;
      this->e--;
    }
  }
  return v;
}

template<class Tv, class Te>
ETYPE &GraphMatrix<Tv, Te>::type(int i, int j) {
  return edges[i][j]->type;
}

template<class Tv, class Te>
Te &GraphMatrix<Tv, Te>::edge(int i, int j) {
  return edges[i][j]->data;
}

template<class Tv, class Te>
const Te &GraphMatrix<Tv, Te>::edge(int i, int j) const {
  return edges[i][j]->data;
}

template<class Tv, class Te>
int &GraphMatrix<Tv, Te>::weight(int i, int j) {
  return edges[i][j]->weight;
}

template<class Tv, class Te>
bool GraphMatrix<Tv, Te>::exists(int i, int j) const {
  return (i < this->n) && (j < this->n) && edges[i][j] != NULL;
}

template<class Tv, class Te>
void GraphMatrix<Tv, Te>::insert(const Te &edge, int w, int i, int j) {
  if (exists(i, j)) {
    return;
  }
  edges[i][j] = new Edge<Te>(edge, w);
  this->e++;
}

template<class Tv, class Te>
Te GraphMatrix<Tv, Te>::remove(int i, int j) {
  Te te = edge(i, j);
  delete edges[i][j];
  edges[i][j] = nullptr;
  this->e--;
  vertices[i].out_degree--;
  vertices[i].in_degree--;
  return te;
}

}// namespace jtd

#endif//GRAPHMATRIX_H
