/* FILE NAME: mtdefh.h
 * PROGRAMMER: AD6
 * LAST UPDATE: 13.07.2018
 * PURPOSE
 */

#ifndef ANIM_INCLUDE_MATH_MTHDEF_HPP_INCLUDED
#define ANIM_INCLUDE_MATH_MTHDEF_HPP_INCLUDED

#include <cmath>
#include <concepts>
#include <limits>
#include <numbers>

namespace mth
{

template <std::floating_point T>
constexpr T D2R(T AngleinDegree)
{
  return AngleinDegree * std::numbers::pi_v<T> / 180.0;
}

template <class T>
concept Number = std::is_floating_point_v<T> || std::is_integral_v<T>;

template <Number T>
class ThresComp final
{
private:
  static constexpr T baseThres_ = 1e2 * std::numeric_limits<T>::epsilon();
  static inline T threshold_ = baseThres_;

public:
  constexpr ThresComp() = delete;

  constexpr static void setThreshold(T thres)
    requires std::is_floating_point_v<T>
  {
    threshold_ = thres;
  }

  constexpr static T getThreshold()
    requires std::is_floating_point_v<T>
  {
    return threshold_;
  }

  constexpr static void scaleThreshold(T factor)
    requires std::is_floating_point_v<T>
  {
    threshold_ *= factor;
  }

  constexpr static void resetThreshold()
    requires std::is_floating_point_v<T>
  {
    threshold_ = baseThres_;
  }

  constexpr static bool isEqual(T lhs, T rhs)
  {
    if constexpr (std::is_floating_point_v<T>)
    {
      return std::abs(rhs - lhs) < threshold_;
    }
    else
    {
      return lhs == rhs;
    }
  }

  constexpr static bool isZero(T num)
  {
    return isEqual(num, T{});
  }
};

template <Number T>
constexpr bool isEqualThreshold(T num1, T num2)
{
  return ThresComp<T>::isEqual(num1, num2);
}

constexpr bool isZeroThreshold(Number auto num)
{
  return ThresComp<decltype(num)>::isZero(num);
}

} // namespace mth

#endif /* ANIM_INCLUDE_MATH_MTHDEF_HPP_INCLUDED */

/* End of 'mthdef.h' file */
