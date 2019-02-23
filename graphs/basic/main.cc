#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "./lib/dijkstra.h"
#include "./lib/floyd_warshall.h"
#include "./lib/prim.h"
#include "./lib/depth_first_search.h"
#include "./lib/breadth_first_search.h"

inline const size_t vertex_count = 25;

typedef std::string vertex_t;
typedef double weight_t;

int main() {
  auto verticies = new vertex_t[vertex_count];
  auto edges = new weight_t*[vertex_count];

  for (int source_index(0); source_index < vertex_count; ++source_index) {
    edges[source_index] = new weight_t[vertex_count];
    for (int dest_index(0); dest_index < vertex_count; ++dest_index) {
      edges[source_index][dest_index] = std::numeric_limits<weight_t>::infinity();
    }
  }

  std::ifstream cities("./data/cities.txt");
  for (int vertex_index(0); vertex_index < vertex_count; ++vertex_index) {
    cities >> verticies[vertex_index];
  }
  cities.close();

  std::ifstream roads("./data/roads.txt");
  vertex_t source, dest;
  weight_t weight;
  while (roads >> source >> dest >> weight) {
    int source_index = std::distance(verticies, std::find(verticies, verticies + vertex_count, source));
    int dest_index = std::distance(verticies, std::find(verticies, verticies + vertex_count, dest));
    edges[source_index][dest_index] = weight;
    edges[dest_index][source_index] = weight;
  }
  roads.close();

  // Print graph
  // for (int i(0); i < vertex_count; ++i) {
  //   for (int j(0); j < vertex_count; ++j) {
  //     if (edges[i][j] != std::numeric_limits<weight_t>::infinity())
  //     std::cout << verticies[i] << " - " << verticies[j] << " is " << edges[i][j] << " km." << std::endl;
  //   }
  // }

  // Dijkstra test source only
  // auto map = dijkstra::dijkstra(verticies, edges, vertex_count, "Lviv");
  // dijkstra::print(verticies, vertex_count, map, "Lviv");
  // delete[] map;

  // Dijkstra test source and dest
  // auto map = dijkstra::dijkstra(verticies, edges, vertex_count, "Lviv", "Kharkiv");
  // dijkstra::print(verticies, vertex_count, map, "Lviv", "Kharkiv");
  // delete[] map;

  // Floyd-Warshall test
  // auto map = floyd_warshall::floyd_warshall(verticies, edges, vertex_count);
  // floyd_warshall::print(verticies, vertex_count, map);
  // delete[] map;

  // Prim test
  // auto map = prim::prim(verticies, edges, vertex_count, "Kharkiv");
  // prim::print(verticies, vertex_count, map, "Kharkiv");
  // delete[] map;

  // Depth-first search test
  // dfs::search(verticies, edges, vertex_count, "Kharkiv");

  // Breadth-first search test
  // bfs::search(verticies, edges, vertex_count, "Kharkiv");

  return 0;
}
