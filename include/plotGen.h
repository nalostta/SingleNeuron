#ifndef __INCLUDED_PLOTGEN_H__
#define __INCLUDED_PLOTGEN_H__

#include <fstream>
#include <string>
#include <iostream>

class plotGen
{
    unsigned int numOfframes;
    unsigned int numOfCurves;
    ofstream plotFile;
    std::string tempFilePath;
    std::string outputPath;
}

#endif // __INCLUDED_PLOTGEN_H__