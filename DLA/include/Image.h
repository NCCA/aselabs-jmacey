#ifndef IMAGE_H_
#define IMAGE_H_
#include "RGBA.h"
#include <memory>
#include <string_view>
class Image
{
public :
    Image()=default;
    Image(int _w, int _h);
    Image(int _w, int _h,unsigned char _r, unsigned char _g,
    unsigned char _b, unsigned char _a=255);
    [[nodiscard]] int width() const noexcept ;
    [[nodiscard]] int height() const noexcept ;
    [[nodiscard]] RGBA * pixels() noexcept;
    [[nodiscard]] RGBA getPixel(int _x, int _y) const noexcept;
    void setPixel(int x, int y, unsigned char _r, unsigned char _g,
                  unsigned char _b, unsigned char _a=255);
    bool save(std::string_view fname) const;
private :
    int m_width=0;
    int m_height=0;
    std::unique_ptr<RGBA []> m_pixels;
};

#endif
