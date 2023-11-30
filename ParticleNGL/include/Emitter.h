#ifndef EMITTER_H_
#define EMITTER_H_
#include <cstdlib>
#include <vector>
#include "Particle.h"
#include <string_view>

#include <ngl/AbstractVAO.h>
#include <memory>

class Emitter
{
public :
    Emitter(ngl::Vec3 _pos,size_t _numParticles);
    size_t numParticles() const;
    ngl::Vec3 getPosition() const;
    void draw() const;
    void update(float _delta);
private :
    [[nodiscard]] ngl::Vec3 randomVectorOnSphere(float _radius = 1.0f);
    void resetParticle(Particle &_p);
    void birthParticles();
    std::vector<Particle> m_particles;
    ngl::Vec3 m_pos;
    ngl::Vec3 m_emitDir={0.0f,0.5f,0.0f};
    float m_spread=5.0f;
    // max alive at one time
    size_t m_maxAlive =5000;
    // max birthed at one time
    size_t m_numPerFrame =120;
    std::unique_ptr<ngl::AbstractVAO> m_vao;
};


#endif