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

template <typename T>
concept Number = std::floating_point<T> || std::integral<T>;

template <std::floating_point T>
constexpr T D2R(T AngleinDegree)
{
  return AngleinDegree * std::numbers::pi_v<T> / 180;
}

} // namespace mth

#endif // __MATH_MTHDEF_H__

/* End of 'mthdef.h' file */
