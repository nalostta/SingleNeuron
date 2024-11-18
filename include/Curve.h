#ifndef __INCLUDED_CURVE_H__
#define __INCLUDED_CURVE_H__

#include <cstdlib>
#include <iostream>
#include <cmath>

const double _PI = 3.14159f;
const double _2PI = 2.0f*_PI;
const int noise_resolution = 100;

class Curve 
{
public:
    double* _data;
    enum inputDataType{ enSINE, enCustom, enEmpty };
    unsigned int _len;
    friend class Regressor;

    Curve(unsigned int len, enum inputDataType idt, const double amplitude=1, const double* data=nullptr)
    {
        // Generate data
        if(len>0)
        {
            _len = len;
            _data = new double[len];
            switch(idt)
            {
                case enSINE:
                    
                    for(int i=0; i<_len; i++) 
                    {
                        double _rad = _2PI*i/len;
                        _data[i] = amplitude*sin(_rad); 
                    }
                    break;
                case enCustom:
                    if(data!=NULL)
                    {
                        for(int i=0; i<_len; i++) _data[i] = data[i];
                    }

                case enEmpty:
                    break;
                default:
                    break;
            }
        }
    }

    ~Curve()
    {
        delete[] _data;
    }

    void addNoise(double maxNoise)
    {
        for(int i=0; i<_len; i++) _data[i] += (maxNoise*(rand()%100)/100)-(maxNoise/2);
    }

    int len()
    {
        return _len;
    }

    double operator[](int index)
    {
        return _data[index];
    }

    void replace(double data, unsigned int index)
    {
        if(index<_len) _data[index] = data;
    }

    void show(std::string text)
    {
        std::cout << text << std::endl;
        for(int i=0; i<_len; i++) std::cout << _data[i] << " ";
        std::cout << std::endl;
    }

    double sqErr(Curve& ref)
    {
        double sum = 0.0f;
        for(int i=0; i<_len; i++) sum += (_data[i]-ref[i])*(_data[i]-ref[i]);
        return sum;
    }

};

#endif // __INCLUDED_CURVE_H__
