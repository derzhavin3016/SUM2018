/* FILE NAME: matr.h
 * PROGRAMMER: AD6
 * LAST UPDATE: 11.07.2018
 * PURPOSE
 */

#ifndef ANIM_INCLUDE_MATH_MATR_HPP_INCLUDED
#define ANIM_INCLUDE_MATH_MATR_HPP_INCLUDED

#include <algorithm>
#include <cmath>
#include <concepts>
#include <format>
#include <functional>
#include <initializer_list>
#include <numeric>
#include <ostream>
#include <ranges>
#include <stdexcept>
#include <vector>

#include "math/vec.hpp"
#include "mthdef.hpp"
#include "vec.hpp"

namespace mth
{
namespace detail
{
template <typename U>
class RowProxy final
{
  U m_it;

public:
  explicit RowProxy(U it) : m_it(it)
  {}

  [[nodiscard]] auto &operator[](std::size_t i) const
  {
    return m_it[i];
  }
  [[nodiscard]] auto &operator[](std::size_t i)
  {
    return m_it[i];
  }
};
} // namespace detail

template <std::floating_point T>
class Matr4x4 final
{
private:
  static constexpr std::size_t kCol = 4;
  static constexpr std::size_t kRow = 4;

public:
  static constexpr std::size_t kSize = kCol * kRow;

private:
  std::vector<T> m_data{};
  using Comparator = ThresComp<T>;

  [[nodiscard]] constexpr static T det3x3(T A11, T A12, T A13, T A21, T A22, T A23, T A31, T A32,
                                          T A33)
  {
    return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
           A13 * A22 * A31;
  }
  using Idx = std::pair<std::size_t, std::size_t>;

  [[nodiscard]] constexpr static std::size_t transformIdx(std::size_t i, std::size_t j)
  {
    return i * kCol + j;
  }

  [[nodiscard]] constexpr static std::size_t transformIdx(Idx idx)
  {
    return transformIdx(idx.first, idx.second);
  }

public:
  template <std::input_iterator It>
  explicit Matr4x4(It begin, It end) : m_data(kSize)
  {
    std::ranges::copy(std::ranges::subrange(begin, end) | std::views::take(kSize), m_data.begin());
  }

  explicit Matr4x4(T val) : m_data(kSize, val)
  {}

  Matr4x4(std::initializer_list<T> vals) : Matr4x4(vals.begin(), vals.end())
  {}

  Matr4x4() : m_data(kSize)
  {}

  [[nodiscard]] auto &at(std::size_t i, std::size_t j) const
  {
    return m_data.at(transformIdx(i, j));
  }

  [[nodiscard]] auto &at(std::size_t i, std::size_t j)
  {
    return m_data.at(transformIdx(i, j));
  }

  [[nodiscard]] auto &operator[](Idx idx) const
  {
    return m_data[transformIdx(idx)];
  }

  [[nodiscard]] auto &operator[](Idx idx)
  {
    return m_data[transformIdx(idx)];
  }

  [[nodiscard]] auto operator[](std::size_t i)
  {
    return detail::RowProxy{m_data.begin() + transformIdx(i, 0)};
  }

  [[nodiscard]] bool equal(const Matr4x4 &other) const
  {
    return std::ranges::equal(m_data, other.m_data, Comparator::isEqual);
  }

  [[nodiscard]] auto operator[](std::size_t i) const
  {
    return detail::RowProxy{m_data.begin() + transformIdx(i, 0)};
  }

  [[nodiscard]] constexpr static auto identity()
  {
    Matr4x4<T> res;
    res.setWalk([](auto i, auto j) -> T { return i == j; });
    return res;
  }

  auto &transpose()
  {
    walkIdx([this](auto &v, auto i, auto j) {
      if (i < j)
      {
        std::swap(v, m_data[transformIdx(j, i)]);
      }
    });
    return *this;
  }

  auto operator-() const
  {
    auto &&rng = m_data | std::views::transform(std::negate<>{});
    return Matr4x4(rng.begin(), rng.end());
  }

  auto &operator*=(const Matr4x4 &other)
  {
    auto tmp = *this;
    tmp.setWalk([this, &other](auto i, auto j) {
      T acc{};

      for (std::size_t k = 0; k < kCol; ++k)
      {
        acc += m_data[transformIdx(i, k)] * other.m_data[transformIdx(k, j)];
      }

      return acc;
    });

    std::swap(*this, tmp);

    return *this;
  }

  auto &operator+=(const Matr4x4 &other)
  {
    std::ranges::transform(m_data, other.m_data, m_data.begin(), std::plus<>{});

    return *this;
  }

