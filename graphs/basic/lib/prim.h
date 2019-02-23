#ifndef PRIM_H_
#define PRIM_H_

#include <string>
#include <limits>
#include <algorithm>
#include <iostream>

namespace prim {

typedef std::string vertex_t;
typedef double weight_t;

struct Node {
  int source_index;
  weight_t weight = std::numeric_limits<weight_t>::infinity();
  bool visited = false;
};

Node* prim(vertex_t* verticies, weight_t** edges, const size_t& vertex_count, const vertex_t& source) {
  int source_index = std::distance(verticies, std::find(verticies, verticies + vertex_count, source));
  if (source_index == vertex_count)
    throw std::logic_error("source vertex not found");
  auto map = new Node[vertex_count];
  map[source_index].weight = 0;
  for (int step(0); step < vertex_count - 1; ++step) {
    int min_index = std::distance(map, std::min_element(map, map + vertex_count,
      [](const Node &l, const Node &r) -> bool {
        return !l.visited && l.weight < r.weight;
      }
    ));
    if (map[min_index].visited) break;
    map[min_index].visited = true;
    for (int neighbour_index = 0; neighbour_index < vertex_count; ++neighbour_index) {
      if (!map[neighbour_index].visited && edges[min_index][neighbour_index] < map[neighbour_index].weight) {
        map[neighbour_index].weight = edges[min_index][neighbour_index];
        map[neighbour_index].source_index = min_index;
      }
    }
  }
  return map;
}

void print(vertex_t* verticies, const size_t& vertex_count, Node* map, const int& source_index) {
  for (int vertex_index(0); vertex_index < vertex_count; ++vertex_index) {
    if (map[vertex_index].source_index == source_index) {
      std::cout << verticies[map[vertex_index].source_index] << " -> " << verticies[vertex_index] << std::endl;
      print(verticies, vertex_count, map, vertex_index);
    }
  }
}

void print(vertex_t* verticies, const size_t& vertex_count, Node* map, const vertex_t& source) {
  int source_index = std::distance(verticies, std::find(verticies, verticies + vertex_count, source));
  print(verticies, vertex_count, map, source_index);
}

}

#endif // PRIM_H_
