#ifndef BREADTH_FIRS_SEARC_H_
#define BREADTH_FIRS_SEARC_H_

#include <string>
#include <iostream>

#include "./utils.h"

void breadth_search(vertex_t* verticies, weight_t** edges, const int& vertex_count, const vertex_t& source) {
  int source_index = get_vertex_index(verticies, verticies + vertex_count, source);
  auto visited = new bool[vertex_count];
  auto levels = new int[vertex_count];
  auto queue = new int[vertex_count];
  visited[source_index] = true;
  levels[source_index] = 1;
  int queue_back = 0;
  int queue_front = 0;
  queue[queue_back++] = source_index;
  while(queue_front != queue_back) {
    int source_index = queue[queue_front++];
    int level = levels[source_index];
    std::cout << std::string(level, '=') << verticies[source_index] << std::endl;
    for (int dest_index(0); dest_index < vertex_count; ++dest_index) {
      if (!visited[dest_index] && edges[source_index][dest_index] < INFINITY) {
        visited[dest_index] = true;
        levels[dest_index] = level + 1;
        queue[queue_back++] = dest_index;
      }
    }
  }
  delete[] levels;
  delete[] visited;
  delete[] queue;
}

#endif // BREADTH_FIRS_SEARC_H_
