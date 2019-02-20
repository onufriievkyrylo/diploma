#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include <limits>
#include <algorithm>

namespace dijkstra {

typedef std::string vertex_t;
typedef double weight_t;

struct Node {
  int source_index;
  weight_t weight = std::numeric_limits<weight_t>::infinity();
  bool visited = false;
};

Node* dijkstra(vertex_t* verticies, weight_t** edges, const size_t& vertex_count, const vertex_t& source, const vertex_t& dest) {
  int source_index = std::distance(verticies, std::find(verticies, verticies + vertex_count, source));
  if (source_index == vertex_count)
    throw std::logic_error("source vertex not found");
  int dest_index = std::distance(verticies, std::find(verticies, verticies + vertex_count, dest));
  if (dest_index == vertex_count)
    throw std::logic_error("dest vertex not found");
  auto map = new Node[vertex_count];
  map[source_index].weight = 0;
  map[source_index].source_index = source_index;
  for (int step(0); step < vertex_count - 1; ++step) {
    int min_index = std::distance(map, std::min_element(map, map + vertex_count,
      [](const Node &l, const Node &r) -> bool {
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

Node* dijkstra(vertex_t* verticies, weight_t** edges, const size_t& vertex_count, const vertex_t& source) {
  int source_index = std::distance(verticies, std::find(verticies, verticies + vertex_count, source));
  if (source_index == vertex_count)
    throw std::logic_error("source vertex not found");
  auto map = new Node[vertex_count];
  map[source_index].weight = 0;
  map[source_index].source_index = source_index;
  for (int step(0); step < vertex_count - 1; ++step) {
    int min_index = std::distance(map, std::min_element(map, map + vertex_count,
      [](const Node &l, const Node &r) -> bool {
        return !l.visited && l.weight <= r.weight;
      }
    ));
    if (map[min_index].visited) break;
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

void print(vertex_t* verticies, const size_t& vertex_count, Node* map, const int& source_index, const int& dest_index) {
  if (source_index != dest_index) {
    if (map[dest_index].visited) {
      std::cout << "Distance from " << verticies[source_index] << " to " << verticies[dest_index] << " is " << map[dest_index].weight << "km." << std::endl;
      auto sequence = new int[vertex_count];
      int sequence_length = 0;
      for (int from_index(map[dest_index].source_index); from_index != source_index; from_index = map[from_index].source_index) {
        sequence[sequence_length++] = from_index;
      }
      if (sequence_length) {
        std::cout << "Pass through: ";
        for (int from_index(sequence[--sequence_length]); sequence_length >= 0; from_index = sequence[--sequence_length]) {
          std::cout << verticies[from_index];
          if (sequence_length != 0) {
            std::cout << ", ";
          } else {
            std::cout << std::endl;
          }
        }
      }
      delete[] sequence;
    } else {
      std::cout << verticies[dest_index] << " is unreachable from " << verticies[source_index] << std::endl;
    }
  }
}

void print(vertex_t* verticies, const size_t& vertex_count, Node* map, const vertex_t& source, const vertex_t& dest) {
  int source_index = std::distance(verticies, std::find(verticies, verticies + vertex_count, source));
  int dest_index = std::distance(verticies, std::find(verticies, verticies + vertex_count, dest));
  print(verticies, vertex_count, map, source_index, dest_index);
}

void print(vertex_t* verticies, const size_t& vertex_count, Node* map, const vertex_t& source) {
  int source_index = std::distance(verticies, std::find(verticies, verticies + vertex_count, source));

  for (int dest_index(0); dest_index < vertex_count; ++dest_index) {
    print(verticies, vertex_count, map, source_index, dest_index); 
    std::cout << std::endl;
  }
}

}

#endif // DIJKSTRA_H_