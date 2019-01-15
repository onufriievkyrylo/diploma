#ifndef ABSTRACT_DIJKSTRA_H_
#define ABSTRACT_DIJKSTRA_H_

#include "../GraphPath.h"

template <class S, class W>
struct DijkstraNode {
  S* source;
  W weight;
  bool visited = false;
};

template <class V>
class AbstractDijkstra {
  public:
  /**
     * @params
     *  from - graph vertex start position
     * @return array of verticies that present path or nullptr if path doesn't exist
     */
  virtual GraphPath<V> *dijkstra_single_source(V from) = 0;
  /**
     * @params
     *  from, to - graph verticies beetwen path should be found
     * @return array of verticies that present path or nullptr if path doesn't exist
     */
  // virtual V* dijkstra_double_source(V from, V to) = 0;
};

#endif // ABSTRACT_DIJKSTRA_H_