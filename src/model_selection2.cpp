#include <Curve.h>
#include <iostream>
#include <model.h>
#include <fstream>
#include <gnuplot.h>
#include <regression.h>
#include <unistd.h>
#include <iomanip>
#include "gifGen.h"
#include "DataBox.h"

unsigned int data_len=50;
unsigned int num_of_curves=2;


int main()
{
    DataBox db(50, num_of_curves);
    db.newCurve(0, data_len/2, Curve::enSINE, 1);
    db.newCurve(1, data_len, Curve::enCustom, 1);

    Curve* sine    = db.getCurveAtIdx(0);
    Curve* myCurve = db.getCurveAtIdx(1);

    Regressor ash(0.000002, 50, 4); //middle argument speeds up the process so gifs are sped up

    std::cout << std::fixed;
    std::cout << std::setprecision(6);
    double min_err = 0.0f;
    double prev_err = 1000000.0f;

    int total_iterations = 100;



    for(int j=2; j<total_iterations; j++)
    {
        min_err = ash.train_on(*sine);
        //
        ash.populateCurve(*myCurve);
        db.genFrameData();
        //
        if(min_err < prev_err) 
        {
            prev_err = min_err;
        }
        else if(min_err == prev_err) 
        {
            total_iterations = j;
            break;
        }
    }

    db.generateGif(db.getFrameIndex());

    std::cout << "\nMin Error = " << min_err << "\ntotal iterations = " << total_iterations << "\n\n";
    return 0;
}