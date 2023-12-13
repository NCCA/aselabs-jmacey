#ifndef EMITTER_H_
#define EMITTER_H_
#include <cstdlib>
#include <vector>
#include <string_view>

#include <ngl/MultiBufferVAO.h>
#include <memory>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>


class Emitter
{
public :
    Emitter(ngl::Vec3 _pos,size_t _numParticles, float _spread,size_t _maxAlive,size_t _maxUpdate);
    size_t numParticles() const;
    ngl::Vec3 getPosition() const;
    void draw() const;
    void update(float _delta);
    void reset();
    void addParticles(size_t _num);
    void move(const ngl::Vec3 &_dp);
private :
    [[nodiscard]] ngl::Vec3 randomVectorOnSphere(float _radius = 1.0f);
    void resetParticle(size_t _index);
    void birthParticles();
    enum class ParticleState : bool {Alive,Dead};
    std::vector<ngl::Vec4> m_particlePos;
    std::vector<ngl::Vec3> m_dir;
    std::vector<ngl::Vec3> m_colour;
    std::vector<int> m_life;
    std::vector<ParticleState> m_state;
    size_t m_numParticles;
    //std::vector<Particle> m_particles;
    ngl::Vec3 m_pos;
    ngl::Vec3 m_emitDir={0.0f,0.5f,0.0f};
    float m_spread=5.0f;
    // max alive at one time
    size_t m_maxAlive =5000;
    // max birthed at one time
    size_t m_numPerFrame =120;
    std::unique_ptr<ngl::MultiBufferVAO> m_vao;
};


#endif