  auto &operator-=(const Matr4x4 &other)
  {
    std::ranges::transform(m_data, other.m_data, m_data.begin(), std::minus<>{});

    return *this;
  }

  auto &operator*=(Number auto num)
  {
    for (auto &elem : m_data)
    {
      elem *= num;
    }

    return *this;
  }

  auto &operator/=(Number auto num)
  {
    for (auto &elem : m_data)
    {
      elem /= num;
    }

    return *this;
  }

  [[nodiscard]] T det() const
  {
    auto &A = *this;
    return A[0][0] * det3x3(A[1][1], A[1][2], A[1][3], A[2][1], A[2][2], A[2][3], A[3][1], A[3][2],
                            A[3][3]) -
           A[0][1] * det3x3(A[1][0], A[1][2], A[1][3], A[2][0], A[2][2], A[2][3], A[3][0], A[3][2],
                            A[3][3]) +
           A[0][2] * det3x3(A[1][0], A[1][1], A[1][3], A[2][0], A[2][1], A[2][3], A[3][0], A[3][1],
                            A[3][3]) -
           A[0][3] * det3x3(A[1][0], A[1][1], A[1][2], A[2][0], A[2][1], A[2][2], A[3][0], A[3][1],
                            A[3][2]);
  }

  auto inversed() const
  {
    const auto determinant = det();

    if (determinant == 0)
    {
      throw std::runtime_error{
        std::format("Matrix with zero determinant cannot have inverse one. det: {}", determinant)};
    }
    Matr4x4 r(1 / determinant);

    auto &m = m_data;

    r.m_data[0] *= m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] +
                   m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];

    r.m_data[4] *= -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] -
                   m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];

    r.m_data[8] *= m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] +
                   m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];

    r.m_data[12] *= -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] -
                    m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];

    r.m_data[1] *= -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] -
                   m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];

    r.m_data[5] *= m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] +
                   m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];

    r.m_data[9] *= -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] -
                   m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];

    r.m_data[13] *= m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] +
                    m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];

    r.m_data[2] *= m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] +
                   m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];

    r.m_data[6] *= -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] -
                   m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];

    r.m_data[10] *= m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] +
                    m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];

    r.m_data[14] *= -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] -
                    m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];

    r.m_data[3] *= -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] -
                   m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];

    r.m_data[7] *= m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] +
                   m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];

    r.m_data[11] *= -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] -
                    m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];

    r.m_data[15] *= m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] +
                    m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

    return r;
  }

  void inverse()
  {
    *this = inversed();
  }

  static auto translate(const Vec<T> &V)
  {
    return Matr4x4{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, V.x(), V.y(), V.z(), 1};
  }

  static auto scale(const Vec<T> &S)
  {
    return Matr4x4{S.x(), 0, 0, 0, 0, S.y(), 0, 0, 0, 0, S.z(), 0, 0, 0, 0, 1};
  }

  static auto rotX(T AngleInDegree)
  {
    const T angle = D2R(AngleInDegree);
    const auto si = std::sin(angle);
    const auto co = std::cos(angle);

    return Matr4x4{1, 0, 0, 0, 0, co, si, 0, 0, -si, co, 0, 0, 0, 0, 1};
  }

  static auto rotY(T AngleInDegree)
  {
    T angle = D2R(AngleInDegree);
    const auto si = std::sin(angle);
    const auto co = std::cos(angle);

    return Matr4x4{co, 0, -si, 0, 0, 1, 0, 0, si, 0, co, 0, 0, 0, 0, 1};
  }

  static auto rotZ(T AngleInDegree)
  {
    T angle = D2R(AngleInDegree);
    const auto si = std::sin(angle);
    const auto co = std::cos(angle);

    return Matr4x4{co, si, 0, 0, -si, co, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  }

  static auto rot(T AngleInDegree, Vec<T> r)
  {
    T angle = D2R(AngleInDegree);
    const auto si = std::sin(angle);
    const auto co = std::cos(angle);
    r.normalize();

    return Matr4x4{co + r[0] * r[0] * (1 - co),
                   r[0] * r[1] * (1 - co) + r[2] * si,
                   r[0] * r[2] * (1 - co) - r[1] * si,
                   0,
                   r[1] * r[0] * (1 - co) - r[2] * si,
                   co + r[1] * r[1] * (1 - co),
                   r[1] * r[2] * (1 - co) + r[0] * si,
                   0,
                   r[2] * r[0] * (1 - co) + r[1] * si,
                   r[2] * r[1] * (1 - co) - r[0] * si,
                   co + r[2] * r[2] * (1 - co),
                   0,
                   0,
                   0,
                   0,
                   1};
  }

  static auto view(const Vec<T> &loc, const Vec<T> &at, const Vec<T> &up1)
  {
    auto dir = (at - loc).normalize();
    auto right = dir.cross(up1).normalize();
    auto up = right.cross(dir).normalize();

    return Matr4x4{right[0], up[0], -dir[0], 0, right[1],        up[1],        -dir[1],      0,
                   right[2], up[2], -dir[2], 0, -loc.dot(right), -loc.dot(up), loc.dot(dir), 1};
  }

  static auto frustum(T left, T right, T bottom, T top, T near, T far)
  {

    return Matr4x4{(2 * near) / (right - left),
                   0,
                   0,
                   0,
                   0,
                   (2 * near) / (top - bottom),
                   0,
                   0,
                   (right + left) / (right - left),
                   (top + bottom) / (top - bottom),
                   -(far + near) / (far - near),
                   -1,
                   0,
                   0,
                   -(2 * near * far) / (far - near),
                   0};
  }

  void dump(std::ostream &ost)
  {
    walkIdx([&](auto &v, auto i, auto j) {
      ost << v << ", ";
      if (j == kCol - 1)
      {
        ost << '\n';
      }
    });
  }

private:
  void setWalk(auto walker)
  {
    walkIdx([&walker](auto &v, auto i, auto j) { v = walker(i, j); });
  }

  void walkIdx(auto walker)
  {
    for (std::size_t i = 0; i < kRow; ++i)
    {
      for (std::size_t j = 0; j < kCol; ++j)
        walker(m_data[transformIdx(i, j)], i, j);
    }
  }
};

