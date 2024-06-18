#ifndef __INCLUDED_SINGLENEURON_H__
#define __INCLUDED_SINGLENEURON_H__

class SingleNeuron
{
    unsigned int inputSize;
    double* weight;
    double bias;

    double ReLU(double x)
    {
        return x > 0 ? x : 0;
    }


public:
    SingleNeuron(unsigned int inputSize) : inputSize(inputSize), bias(0)
    {
        weight  = new double[inputSize];
    }

    double forward(double *inputs);
    void print();
};


#endif // __INCLUDED_SINGLENEURON_H__