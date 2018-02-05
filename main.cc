#include "indefinite-stream.hpp"

int main()
{
  filter_handler f;
  IndefiniteStream<int> a(3);
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

