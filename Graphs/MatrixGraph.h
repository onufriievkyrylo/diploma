#ifndef MATRIX_GRAPH_H_
#define MATRIX_GRAPH_H_

#include <iostream>
#include <algorithm>
#include <exception>
#include "./AbstractGraph.h"

#define DEFAULT_SIZE 10
#define STEP_SIZE 10

template <class V, class E>
class MatrixGraph : AbstractGraph<V, E> {
  private:
  size_t max_size = DEFAULT_SIZE;
  size_t step_size = STEP_SIZE;
  size_t current_size = 0;

  V* verticies;
  E** edges;
  public:
  MatrixGraph() {
    verticies = new V[max_size];
    edges = new E*[max_size];
    for (size_t i(0); i < max_size; ++i){
      edges[i] = new E[max_size];
    }
  }
  MatrixGraph* addVertex(V vertex)  {
    V* add = std::find(verticies, verticies + size(), vertex);
    if (add != verticies + size()) throw std::logic_error("vertex already added");
    if (current_size + 1 > max_size) {
      resize(max_size + step_size);
    }
    verticies[size()] = vertex;
    current_size += 1;
    return this;
  }
  MatrixGraph* removeVertex(V vertex)  {
    if (empty()) throw std::logic_error("graph is empty");
    V* removal = std::find(verticies, verticies + size(), vertex);
    if (removal == verticies + size()) throw std::logic_error("vertex not found");
    size_t removal_index = removal - verticies;
    return removeVertex(removal_index);
  }
  MatrixGraph* removeVertex(size_t removal_index) {
    if (empty()) throw std::logic_error("graph is empty");
    if (removal_index >= size()) throw std::out_of_range("index is out of range");
    if (removal_index < size() - 1) {
      std::copy(verticies + removal_index + 1, verticies + size(), verticies + removal_index);
      std::copy(edges + removal_index + 1, edges + size(), edges + removal_index);
      for (size_t index(0); index < size() - 1; ++index)
        std::copy(edges[index] + removal_index + 1, edges[index] + size(), edges[index] + removal_index);
    }
    delete[] edges[size() - 1];
    current_size -= 1;
    return this;
  }
  void resize(size_t new_size) {
    max_size = new_size;
    current_size = std::min(size(), new_size);
    V* verticies_buffer = new V[max_size];
    std::copy(verticies, verticies + size(), verticies_buffer);
    delete[] verticies;
    verticies = verticies_buffer;
    E** edges_buffer= new E*[max_size];
    std::copy(edges, edges + size(), edges_buffer);
    delete[] edges;
    edges = edges_buffer;
    for (size_t index(0); index < max_size; ++index) {
      E* vertex_edges_buffer = new E[max_size];
      if (index < size()) {
        std::copy(edges[index], edges[index] + size(), vertex_edges_buffer);
        delete[] edges[index];
      }
      edges[index] = vertex_edges_buffer;
    }
  }
  size_t size() {
    return current_size;
  }
  bool empty() {
    return current_size == 0;
  }
  void print() {
    for (int i(0); i < current_size; ++i)
      std::cout << i << ' '<< verticies[i] << std::endl;
    std::cout << current_size << ' '<< max_size << std::endl;
  }
};

#endif // MATRIX_GRAPH_H_