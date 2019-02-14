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
class MatrixGraph : AbstractGraph<V, E>, AbstractDijkstra<V, int, E> {
  private:
  std::vector<V> verticies;
  std::vector<std::vector<std::optional<E>>> edges;
  public:
  typedef typename AbstractDijkstra<V, int, E>::Map AbstractDijkstraMap;
  class DijkstraMap : public AbstractDijkstraMap {
    typedef typename AbstractDijkstraMap::Node Node;
    private:
    int source_index;
    std::vector<Node> nodes;
    MatrixGraph* graph;
    public:
    DijkstraMap(MatrixGraph* graph, int source_index, size_t length)
      : graph(graph), nodes(length), source_index(source_index) {
      nodes[source_index].determined = true;
      nodes[source_index].source = source_index;
    }
    ~DijkstraMap() {
      delete[] nodes;
    }
    int next() {
      return std::distance(nodes.begin(), std::min_element(nodes.begin(), nodes.end(),
        [](const Node &l, const Node &r) -> bool {
          return l.visited || r.visited ? r.visited && !l.visited
            : !l.determined || !r.determined ? !r.determined
            : l.weight <= r.weight;
        }
      ));
    }
    Node& get(const int& index) {
      return nodes[index];
    }
    void set(const int& from, const int& to, const E& weight) {
      nodes[to].determined = true;
      nodes[to].weight = weight;
      nodes[to].source = from;
    }
    void visit(const int& index) {
      nodes[index].visited = true;
    }
    GraphPath<V, E> path(const V& dest) {
      int dest_index = graph->index_of(dest);
      if (dest_index < 0)
        throw std::logic_error("dest vertex not found");
      GraphPath<V, E> path;
      path.from = graph->verticies[source_index];
      path.to = graph->verticies[dest_index];
      path.weight = nodes[dest_index].weight;
      if (nodes[dest_index].visited) {
        for (int from_index(nodes[dest_index].source); from_index != source_index; from_index = nodes[from_index].source) {
          ++path.sequence_length;
        }
        if (path.sequence_length) {
          path.sequence = new V[path.sequence_length]();
          int node_index(path.sequence_length - 1);
          for (int from_index(nodes[dest_index].source); from_index != source_index; from_index = nodes[from_index].source) {
            path.sequence[node_index--] = graph->verticies[from_index];
          }
        }
      } else {
        path.unreachable = true;
      }
      return path;
    }
    GraphPath<V, E>* path() {
      auto paths = new GraphPath<V, E>[nodes.size()];
      for (int dest_index(0); dest_index < nodes.size(); ++dest_index) {
        auto path = &paths[dest_index];
        path->from = graph->verticies[source_index];
        path->to = graph->verticies[dest_index];
        path->weight = nodes[dest_index].weight;
        if (nodes[dest_index].visited) {
          for (int from_index(nodes[dest_index].source); from_index != source_index; from_index = nodes[from_index].source) {
            ++path->sequence_length;
          }
          if (path->sequence_length) {
            path->sequence = new V[path->sequence_length]();
            int node_index(path->sequence_length - 1);
            for (int from_index(nodes[dest_index].source); from_index != source_index; from_index = nodes[from_index].source) {
              path->sequence[node_index--] = graph->verticies[from_index];
            }
          }
        } else {
          path->unreachable = true;
        }
      }
      return paths;
    }
  };
  AbstractDijkstraMap* dijkstra(const V& source) {
    const size_t vertex_count = size();
    int source_index = index_of(source);
    if (source_index < 0)
      throw std::logic_error("source vertex not found");
    auto map = new DijkstraMap(this, source_index, vertex_count);
    for (int step(0); step < vertex_count - 1; ++step) {
      int min_index = map->next();
      if (!map->get(min_index).determined) break;
      map->visit(min_index);
      for (int neighbour_index = 0; neighbour_index < vertex_count; ++neighbour_index) {
        if (edges[min_index][neighbour_index].has_value() && !map->get(neighbour_index).visited) {
          E weight = map->get(min_index).weight + edges[min_index][neighbour_index].value();
          if (!map->get(neighbour_index).determined || weight < map->get(neighbour_index).weight) {
            map->set(min_index, neighbour_index, weight);
          }
        }
      }
    }
    return map;
  }
  AbstractDijkstraMap* dijkstra(const V& source, const V& dest) {
    size_t vertex_count = size();
    int source_index = index_of(source);
    if (source_index < 0)
      throw std::logic_error("source vertex not found");
    int dest_index = index_of(dest);
    if (dest_index < 0)
      throw std::logic_error("dest vertex not found");
    auto map = new DijkstraMap(this, source_index, vertex_count);
    for (int step(0); step < vertex_count - 1; ++step) {
      int min_index = map->next();
      if (min_index == dest_index || !map->get(min_index).determined) break;
      map->visit(min_index);
      for (int neighbour_index = 0; neighbour_index < vertex_count; ++neighbour_index) {
        if (edges[min_index][neighbour_index].has_value() && !map->get(neighbour_index).visited) {
          E weight = map->get(min_index).weight + edges[min_index][neighbour_index].value();
          if (!map->get(neighbour_index).determined || weight < map->get(neighbour_index).weight) {
            map->set(min_index, neighbour_index, weight);
          }
        }
      }
    }
    return map;
  }
  MatrixGraph* add(const V& vertex) {
    if (contains(vertex)) throw std::logic_error("vertex already added");
    verticies.push_back(vertex);
    for (auto &edge : edges) {
      edge.push_back(std::optional<E>());
    }
    edges.push_back(std::vector<std::optional<E>>(size(), std::optional<E>()));
    return this;
  }
  MatrixGraph* remove(const V& vertex) {
    int removal_index = index_of(vertex);
    if (removal_index < 0) throw std::logic_error("vertex not found");
    return remove(removal_index);
  }
  MatrixGraph* remove(const int removal_index) {
    if (removal_index < 0 || removal_index >= size())
      throw std::out_of_range("index is out of range");
    verticies.erase(verticies.begin() + removal_index);
    edges.erase(edges.begin() + removal_index);
    for (auto &edge : edges) {
      edge.erase(edge.begin() + removal_index);
    }
    return this;
  }
  MatrixGraph* connect(const V& vertex1, const V& vertex2, const E& edge) {
    int vertex1_index = index_of(vertex1);
    if (vertex1_index < 0)
      throw std::logic_error("vertex1 not found");
    int vertex2_index = index_of(vertex2);
    if (vertex2_index < 0)
      throw std::logic_error("vertex2 not found");
    edges[vertex1_index][vertex2_index] = edge;
    return this;
  }
  MatrixGraph* connect(const int vertex1_index, const int vertex2_index, const E& edge) {
    if (vertex1_index < 0 || vertex1_index >= size())
      throw std::out_of_range("vertex1 index is out of range");
    if (vertex2_index < 0 || vertex2_index >= size())
      throw std::out_of_range("vertex2 index is out of range");
    edges[vertex1_index][vertex2_index] = edge;
    return this;
  }
  MatrixGraph* disconnect(const V& vertex1, const V& vertex2) {
    int vertex1_index = index_of(vertex1);
    if (vertex1_index < 0)
      throw std::logic_error("vertex1 not found");
    int vertex2_index = index_of(vertex2);
    if (vertex2_index < 0)
      throw std::logic_error("vertex2 not found");
    edges[vertex1_index][vertex2_index].reset();
    return this;
  }
  MatrixGraph* disconnect(const int vertex1_index, const int vertex2_index) {
    if (vertex1_index < 0 || vertex1_index >= size())
      throw std::out_of_range("vertex1 index is out of range");
    if (vertex2_index < 0 || vertex2_index >= size())
      throw std::out_of_range("vertex2 index is out of range");
    edges[vertex1_index][vertex2_index].reset();
    return this;
  }
  bool contains(const V& vertex) {
    return std::find(verticies.begin(), verticies.end(), vertex) != verticies.end();
  }
  int index_of(const V& vertex) {
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