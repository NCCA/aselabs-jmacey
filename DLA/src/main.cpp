#include <iostream>
#include <cstdlib>
#include "Walker.h"
#include <fmt/format.h>


int main()
{
    std::cout<<"DLA \n";
    Walker w(400,400);
    w.randomSeeds(50);
    int frameNumber=0;
    for(int i=0; i<10000; ++i)
    {
        if(w.walk() )
        {
            w.save(fmt::format("DLA.{:04d}.jpg",frameNumber++));
        }
        w.resetStart();
    }
    //w.save("test.bmp");
    return EXIT_SUCCESS;
}