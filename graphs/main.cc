#include <fstream>
#include <string>

#include "./lib/MatrixGraph.h"

struct Road {
  std::string from;
  std::string to;
  double distance;
};

void dijkstra(RoadMatrixGraph* graph, const std::string& source, const std::string& dest) {
  auto map = graph->dijkstra(source, dest);
  int source_index = graph->index_of(source);
  int dest_index = graph->index_of(dest);

  if (map[dest_index].visited) {
    std::cout << "Distance from " << source << " to " << dest << " is " << map[dest_index].weight << "km." << std::endl;
    auto sequence = new int[graph->size()];
    int sequence_length = 0;
    for (int from_index(map[dest_index].source_index); from_index != source_index; from_index = map[from_index].source_index) {
      sequence[sequence_length++] = from_index;
    }
    if (sequence_length) {
      std::cout << "Pass through: ";
      for (int from_index(sequence[--sequence_length]); sequence_length >= 0; from_index = sequence[--sequence_length]) {
        std::cout << graph->get_vertex(from_index);
        if (sequence_length != 0) {
          std::cout << ", ";
        } else {
          std::cout << std::endl;
        }
      }
    }
    delete[] sequence;
  } else {
    std::cout << dest << " is unreachable from " << source << std::endl;
  }
}

void dijkstra(RoadMatrixGraph* graph, const std::string& source) {
  auto map = graph->dijkstra(source);
  int source_index = graph->index_of(source);

  for (int dest_index(0); dest_index < graph->size(); ++dest_index) {
    if (map[dest_index].visited) {
      std::cout << "Distance from " << source << " to " << graph->get_vertex(dest_index) << " is " << map[dest_index].weight << "km." << std::endl;
      auto sequence = new int[graph->size()];
      int sequence_length = 0;
      for (int from_index(map[dest_index].source_index); from_index != source_index; from_index = map[from_index].source_index) {
        sequence[sequence_length++] = from_index;
      }
      if (sequence_length) {
        std::cout << "Pass through: ";
        for (int from_index(sequence[--sequence_length]); sequence_length >= 0; from_index = sequence[--sequence_length]) {
          std::cout << graph->get_vertex(from_index);
          if (sequence_length != 0) {
            std::cout << ", ";
          } else {
            std::cout << std::endl;
          }
        }
      }
      delete[] sequence;
    } else {
      std::cout << graph->get_vertex(dest_index) << " is unreachable from " << source << std::endl;
    }
    std::cout << std::endl;
  }
}

void floyd_warshall(RoadMatrixGraph* graph, const std::string& source, const std::string& dest) {

}

int main() {
  auto graph = new RoadMatrixGraph();
  
  std::ifstream cities("./data/cities.txt");
  std::string city;
  while (cities >> city) {
    graph->add(city);
  }
  cities.close();

  graph->add("Warszawa");
  graph->add("Weilun");

  std::ifstream roads("./data/roads.txt");
  Road road;
  while (roads >> road.from >> road.to >> road.distance) {
    graph
      ->connect(road.from, road.to, road.distance)
      ->connect(road.to, road.from, road.distance);
  }
  roads.close();

  // Print graph
  // graph->print();

  // Dijkstra test source only
  dijkstra(graph, "Lviv");

  // Dijkstra test source and dest
  dijkstra(graph, "Lviv", "Kharkiv");

  // Floyd-Warshall test
  floyd_warshall(graph, "Lviv", "Kharkiv");

  delete graph;

  return 0;
}
