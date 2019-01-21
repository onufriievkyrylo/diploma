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
   * @return array of all paths to source
   */
  virtual DijkstraPath<V, E>* dijkstra_single_source(const V& source) = 0;
  /**
   * @params
   *  from, to - graph verticies beetwen path should be found
   * @return array of verticies that present path or nullptr if path doesn't exist
   */
  // virtual V* dijkstra_double_source(V from, V to) = 0;
};

#endif // ABSTRACT_DIJKSTRA_H_