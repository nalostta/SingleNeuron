// This file defines classes and data structures to describe input data for regression.
// Include necessary headers here
#include <data.h>
#include <cstdlib>

class dataGen
{
    typedef enum
    {
        enSINE;
    }inputDataType;

    double* data;
public:
    dataGen(int size, enum inputDataType)
    {
        // Generate data
        if(size>0)
        {
            data = new double[size];
            switch(inputDataType)
            {
                case enSINE:
                    for(int i=0; i<size; i++) data[i] = sin(i);
                    break;
                default:
                    break;
            }
        }
    }

    ~dataGen()
    {
        delete[] data;
    }

    void addNoise(double maxNoise)
    {
        maxNoise = maxNoise/2;
        for(int i=0; i<size; i++) data[i] += (rand()%maxNoise)-maxNoise;
    }
}
