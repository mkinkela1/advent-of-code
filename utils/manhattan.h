#include <cmath>
#include <cstdlib>
#include <tuple>
#include <type_traits>

template <typename T> auto abs_diff(T a, T b) -> T {
  if constexpr (std::is_same_v<T, long long>) {
    return std::llabs(a - b);
  } else if constexpr (std::is_same_v<T, unsigned long long>) {
    return (a > b) ? (a - b) : (b - a);
  } else if constexpr (std::is_same_v<T, long>) {
    return std::labs(a - b);
  } else {
    return std::abs(a - b);
  }
}

template <typename T>
auto manhattan(std::pair<T, T> a, std::pair<T, T> b) -> T {
  return abs_diff(a.first, b.first) + abs_diff(a.second, b.second);
}

template <typename T>
auto manhattan(std::tuple<T, T, T> a, std::tuple<T, T, T> b) -> T {
  return abs_diff(std::get<0>(a), std::get<0>(b)) +
         abs_diff(std::get<1>(a), std::get<1>(b)) +
         abs_diff(std::get<2>(a), std::get<2>(b));
}

template <typename T> auto manhattan(std::tuple<T, T, T> a) -> T {
  return abs_diff(std::get<0>(a), T(0)) + abs_diff(std::get<1>(a), T(0)) +
         abs_diff(std::get<2>(a), T(0));
}