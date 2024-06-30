/* FILE NAME: vec.h
 * PROGRAMMER: AD6
 * LAST UPDATE: 11.07.2018
 * PURPOSE
 */

#ifndef ANIM_INCLUDE_MATH_VEC_HPP_INCLUDED
#define ANIM_INCLUDE_MATH_VEC_HPP_INCLUDED

#include <array>
#include <concepts>
#include <iostream>
#include <limits>
#include <numeric>
#include <ranges>
#include <type_traits>

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
  constexpr Vec() = default;

  constexpr explicit Vec(std::convertible_to<T> auto arg) noexcept
  {
    coords.fill(arg);
  }

  /* Vector constructor method */
  constexpr Vec(std::convertible_to<T> auto... arg) noexcept
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
  constexpr Vec &operator+=(const Vec &V) noexcept
  {
    return transform([&V](const auto &ci, auto i) { return ci + V[i]; });
  } /* End of 'operator+=' function */

  [[nodiscard]] constexpr T operator[](std::size_t i) const noexcept
  {
    return coords[i];
  }

  [[nodiscard]] constexpr T &operator[](std::size_t i) noexcept
  {
    return coords[i];
  }

  [[nodiscard]] constexpr auto x() const noexcept
  {
    return this->operator[](0);
  }
  [[nodiscard]] constexpr auto y() const noexcept
  {
    return this->operator[](1);
  }
  [[nodiscard]] constexpr auto z() const noexcept
    requires(numCoords >= 3)
  {
    return this->operator[](2);
  }
  [[nodiscard]] constexpr auto w() const noexcept
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
  constexpr Vec &operator-=(const Vec &V) noexcept
  {
    return transform([&V](const auto &ci, auto i) { return ci - V[i]; });
  } /* End of 'operator-=' function */

  [[nodiscard]] constexpr auto operator-() const noexcept
  {
    auto tmp = *this;
    tmp.transform([](auto ci, auto) { return -ci; });
    return tmp;
  }

  [[nodiscard]] constexpr auto length() const noexcept
  {
    return sqrt(length2());
  }

  [[nodiscard]] constexpr auto dot(const Vec &V) const noexcept
  {
    return std::inner_product(coords.cbegin(), coords.cend(), V.coords.cbegin(), T{0});
  }

  [[nodiscard]] constexpr auto cross(const Vec &V) const noexcept
  {
    return Vec(y() * V.z() - z() * V.y(), z() * V.x() - x() * V.z(), x() * V.y() - y() * V.x());
  }

  constexpr Vec &operator*=(Number auto number) noexcept
  {
    return transform([number](auto ci, auto) { return ci * number; });
  }

  constexpr Vec &operator/=(Number auto number) noexcept
  {
    return operator*=(static_cast<T>(1) / number);
  }

  constexpr auto &normalize() noexcept
  {
    auto len = length();

    if (len != 0 && len != 1)
      *this /= len;

    return *this;
  }

  [[nodiscard]] auto normalized() const
  {
    auto v = *this;
    return v.normalize();
  }

  [[nodiscard]] constexpr auto length2()
  {
    return dot(*this);
  }

  [[nodiscard]] constexpr auto distance(const Vec &V)
  {
    return (*this - V).length();
  }

  [[nodiscard]] constexpr bool isEqual(const Vec &V) const noexcept
  {
    return std::equal(coords.cbegin(), coords.cend(), V.coords.cbegin(), V.coords.cend(),
                      Comparator::isEqual);
  }

private:
  constexpr Vec &transform(auto trans)
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
[[nodiscard]] constexpr bool operator==(const Vec<T, N> &lhs, const Vec<T, N> &rhs) noexcept
{
  return lhs.isEqual(rhs);
}

template <std::floating_point T, std::size_t N>
[[nodiscard]] constexpr auto operator+(const Vec<T, N> &lhs, const Vec<T, N> &rhs) noexcept
{
  auto tmp = lhs;
  tmp += rhs;
  return tmp;
}

template <std::floating_point T, std::size_t N>
[[nodiscard]] constexpr auto operator-(const Vec<T, N> &lhs, const Vec<T, N> &rhs) noexcept
{
  auto tmp = lhs;
  tmp -= rhs;
  return tmp;
}

template <std::floating_point T, std::size_t N, std::convertible_to<T> U>
[[nodiscard]] constexpr auto operator*(const Vec<T, N> &lhs, U rhs) noexcept
{
  auto tmp = lhs;
  tmp *= rhs;
  return tmp;
}

template <std::floating_point T, std::size_t N, Number U>
[[nodiscard]] constexpr auto operator/(const Vec<T, N> &lhs, U rhs) noexcept
{
  auto tmp = lhs;
  tmp /= rhs;
  return tmp;
}

template <std::floating_point T, std::size_t N, Number U>
[[nodiscard]] constexpr auto operator*(U lhs, const Vec<T, N> &rhs) noexcept
{
  auto tmp = rhs;
  tmp *= lhs;
  return tmp;
}
} // namespace detail

enum class Axis : std::int8_t
{
  X = 0,
  Y = 1,
  Z = 2,
  W = 3,
};

template <std::floating_point T>
using Vec2 = detail::Vec<T, 2>;

template <std::floating_point T>
using Vec = detail::Vec<T, 3>;

template <std::floating_point T>
using Vec4 = detail::Vec<T, 4>;

} // namespace mth

#endif /* ANIM_INCLUDE_MATH_VEC_HPP_INCLUDED */

/* End of 'vec.h' file */
