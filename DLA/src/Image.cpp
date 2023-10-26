#include "Image.h"
#include <OpenImageIO/imageio.h>
Image::Image(int _w, int _h) : m_width{_w},m_height{_h}
{
    m_pixels=std::make_unique<RGBA []>(m_width*m_height);
}

Image::Image(int _w, int _h,unsigned char _r, unsigned char _g,
      unsigned char _b, unsigned char _a) : Image(_w,_h)
{
    for(int i=0; i<m_width*m_height; ++i)
    {
        m_pixels[i].set(_r,_g,_b,_a);
    }
}


int Image::width() const noexcept
{
    return m_width;
}


int Image::height() const noexcept
{
    return m_height;
}

RGBA* Image::pixels() noexcept
{
    return m_pixels.get();
}

RGBA Image::getPixel(int _x, int _y) const noexcept
{
    return m_pixels[ (m_width*_y) + _x];
}

void Image::setPixel(int _x, int _y, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
    m_pixels[(m_width*_y) + _x].set(_r,_g,_b,_a);
}

bool Image::save(std::string_view fname) const
{
    using namespace OIIO;
    bool success=false;
    auto out = ImageOutput::create(fname.data());
    if(!out)
    {
        return false;
    }
    ImageSpec spec(m_width,m_height,4,TypeDesc::UINT8);
    success =out->open(fname.data(),spec);
    success=out->write_image(TypeDesc::UINT8,m_pixels.get());
    success=out->close();

    return success;
}