#include "./MatrixGraph.h"
#include <string>

struct Road {
  std::string from;
  std::string to;
  double distance;
};

const std::string cities[] = {
  "Luhansk",
  "Kharkiv",
  "Donetsk",
  "Sumy",
  "Poltava",
  "Dnipro",
  "Zaporizhia",
  "Chernihiv",
  "Kyiv",
  "Cherkasy",
  "Kropyvnytskyi",
  "Mykolaiv",
  "Kherson",
  "Simferopol",
  "Zhytomyr",
  "Vinnytsia",
  "Odessa",
  "Rivne",
  "Khmelnytskyi",
  "Chernivtsi",
  "Lutsk",
  "Lviv",
  "Ternopil",
  "Ivano-Frankivsk",
  "Uzhhorod"
};

const Road roads[] = {
  { "Luhansk", "Kharkiv", 333 },
  { "Luhansk", "Donetsk", 6 },
  { "Kharkiv", "Sumy", 190 },
  { "Kharkiv", "Poltava", 141 },
  { "Kharkiv", "Dnipro", 213 },
  { "Kharkiv", "Donetsk", 335 },
  { "Donetsk", "Dnipro", 252 },
  { "Donetsk", "Zaporizhia", 231 },
  { "Sumy", "Poltava", 177 },
  { "Sumy", "Kyiv", 365 },
  { "Sumy", "Chernihiv", 308 },
  { "Poltava", "Kyiv", 160 },
  { "Poltava", "Dnipro", 197 },
  { "Poltava", "Cherkasy", 241 },
  { "Poltava", "Kropyvnytskyi", 251 },
  { "Dnipro", "Zaporizhia", 85 },
  { "Dnipro", "Kropyvnytskyi", 246 },
  { "Dnipro", "Mykolaiv", 322 },
  { "Zaporizhia", "Simferopol", 375 },
  { "Kyiv", "Zhytomyr", 140 },
  { "Kyiv", "Chernihiv", 149 },
  { "Kyiv", "Cherkasy", 192 },
  { "Kyiv", "Odessa", 475 },
  { "Cherkasy", "Kropyvnytskyi", 130 },
  { "Kropyvnytskyi", "Mykolaiv", 182 },
  { "Kropyvnytskyi", "Vinnytsia", 329 },
  { "Mykolaiv", "Odessa", 132 },
  { "Mykolaiv", "Kherson", 69 },
  { "Simferopol", "Kherson", 277 },
  { "Zhytomyr", "Vinnytsia", 128 },
  { "Zhytomyr", "Khmelnytskyi", 189 },
  { "Zhytomyr", "Rivne", 188 },
  { "Vinnytsia", "Khmelnytskyi", 119 },
  { "Khmelnytskyi", "Chernivtsi", 187 },
  { "Khmelnytskyi", "Ternopil", 111 },
  { "Rivne", "Lutsk", 73 },
  { "Rivne", "Ternopil", 159 },
  { "Rivne", "Lviv", 211 },
  { "Chernivtsi", "Ternopil", 172 },
  { "Chernivtsi", "Ivano-Frankivsk", 135 },
  { "Ternopil", "Lviv", 137 },
  { "Lutsk", "Lviv", 151 },
  { "Lutsk", "Ternopil", 168 },
  { "Lviv", "Uzhhorod", 420 },
  { "Ternopil", "Ivano-Frankivsk", 134 }
};

int main() {
  auto graph = new MatrixGraph<std::string, double>();
  
  for (const auto& city : cities) {
    graph->add(city);
  }

  for (const auto& road : roads) {
    graph
      ->connect(road.from, road.to, road.distance)
      ->connect(road.to, road.from, road.distance);
  }

  std::string f = "Lviv";

  auto paths = graph->dijkstra_single_source(f);

  for (auto* path = paths; path != paths + graph->size(); ++path) {
    std::cout << path->from << " - " << path->to << " " << path->weight << std::endl;
    for (int node_index(0); node_index < path->sequence_length; ++node_index) {
      std::cout << path->sequence[node_index] << " ";
    }
    std::cout << std::endl << std::endl;
  }

  delete[] paths;
  delete graph;

  return 0;
}