#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include <string>
#include <iostream>

#include "./utils.h"

struct DijkstraNode {
  int source_index;
  weight_t weight = INFINITY;
  bool visited = false;
};

DijkstraNode* dijkstra(vertex_t* verticies, weight_t** edges, const int& vertex_count, const vertex_t& source, const vertex_t& dest) {
  int source_index = get_vertex_index(verticies, verticies + vertex_count, source);
  if (source_index == vertex_count)
    throw std::logic_error("source vertex not found");
  int dest_index = get_vertex_index(verticies, verticies + vertex_count, dest);
  if (dest_index == vertex_count)
    throw std::logic_error("dest vertex not found");
  auto map = new DijkstraNode[vertex_count];
  for (int node_index(0); node_index < vertex_count; ++node_index) {
    map[node_index].visited = false;
    map[node_index].weight = INFINITY;
  }
  map[source_index].weight = 0;
  for (int step(0); step < vertex_count; ++step) {
    int min_index = 0;
    for (int node_index(1); node_index < vertex_count; ++node_index) {
      if (map[min_index].visited || !map[node_index].visited && map[node_index].weight < map[min_index].weight) {
        min_index = node_index;
      }
    }
    if (map[min_index].visited) break;
    map[min_index].visited = true;
    if (min_index == dest_index) break;
    for (int neighbour_index = 0; neighbour_index < vertex_count; ++neighbour_index) {
      if (!map[neighbour_index].visited && edges[min_index][neighbour_index] < INFINITY) {
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

DijkstraNode* dijkstra(vertex_t* verticies, weight_t** edges, const int& vertex_count, const vertex_t& source) {
  int source_index = get_vertex_index(verticies, verticies + vertex_count, source);
  if (source_index == vertex_count)
    throw std::logic_error("source vertex not found");
  auto map = new DijkstraNode[vertex_count];
  for (int node_index(0); node_index < vertex_count; ++node_index) {
    map[node_index].visited = false;
    map[node_index].weight = INFINITY;
  }
  map[source_index].weight = 0;
  for (int step(0); step < vertex_count; ++step) {
    int min_index = 0;
    for (int node_index(1); node_index < vertex_count; ++node_index) {
      if (map[min_index].visited || !map[node_index].visited && map[node_index].weight < map[min_index].weight) {
        min_index = node_index;
      }
    }
    if (map[min_index].visited) break;
    map[min_index].visited = true;
    for (int neighbour_index = 0; neighbour_index < vertex_count; ++neighbour_index) {
      if (!map[neighbour_index].visited && edges[min_index][neighbour_index] < INFINITY) {
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

void dijkstra_print(vertex_t* verticies, const int& vertex_count, DijkstraNode* map, const int& source_index, const int& dest_index) {
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

void dijkstra_print(vertex_t* verticies, const int& vertex_count, DijkstraNode* map, const vertex_t& source, const vertex_t& dest) {
  int source_index = get_vertex_index(verticies, verticies + vertex_count, source);
  int dest_index = get_vertex_index(verticies, verticies + vertex_count, dest);
  dijkstra_print(verticies, vertex_count, map, source_index, dest_index);
}

void dijkstra_print(vertex_t* verticies, const int& vertex_count, DijkstraNode* map, const vertex_t& source) {
  int source_index = get_vertex_index(verticies, verticies + vertex_count, source);

  for (int dest_index(0); dest_index < vertex_count; ++dest_index) {
    dijkstra_print(verticies, vertex_count, map, source_index, dest_index); 
    std::cout << std::endl;
  }
}

#endif // DIJKSTRA_H_