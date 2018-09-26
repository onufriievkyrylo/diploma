#ifndef MATRIX_GRAPH_H_
#define MATRIX_GRAPH_H_

#include "./AbstractGraph.h"

template <class V, class E>
class MatrixGraph : AbstractGraph<V, E> {
  private:
  V* verticies;
  E** edges;
  public:
  

};

#endif // MATRIX_GRAPH_H_