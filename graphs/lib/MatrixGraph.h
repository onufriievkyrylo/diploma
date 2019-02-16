#ifndef MATRIX_GRAPH_H_
#define MATRIX_GRAPH_H_

#include <string>
#include <iostream>
#include <algorithm>
#include <exception>
#include <vector>
#include <limits>

class RoadMatrixGraph {
  private:
  typedef std::string vertex_t;
  typedef double weight_t;

  struct DijkstraNode {
    int source_index;
    weight_t weight = std::numeric_limits<weight_t>::infinity();
    bool visited = false;
  };

  std::vector<vertex_t> verticies;
  std::vector<std::vector<weight_t>> edges;
  public:
  std::vector<DijkstraNode> dijkstra(const vertex_t& source) {
    const size_t vertex_count = size();
    int source_index = index_of(source);
    if (source_index < 0)
      throw std::logic_error("source vertex not found");
    std::vector<DijkstraNode> map(vertex_count);
    map[source_index].weight = 0;
    map[source_index].source_index = source_index;
    for (int step(0); step < vertex_count - 1; ++step) {
      int min_index = std::distance(map.begin(), std::min_element(map.begin(), map.end(),
        [](const DijkstraNode &l, const DijkstraNode &r) -> bool {
          return !l.visited && l.weight <= r.weight;
        }
      ));
      if (map[min_index].weight == std::numeric_limits<weight_t>::infinity()) break;
      map[min_index].visited = true;
      for (int neighbour_index = 0; neighbour_index < vertex_count; ++neighbour_index) {
        if (!map[neighbour_index].visited && edges[min_index][neighbour_index] != std::numeric_limits<weight_t>::infinity()) {
          weight_t weight = map[min_index].weight + edges[min_index][neighbour_index];
          if (weight < map[neighbour_index].weight) {
            map[neighbour_index].weight = weight;
            map[neighbour_index].source_index = min_index;
          }
        }
      }
    }
    return map;
  }
  std::vector<DijkstraNode> dijkstra(const vertex_t& source, const vertex_t& dest) {
    size_t vertex_count = size();
    int source_index = index_of(source);
    if (source_index < 0)
      throw std::logic_error("source vertex not found");
    int dest_index = index_of(dest);
    if (dest_index < 0)
      throw std::logic_error("dest vertex not found");
    std::vector<DijkstraNode> map(vertex_count);
    map[source_index].weight = 0;
    map[source_index].source_index = source_index;
    for (int step(0); step < vertex_count - 1; ++step) {
      int min_index = std::distance(map.begin(), std::min_element(map.begin(), map.end(),
        [](const DijkstraNode &l, const DijkstraNode &r) -> bool {
          return !l.visited && l.weight <= r.weight;
        }
      ));
      if (map[min_index].visited) break;
      map[min_index].visited = true;
      if (min_index == dest_index) break;
      for (int neighbour_index = 0; neighbour_index < vertex_count; ++neighbour_index) {
        if (!map[neighbour_index].visited && edges[min_index][neighbour_index] != std::numeric_limits<weight_t>::infinity()) {
          weight_t weight = map[min_index].weight + edges[min_index][neighbour_index];
          if (weight < map[neighbour_index].weight) {
            map[neighbour_index].weight = weight;
            map[neighbour_index].source_index = min_index;
          }
        }
      }
    }
    return map;
  }
  RoadMatrixGraph* add(const vertex_t& vertex) {
    if (contains(vertex)) throw std::logic_error("vertex already added");
    verticies.push_back(vertex);
    for (auto &edge : edges) {
      edge.push_back(std::numeric_limits<weight_t>::infinity());
    }
    edges.push_back(std::vector<weight_t>(size(), std::numeric_limits<weight_t>::infinity()));
    return this;
  }
  RoadMatrixGraph* remove(const vertex_t& vertex) {
    int removal_index = index_of(vertex);
    if (removal_index < 0)
      throw std::logic_error("vertex not found");
    verticies.erase(verticies.begin() + removal_index);
    edges.erase(edges.begin() + removal_index);
    for (auto &edge : edges) {
      edge.erase(edge.begin() + removal_index);
    }
    return this;
  }
  RoadMatrixGraph* connect(const vertex_t& vertex1, const vertex_t& vertex2, const weight_t& weight) {
    int vertex1_index = index_of(vertex1);
    if (vertex1_index < 0)
      throw std::logic_error("vertex1 not found");
    int vertex2_index = index_of(vertex2);
    if (vertex2_index < 0)
      throw std::logic_error("vertex2 not found");
    edges[vertex1_index][vertex2_index] = weight;
    return this;
  }
  RoadMatrixGraph* disconnect(const vertex_t& vertex1, const vertex_t& vertex2) {
    int vertex1_index = index_of(vertex1);
    if (vertex1_index < 0)
      throw std::logic_error("vertex1 not found");
    int vertex2_index = index_of(vertex2);
    if (vertex2_index < 0)
      throw std::logic_error("vertex2 not found");
    edges[vertex1_index][vertex2_index] = std::numeric_limits<weight_t>::infinity();
    return this;
  }
  bool contains(const vertex_t& vertex) {
    return std::find(verticies.begin(), verticies.end(), vertex) != verticies.end();
  }
  vertex_t get_vertex(int vertex_index) {
    if (vertex_index < 0 || vertex_index >= size())
      throw std::out_of_range("vertex index is out of range");
    return verticies[vertex_index];
  }
  int index_of(const vertex_t& vertex) {
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
    std::cout << "Count of verticies: " << size() << std::endl;
    for (int i(0); i < size(); ++i) {
      for (int j(0); j < size(); ++j) {
        if (edges[i][j] != std::numeric_limits<weight_t>::infinity())
        std::cout << verticies[i] << " - " << verticies[j] << " is " << edges[i][j] << " km." << std::endl;
      }
    }
  }
};

#endif // MATRIX_GRAPH_H_