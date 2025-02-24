#include <iostream>
#include <vector>
#include "Curve.h"
#include "CurveBag.h"
#include "regression.h"

using namespace std;

int main()
{
    int number_of_frames = 300;
    
    Regressor ash(0.1, 80, 4);
    //ash.randomizeCoeffs();
    unsigned int data_len = 40;
    
    double st_line[data_len];
    for(int i=0; i<data_len; i++)
    {
        st_line[i] = i;
    }


    CurveBag cb(number_of_frames, -1,40);
    //cb.new_curve(data_len, Curve::enSINE, 1, 0.0);
    cb.new_curve(data_len, Curve::enCustom, 1, 0.0, st_line);
    cb.new_curve(data_len, Curve::enEmpty);
    //cb.gen_frame();
    //cb.gen_frame();
    //cb.gen_frame();
    //cb.view_frame(1);
    //cout<<"Matrix.size() = "<< cb.matrix_size() << endl;

    unsigned int total_iterations = number_of_frames;
    double prev_err = 1000000;
    for(int j=0; j<total_iterations; j++)
    {
        double min_err = ash.train_on(*cb.get_curve_at(0));
        ash.populateCurve(*cb.get_curve_at(1));
        cb.gen_frame();
        if(j%2==0)
        {
            std::cout<<"Iteration "<<j<<": Error = "<<min_err<<"  Learning Rate = "<<ash.getLearningRate()<<std::endl;
        }
        if(min_err < (prev_err-0.0001)) 
        {
            prev_err = min_err;
        }
        else //if(min_err >= (prev_err-0.01)) 
        {
            ash.setLearningRate(ash.getLearningRate()*0.8);
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