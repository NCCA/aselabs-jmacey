#include <gtest/gtest.h>
#include "Particle.h"
#include "Vec3.h"
#include "Emitter.h"
TEST(Particle,ctor)
{
    Particle p;
    EXPECT_FLOAT_EQ(p.pos.x,0.0f);
    EXPECT_FLOAT_EQ(p.pos.y,0.0f);
    EXPECT_FLOAT_EQ(p.pos.z,0.0f);

    EXPECT_FLOAT_EQ(p.dir.x,0.0f);
    EXPECT_FLOAT_EQ(p.dir.y,0.0f);
    EXPECT_FLOAT_EQ(p.dir.z,0.0f);
    EXPECT_FLOAT_EQ(p.colour.x,0.0f);
    EXPECT_FLOAT_EQ(p.colour.y,0.0f);
    EXPECT_FLOAT_EQ(p.colour.z,0.0f);
    EXPECT_FLOAT_EQ(p.size,1.0f);
    EXPECT_EQ(p.life,100);

}

TEST(Vec3,ctor)
{
    Vec3 v;
    EXPECT_FLOAT_EQ(v.x,0.0f);
    EXPECT_FLOAT_EQ(v.y,0.0f);
    EXPECT_FLOAT_EQ(v.z,0.0f);
}


TEST(Emitter, ctor)
{
    Emitter e(Vec3(0.5f,0.0f,0.0f),20);
    EXPECT_EQ(e.numParticles(),20);
    auto pos=e.getPosition();
    EXPECT_FLOAT_EQ(pos.x,0.5f);
    EXPECT_FLOAT_EQ(pos.y,0.0f);
    EXPECT_FLOAT_EQ(pos.z,0.0f);
}


TEST(Vec3,add)
{
    Vec3 a(1.0f,2.0f,3.0f);
    Vec3 b(3.0f,2.0f,1.0f);
    auto c=a+b;
    EXPECT_FLOAT_EQ(c.x,4.0f);
    EXPECT_FLOAT_EQ(c.y,4.0f);
    EXPECT_FLOAT_EQ(c.z,4.0f);
}

TEST(Vec3,multFloat)
{
    Vec3 a(1.0f,2.0f,3.0f);
    auto b=a*0.5f;
    EXPECT_FLOAT_EQ(b.x,0.5f);
    EXPECT_FLOAT_EQ(b.y,1.0f);
    EXPECT_FLOAT_EQ(b.z,1.5f);


}





