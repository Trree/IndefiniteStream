#include "indefinite-stream.hpp"
#include <vector>
#include <algorithm>
#include <cmath>

using namespace indefinite;

int main()
{
  IndefiniteStream<int> a(IndefiniteStream<int>::Start(3));
  a.scale_before(
    [](int value) {
      return value * 10;
    }) 
   .filter(
    [](int value) {
      return (value % 5 == 0);
    })
   .filter(
     [](int value) {
       return (value % 9 == 0);
     });

  std::cout << "One by one: " << '\n';
  std::cout << a.top() << '\n';
  std::cout << a.pop() << '\n';
  std::cout << a.pop() << '\n';
  std::cout << a.pop() << '\n';
  std::cout << a.pop() << '\n';
  std::cout << '\n';
  
  int size = 10;
  std::cout << "Get " << size << " numbers: " << '\n';
  indefinite::IndefiniteStream<int> b(IndefiniteStream<int>::Start(2), IndefiniteStream<int>::Step(5));
  std::vector<int> v = b.filter(
    [](int value) {
      return (value % 7 == 0);
    })
   .filter(
    [](int value) {
      return (value % 11 == 0);
    })
  .scale_after(
    [](int value) {
      return value * 10;
    })
   .limit(size);
  std::for_each(v.begin(), v.end(), 
                [](int value){ std::cout << value << ' '; });
  std::cout << '\n';
  std::cout << '\n';

  int primeslen = 100;
  std::cout << "Get " << primeslen << " primes numbers: " << '\n';
  IndefiniteStream<int> primes(IndefiniteStream<int>::Start(2));
  std::vector<int> vp = primes.filter(
    [](int value) {
      if (value < 2) {
        return false;
      }
      else if (value == 2) {
        return true;
      }
      
      for(int i = 2; i <= std::sqrt(value); ++i) {
        if (value % i == 0) {
          return false;
        }
      }
      return true;
    })
    .limit(primeslen);
    for (auto v : vp) {
      std::cout << v << ' ';
    }
    std::cout << '\n';
  

  return 0;
}

