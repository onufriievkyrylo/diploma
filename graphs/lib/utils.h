#ifndef UTILS_H_
#define UTILS_H_

typedef std::string vertex_t;
typedef double weight_t;

inline const double INFINITY = 1000000.0;

int get_vertex_index(vertex_t* begin, vertex_t* end, const vertex_t& vertex) {
  vertex_t* temp = begin;
  while (temp < end) {
    if (*temp == vertex) {
      break;
    }
    temp++;
  }
  return temp - begin;
}

#endif // UTILS_H_