#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Vec3.h"
struct Particle
{
    Particle()=default;
    Vec3 pos;
    Vec3 dir;
    Vec3 colour;
    float size=1.0f;
    int life=100;
};

#endif