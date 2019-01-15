#ifndef ABSTRACT_GRAPH_H_
#define ABSTRACT_GRAPH_H_

template <class V, class E>
class AbstractGraph {
  public:
  /**
   * @params
   *  vertex - vertex should be added to graph
   * @return "this" for chaining, could be replaced by void
   */
  virtual AbstractGraph* add(V vertex) = 0;
  /**
   * @params
   *  vertex - vertex should be removed to graph
   * @return "this" for chaining, could be replaced by void
   */
  virtual AbstractGraph* remove(V vertex) = 0;
  /**
   * @params
   *  vertex1, vertex2 - graph verticies beetwen edge should be added
   *  edge - edge data should be added between verticies
   * @return "this" for chaining, could be replaced by void
   */
  virtual AbstractGraph* connect(V vertex1, V vertex2, E edge) = 0;
  /**
   * @params
   *  vertex1, vertex2 - graph verticies beetwen edge should be removed
   * @return "this" for chaining, could be replaced by void
   */
  virtual AbstractGraph* disconnect(V vertex1, V vertex2) = 0;
  /**
   * @params
   *  vertex - vertext to check
   * @return true if graph contains vertex
   */
  virtual bool contains(V vertex) = 0;
  /** 
   * @return number of verticies
   */
  virtual size_t size() = 0;
  /**
   * @return true - if graph doesn't contain any vertex
   */
  virtual bool empty() = 0;
};

#endif  // ABSTRACT_GRAPH_H_