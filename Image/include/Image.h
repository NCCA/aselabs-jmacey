#ifndef IMAGE_H_
#define IMAGE_H_
#include "RGBA.h"
class Image
{
public :
 [[nodiscard]] int width() const noexcept ;
 [[nodiscard]] int height() const noexcept ;
 [[nodiscard]] RGBA * pixels() noexcept;
private :

};

#endif
