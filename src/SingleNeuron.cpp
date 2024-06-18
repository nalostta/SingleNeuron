#include "SingleNeuron.h"
#include <iostream>

double SingleNeuron::forward(double *inputs)
{
    double sum = 0;
    for (int i = 0; i < inputSize; i++)
    {
        sum += inputs[i] * weight[i];
    }
    return ReLU(sum + bias);
}

void SingleNeuron::print()
{
    std::cout << "Weights: ";
    for (int i = 0; i < inputSize; i++)
    {
        std::cout << weight[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Bias: " << bias << std::endl;
}