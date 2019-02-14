#ifndef ABSTRACT_DIJKSTRA_H_
#define ABSTRACT_DIJKSTRA_H_

#include "../lib/AbstractGraph.h"
#include "../lib/GrapthPath.h"

/**
 * @tparam V vertex type
 * @tparam K vertex key type
 * @tparam E edge weight type
 */
template <class V, class K, class E>
class AbstractDijkstra {
  public:
  class Map {
    public:
    struct Node {
      K source;
      E weight;
      bool visited = false;
      bool determined = false;
    };
    /**
     * @return min key for processing
     */
    virtual K next() = 0;
    /**
     * @param key identifier to get node
     * @return node for specified key
     */
    virtual Node& get(const K& key) = 0;
    /**
     * @param from source node identifier
     * @param to dist node identifier
     * @param weight value between nodes
     */
    virtual void set(const K& from, const K& to, const E& weight) = 0;
    /**
     * @param key identifier to set visited flag
     */
    virtual void visit(const K& key) = 0;
    /**
     * @param dest vertex
     * @return path from source to dest
     */
    virtual GraphPath<V, E> path(const V& dest) = 0;
    /**
     * @return all paths from source
     */
    virtual GraphPath<V, E>* path() = 0;
  };
  /**
   * @param source graph vertex start position
   * @return array of all paths from source
   */
  virtual Map* dijkstra(const V& source) = 0;
  /**
   * @param source graph vertex start position
   * @param dest graph vertex finish position
   * @return paths from source to dest
   */
  virtual Map* dijkstra(const V& source, const V& dest) = 0;
};

#endif // ABSTRACT_DIJKSTRA_H_