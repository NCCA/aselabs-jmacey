#include "Walker.h"
#include <iostream>
std::random_device g_rd;
std::seed_seq g_seed{g_rd(),g_rd(),g_rd(),g_rd(),g_rd(),g_rd(),g_rd(),g_rd(),g_rd()};
std::mt19937 g_rng(g_seed);
std::uniform_int_distribution<> g_walkDir(-1,1);
Walker::Walker(int _w, int _h)
{
    m_image = std::make_unique<Image>(_w,_h,255,255,255,0);
    initRNG();
    resetStart();
}

void Walker::resetStart()
{
    m_xpos=m_xRand(g_rng);
    m_ypos=m_yRand(g_rng);
    std::cout<<"Reset Start "<<m_xpos<<' '<<m_ypos<<'\n';
}


bool Walker::save(std::string_view _filename) const
{
    return m_image->save(_filename);
}


void Walker::initRNG()
{
    m_xRand=std::uniform_int_distribution<>(1,m_image->width()-1);
    m_yRand=std::uniform_int_distribution<>(1,m_image->height()-1);
}

void Walker::randomSeeds(size_t _number)
{
    for(size_t i=0; i<_number; ++i)
    {
        m_image->setPixel(m_xRand(g_rng),m_yRand(g_rng),255,255,255,255);
    }
}

bool Walker::walk()
{
  // while not walking
  // have I hit the edge? If so return false
  // else
  // get current pixel is it a seed?
  // if yes set pixel return true
  // else walk
  // got  top
  bool walking = true;
  bool found;

    while(walking)
    {
        // move to new pos
        m_xpos+=g_walkDir(g_rng);
        m_ypos+=g_walkDir(g_rng);
        if(m_xpos ==0 || m_xpos>=m_image->width() ||
           m_ypos ==0 || m_ypos>=m_image->height() )
        {
            walking =false;
            found = false;
            std::cout<<"hit edge\n";
            break;
        }
        // sample
        RGBA p;
        for(int y=-1; y<=1; ++y)
        {
            for(int x=-1; x<=1; ++x)
            {
                p=m_image->getPixel(m_xpos+x,m_ypos+y);
                if(p.a == 255)
                {
                    std::cout<<"Found pixel\n";
                    m_image->setPixel(m_xpos,m_ypos,0,0,0,255);
                    return true;
                }
            }
        }

    }
  return found;

}