//#include "Graphs/Vertex.h"
#include "Graphs/MatrixGraph.h"
#include <string>

int main() {
  auto graph = new MatrixGraph<std::string, std::string>();
  for(int i(13); i > 0; --i)
    graph->addVertex(std::to_string(i));
  graph->addVertex("asd");
  graph->print();
  graph->removeVertex("asd");
  graph->print();
  graph->resize(5);
  graph->print();
  return 0;
}