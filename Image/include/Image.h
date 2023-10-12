#ifndef IMAGE_H_
#define IMAGE_H_
#include "RGBA.h"
class Image
{
public :
    Image()=default;
    Image(int _w, int _h);
    [[nodiscard]] int width() const noexcept ;
    [[nodiscard]] int height() const noexcept ;
    [[nodiscard]] RGBA * pixels() noexcept;
private :
    int m_width=0;
    int m_height=0;
};

#endif
