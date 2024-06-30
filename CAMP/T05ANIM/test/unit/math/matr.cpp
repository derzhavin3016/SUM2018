#include <algorithm>
#include <gtest/gtest.h>
#include <random>
#include <ranges>
#include <stdexcept>

#include "math/matr.hpp"
#include "math/vec.hpp"

using Mat = mth::Matr4x4<double>;

Mat genRandMatrix(double min, double max)
{
  if (min > max)
  {
    throw std::invalid_argument{std::format("Bad range: [{}, {}]", min, max)};
  }
  std::mt19937_64 mt;
  std::uniform_real_distribution<double> dist(min, max);
  auto &&rng = std::views::iota(Mat::kSize) | std::views::transform([&](auto i) {
                 mt.seed(i);
                 return dist(mt);
               });
  auto &&com = std::ranges::common_view{rng};
  return Mat{com.begin(), com.end()};
}

TEST(Matr, ctor)
{
  Mat m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

  for (std::size_t i = 0; i < 16; ++i)
  {
    EXPECT_EQ(m[i / 4][i % 4], i + 1);
  }
}

TEST(Matr, transpose)
{
  Mat m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

  EXPECT_EQ(m.transpose().transpose(), m);
}

TEST(Matr, invBad)
{
  Mat m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

  EXPECT_THROW(m.inversed(), std::runtime_error);
}

TEST(Matr, invTrivial)
{
  auto m = Mat::identity();

  auto inv = m.inversed();
  EXPECT_EQ(m, inv);
}

TEST(Matr, invNormal)
{
  auto m = Mat::rotX(45);

  if (m.det() == 0)
  {
    return;
  }
  auto inv = m.inversed();
  EXPECT_EQ(m * inv, Mat::identity());
}

TEST(Matr, minNormal)
{
  auto m = genRandMatrix(-10, 20);

  EXPECT_EQ(m -= m, Mat{});
}

TEST(Matr, plusNormal)
{
  auto m = genRandMatrix(-10, 20);

  EXPECT_EQ(m + m, 2 * m);
}

TEST(Matr, plusNormalDiv)
{
  auto m = genRandMatrix(-10, 20);

  EXPECT_EQ(m + m, m / 0.5);
}

TEST(Matr, translate)
{
  auto v = mth::Vec<double>{1, 2, 3};
  auto t = Mat::translate(v);

  EXPECT_EQ(mth::pointTrans(t, -v), decltype(v){});
  t.inverse();
  EXPECT_EQ(mth::pointTrans(t, v), decltype(v){});
}

TEST(Matr, scale)
{
  auto v = mth::Vec<double>{3, 0.5, 1};
  mth::Vec<double> exp{1, 1, 1};
  auto t = Mat::scale(v).inversed();

  EXPECT_EQ(mth::vecTrans(t, v), exp);
}

TEST(Matr, rotX)
{
  ASSERT_EQ(Mat::rotX(32).inversed(), Mat::rotX(-32));

  auto v = mth::Vec<double>{3, 2, 1};
  decltype(v) exp{3, 1, -2};
  auto t = Mat::rotX(90);

  EXPECT_EQ(mth::vecTrans(t, v), exp);
}
TEST(Matr, rotY)
{
  ASSERT_EQ(Mat::rotY(72).inversed(), Mat::rotY(-72));

  auto v = mth::Vec<double>{3, 2, 1};
  decltype(v) exp{-1, 2, 3};
  auto t = Mat::rotY(90);

  EXPECT_EQ(mth::vecTrans(t, v), exp);
}
