#ifndef PRIM_H_
#define PRIM_H_

#include <string>
#include <iostream>

#include "./utils.h"

struct PrimNode {
  int source_index;
  weight_t weight = INFINITY;
  bool visited = false;
};

PrimNode* prim(vertex_t* verticies, weight_t** edges, const int& vertex_count, const vertex_t& source) {
  int source_index = get_vertex_index(verticies, verticies + vertex_count, source);
  if (source_index == vertex_count)
    throw std::logic_error("source vertex not found");
  auto map = new PrimNode[vertex_count];
  for (int node_index(0); node_index < vertex_count; ++node_index) {
    map[node_index].visited = false;
    map[node_index].weight = INFINITY;
  }
  map[source_index].weight = 0;
  for (int step(0); step < vertex_count - 1; ++step) {
    int min_index = 0;
    for (int node_index(1); node_index < vertex_count; ++node_index) {
      if (map[min_index].visited || !map[node_index].visited && map[node_index].weight < map[min_index].weight) {
        min_index = node_index;
      }
    }
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

void prim_print(vertex_t* verticies, const int& vertex_count, PrimNode* map, const int& source_index) {
  for (int vertex_index(0); vertex_index < vertex_count; ++vertex_index) {
    if (map[vertex_index].source_index == source_index) {
      std::cout << verticies[map[vertex_index].source_index] << " -> " << verticies[vertex_index] << std::endl;
      prim_print(verticies, vertex_count, map, vertex_index);
    }
  }
}

void prim_print(vertex_t* verticies, const int& vertex_count, PrimNode* map, const vertex_t& source) {
  int source_index = get_vertex_index(verticies, verticies + vertex_count, source);
  prim_print(verticies, vertex_count, map, source_index);
}

#endif // PRIM_H_
