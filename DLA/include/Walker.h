#ifndef WALKER_H_
#define WALKER_H_

#include "Image.h"
#include <memory>
#include <random>
#include <string_view>

class Walker
{
public :
    Walker(int _w, int _h);
    void randomSeeds(size_t _number);
    bool save(std::string_view _filename) const;
    void resetStart();
    [[nodiscard]] bool walk();
private :
    void initRNG();
    std::unique_ptr<Image> m_image;
    std::uniform_int_distribution<> m_xRand;
    std::uniform_int_distribution<> m_yRand;
    int m_xpos;
    int m_ypos;

};

#endif