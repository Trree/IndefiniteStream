#include <type_traits>
#include <cstddef>
#include <algorithm>

namespace indefinite{

template<typename T, typename Parameter>
class NamedType
{
public:
  explicit NamedType(T const& value) : value_(value) {}
  template<typename T_ = T>
  explicit NamedType(T&& value, 
    typename std::enable_if<!std::is_reference<T_>{}, 
                     std::nullptr_t>::type = nullptr)
  : value_(std::move(value)) {}

  T& get() { return value_; }
  T const& get() const {return value_; }
private:
  T value_;
};

} // name namespace indefinite
