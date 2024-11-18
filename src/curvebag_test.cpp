#include <iostream>
#include <vector>
#include "Curve.h"
#include "CurveBag.h"
#include "regression.h"

using namespace std;

int main()
{
    CurveBag cb(400);
    Regressor ash(0.001, 50, 10);
    //ash.randomizeCoeffs();
    double scale = 0.2;
    double data_len = 200;
    cb.new_curve(data_len*scale, Curve::enSINE, 3, 0.5f);
    cb.new_curve(data_len, Curve::enEmpty);
    cb.gen_frame();
    //cb.gen_frame();
    //cb.gen_frame();
    //cb.view_frame(1);
    //cout<<"Matrix.size() = "<< cb.matrix_size() << endl;

    unsigned int total_iterations = 400;
    double prev_err = 1000000;
    for(int j=0; j<total_iterations; j++)
    {
        double min_err = ash.train_on(*cb.get_curve_at(0));
        ash.populateCurve(*cb.get_curve_at(1), scale);
        cb.gen_frame();
        std::cout<<"Iteration "<<j<<": Error = "<<min_err<<std::endl;
        if(min_err < (prev_err-0.1)) 
        {
            prev_err = min_err;
        }
        else //if(min_err >= (prev_err-0.01)) 
        {
            ash.setLearningRate(ash.getLearningRate()*0.95);
        }
        //
    }

    cout<< endl << "Coeffs = ";
    for(int i=0; i< ash.get_model_order(); i++)
    {
        cout<< ash.getCoeff(i) << " ";
    }

    //ash.train_on(*cb.get_curve_at(0));

    //ash.populateCurve(*cb.get_curve_at(1));

    cb.gen_frame();
    cb.gen_gif();
    std::cout<<"Done!"<<std::endl;

    return 0;
}