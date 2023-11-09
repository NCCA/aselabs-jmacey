#include <iostream>
#include <chrono>
#include "Emitter.h"
#include <fmt/format.h>
#include <filesystem>
int main()
{
  namespace fs=std::filesystem;
  fs::create_directories("/transfer/particles/");
  std::cout<<"Particle System\n";
  Emitter e(Vec3(0,0,0),20000);

  for(int i=0; i<1000; ++i)
  {
      //e.draw();
      e.writeGeo(fmt::format("/transfer/particles/particle.{:04d}.geo",i));
      e.update();
  }
  return EXIT_SUCCESS;
}