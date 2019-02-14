#ifndef GRAPH_PATH_H_
#define GRAPH_PATH_H_

/**
 * @tparam V vertex type
 * @tparam E edge's weight type
 */
template <class V, class E>
struct GraphPath {
  E weight;
  V from;
  V to;
  V* sequence = nullptr;
  size_t sequence_length = 0;
  bool unreachable = false;

  ~GraphPath() {
    delete[] sequence;
  }
};

#endif  // GRAPH_PATH_H_