#include "indefinite-stream.hpp"
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace indefinite;

int main()
{
  std::cout << "stream[3]-> *10, divide 5, divide 9:" << '\n';
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

  std::cout << "top: "<<  a.top() << '\n';
  std::cout << "pop: " << a.pop() << '\n';
  std::cout << "pop: " << a.pop() << '\n';
  std::cout << "pop: " << a.pop() << '\n';
  std::cout << "pop: " << a.pop() << '\n';
  std::cout << '\n';
  
  int size = 100;
  std::cout << "stream[2, 5]-> divide 7, divide 11, * 10:" << '\n';
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

  IndefiniteStream<int> s(IndefiniteStream<int>::Start(1));
  auto sum = s.accumulate(size, 0);
  std::cout << "Get 1-"<< size <<" sum: " << sum << '\n';
  std::cout << '\n';

  std::cout << "Get " << size << " primes numbers: " << '\n';
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
    .limit(size);
    for (auto v : vp) {
      std::cout << v << ' ';
    }
    std::cout << '\n';
  

  return 0;
}

