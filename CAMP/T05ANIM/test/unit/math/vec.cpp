#include <gtest/gtest.h>

#include "math/vec.hpp"

TEST(vec, ctor)
{
  mth::Vec<double> v{1, 2, 3};

  EXPECT_EQ(v.x(), 1);
  EXPECT_EQ(v.y(), 2);
  EXPECT_EQ(v.z(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(vec, ctorOne)
{
  mth::Vec<double> v{-4};

  EXPECT_EQ(v.x(), -4);
  EXPECT_EQ(v.y(), -4);
  EXPECT_EQ(v.z(), -4);
  EXPECT_EQ(v[0], -4);
  EXPECT_EQ(v[1], -4);
  EXPECT_EQ(v[2], -4);
}

TEST(vec, add)
{
  mth::Vec<double> v{1, 2, 3}, vv{v};

  v = v + vv;

  EXPECT_EQ(v.x(), 2);
  EXPECT_EQ(v.y(), 4);
  EXPECT_EQ(v.z(), 6);
}

TEST(vec, sub)
{
  mth::Vec<double> v{1, 2, 3}, vv{v};

  v = v - vv;

  EXPECT_EQ(v.x(), 0);
  EXPECT_EQ(v.y(), 0);
  EXPECT_EQ(v.z(), 0);
}

TEST(vec, unmin)
{
  mth::Vec<double> v{1, 2, 3}, vv{v};

  v = -v;

  EXPECT_EQ(v.x(), -1);
  EXPECT_EQ(v.y(), -2);
  EXPECT_EQ(v.z(), -3);
}

TEST(vec, dot)
{
  mth::Vec<double> v{1, 2, 3}, vv{0, 3, -2};

  auto res = v.dot(vv);
  auto res2 = vv.dot(v);

  EXPECT_EQ(res, res2);
  EXPECT_EQ(res, 0);
}

TEST(vec, cross)
{
  mth::Vec<double> v{1, 0, 0}, vv{0, 3, 0}, answ{0, 0, 3};

  auto res = v.cross(vv);
  auto res2 = vv.cross(v);

  EXPECT_EQ(res, -res2);
  EXPECT_EQ(res, answ);
}

TEST(vec, eq)
{
  mth::Vec<double> v{1, 2, 3}, vv{v}, vvv{-v};

  auto res = v == vv;
  auto res1 = v != vv;
  auto res2 = v != vvv;
  auto res3 = v == vvv;

  EXPECT_TRUE(res);
  EXPECT_FALSE(res1);
  EXPECT_TRUE(res2);
  EXPECT_FALSE(res3);
}

TEST(vec, mul)
{
  mth::Vec<double> v{1, 2, 3}, answ{3, 6, 9};
  constexpr int val = 3;

  auto res = v * val;
  auto res1 = val * v;

  EXPECT_EQ(res, res1);
  EXPECT_EQ(res, answ);
}
