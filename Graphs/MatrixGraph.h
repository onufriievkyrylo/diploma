#ifndef MATRIX_GRAPH_H_
#define MATRIX_GRAPH_H_

#include <iostream>
#include <algorithm>
#include <exception>
#include <optional>
#include "./AbstractGraph.h"

#define DEFAULT_SIZE 10
#define STEP_SIZE 10

template <class V, class E>
class MatrixGraph : AbstractGraph<V, E> {
  private:
  size_t max_size;
  size_t step_size;
  size_t current_size = 0;

  V* verticies;
  std::optional<E>** edges;
  public:
  MatrixGraph(size_t init_size, size_t step_size) : max_size(init_size), step_size(step_size) {
    verticies = new V[max_size];
    edges = new std::optional<E>*[max_size];
    for (int index(0); index < max_size; ++index){
      edges[index] = new std::optional<E>[max_size];
    }
  }
  MatrixGraph() : MatrixGraph(DEFAULT_SIZE, STEP_SIZE) {
  }
  ~MatrixGraph() {
    delete[] verticies;
    for (int index(0); index < max_size; ++index){
      delete[] edges[index];
    }
    delete[] edges;
  }
  MatrixGraph* add(V vertex) {
    if (contains(vertex)) throw std::logic_error("vertex already added");
    if (current_size + 1 > max_size) {
      resize(max_size + step_size);
    }
    verticies[current_size] = vertex;
    current_size += 1;
    return this;
  }
  MatrixGraph* remove(V vertex) {
    int removal_index = index_of(vertex);
    if (removal_index < 0) throw std::logic_error("vertex not found");
    return remove(removal_index);
  }
  MatrixGraph* remove(int removal_index) {
    if (removal_index < 0 || removal_index >= current_size)
      throw std::out_of_range("index is out of range");
    if (removal_index < current_size - 1) {
      std::copy(verticies + removal_index + 1, verticies + current_size, verticies + removal_index);
      std::copy(edges + removal_index + 1, edges + current_size, edges + removal_index);
      for (int index(0); index < current_size - 1; ++index)
        std::copy(edges[index] + removal_index + 1, edges[index] + current_size, edges[index] + removal_index);
    }
    delete[] edges[current_size - 1];
    current_size -= 1;
    return this;
  }
  MatrixGraph* connect(V vertex1, V vertex2, E edge) {
    int vertex1_index = index_of(vertex1);
    if (vertex1_index < 0)
      throw std::logic_error("vertex1 not found");
    int vertex2_index = index_of(vertex2);
    if (vertex2_index < 0)
      throw std::logic_error("vertex2 not found");
    edges[vertex1_index][vertex2_index] = edge;
    return this;
  }
  MatrixGraph* connect(int vertex1_index, int vertex2_index, E edge) {
    if (vertex1_index < 0 || vertex1_index >= current_size)
      throw std::out_of_range("vertex1 index is out of range");
    if (vertex2_index < 0 || vertex2_index >= current_size)
      throw std::out_of_range("vertex2 index is out of range");
    edges[vertex1_index][vertex2_index] = edge;
    return this;
  }
  MatrixGraph* disconnect(V vertex1, V vertex2) {
    int vertex1_index = index_of(vertex1);
    if (vertex1_index < 0)
      throw std::logic_error("vertex1 not found");
    int vertex2_index = index_of(vertex2);
    if (vertex2_index < 0)
      throw std::logic_error("vertex2 not found");
    edges[vertex1_index][vertex2_index].reset();
    return this;
  }
  MatrixGraph* disconnect(int vertex1_index, int vertex2_index) {
    if (vertex1_index < 0 || vertex1_index >= current_size)
      throw std::out_of_range("vertex1 index is out of range");
    if (vertex2_index < 0 || vertex2_index >= current_size)
      throw std::out_of_range("vertex2 index is out of range");
    edges[vertex1_index][vertex2_index].reset();
    return this;
  }
  void resize(size_t new_size) {
    max_size = new_size;
    current_size = std::min(current_size, new_size);
    V* verticies_buffer = new V[max_size];
    std::copy(verticies, verticies + current_size, verticies_buffer);
    delete[] verticies;
    verticies = verticies_buffer;
    std::optional<E>** edges_buffer= new std::optional<E>*[max_size];
    std::copy(edges, edges + current_size, edges_buffer);
    delete[] edges;
    edges = edges_buffer;
    for (int index(0); index < max_size; ++index) {
      std::optional<E>* vertex_edges_buffer = new std::optional<E>[max_size];
      if (index < current_size) {
        std::copy(edges[index], edges[index] + current_size, vertex_edges_buffer);
        delete[] edges[index];
      }
      edges[index] = vertex_edges_buffer;
    }
  }
  bool contains(V vertex) {
    V* end = verticies + current_size;
    return std::find(verticies, end, vertex) != end;
  }
  int index_of(V vertex) {
    V* end = verticies + current_size;
    int index = std::find(verticies, end, vertex) - verticies;
    return current_size != index ? index : -1;
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
    for (int i(0); i < current_size; ++i) {
      for (int j(0); j < current_size; ++j) {
        std::cout << i << '|' << j << '|' << edges[i][j].value_or("?") << ' ';
      }
      std::cout << std::endl;
    }
  }
};

#endif // MATRIX_GRAPH_H_