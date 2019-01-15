//#include "Graphs/Vertex.h"
#include "Graphs/MatrixGraph.h"
#include <string>

int main() {
  auto graph = new MatrixGraph<std::string, std::string>();
  for(int i(0); i < 13; ++i)
    graph->add(std::to_string(i));
  graph->add("asd");
  graph->print();
  graph->remove("asd");
  graph->print();
  // graph->connect("1", "3", "***");
  // graph->resize(5);
  // graph->print();
  return 0;
}