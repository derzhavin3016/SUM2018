/* FILE NAME: mtdefh.h
 * PROGRAMMER: AD6
 * LAST UPDATE: 13.07.2018
 * PURPOSE
 */

#ifndef __MATH_MTHDEF_H__
#define __MATH_MTHDEF_H__

#include <concepts>
#include <numbers>

namespace mth
{

template <std::floating_point T>
constexpr T D2R(T AngleinDegree)
{
  return AngleinDegree * std::numbers::pi_v<T> / 180;
}

template <class T>
concept Number = std::is_floating_point_v<T> || std::is_integral_v<T>;

enum class Axis : std::int8_t
{
  X = 0,
  Y = 1,
  Z = 2,
  NONE
};

template <Number T>
class ThresComp final
{
private:
  static constexpr T baseThres_ = 1e2 * std::numeric_limits<T>::epsilon();
  static inline T threshold_ = baseThres_;

public:
  ThresComp() = delete;

  static void setThreshold(T thres)
    requires std::is_floating_point_v<T>
  {
    threshold_ = thres;
  }

  static T getThreshold()
    requires std::is_floating_point_v<T>
  {
    return threshold_;
  }

  static void scaleThreshold(T factor)
    requires std::is_floating_point_v<T>
  {
    threshold_ *= factor;
  }

  static void resetThreshold()
    requires std::is_floating_point_v<T>
  {
    threshold_ = baseThres_;
  }

  static bool isEqual(T lhs, T rhs)
  {
    if constexpr (std::is_floating_point_v<T>)
      return std::abs(rhs - lhs) < threshold_;
    else
      return lhs == rhs;
  }

  static bool isZero(T num)
  {
    return isEqual(num, T{});
  }
};

template <Number T>
bool isEqualThreshold(T num1, T num2)
{
  return ThresComp<T>::isEqual(num1, num2);
}

template <Number T>
bool isZeroThreshold(T num)
{
  return ThresComp<T>::isZero(num);
}

} // namespace mth

#endif // __MATH_MTHDEF_H__

/* End of 'mthdef.h' file */
