#include <data.h>
#include <iostream>
#include <iomanip>

#include <model.h>
#include <trainer.h>


void test1();
void test2();

int main()
{
    test2();
    return 0;
}

void test1()
{
    std::cout << std::setprecision(3) << std::fixed;
    dataGen d(100, dataGen::enSINE, nullptr);
    std::cout<<std::endl;
    std::cout<<"\nwithout noise:";
    for(int i=0; i<d.len(); i++) std::cout << d[i] << " ";
    d.addNoise(0.5);
    std::cout<<"\n\nwith noise:";
    for(int i=0; i<d.len(); i++) std::cout << d[i] << " ";
    std::cout<<std::endl;
    std::cout<<std::endl;
    dataGen d2(100, dataGen::enSINE, nullptr);
    //std::cout<< "Error = " << d-d2 << std::endl;
}

void test2()
{
    dataGen sine_actual(20, dataGen::enSINE, nullptr);
    dataGen sine_noisy(20, dataGen::enSINE, nullptr);
    sine_noisy.addNoise(0.1);

    trainer ash(0.0001, &sine_actual, 5);

    sine_noisy.show("sine actual=");
    ash.show();
    ash.train(10);
    ash.show();
}