#ifndef MATRIX_GRAPH_H_
#define MATRIX_GRAPH_H_

#include <iostream>
#include <algorithm>
#include <exception>
#include <optional>
#include <vector>
#include <functional>

#include "../lib/AbstractGraph.h"
#include "../algorithms/Dijkstra.h"

template <class V, class E>
class MatrixGraph : AbstractGraph<V, E>, AbstractDijkstra<V, E> {
  private:
  std::vector<V> verticies;
  std::vector<std::vector<std::optional<E>>> edges;
  public:
  DijkstraPath<V, E>* dijkstra_single_source(V source) {
    size_t vertex_count = size();
    int source_index = index_of(source);
    if (source_index < 0)
      throw std::logic_error("vertex 'from' not found");
    std::vector<DijkstraNode<int, E>> map(vertex_count);
    map[source_index].source = source_index;
    map[source_index].determined = true;
    for (int step = 0; step < vertex_count - 1; ++step) {
      int min_index = std::distance(map.begin(), std::min_element(map.begin(), map.end(),
        [](const DijkstraNode<int, E> &l, const DijkstraNode<int, E> &r) -> bool {
          return l.visited || r.visited ? r.visited && !l.visited
            : !l.determined || !r.determined ? !r.determined
            : l.weight <= r.weight;
        }
      ));
      map[min_index].visited = true;
      for (int neighbour_index = 0; neighbour_index < vertex_count; ++neighbour_index) {
        if (edges[min_index][neighbour_index].has_value() && !map[neighbour_index].visited) {
          E weight = map[min_index].weight + edges[min_index][neighbour_index].value();
          if (!map[neighbour_index].determined || weight < map[neighbour_index].weight) {
            map[neighbour_index].determined = true;
            map[neighbour_index].weight = weight;
            map[neighbour_index].source = min_index;
          }
        }
      }
    }
    auto paths = new DijkstraPath<V, E>[vertex_count];
    for (int to_index = 0; to_index < vertex_count; ++to_index) {
      DijkstraPath<V, E> graph_path;
      graph_path.from = verticies[source_index];
      graph_path.to = verticies[to_index];
      graph_path.weight = map[to_index].weight;
      int from_index = map[to_index].source;
      int path_length = 0;
      while (from_index != source_index) {
        from_index = map[from_index].source;
        ++path_length;
      }
      graph_path.path_length = path_length;
      graph_path.path = new V[path_length];
      for (int node_index(map[to_index].source), step = 1; node_index != from_index; node_index = map[node_index].source, ++step) {
        graph_path.path[path_length - step] = verticies[node_index];
      }
      paths[to_index] = graph_path;
    }
    return paths;
  }
  MatrixGraph* add(V vertex) {
    if (contains(vertex)) throw std::logic_error("vertex already added");
    verticies.push_back(vertex);
    for (auto &edge : edges) {
      edge.push_back(std::optional<E>());
    }
    edges.push_back(std::vector<std::optional<E>>(size(), std::optional<E>()));
    return this;
  }
  MatrixGraph* remove(V vertex) {
    int removal_index = index_of(vertex);
    if (removal_index < 0) throw std::logic_error("vertex not found");
    return remove(removal_index);
  }
  MatrixGraph* remove(int removal_index) {
    if (removal_index < 0 || removal_index >= size())
      throw std::out_of_range("index is out of range");
    verticies.erase(verticies.begin() + removal_index);
    edges.erase(edges.begin() + removal_index);
    for (auto &edge : edges) {
      edge.erase(edge.begin() + removal_index);
    }
    return this;
  }
  MatrixGraph* connect(V vertex1, V vertex2, E edge) {
    int vertex1_index = index_of(vertex1);
    if (vertex1_index < 0)
      throw std::logic_error("vertex1 not found");
    int vertex2_index = index_of(vertex2);
    if (vertex2_index < 0)
      throw std::logic_error("vertex2 not found");
    edges[vertex1_index][vertex2_index] = edge;
    return this;
  }
  MatrixGraph* connect(int vertex1_index, int vertex2_index, E edge) {
    if (vertex1_index < 0 || vertex1_index >= size())
      throw std::out_of_range("vertex1 index is out of range");
    if (vertex2_index < 0 || vertex2_index >= size())
      throw std::out_of_range("vertex2 index is out of range");
    edges[vertex1_index][vertex2_index] = edge;
    return this;
  }
  MatrixGraph* disconnect(V vertex1, V vertex2) {
    int vertex1_index = index_of(vertex1);
    if (vertex1_index < 0)
      throw std::logic_error("vertex1 not found");
    int vertex2_index = index_of(vertex2);
    if (vertex2_index < 0)
      throw std::logic_error("vertex2 not found");
    edges[vertex1_index][vertex2_index].reset();
    return this;
  }
  MatrixGraph* disconnect(int vertex1_index, int vertex2_index) {
    if (vertex1_index < 0 || vertex1_index >= size())
      throw std::out_of_range("vertex1 index is out of range");
    if (vertex2_index < 0 || vertex2_index >= size())
      throw std::out_of_range("vertex2 index is out of range");
    edges[vertex1_index][vertex2_index].reset();
    return this;
  }
  bool contains(V vertex) {
    return std::find(verticies.begin(), verticies.end(), vertex) != verticies.end();
  }
  int index_of(V vertex) {
    auto found = std::find(verticies.begin(), verticies.end(), vertex);
    return found != verticies.end() ? found - verticies.begin() : -1;
  }
  size_t size() {
    return verticies.size();
  }
  bool empty() {
    return verticies.empty();
  }
  void print() {
    for (int i(0); i < size(); ++i)
      std::cout << i << ' '<< verticies[i] << std::endl;
    std::cout << size() << ' ' << std::endl;
    for (int i(0); i < size(); ++i) {
      for (int j(0); j < size(); ++j) {
        std::cout << verticies[i] << '|' << verticies[j] << '|' << edges[i][j].value_or(-1) << ' ';
      }
      std::cout << std::endl;
    }
  }
};

#endif // MATRIX_GRAPH_H_