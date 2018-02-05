#include "indefinite-stream.hpp"

int main()
{
  filter_handler f;
  IndefiniteStream<int> a(3);
  a.filter([](int value) {return (value % 5 == 0);}).filter([](int value) {return (value % 9 == 0);});
  std::cout << a.top() << '\n';
  std::cout << a.next() << '\n';
  std::cout << a.next() << '\n';
  std::cout << a.next() << '\n';
  std::cout << a.next() << '\n';
  a.printstream();

  return 0;
}

