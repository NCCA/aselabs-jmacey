#include <gtest/gtest.h>
#include "RGBA.h"


TEST(RGBA,construct)
{
    RGBA pixel;
    EXPECT_EQ(pixel.r,0);
    EXPECT_EQ(pixel.g,0);
    EXPECT_EQ(pixel.b,0);
    EXPECT_EQ(pixel.a,255);
}

TEST(RGBA,construcUser)
{
    RGBA pixel(255,128,75,23);
    EXPECT_EQ(pixel.r,255);
    EXPECT_EQ(pixel.g,128);
    EXPECT_EQ(pixel.b,75);
    EXPECT_EQ(pixel.a,23);
}

TEST(RGBA,set)
{
    RGBA pixel;
    pixel.set(0,255,128,255);
    EXPECT_EQ(pixel.r,0);
    EXPECT_EQ(pixel.g,255);
    EXPECT_EQ(pixel.b,128);
    EXPECT_EQ(pixel.a,255);
}

TEST(RGBA,clamp)
{
    RGBA pixel(255,0,128,220);
    pixel.clamp(50,220);
    EXPECT_EQ(pixel.r,220);
    EXPECT_EQ(pixel.g,50);
    EXPECT_EQ(pixel.b,128);
    EXPECT_EQ(pixel.a,220);
}

