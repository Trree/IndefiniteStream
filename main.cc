#include "indefinite-stream.hpp"

int main()
{
  filter_handler f;
  f.push_back([](int value){ return (value % 3 == 0); });
  IndefiniteStream<int> a(3, 2, f);
  a.filter([](int value) {return (value % 5 == 0);}).filter([](int value) {return (value % 9 == 0);});
  a.next();
  a.next();
  a.next();
  a.next();
  a.next();
  a.limit(1000);

  a.printstream();

  return 0;
}

