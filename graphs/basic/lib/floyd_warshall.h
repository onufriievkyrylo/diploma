#ifndef FLOYD_WARSHALL_H_
#define FLOYD_WARSHALL_H_

#include <limits>
#include <algorithm>

namespace floyd_warshall {

typedef std::string vertex_t;
typedef double weight_t;

struct Node {
  int through_index = -1;
  weight_t weight = std::numeric_limits<weight_t>::infinity();
};

Node** floyd_warshall(vertex_t* verticies, weight_t** edges, const size_t& vertex_count) {
  auto map = new Node*[vertex_count];

  for (int source_index(0); source_index < vertex_count; ++source_index) {
    map[source_index] = new Node[vertex_count];
    for (int dest_index(0); dest_index < vertex_count; ++dest_index) {
      if (edges[source_index][dest_index] != std::numeric_limits<weight_t>::infinity()) {
        map[source_index][dest_index].weight = edges[source_index][dest_index];
        map[source_index][dest_index].through_index = dest_index;
      }
    }
  }

  for (int source_index(0); source_index < vertex_count; ++source_index) {
    for (int throught_index(0); throught_index < vertex_count; ++throught_index) {
      if (map[source_index][throught_index].weight != std::numeric_limits<weight_t>::infinity()) {
        for (int dest_index(0); dest_index < vertex_count; ++dest_index) {
          weight_t weight = map[source_index][throught_index].weight + map[throught_index][dest_index].weight;
          if (map[source_index][dest_index].weight > weight) {
            map[source_index][dest_index].weight = weight;
            map[source_index][dest_index].through_index = map[source_index][throught_index].through_index;
          }
        }
      }
    }
  }

  return map;
}

void print(vertex_t* verticies, const size_t& vertex_count, Node** map) {
  for (int source_index(0); source_index < vertex_count; ++source_index) {
    for (int dest_index(0); dest_index < vertex_count; ++dest_index) {
      if (source_index == dest_index) {
        continue;
      } else if (map[source_index][dest_index].through_index >= 0) {
        std::cout << "Distance from " << verticies[source_index] << " to " << verticies[dest_index] << " is " << map[source_index][dest_index].weight << "km." << std::endl;
        if (map[source_index][dest_index].through_index != dest_index) {
          std::cout << "Pass through: ";
          for (int through_index = map[source_index][dest_index].through_index; through_index != dest_index; through_index = map[through_index][dest_index].through_index) {
            std::cout << verticies[through_index];
            if (map[through_index][dest_index].through_index != dest_index) {
              std::cout << ", ";
            } else {
              std::cout << std::endl;
            }
          }
        }
      } else {
        std::cout << verticies[dest_index] << " is unreachable from " << verticies[source_index] << std::endl;
      }
    }
  }
}

}

#endif // FLOYD_WARSHALL_H_
