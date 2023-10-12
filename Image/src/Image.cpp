#include "Image.h"

Image::Image(int _w, int _h) : m_width{_w},m_height{_h}
{

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
    return nullptr;
}