#include "Emitter.h"
#include "Random.h"
#include <iostream>
#include <fstream>

Emitter::Emitter(Vec3 _pos,size_t _numParticles) : m_pos{_pos}
{
    m_particles.resize(_numParticles);
    for(auto &p : m_particles)
    {
        p.pos=m_pos;
        p.dir = m_emitDir * Random::randomPositiveFloat() + Random::randomVectorOnSphere() * m_spread;
        p.dir.y = std::abs(p.dir.y);
        p.colour=Random::randomPositiveVec3();
        p.life = 20 + static_cast<int>(Random::randomPositiveFloat(100));
    }


}

size_t Emitter::numParticles()const
{
    return m_particles.size();
}

Vec3 Emitter::getPosition() const
{
    return m_pos;
}


void Emitter::draw() const
{
    std::cout<<"**********************\n";
    for(auto p : m_particles)
    {
        std::cout<<p.pos.x<<' '<<p.pos.y<<' '<<p.pos.z<<'\n';
    }
}

void Emitter::update()
{
    float dt=0.01f;
    Vec3 gravity(0.0,-9.81f,0.0);
    for(auto &p : m_particles)
    {
        p.dir += gravity * dt * 0.5f;
        p.pos += p.dir * 0.5f;
    }
}

void Emitter::writeGeo(std::string_view filename) const
{
    auto file=std::ofstream(filename.data());
    file<<"PGEOMETRY V5\n";
    file<<"NPoints "<<m_particles.size() <<" NPrims 1 \n";
    file<<"NPointGroups 0 NPrimGroups 0 \n";
    file<<"NPointAttrib 2 NVertexAttrib 0 NPrimAttrib 1 NAttrib 0\n";
    file<<"PointAttrib \n";
    file<<"Cd 3 float 1 1 1 \n";
    file<<"pscale 1 float 0.5 \n";
    for(auto p : m_particles)
    {
        file<<p.pos.x<<' '<<p.pos.y<<' '<<p.pos.z<<" 1.0 (";
        file<<p.colour.x<<' '<<p.colour.y<<' '<<p.colour.z<<' ';
        file<<p.size<<")\n";
    }

    file<<"PrimitiveAttrib\n";
    file<<"generator 1 index 1 papi\n";
    file<<"Part "<<m_particles.size()<<' ';
    for(size_t i=0; i<m_particles.size(); ++i)
    {
        file<<i<<' ';
    }
    file<<"[0]\n";
    file<<"beginExtra\nendExtra\n";
    file.close();
}