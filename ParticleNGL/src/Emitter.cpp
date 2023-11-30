#include "Emitter.h"
#include <ngl/Random.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ngl/VAOFactory.h>

ngl::Vec3 Emitter::randomVectorOnSphere(float _radius)
{
  auto phi = ngl::Random::randomPositiveNumber(M_PI * 2.0f);
  auto costheta = ngl::Random::randomNumber();
  float u = ngl::Random::randomPositiveNumber();
  float theta = acosf(costheta);
  float r = _radius * std::cbrt(u);
  return ngl::Vec3(r*sinf(theta) * cosf(phi),
                   r*sinf(theta) * sinf(phi),
                   r*cosf(theta)
                   );
}

void Emitter::resetParticle(Particle &_p)
{
  _p.pos=m_pos;
  _p.dir = m_emitDir * ngl::Random::randomPositiveNumber()+ randomVectorOnSphere() * m_spread;
  _p.dir.m_y = std::abs(_p.dir.m_y);
  _p.colour=ngl::Random::getRandomColour3();
  _p.life = 200 + static_cast<int>(ngl::Random::randomPositiveNumber(1000.0f));
  _p.size = 0.01f;
}

void Emitter::birthParticles()
{
  auto dont = static_cast<int>(ngl::Random::randomPositiveNumber(100.0f));
  if(dont <=80)
    return;
  auto births = 0 + static_cast<int>(ngl::Random::randomPositiveNumber(m_numPerFrame));
  for(size_t i=0; i<births; ++i)
  {
    for(auto &p : m_particles)
    {
      if(p.alive == ParticleState::Dead)
      {
        resetParticle(p);
        p.alive=ParticleState::Alive;
        break;
      }
    }
  }
}

Emitter::Emitter(ngl::Vec3 _pos,size_t _numParticles) : m_pos{_pos}
{
    m_particles.resize(_numParticles);
    for(auto &p : m_particles)
    {
      resetParticle(p);
    }

  birthParticles();

  m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_POINTS);

}

size_t Emitter::numParticles()const
{
    return m_particles.size();
}

ngl::Vec3 Emitter::getPosition() const
{
    return m_pos;
}


void Emitter::draw() const
{
  glPointSize(4.0);
  m_vao->bind();
  m_vao->setData(ngl::AbstractVAO::VertexData(m_particles.size()*sizeof(Particle),m_particles[0].pos.m_x));
  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Particle),0);
  m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Particle),6);

  m_vao->setNumIndices(m_particles.size());
  m_vao->draw();
  m_vao->unbind();


  //std::cout<<"draw \n";
//    std::cout<<"**********************\n";
//    for(auto p : m_particles)
//    {
//        std::cout<<p.pos.x<<' '<<p.pos.y<<' '<<p.pos.z<<'\n';
//    }
}

void Emitter::update(float _delta)
{
   // std::cout<<"update\n";
    float dt=_delta;
    ngl::Vec3 gravity(0.0,-9.81f,0.0);
    // find how many particles alive
    size_t numAlive = std::count_if(std::begin(m_particles),std::end(m_particles),
    [](auto p)
    {
      return p.alive == ParticleState::Alive;
    });
    if(numAlive < m_maxAlive)
    {
      birthParticles();
    }
    // add new particles if not enough




    for(auto &p : m_particles)
    {
        if(p.alive == ParticleState::Dead)
          continue;
        p.dir += gravity * dt * 0.5f;
        p.pos += p.dir * 0.5f;
        p.life -=1;
        p.size+=0.01f;
        p.size=std::clamp(p.size,0.0f,2.0f);
        if(p.pos.m_y <= 0.0f || p.life <=0)
        {
          resetParticle(p);
        }
    }
}


