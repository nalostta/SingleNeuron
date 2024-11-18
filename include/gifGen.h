#ifndef __INCLUDED_PLOTGEN_H__
#define __INCLUDED_PLOTGEN_H__

#include <fstream>
#include <string>
#include <iostream>
#include "Curve.h"
#include <gnuplot.h>

// V1.0 features:
// Given a 2D collection of .dat files, generate a gif of the data 

class gifGen
{
    unsigned int numOfframes;
    unsigned int curvesPerFrame;
    std::ofstream plotFile;
    std::string tempFilePath;
    std::string outputPath;
    unsigned int animationDelay;
    
public:
    gifGen(unsigned int numOfframes, unsigned int _curvesPerFrame, unsigned int animationDelay = 300, std::string outputPath = "./", std::string tempFilePath = "temp") :
    numOfframes(numOfframes),
    curvesPerFrame(_curvesPerFrame),
    outputPath(outputPath),
    tempFilePath(tempFilePath),
    animationDelay(animationDelay)
    {       }

    ~gifGen() {}

    void generateGif(int numOfFrames)
    {
        std::ofstream gpscript("gpscript.txt");

        gpscript << "set yrange [-1:1]" << std::endl <<
"set terminal gif animate delay " << animationDelay << std::endl <<
"set terminal gif animate" << std::endl <<
"set output '"<< outputPath << "output.gif'" << std::endl<<
"do for [i=1:" <<numOfFrames <<"] \
{ \n\
    plot for [j=1:"<< curvesPerFrame << "] '"<< tempFilePath << "fr'i'_crv'" << "j'.frame' using 0:i with lines \n\
}" ;

        gpscript.close();
        GnuplotPipe gp;
        gp.sendLine("load \'gpscript.txt\'");
    }

    std::string getTempFilePath()
    {
        return tempFilePath;
    }
};

#endif // __INCLUDED_PLOTGEN_H__