#ifndef __INCLUDED_MODEL_H__
#define __INCLUDED_MODEL_H__

#include <cmath>

class model
{
    unsigned int order;
    double *_coeff;
public:
    model(unsigned int order) : order(order)
    {
        _coeff = new double[order+1];
    }

    model(unsigned int order, const double* initializer)
    {
        _coeff = new double[order+1];
        for(int i=0; i<=order; i++)
        {
            _coeff[i] = initializer[i];
        }
    }

    model(const model& src)
    {
        order = src.order;
        _coeff = new double[order+1];
        for(int i=0; i<=order; i++)
        {
            _coeff[i] = src._coeff[i];
        }
    }

    ~model()
    {
        delete[] _coeff;
    }

    unsigned int getOrder() { return order;}

    double operator[](int x)
    {
        double sum=0.0f;
        for(int i=0; i<=order; i++)
        {
            sum+= _coeff[i]*pow(x, i);
        }
        return sum;
    }

    double getCoeff(int index)
    {
        return _coeff[index];
    }

    void updateCoeff(const unsigned int index, const double weight)
    {

        if(index <= order)
        {
            _coeff[index] += weight;
        }
    }

    void replaceCoeff(const unsigned int index, const double weight)
    {
        if(index < order) 
            _coeff[index] = weight;
    }

    double peek_val_at(const unsigned int peeking_order, double weight, double x)
    {
        double sum = 0.0f;
        for(int i=0; i<=order; i++)
        {
            if(i==peeking_order) sum+= weight*pow(x, i);
            else sum+= _coeff[i]*pow(x, i);
        }
        return sum;
    }

    void showCoeffs()
    {
        std::cout << "Model = ";
        for(int i=0; i<=order; i++)
        {
            std::cout << _coeff[i] << " ";
        }
        std::cout<<std::endl;
    }

    double Erms(dataGen& d)
    {
        double error = 0.0f;
        for(int i=0; i<d.len(); i++)
        {
            error += pow((*this)[i]-d[i], 2);
        }
        return sqrt(error/d.len());
    }
    
    void copyWeightsFrom(const model& src)
    {
        if(order != src.order)
        {
            delete[] _coeff;
            order = src.order;
            _coeff = new double[order+1];
        }
        
        for(int i=0; i<=order; i++)
        {
            _coeff[i] = src._coeff[i];
        }
    }
};

#endif // __INCLUDED_MODEL_H__