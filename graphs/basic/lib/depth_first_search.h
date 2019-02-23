#ifndef DEPTH_FIRS_SEARC_H_
#define DEPTH_FIRS_SEARC_H_

#include <string>
#include <limits>
#include <algorithm>
#include <iostream>

namespace dfs {

typedef std::string vertex_t;
typedef double weight_t;

void search(vertex_t* verticies, weight_t** edges, const size_t& vertex_count, const int& source_index, bool* visited, int level = 1) {
  std::cout << std::string(level, '=') << verticies[source_index] << std::endl;
  for (int dest_index(0); dest_index < vertex_count; ++dest_index) {
    if (!visited[dest_index] && edges[source_index][dest_index] < std::numeric_limits<weight_t>::infinity()) {
      visited[dest_index] = true;
      search(verticies, edges, vertex_count, dest_index, visited, level + 1);
    }
  }
}

void search(vertex_t* verticies, weight_t** edges, const size_t& vertex_count, const vertex_t& source) {
  int source_index = std::distance(verticies, std::find(verticies, verticies + vertex_count, source));
  auto visited = new bool[vertex_count];
  visited[source_index] = true;
  search(verticies, edges, vertex_count, source_index, visited);
  delete[] visited;
}

}

#endif // DEPTH_FIRS_SEARC_H_
