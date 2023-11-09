#ifndef EMITTER_H_
#define EMITTER_H_
#include <cstdlib>
#include <vector>
#include "Particle.h"
#include <string_view>
class Emitter
{
public :
    Emitter(Vec3 _pos,size_t _numParticles);
    size_t numParticles() const;
    Vec3 getPosition() const;
    void draw() const;
    void update();
    void writeGeo(std::string_view filename) const;
private :
    void resetParticle(Particle &_p);
    void birthParticles();
    std::vector<Particle> m_particles;
    Vec3 m_pos;
    Vec3 m_emitDir={0.0f,0.5f,0.0f};
    float m_spread=5.0f;
    // max alive at one time
    size_t m_maxAlive =5000;
    // max birthed at one time
    size_t m_numPerFrame =120;
};


#endif