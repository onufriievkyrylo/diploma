#ifndef ABSTRACT_FLOYDWARSHALL_H_
#define ABSTRACT_FLOYDWARSHALL_H_

/**
 * @tparam V source vertex type
 * @tparam E path weight type
 */
template <class V, class E>
class FloydWarshallNode {
  private:
  V source;
  E weight;
  bool visited = false;
  bool determined = false;
};

/**
 * @tparam V vertex type
 * @tparam E edge's weight type
 */
template <class V, class E>
class AbstractFloydWarshall {
  public:
  /**
   * @return map of all paths on the graph
   */
  virtual FloydWarshallMap<V, E> floyd_warshall() = 0;
};

#endif // ABSTRACT_FLOYDWARSHALL_H_