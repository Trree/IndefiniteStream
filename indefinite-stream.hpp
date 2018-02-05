#include <iostream>
#include <vector>
#include <functional>

namespace indefinite{

typedef std::vector<std::function<bool (const int&)>> filter_handler;

template<class T = int> class IndefiniteStream {
public:
  IndefiniteStream() : start_(0), end_(-1) {}
  IndefiniteStream(T start) : start_(start), end_(-1) {}
  IndefiniteStream(T start, filter_handler filter) : start_(start), end_(-1), filters_(filter) {} 
  IndefiniteStream(T start, T step, filter_handler filter) : start_(start), step_(step), end_(-1), filters_(filter) {} 
  IndefiniteStream(T start, T step) : start_(start), step_(step) {}
  IndefiniteStream(T start, T step, T end) : start_(start), step_(step), end_(end) {}
  IndefiniteStream(T start, T step, T end, filter_handler filter) : start_(start), step_(step), end_(end), filters_(filter) {}
  ~IndefiniteStream() {}

  IndefiniteStream& from(T t) {
    start_ = t;
  }
  IndefiniteStream& from(T t, T step) {
    start_ = t;
    step_ = step;
  }

  IndefiniteStream& range(T start, T end) {
    start_ = start;
    end_ = end;
  }

  T size() const 
  {
    if (end_ != -1 && start_ <= end_) {
      return (end_ - start_) / step_;
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
    if (end_ == -1 || start_ < end_) {
      for (auto i = start_; ; i += step_) {
        auto value = handler_filer(i);
        if (value != -1) {
          start_ = i;
          return i;
        }
      }
    }
    return -1;
  }
  
  T next() 
  {
    if (end_ == -1 || start_ < end_) {
      for (auto i = start_; ; i += step_) {
        auto value = handler_filer(i);
        if (value != -1) {
          start_ = i + step_;
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
    auto i = start_;
    auto j = 0;
    while ((end_ == -1 || (i <= end_)) && j < size) {
      auto value = handler_filer(i);
      if (value != -1) {
        tmp.push_back(i);
        j++;
      }
      i = i + step_;
    }
    return tmp;
  }

  void printstream() const 
  {
    if (end_ != -1 && start_ <= end_) {
      for (int i = start_; i <= end_; i += step_) {
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
  T start_ = 0;
  T step_ = 1;
  T end_  = -1;
  filter_handler filters_;
};

} // name namespace indefinite
