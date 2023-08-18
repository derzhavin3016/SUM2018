/* FILE NAME: vec.h
 * PROGRAMMER: AD6
 * LAST UPDATE: 11.07.2018
 * PURPOSE
 */

#ifndef __INCLUDE_MATH_VEC_HPP__
#define __INCLUDE_MATH_VEC_HPP__

#include <array>
#include <concepts>
#include <iostream>
#include <limits>
#include <numeric>
#include <ranges>

#include "mthdef.hpp"

namespace mth
{
namespace detail
{
/* Vector class base template */
template <std::floating_point T, std::size_t numCoords>
class Vec final
{
private:
  static_assert(numCoords >= 2 && numCoords <= 4, "Number of coordinates must be in range [2, 4]");
  using Comparator = ThresComp<T>;

  std::array<T, numCoords> coords{};

public:
  Vec() = default;

  template <std::convertible_to<T> Arg>
  explicit Vec(Arg arg) noexcept
  {
    coords.fill(arg);
  }

  /* Vector constructor method */
  template <std::convertible_to<T>... Arg>
  Vec(Arg... arg) noexcept
    requires(sizeof...(arg) == numCoords)
    : coords{static_cast<T>(arg)...}
  {}

  /* Vector add and equal vector (reload +=) function
   * ARGUMENTS:
   *   - link to vector:
   *       vec<T> &V;
   * RETURNS:
   *       (vec<T> &) link to result vector;
   */
  Vec &operator+=(const Vec &V) noexcept
  {
    return transform([&V](const auto &ci, auto i) { return ci + V[i]; });
  } /* End of 'operator+=' function */

  [[nodiscard]] T operator[](std::size_t i) const noexcept
  {
    return coords[i];
  }

  [[nodiscard]] T &operator[](std::size_t i) noexcept
  {
    return coords[i];
  }

  [[nodiscard]] auto x() const noexcept
  {
    return this->operator[](0);
  }
  [[nodiscard]] auto y() const noexcept
  {
    return this->operator[](1);
  }
  [[nodiscard]] auto z() const noexcept
    requires(numCoords >= 3)
  {
    return this->operator[](2);
  }
  [[nodiscard]] auto w() const noexcept
    requires(numCoords >= 4)
  {
    return this->operator[](3);
  }

  /* Vector substraction and equal vector (reload -=) function
   * ARGUMENTS:
   *   - link to Vector:
   *       vec<T> &V;
   * RETURNS:
   *       (vec<T> &) link to result vector;
   */
  Vec &operator-=(const Vec &V) noexcept
  {
    return transform([&V](const auto &ci, auto i) { return ci - V[i]; });
  } /* End of 'operator-=' function */

  auto operator-() const noexcept
  {
    auto tmp = *this;
    tmp.transform([](auto ci, auto i) { return -ci; });
    return tmp;
  }

  [[nodiscard]] auto length() const noexcept
  {
    return sqrt(length2());
  }

  [[nodiscard]] auto dot(const Vec &V) const noexcept
  {
    return std::inner_product(coords.cbegin(), coords.cend(), V.coords.cbegin(), T{0});
  }

  [[nodiscard]] auto cross(const Vec &V) const noexcept
  {
    return Vec(y() * V.z() - z() * V.y(), z() * V.x() - x() * V.z(), x() * V.y() - y() * V.x());
  }

  template <Number U>
  Vec &operator*=(U number) noexcept
  {
    return transform([number](auto ci, auto) { return ci * number; });
  }

  template <Number U>
  Vec &operator/=(U number) noexcept
  {
    return operator*=(static_cast<T>(1) / number);
  }

  [[nodiscard]] auto normalize() const noexcept
  {
    auto len = length();
    auto V = *this;

    if (len != 0 && len != 1)
      V /= len;

    return V;
  }

  [[nodiscard]] static auto normalizing(const Vec &V) noexcept
  {
    return V.normalize();
  }

  [[nodiscard]] auto length2()
  {
    return dot(*this);
  }

  [[nodiscard]] auto distance(const Vec &V)
  {
    return (*this - V).length();
  }

  [[nodiscard]] bool isEqual(const Vec &V) const noexcept
  {
    return std::equal(coords.cbegin(), coords.cend(), V.coords.cbegin(), V.coords.cend(),
                      [](auto c1, auto c2) { return Comparator::isEqual(c1, c2); });
  }

private:
  template <typename Transformer>
  Vec &transform(Transformer &&trans)
  {
    std::ranges::copy(coords |
                        std::views::transform([i = std::size_t{}, &trans](auto coord) mutable {
                          return trans(coord, i++);
                        }),
                      coords.begin());

    return *this;
  }
};

template <std::floating_point T, std::size_t N>
[[nodiscard]] bool operator==(const Vec<T, N> &lhs, const Vec<T, N> &rhs) noexcept
{
  return lhs.isEqual(rhs);
}

template <std::floating_point T, std::size_t N>
auto operator+(const Vec<T, N> &lhs, const Vec<T, N> &rhs) noexcept
{
  auto tmp = lhs;
  tmp += rhs;
  return tmp;
}

template <std::floating_point T, std::size_t N>
auto operator-(const Vec<T, N> &lhs, const Vec<T, N> &rhs) noexcept
{
  auto tmp = lhs;
  tmp -= rhs;
  return tmp;
}

template <std::floating_point T, std::size_t N, std::convertible_to<T> U>
auto operator*(const Vec<T, N> &lhs, U rhs) noexcept
{
  auto tmp = lhs;
  tmp *= rhs;
  return tmp;
}

template <std::floating_point T, std::size_t N, Number U>
auto operator/(const Vec<T, N> &lhs, U rhs) noexcept
{
  auto tmp = lhs;
  tmp /= rhs;
  return tmp;
}

template <std::floating_point T, std::size_t N, Number U>
auto operator*(U lhs, const Vec<T, N> &rhs) noexcept
{
  auto tmp = rhs;
  tmp *= lhs;
  return tmp;
}
} // namespace detail

template <std::floating_point T>
using Vec2 = detail::Vec<T, 2>;

template <std::floating_point T>
using Vec = detail::Vec<T, 3>;

template <std::floating_point T>
using Vec4 = detail::Vec<T, 4>;

} // namespace mth

#endif // __INCLUDE_MATH_VEC_HPP__

/* End of 'vec.h' file */
