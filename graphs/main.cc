#include <string>
#include <iostream>
#include <fstream>

#include "./lib/utils.h"
#include "./lib/dijkstra.h"
#include "./lib/floyd_warshall.h"
#include "./lib/prim.h"
#include "./lib/depth_first_search.h"
#include "./lib/breadth_first_search.h"

inline const int vertex_count = 7;

void dijkstra_single_test(vertex_t* verticies, weight_t** edges) {
  DijkstraNode* map = dijkstra(verticies, edges, vertex_count, "A");
  dijkstra_print(verticies, vertex_count, map, "A");
  delete[] map;
}

void dijkstra_double_test(vertex_t* verticies, weight_t** edges) {
  DijkstraNode* map = dijkstra(verticies, edges, vertex_count, "A", "E");
  dijkstra_print(verticies, vertex_count, map, "A", "E");
  delete[] map;
}

void floyd_warshall_test(vertex_t* verticies, weight_t** edges) {
  FloydWarshalNode** map = floyd_warshall(verticies, edges, vertex_count);
  floyd_warshall_print(verticies, vertex_count, map);
  for (int source_index(0); source_index < vertex_count; ++source_index) {
    delete[] map[source_index];
  }
  delete[] map;
}

void prim_test(vertex_t* verticies, weight_t** edges) {
  PrimNode* map = prim(verticies, edges, vertex_count, "A");
  prim_print(verticies, vertex_count, map, "A");
  delete[] map;
}

void depth_search_test(vertex_t* verticies, weight_t** edges) {
  depth_search(verticies, edges, vertex_count, "A");
}

void breadth_search_test(vertex_t* verticies, weight_t** edges) {
  breadth_search(verticies, edges, vertex_count, "A");
}

int main() {
  auto verticies = new vertex_t[vertex_count];
  auto edges = new weight_t*[vertex_count];

  for (int source_index(0); source_index < vertex_count; ++source_index) {
    edges[source_index] = new weight_t[vertex_count];
    for (int dest_index(0); dest_index < vertex_count; ++dest_index) {
      edges[source_index][dest_index] = INFINITY;
    }
  }

  std::ifstream verticies_file("./data/verticies.txt");
  for (int vertex_index(0); vertex_index < vertex_count; ++vertex_index) {
    verticies_file >> verticies[vertex_index];
  }
  verticies_file.close();

  std::ifstream edges_file("./data/edges.txt");
  vertex_t source, dest;
  weight_t weight;
  while (edges_file >> source >> dest >> weight) {
    int source_index = get_vertex_index(verticies, verticies + vertex_count, source);
    int dest_index = get_vertex_index(verticies, verticies + vertex_count, dest);
    edges[source_index][dest_index] = weight;
    edges[dest_index][source_index] = weight;
  }
  edges_file.close();

  // Print graph
  for (int i(0); i < vertex_count; ++i) {
    for (int j(0); j < vertex_count; ++j) {
      if (edges[i][j] < INFINITY) {
        std::cout << verticies[i] << " - " << verticies[j] << " is " << edges[i][j] << " km." << std::endl;
      }
    }
  }

  // Dijkstra test source only
  dijkstra_single_test(verticies, edges);

  // Dijkstra test source and dest
  // dijkstra_double_test(verticies, edges);

  // Floyd-Warshall test
  // floyd_warshall_test(verticies, edges);

  // Prim test
  // prim_test(verticies, edges);

  // Depth-first search test
  // depth_search_test(verticies, edges);

  // Breadth-first search test
  // breadth_search_test(verticies, edges);

  return 0;
}
