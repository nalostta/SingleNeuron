#ifndef __INCLUDED_TRAINER_H__
#define __INCLUDED_TRAINER_H__

#include <data.h>
#include <model.h>

// Include any necessary headers here
// Declare any classes or functions here
class trainer
{
    double learning_rate;
    double numOfIterations;
    //dataGen& input;
    dataGen* _train_data;
    model *m;
public:
    trainer(double learning_rate, dataGen* train_data, const unsigned int model_order) : 
        learning_rate(learning_rate) 
    {
        //this->input = input;
        _train_data = train_data;
        m = new model(model_order);
    }
    ~trainer() {}

    void train(const unsigned long numOfIterations)
    {
        for(int i=0; i<numOfIterations; i++)
        {
            show();
        }
            
    }

    void show()
    {
        std::cout<< "\nmodel =";
        for(int i=0; i<=m->getOrder(); i++)
        {
            std::cout<<"\t"<<m->getCoeff(i)<<"x^"<<i;
        }
        std::cout<<std::endl;
    }

};

#endif // __INCLUDED_TRAINER_H__
