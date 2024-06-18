#ifndef __INCLUDED_REGRESSION_H__
#define __INCLUDED_REGRESSION_H__

#include <data.h>
#include <model.h>

const double bias_learning_rate = 1;

// For a model m, use regression to find the best fit for the data...
class Regressor
{
    double learning_rate;
    double numOfIterations;
    model* m;
public:
    Regressor(double learning_rate, unsigned int _numOfIterations , unsigned int model_order) : 
    learning_rate(learning_rate),
    numOfIterations(_numOfIterations)
    {
        m = new model(model_order);
    }

    ~Regressor() 
    {
        delete m;
    }

    double getCoeff(unsigned int index)
    {
        return m->getCoeff(index);
    }

    double sqErr(dataGen& d)
    {
        double error = 0.0f;
        for(int i=0; i<d.len(); i++)
        {
            error += pow((*m)[i]-d[i], 2);
        }
        return error;
    }

    void updateCoeff(unsigned int coeff_order, double error)
    {
        m->updateCoeff(coeff_order, error);
    }

    double train_on(dataGen& d)
    {
        model m_left  = model(m->getOrder());
        model m_right = model(m->getOrder());
        double minErr=0.0f;
        //std::cout<<"\n[debug] : newFunc()";
        for(int i=0; i<numOfIterations; i++)
        {
            for(int j=0; j<d.len(); j++)
            {
                for(int order = 0; order<=m->getOrder(); order++)
                {
                    double error = (*m)[j] - d[j];
                    double scale = (order>0)? order : bias_learning_rate;

                    // get Erms
                    // get Erms_left
                    // get Erms_right        
                    m_left.copyWeightsFrom(*m);
                    m_left.updateCoeff(order, -scale*error*learning_rate);

                    m_right.copyWeightsFrom(*m); //how to use copy constructor here?
                    m_right.updateCoeff(order, scale*error*learning_rate);

                    double left  = m_left.Erms(d);
                    double right = m_right.Erms(d);
                    double mid   = m->Erms(d);
                    

                    if(left<mid && left<right)
                    {
                        m->updateCoeff(order, -scale*error*learning_rate);
                        minErr = left;
                    }
                    else if(right<mid && right<left)
                    {
                        m->updateCoeff(order, scale*error*learning_rate);
                        minErr = right;
                    }else
                    {
                        minErr = mid;
                    }

                    // find lowest Erms and update the model
                    //std::cout<< "order_index = " << order << " error = "<< error << " ";
                    //m->showCoeffs();                    
                }
            }
        }
        return minErr;
    }

    double predict(double x)
    {
        return (*m)[x];
    }

    /* ---- Upcoming code...
    double train_till_convergence(unsigned int data_len, )
    {
        double min_sqErr = 0.0f;
        double prev_sqErr = 0.0f;

        do
        {
            prev_sqErr = min_sqErr;    
            min_sqErr = ash.train_on(sine_actual);

            if(min_sqErr == prev_sqErr) 
            {
                total_curves = j;
                break;
            }
            //std::cout << "\n" << j << ".\tm0 = " << ash.getCoeff(0) << "\tm1 = " << ash.getCoeff(1) << "\tm2 = " << ash.getCoeff(2) << "\tError = " << ash.sqErr(sine_actual);
        }while(min_sqErr > prev_sqErr);
    }*/
};

#endif // __INCLUDED_REGRESSION_H__
