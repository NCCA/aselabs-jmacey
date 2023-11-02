#include <iostream>
#include <chrono>
#include "Emitter.h"
#include <fmt/format.h>
int main()
{
  std::cout<<"Particle System\n";
  Emitter e(Vec3(0,0,0),200);
  for(int i=0; i<250; ++i)
  {
      //e.draw();
      e.writeGeo(fmt::format("particle.{:04d}.geo",i));
      e.update();
  }
  return EXIT_SUCCESS;
}