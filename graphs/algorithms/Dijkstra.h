#ifndef ABSTRACT_DIJKSTRA_H_
#define ABSTRACT_DIJKSTRA_H_

/**
 * @tparam V vertex type
 * @tparam E edge's weight type
 */
template <class V, class E>
struct DijkstraPath {
  E weight;
  V from;
  V to;
  V* sequence = nullptr;
  size_t sequence_length = 0;

  ~DijkstraPath() {
    delete[] sequence;
  }
};

/**
 * @tparam S source type
 * @tparam E edge's weight type
 */
template <class S, class E>
struct DijkstraNode {
  S source;
  E weight;
  bool visited = false;
  bool determined = false;
};

/**
 * @tparam V vertex type
 * @tparam E edge's weight type
 */
template <class V, class E>
class AbstractDijkstra {
  public:
  /**
   * @param source graph vertex start position
   * @return array of all paths from source
   */
  virtual DijkstraPath<V, E>* dijkstra(const V& source) = 0;
  /**
   * @param source graph vertex start position
   * @param dest graph vertex finish position
   * @return paths from source to dest
   */
  virtual DijkstraPath<V, E> dijkstra(const V& source const V& dest) = 0;
};

#endif // ABSTRACT_DIJKSTRA_H_