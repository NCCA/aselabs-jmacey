#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <ngl/Vec3.h>
enum class ParticleState : bool {Alive,Dead};
struct Particle
{
    Particle()=default;
    ngl::Vec3 pos;
    ngl::Vec3 dir;
    ngl::Vec3 colour;
    float size=1.0f;
    int life=100;
    ParticleState alive = ParticleState::Dead;
};

#endif