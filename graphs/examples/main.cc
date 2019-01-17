#include "./MatrixGraph.h"
#include <string>

int main() {
  auto graph = new MatrixGraph<std::string, double>();
  graph
    ->add("Luhansk")
    ->add("Kharkiv")
    ->add("Donetsk")
    ->add("Sumy")
    ->add("Poltava")
    ->add("Dnipro")
    ->add("Zaporizhia")
    ->add("Chernihiv")
    ->add("Kyiv")
    ->add("Cherkasy")
    ->add("Kropyvnytskyi")
    ->add("Mykolaiv")
    ->add("Kherson")
    ->add("Simforopol")
    ->add("Zhytomyr")
    ->add("Vinnytsia")
    ->add("Odessa")
    ->add("Rivne")
    ->add("Khmelnytski")
    ->add("Chernivtsi")
    ->add("Lutsk")
    ->add("Lviv")
    ->add("Ternopil")
    ->add("Ivano-Frankivsk")
    ->add("Uzhhorod");

  graph
    ->connect("Luhansk", "Kharkiv", 333)->connect("Kharkiv", "Luhansk", 333)
    ->connect("Luhansk", "Donetsk", 6)->connect("Donetsk", "Luhansk", 148)
    ->connect("Kharkiv", "Sumy", 190)->connect("Sumy", "Kharkiv", 190)
    ->connect("Kharkiv", "Poltava", 141)->connect("Poltava", "Kharkiv", 141)
    ->connect("Kharkiv", "Dnipro", 213)->connect("Dnipro", "Kharkiv", 213)
    ->connect("Kharkiv", "Donetsk", 335)->connect("Donetsk", "Kharkiv", 335)
    ->connect("Donetsk", "Dnipro", 252)->connect("Dnipro", "Donetsk", 252)
    ->connect("Donetsk", "Zaporizhia", 231)->connect("Zaporizhia", "Donetsk", 231)
    ->connect("Sumy", "Poltava", 177)->connect("Poltava", "Sumy", 177)
    ->connect("Sumy", "Kyiv", 365)->connect("Kyiv", "Sumy", 365)
    ->connect("Sumy", "Chernihiv", 308)->connect("Chernihiv", "Sumy", 308)
    ->connect("Poltava", "Kyiv", 160)->connect("Kyiv", "Poltava", 160)
    ->connect("Poltava", "Dnipro", 197)->connect("Dnipro", "Poltava", 197)
    ->connect("Poltava", "Cherkasy", 241)->connect("Cherkasy", "Poltava", 241)
    ->connect("Poltava", "Kropyvnytskyi", 251)->connect("Kropyvnytskyi", "Poltava", 251)
    ->connect("Dnipro", "Zaporizhia", 85)->connect("Zaporizhia", "Dnipro", 85)
    ->connect("Dnipro", "Kropyvnytskyi", 246)->connect("Kropyvnytskyi", "Dnipro", 246)
    ->connect("Dnipro", "Mykolaiv", 322)->connect("Mykolaiv", "Dnipro", 322)
    ->connect("Zaporizhia", "Simferopol", 375)->connect("Simferopol", "Zaporizhia", 375)
    ->connect("Kyiv", "Zhytomyr", 140)->connect("Zhytomyr", "Kyiv", 140)
    ->connect("Kyiv", "Chernihiv", 149)->connect("Chernihiv", "Kyiv", 149)
    ->connect("Kyiv", "Cherkasy", 192)->connect("Cherkasy", "Kyiv", 192)
    ->connect("Kyiv", "Odessa", 475)->connect("Odessa", "Kyiv", 475)
    ->connect("Cherkasy", "Kropyvnytskyi", 130)->connect("Kropyvnytskyi", "Cherkasy", 130)
    ->connect("Kropyvnytskyi", "Mykolaiv", 182)->connect("Mykolaiv", "Kropyvnytskyi", 182)
    ->connect("Kropyvnytskyi", "Vinnytsia", 329)->connect("Vinnytsia", "Kropyvnytskyi", 329)
    ->connect("Mykolaiv", "Odessa", 132)->connect("Odessa", "Mykolaiv", 132)
    ->connect("Mykolaiv", "Kherson", 69)->connect("Kherson", "Mykolaiv", 69)
    ->connect("Zhytomyr", "Vinnytsia", 277)->connect("Vinnytsia", "Zhytomyr", 277);
    ->connect("Zhytomyr", "Khmelnytskyi", 277)->connect("Khmelnytskyi", "Zhytomyr", 277)
    ->connect("Zhytomyr", "Rivne", 277)->connect("Rivne", "Zhytomyr", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)
    ->connect("Simferopol", "Kherson", 277)->connect("Kherson", "Simferopol", 277)




    

  graph->connect("1", "3", 2424);
  graph->print();
  return 0;
}