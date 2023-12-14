#include "Emitter.h"
#include <ngl/Random.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ngl/VAOFactory.h>
#include <ngl/MultiBufferVAO.h>

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

void Emitter::resetParticle(size_t _index)
{
  m_particlePos[_index]=m_pos;
  m_dir[_index] = m_emitDir * ngl::Random::randomPositiveNumber()+ randomVectorOnSphere() * m_spread;
  m_dir[_index].m_y = std::abs(m_dir[_index].m_y);
  m_colour[_index]=ngl::Random::getRandomColour3();
  m_life[_index] = 10 + static_cast<int>(ngl::Random::randomPositiveNumber(2000.0f));
  m_particlePos[_index].m_w = 0.1f;
  m_state[_index] = ParticleState::Dead;
}


void Emitter::reset()
{
  m_particlePos.clear();
  m_dir.clear();
  m_colour.clear();
  m_life.clear();
  m_state.clear();
  m_numParticles=0;
}

void Emitter::birthParticles()
{
  auto births = 0 + static_cast<int>(ngl::Random::randomPositiveNumber(m_numPerFrame));
  for(size_t i=0; i<births; ++i)
  {
    for(size_t p=0; p<m_numParticles; ++p)
    {
      if(m_state[p] == ParticleState::Dead)
      {
        resetParticle(p);
        m_state[p]=ParticleState::Alive;
        break;
      }
    }
  }

}

Emitter::Emitter(ngl::Vec3 _pos,size_t _numParticles, float _spread,size_t _maxAlive,size_t _maxUpdate) :
    m_pos{_pos}, m_numParticles{_numParticles},m_spread{_spread},m_maxAlive{_maxAlive},m_numPerFrame{_maxUpdate}
{
  m_particlePos.resize(_numParticles);
  m_dir.resize(_numParticles);
  m_colour.resize(_numParticles);
  m_life.resize(_numParticles);
  m_state.resize(_numParticles);
  for(size_t i=0; i<m_numParticles; ++i)
  {
    resetParticle(i);
  }

  birthParticles();

  m_vao = ngl::vaoFactoryCast<ngl::MultiBufferVAO>(ngl::VAOFactory::createVAO(ngl::multiBufferVAO,GL_POINTS));
  m_vao->bind();
  m_vao->setData(ngl::MultiBufferVAO::VertexData(0,0)); // index 0 points
  m_vao->setData(ngl::MultiBufferVAO::VertexData(0,0)); // index 1 colours
  m_vao->unbind();
}

size_t Emitter::numParticles()const
{
    return m_numParticles;
}

ngl::Vec3 Emitter::getPosition() const
{
    return m_pos;
}


void Emitter::addParticles(size_t _num)
{


  m_numParticles+=_num;
  m_maxAlive+=_num;
  m_particlePos.resize(m_numParticles);
  m_dir.resize(m_numParticles);
  m_colour.resize(m_numParticles);
  m_state.resize(m_numParticles);
  m_life.resize(m_numParticles);
   for(size_t i=0; i<_num; ++i)
   {
     for(size_t p=0; p<m_numParticles; ++p)
     {
       if(m_state[p] == ParticleState::Dead)
       {
         resetParticle(p);
         m_state[p]=ParticleState::Alive;
         break;
       }
     }

   }
}


void Emitter::draw() const
{
  if(m_particlePos.size() == 0) return ;
  m_vao->bind();
  m_vao->setData(0,ngl::MultiBufferVAO::VertexData(m_particlePos.size()*sizeof(ngl::Vec4),m_particlePos[0].m_x));
  m_vao->setVertexAttributePointer(0,4,GL_FLOAT,0,0);
  m_vao->setData(1,ngl::MultiBufferVAO::VertexData(m_colour.size()*sizeof(ngl::Vec3),m_colour[0].m_r));
  m_vao->setVertexAttributePointer(1,3,GL_FLOAT,0,0);

  m_vao->setNumIndices(m_numParticles);
  glEnable(GL_PROGRAM_POINT_SIZE);
  m_vao->draw();
  glDisable(GL_PROGRAM_POINT_SIZE);
  m_vao->unbind();

}

void Emitter::update(float _delta)
{
   // std::cout<<"update\n";
    float dt=_delta;
    ngl::Vec3 gravity(0.0,-9.81f,0.0);
    // find how many particles alive
    size_t numAlive = std::count_if(std::begin(m_state),std::end(m_state),
    [](auto p)
    {
      return p == ParticleState::Alive;
    });
    if(numAlive < m_maxAlive)
    {
      birthParticles();
    }
    // add new particles if not enough



  for(size_t i=0; i<m_numParticles; ++i)
    {
        if(m_state[i] == ParticleState::Dead)
          continue;
        m_dir[i] += gravity * dt * 0.5f;
        m_particlePos[i] += m_dir[i] * 0.5f;
        m_life[i] -=1;
        m_particlePos[i].m_w+=0.5f;
        m_particlePos[i].m_w=std::clamp(m_particlePos[i].m_w,1.0f,6.0f);
        if(m_particlePos[i].m_y <= 0.0f || m_life [i] <=0)
        {
          resetParticle(i);
        }
    }

}

void Emitter::move(const ngl::Vec3 &_dp)
{
    m_pos+=_dp;
}


