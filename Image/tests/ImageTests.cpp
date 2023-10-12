#include <gtest/gtest.h>
#include "Image.h"
TEST(Image,constructDefault)
{
    Image img;
    EXPECT_EQ(img.width(),0);
    EXPECT_EQ(img.height(),0);
    EXPECT_EQ(img.pixels(),nullptr);
}

TEST(Image,constructUser)
{
    Image img(10,20);
    EXPECT_EQ(img.width(),10);
    EXPECT_EQ(img.height(),20);

}