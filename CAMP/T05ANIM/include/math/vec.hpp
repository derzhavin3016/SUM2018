/* FILE NAME: vec.h
 * PROGRAMMER: AD6
 * LAST UPDATE: 11.07.2018
 * PURPOSE
 */

#ifndef __VEC_H_
#define __VEC_H_

#include <array>
#include <concepts>
#include <iostream>
#include <numeric>

#include "mthdef.hpp"

namespace mth
{
namespace detail
{
/* Vector class base template */
template <Number T, std::size_t numCoords>
class VecImpl
{
private:
  static_assert(numCoords >= 2 && numCoords <= 4, "Number of coordinates must be in range [2, 4]");

  std::array<T, numCoords> coords{};

public:
  VecImpl() = default;

  /* Vector constructor method */
  template <std::convertible_to<T>... Arg>
  explicit VecImpl(Arg... arg) noexcept : coords{static_cast<T>(arg)...}
  {
    static_assert(sizeof...(arg) == numCoords || sizeof...(arg) == 1,
                  "Invalid number of coordinates in vector ctor");
  }

  /* Vector add and equal vector (reload +=) function
   * ARGUMENTS:
   *   - link to vector:
   *       vec<T> &V;
   * RETURNS:
   *       (vec<T> &) link to result vector;
   */
  VecImpl &operator+=(const VecImpl &V) noexcept
  {
    return transform([&V](const auto &ci, auto i) { return ci + V[i]; });
  } /* End of 'operator+=' function */

  T operator[](std::size_t i) const noexcept
  {
    return coords[i];
  }

  T &operator[](std::size_t i) noexcept
  {
    return coords[i];
  }

  /* Vector substraction and equal vector (reload -=) function
   * ARGUMENTS:
   *   - link to Vector:
   *       vec<T> &V;
   * RETURNS:
   *       (vec<T> &) link to result vector;
   */
  VecImpl &operator-=(const VecImpl &V) noexcept
  {
    return transform([&V](const auto &ci, auto i) { return ci - V[i]; });
  } /* End of 'operator-=' function */

  auto operator-() const noexcept
  {
    auto tmp = *this;
    tmp.transform([](auto ci, auto i) { return -ci; });
    return tmp;
  }

  VecImpl &operator*=(const VecImpl &V) noexcept
  {
    return transform([&V](const auto &ci, auto i) { return ci * V[i]; });
  }

  T length(VOID) const noexcept
  {
    return sqrt(length2());
  }

  T dot(const VecImpl &V) const noexcept
  {
    return std::inner_product(coords.cbegin(), coords.cend(), coords.cbegin(), T{});
  }

  template <std::convertible_to<T> U>
  VecImpl &operator*=(U number) noexcept
  {
    return transform([number](auto ci, auto) { return ci * number; });
  }

  template <std::convertible_to<T> U>
  VecImpl &operator/=(U number) noexcept
  {
    return operator*=(static_cast<T>(1) / number);
  }

  VecImpl normalize(VOID) const noexcept
  {
    auto len = length();
    auto V = *this;

    if (len != 0 && len != 1)
      V /= len;

    return V;
  }

  static auto normalizing(const VecImpl &V) noexcept
  {
    return V.normalize();
  }

  auto length2(VOID)
  {
    return dot(*this);
  }

  auto distance(const VecImpl &V)
  {
    return (*this - V).length();
  }

private:
  template <typename Transformer>
  VecImpl &transform(Transformer trans)
  {
    for (std::size_t i = 0; i < coords.size(); ++i)
    {
      auto coord = coords[i];
      coords[i] = trans(coord, i);
    }

    return *this;
  }
};

template <Number T, std::size_t N>
auto operator+(const VecImpl<T, N> &lhs, const VecImpl<T, N> &rhs) noexcept
{
  auto tmp = lhs;
  tmp += rhs;
  return tmp;
}

template <Number T, std::size_t N>
auto operator-(const VecImpl<T, N> &lhs, const VecImpl<T, N> &rhs) noexcept
{
  auto tmp = lhs;
  tmp -= rhs;
  return tmp;
}

template <Number T, std::size_t N>
auto operator*(const VecImpl<T, N> &lhs, const VecImpl<T, N> &rhs) noexcept
{
  auto tmp = lhs;
  tmp *= rhs;
  return tmp;
}

template <Number T, std::size_t N, std::convertible_to<T> U>
auto operator*(const VecImpl<T, N> &lhs, U rhs) noexcept
{
  auto tmp = lhs;
  tmp *= rhs;
  return tmp;
}

template <Number T, std::size_t N, std::convertible_to<T> U>
auto operator/(const VecImpl<T, N> &lhs, U rhs) noexcept
{
  auto tmp = lhs;
  tmp /= rhs;
  return tmp;
}

template <Number T, std::size_t N>
auto operator*(T lhs, const VecImpl<T, N> &rhs) noexcept
{
  auto tmp = rhs;
  tmp *= lhs;
  return tmp;
}

template <typename... Args>
struct always_false : std::false_type
{};

template <Number T, std::size_t numCoords>
struct Vec final
{
  static_assert(always_false<T>::value, "Unsupported coords amount for vector");
};

template <Number T>
struct Vec<T, 3> : VecImpl<T, 3>
{
  using VecImpl<T, 3>::VecImpl;
  T x() const noexcept
  {
    return this->operator[](0);
  }
  T y() const noexcept
  {
    return this->operator[](1);
  }
  T z() const noexcept
  {
    return this->operator[](2);
  }

  Vec cross(const Vec &V) const noexcept
  {
    return Vec(y() * V.z() - z() * V.y(), z() * V.x() - x() * V.z(), x() * V.y() - y() * V.x());
  }

  /* Vector transform function.
   * ARGUMENTS:
   *   - transform matrix:
   *       MATR M;
   * RETURNS:
   *   (VEC) result vector.
   */
  // Vec vecTrans(const matr<T> &M) const noexcept
  // {
  //   return Vec(M.A[0][0] * x() + M.A[0][1] * y() + M.A[0][2] * z(),
  //              M.A[1][0] * x() + M.A[1][1] * y() + M.A[1][2] * z(),
  //              M.A[2][0] * x() + M.A[2][1] * y() + M.A[2][2] * z());
  // } /* End of 'VecTrans' function */
};

template <Number T>
struct Vec<T, 4> : VecImpl<T, 4>
{
  using VecImpl<T, 4>::VecImpl;
  T x() const noexcept
  {
    return this->operator[](0);
  }
  T y() const noexcept
  {
    return this->operator[](1);
  }
  T z() const noexcept
  {
    return this->operator[](2);
  }
  T w() const noexcept
  {
    return this->operator[](3);
  }
};

template <Number T>
struct Vec<T, 2> : VecImpl<T, 2>
{
  using VecImpl<T, 2>::VecImpl;
  T x() const noexcept
  {
    return this->operator[](0);
  }
  T y() const noexcept
  {
    return this->operator[](1);
  }
};
} // namespace detail

template <Number T>
using Vec2 = detail::Vec<T, 2>;

template <Number T>
using Vec = detail::Vec<T, 3>;

template <Number T>
using Vec4 = detail::Vec<T, 4>;

} // namespace mth

#endif /* __VEC_H_ */

/* End of 'vec.h' file */
