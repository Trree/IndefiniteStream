#include "indefinite-stream.hpp"
#include <vector>
#include <algorithm>

int main()
{
  indefinite::IndefiniteStream<int> a(3);
  a.filter([](int value) {return (value % 5 == 0);}).filter([](int value) {return (value % 9 == 0);});
  
  std::cout << a.top() << '\n';
  std::cout << a.next() << '\n';
  std::cout << a.next() << '\n';
  std::cout << a.next() << '\n';
  std::cout << a.next() << '\n';
  
  std::vector<int> v = a.limit(10);
  std::for_each(v.begin(), v.end(), [](int value){ std::cout << value << ' '; });
  a.printstream();

  return 0;
}