template <std::floating_point T>
[[nodiscard]] auto vecTrans(const Matr4x4<T> &mat, const Vec<T> &v)
{
  return Vec<T>{mat[0][0] * v.x() + mat[0][1] * v.y() + mat[0][2] * v.z(),
                mat[1][0] * v.x() + mat[1][1] * v.y() + mat[1][2] * v.z(),
                mat[2][0] * v.x() + mat[2][1] * v.y() + mat[2][2] * v.z()};
}

template <std::floating_point T>
[[nodiscard]] auto pointTrans(const Matr4x4<T> &mat, const Vec<T> &v)
{
  const T w = v.x() * mat[0][3] + v.y() * mat[1][3] + v.z() * mat[2][3] + mat[3][3];
  return Vec<T>{mat[0][0] * v.x() + mat[1][0] * v.y() + mat[2][0] * v.z() + mat[3][0],
                mat[0][1] * v.x() + mat[1][1] * v.y() + mat[2][1] * v.z() + mat[3][1],
                mat[0][2] * v.x() + mat[1][2] * v.y() + mat[2][2] * v.z() + mat[3][2]} /
         w;
}

template <std::floating_point T>
[[nodiscard]] auto operator*(const Matr4x4<T> &lhs, const Matr4x4<T> &rhs)
{
  auto res = lhs;
  res *= rhs;
  return res;
}

template <std::floating_point T>
[[nodiscard]] Matr4x4<T> operator*(Number auto lhs, const Matr4x4<T> &rhs)
{
  auto res = rhs;
  res *= lhs;
  return res;
}

template <std::floating_point T>
[[nodiscard]] Matr4x4<T> operator*(const Matr4x4<T> &lhs, Number auto rhs)
{
  auto res = lhs;
  res *= rhs;
  return res;
}

template <std::floating_point T>
[[nodiscard]] Matr4x4<T> operator/(const Matr4x4<T> &lhs, Number auto rhs)
{
  auto res = lhs;
  res /= rhs;
  return res;
}
template <std::floating_point T>
[[nodiscard]] auto operator+(const Matr4x4<T> &lhs, const Matr4x4<T> &rhs)
{
  auto res = lhs;
  res += rhs;
  return res;
}
template <std::floating_point T>
[[nodiscard]] auto operator-(const Matr4x4<T> &lhs, const Matr4x4<T> &rhs)
{
  auto res = lhs;
  res -= rhs;
  return res;
}

template <std::floating_point T>
[[nodiscard]] bool operator==(const Matr4x4<T> &lhs, const Matr4x4<T> &rhs)
{
  return lhs.equal(rhs);
}
} // namespace mth
#endif /* ANIM_INCLUDE_MATH_MATR_HPP_INCLUDED */

/* End of 'matr.h' file */
