#include <iostream>
#include "SingleNeuron.h"
#include <cstdlib>
#include <ctime>

//---------------------------
//  AND GATE
//---------------------------

using namespace std;

int trainSize=2000;

double relu(double x)
{
    return x > 0 ? x : 0;
}

typedef struct
{
    double input1;
    double input2;
    double output;
    double gndTruths;
} data_t;

typedef struct
{
    double w1;
    double w2;
    double bias;
    double learning_rate;
} neuron_t;

double forward(data_t* data, neuron_t* neuron)
{
    double output = (data->input1 * neuron->w1) + (data->input2 * neuron->w2) + (neuron->bias);
    if(output<0.0001 && output>-0.0001) output = 0;
    return relu(output);
}

int main()
{
    srand(time(0));
    double m=0.0;
    double c=0.0;

    neuron_t neuron = 
    {
        .w1 = 0.0,
        .w2 = 0.0,
        .bias = 0.0,
        .learning_rate = 0.001
    
    };

    data_t* train_data = new data_t[trainSize];
    data_t* test_data  = new data_t[trainSize];

    // keep looping

    double errors = 1;
    double iter=0;

    while(errors>0)
    {
        // Fill up 
        errors = 0;
        cout<<"Iteration "<<iter++;
        for(int i=0; i<trainSize; i++)
        {
            train_data[i].input1 = rand()%2;
            train_data[i].input2 = rand()%2;
            train_data[i].gndTruths = train_data[i].input1 || train_data[i].input2;
            //cout<<"train data = " << train_data[i].input1 << " " << train_data[i].input2 << " " << train_data[i].gndTruths << endl;

            test_data[i].input1 = rand()%2;
            test_data[i].input2 = rand()%2;
            test_data[i].gndTruths = test_data[i].input1 || test_data[i].input2;
            //cout<<"test data = " << test_data[i].input1 << " " << test_data[i].input2 << " " << test_data[i].gndTruths << endl;
        }
        //

        for(int i=0; i<trainSize; i++)
        {
            double output = forward(&train_data[i], &neuron);
            double err = train_data[i].gndTruths - output;
            //cout<<"Error = " << error << endl;

            neuron.w1 += err * neuron.learning_rate;// * train_data[i].input1;
            neuron.w2 += err * neuron.learning_rate;// * train_data[i].input2;
            neuron.bias += err * neuron.learning_rate;

            if(err<=0.001 && err>=-0.001)
            {
                //cout<<"Training complete" << endl;
                break;
            }
        }

        errors=0;
        for(int i=0; i<trainSize; i++)
        {
            double output = forward(&test_data[i], &neuron)? 1:0;
            errors += (output!=test_data[i].gndTruths)? 1:0;
            //if(iter>15000) cout<< "dbug:\tw1="<<neuron.w1<<"\tw2="<<neuron.w2<< "\tbias="<<neuron.bias<<"\ta="<<test_data[i].input1<<" b="<<test_data[i].input2<<" output="<<output<<" gndTruth="<<test_data[i].gndTruths<<" error="<< (output!=test_data[i].gndTruths) <<endl; 
        }

        cout<<"\tw1="<<neuron.w1<<"\tw2="<<neuron.w2<< "\tbias="<<neuron.bias<<"\tErrors= " << errors << endl;
    }
    

    delete[] train_data;
    delete[] test_data;
}