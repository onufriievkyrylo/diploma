#ifndef ABSTRACT_GRAPH_H_
#define ABSTRACT_GRAPH_H_

typedef unsigned int size_t;

template <class V, class E>
class AbstractGraph {
  public:
  /**
   * @params
   *  vertex - vertex should be added to graph
   * @return "this" for chaining, could be replaced by void
   */
  virtual AbstractGraph* addVertex(V* vertex) = 0
  /**
   * @params
   *  vertex1, vertex2 - graph verticies beetwen edge should be added
   *  edge - edge data should be added between verticies
   * @return "this" for chaining, could be replaced by void
   */
  virtual AbstractGraph* addEdge(V* vertex1, V* vertex2, E* edge) = 0
  /**
   * @params
   *  vertex - vertex should be removed to graph
   * @return "this" for chaining, could be replaced by void
   */
  virtual AbstractGraph* removeVertex(V* vertex) = 0
  /**
   * @params
   *  vertex1, vertex2 - graph verticies beetwen edge should be removed
   * @return "this" for chaining, could be replaced by void
   */
  virtual AbstractGraph* removeEdge(V* vertex1, V* vertex2) = 0
  /** 
   * @return array of verticies
   */
  virtual V* verticies() = 0;
  /**
   *  @return array of neighbor verticies
   */
  virtual V* neighbors(V* vertex) = 0;
  /**
   * @params
   *  vertex - vertext to check
   * @return true if graph contains vertex
   */
  virtual bool contains(V* vertex) = 0;
  /** 
   * @return number of verticies
   */
  virtual size_t size() = 0;
  /**
   * @return true - if graph doesn't contain any vertex
   */
  virtual bool empty() = 0
};

#endif  // ABSTRACT_GRAPH_H_