#include <data.h>
#include <iostream>
#include <model.h>
#include <fstream>
#include <gnuplot.h>
#include <regression.h>
#include <unistd.h>
#include <iomanip>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

unsigned int data_len=50;
unsigned int total_curves=200;


int main()
{
    dataGen sine_actual(data_len, dataGen::enSINE, 1);
    sine_actual.addNoise(0.8);
    Regressor ash(0.000002,50, 4); //middle argument speeds up the process so gifs are sped up
    

    /*for(int i=0; i<data_len; i++)
    {
        sine_actual._data[i] = 5 + 0.5*i;
        //sine_actual._data[i] *= -1;
    }*/

    //dataGen sine_noisy(data_len, dataGen::enSINE, nullptr);
    //sine_actual.addNoise(0.3);
    std::ofstream signal("./sine_actual.dat");
    //std::ofstream noise("./sine_noisy.dat");
    std::ofstream estimate("./estimate.dat");
    std::ofstream gpscript("./gpscript.txt");
    
    for(int i=0; i<sine_actual.len(); i++)
    {
        signal << i << " " << sine_actual[i];
        //noise  << i << " " << sine_noisy[i];
    }
    signal.close();
    //noise.close();
    //gp.sendLine("replot \"sine_noisy.dat\" with points pointtype 4 pointsize 0.5 title \"sine noisy\"");
    //ash.train_on(sine_actual);

    std::vector<std::vector<double>> matrix;
    matrix.resize(data_len, std::vector<double>(total_curves, 0.0f));

    for(int i=0; i<data_len; i++)
    {
        matrix[i][0] = i;
        matrix[i][1] = sine_actual[i];
    }

    std::cout << std::fixed;
    std::cout << std::setprecision(6);
    double min_err = 0.0f;
    double prev_err = 1000000.0f;

    for(int j=2; j<total_curves; j++)
    {
        for(int i=0; i<data_len; i++)
        {
            matrix[i][j] = ash.predict(i);
        }
        min_err = ash.train_on(sine_actual);
        if(min_err < prev_err)
        {
            prev_err = min_err;
        }else if(min_err == prev_err) 
        {
            total_curves = j;
            break;
        }
        //std::cout << "\n" << j << ".\tm0 = " << ash.getCoeff(0) << "\tm1 = " << ash.getCoeff(1) << "\tm2 = " << ash.getCoeff(2) << "\tError = " << ash.sqErr(sine_actual);
    }

    std::cout << "\nMin Error = " << min_err;

    matrix.resize(data_len, std::vector<double>(total_curves, 0.0f));

    for(int i=0; i<data_len; i++)
    {
        for(int j=1; j<total_curves; j++)
        {
            estimate << matrix[i][j] << " ";
        }
        estimate << std::endl;
    }

    estimate.close();
    GnuplotPipe gp;

    gpscript << "set yrange [-1:1]" << std::endl<<
                "set terminal gif animate delay 300" << std::endl<<
                "set terminal gif animate" << std::endl<<
                "set output 'animation.gif'" << std::endl<<
                "do for [i=2:" <<total_curves-1 <<"] { \
                    plot 'estimate.dat' using 0:i with points, 'estimate.dat' using 0:1 with lines title 'sine actual' \
                }" ;
    gpscript.close();
    gp.sendLine("load \'gpscript.txt\'");
    return 0;
}