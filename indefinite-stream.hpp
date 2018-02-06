#include <iostream>
#include <vector>
#include <functional>
#include "NamedType.hpp"

namespace indefinite{

using filter_handler = std::vector<std::function<bool (const int&)>>;
using Start = NamedType<int, struct StartParameter>;
using Step = NamedType<int, struct StepParameter>;
using End = NamedType<int, struct EndParameter>;

template<class T = int> 
class IndefiniteStream {

public:

  IndefiniteStream() {}
  IndefiniteStream(Start start) : start_(start) {}
  IndefiniteStream(Start start, filter_handler filter) : start_(start), filters_(filter) {} 
  IndefiniteStream(Start start, Step step, filter_handler filter) : start_(start), step_(step), filters_(filter) {} 
  IndefiniteStream(Start start, Step step) : start_(start), step_(step) {}
  IndefiniteStream(Start start, Step step, End end) : start_(start), step_(step), end_(end) {}
  IndefiniteStream(Start start, Step step, End end, filter_handler filter) : start_(start), step_(step), end_(end), filters_(filter) {}
  ~IndefiniteStream() {}

  IndefiniteStream& from(Start start) {
    start_ = start;
  }
  IndefiniteStream& from(Start start, Step step) {
    start_ = start;
    step_ = step;
  }

  IndefiniteStream& range(Start start, End end) {
    start_ = start;
    end_ = end;
  }

  T size() const 
  {
    if (end_.get() != -1 && start_.get() <= end_.get()) {
      return (end_.get() - start_.get()) / step_.get();
    }
    else {
      return -1;
    }
  }

  IndefiniteStream& filter(std::function<bool (const T&)> f) 
  {
    filters_.push_back(f);
    return *this;
  }

  T handler_filer(T value)
  {
    auto it = filters_.begin();
    for(; it != filters_.end(); it++) {
      if (!(*it)(value)) {
        return -1;
      }
    }
    if (it == filters_.end()) {
      return value;
    }
    return -1;
  }

  T top() 
  {
    if (end_.get() == -1 || start_.get() < end_.get()) {
      for (auto i = start_.get(); ; i += step_.get()) {
        auto value = handler_filer(i);
        if (value != -1) {
          start_.get() = i;
          return i;
        }
      }
    }
    return -1;
  }
  
  T pop() 
  {
    if (end_.get() == -1 || start_.get() < end_.get()) {
      for (auto i = start_.get(); ; i += step_.get()) {
        auto value = handler_filer(i);
        if (value != -1) {
          start_.get() = i + step_.get();
          return i;
        }
      }
    }
    return -1;
  }

  std::vector<T> limit(T size) 
  {
    std::vector<T> tmp;
    tmp.reserve(size);
    auto i = start_.get();
    auto j = 0;
    while ((end_.get() == -1 || (i <= end_.get())) && j < size) {
      auto value = handler_filer(i);
      if (value != -1) {
        tmp.push_back(i);
        j++;
      }
      i = i + step_.get();
    }
    return tmp;
  }

  void printstream() const 
  {
    if (end_.get() != -1 && start_.get() <= end_.get()) {
      for (int i = start_.get(); i <= end_.get(); i += step_.get()) {
        auto it = filters_.begin();
        for(; it != filters_.end(); it++) {
          if (!(*it)(i)) {
            break;
          }
        }
        if (it == filters_.end()) {
          std::cout << i << ' ';
        }
      }
      std::cout << '\n';
    }
    else {
      return; 
    }
  }

private:
  Start start_ = Start(0) ;
  Step step_ = Step(1);
  End end_ = End(-1);
  filter_handler filters_;
};

} // name namespace indefinite
