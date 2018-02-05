#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../indefinite-stream.hpp"

using namespace indefinite;
// It would be overflow_error
TEST_CASE("testing the indefinite one step function") {
  IndefiniteStream<int> a(3);
  CHECK(a.next() == 3);
  CHECK(a.next() == 4);
}

TEST_CASE("testing the indefinite multi step function") {
  IndefiniteStream<int> a(3, 5);
  CHECK(a.next() == 3);
  CHECK(a.next() == 8);
}


TEST_CASE("testing the indefinite filter function") {
  IndefiniteStream<int> a(3);
  a.filter([](int value) {return ( value % 7 == 0);});
  CHECK(a.next() == 7);
  CHECK(a.next() == 14);
}

TEST_CASE("testing the indefinite range test function") {
  IndefiniteStream<int> a(3, 5);
  a.filter([](int value) {return (value % 7 == 0);});
  CHECK(a.next() == 28);
  CHECK(a.next() == 63);
}


TEST_CASE("testing the indefinite multi filter function") {
  IndefiniteStream<int> a(3);
  a.filter([](int value) {return (value % 2 == 0);}).filter([](int value) {return (value % 7 == 0);});
  CHECK(a.next() == 14);
  CHECK(a.next() == 28);
}

