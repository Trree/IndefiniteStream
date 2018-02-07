#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../indefinite_stream.hpp"

using namespace indefinite;
// It would be overflow_error
TEST_CASE("testing the indefinite one step function") {
  IndefiniteStream<int> a(IndefiniteStream<int>::Start(3));
  CHECK(a.top() == 3);
  CHECK(a.pop() == 3);
  CHECK(a.pop() == 4);
}

TEST_CASE("testing the indefinite scale before function") {
  IndefiniteStream<int> a(IndefiniteStream<int>::Start(3));
  a.scale_before(
      [](int value) {
      return value * 10;
      }
  );
  CHECK(a.pop() == 30);
  CHECK(a.pop() == 40);
}

TEST_CASE("testing the indefinite multi step function") {
  IndefiniteStream<int> a(IndefiniteStream<int>::Start(3), IndefiniteStream<int>::Step(5));
  CHECK(a.pop() == 3);
  CHECK(a.pop() == 8);
}

TEST_CASE("testing the indefinite scale after function") {
  IndefiniteStream<int> a(IndefiniteStream<int>::Start(3), IndefiniteStream<int>::Step(5));
  a.scale_after(
      [](int value) {
      return value * 7;
    });
  CHECK(a.pop() == 21);
  CHECK(a.pop() == 56);
}


TEST_CASE("testing the indefinite filter function") {
  IndefiniteStream<int> a(IndefiniteStream<int>::Start(3));
  a.filter([](int value) {return ( value % 7 == 0);});
  CHECK(a.pop() == 7);
  CHECK(a.pop() == 14);
}

TEST_CASE("testing the indefinite filter and  scale after function") {
  IndefiniteStream<int> a(IndefiniteStream<int>::Start(3));
  a.filter(
      [](int value) {
      return ( value % 7 == 0);
    })
  .scale_after(
      [](int value) {
      return value * 7;
    });
  CHECK(a.pop() == 49);
  CHECK(a.pop() == 98);
}

TEST_CASE("testing the indefinite filter function") {
  IndefiniteStream<int> a(IndefiniteStream<int>::Start(3), IndefiniteStream<int>::Step(5));
  a.filter([](int value) {return (value % 7 == 0);});
  CHECK(a.pop() == 28);
  CHECK(a.pop() == 63);
}


TEST_CASE("testing the indefinite multi filter function") {
  IndefiniteStream<int> a(IndefiniteStream<int>::Start(3));
  a.filter([](int value) {return (value % 2 == 0);}).filter([](int value) {return (value % 7 == 0);});
  CHECK(a.pop() == 14);
  CHECK(a.pop() == 28);
}

TEST_CASE("testing the indefinite accumulate function") {
  IndefiniteStream<int> s(IndefiniteStream<int>::Start(1));
  int sum = s.accumulate(100, 0);
  CHECK(sum == 5050);
}

