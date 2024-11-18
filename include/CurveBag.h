#ifndef __INCLUDED_CURVEBAG_H__
#define __INCLUDED_CURVEBAG_H__

#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>
#include "Curve.h"
#include <iomanip>
#include <fstream>
#include <gnuplot.h>

const int block_size=100;

// Given-> num Of curves and len of Data per curve, manage a curve memory

class CurveBag
{
    unsigned int num_of_frames;
    unsigned int bag_sz;
    unsigned int next_curve_idx;
    unsigned int frame_idx;
    //gif stuff
    std::string output_file_path;
    std::string gif_name;
    unsigned int max_X;


    Curve** bag;
    double*** matrix; // 

    void inflate_bag(unsigned int delta_sz)
    {
        Curve** bigger_bag = new Curve*[bag_sz+delta_sz];

        if(bigger_bag == NULL)
        {
            std::cerr << "Couldn't inflate bag further!" << std::endl;
            exit(1);
        }else 
        {
            for(unsigned int i=0; i<bag_sz; i++)
            {
                bigger_bag[i] = bag[i];
            }
            delete[] bag;
            bag = bigger_bag;
            bag_sz += delta_sz;
        }
    }

public:

    CurveBag(unsigned int num_of_frames) :
    num_of_frames(num_of_frames),
    next_curve_idx(0),
    bag_sz(10),
    frame_idx(0),
    max_X(0)
    {
        bag = new Curve*[bag_sz];
        matrix = new double**[num_of_frames];
    }

    ~CurveBag()
    {
        for(unsigned int i=0; i<next_curve_idx; i++)
        {
            delete bag[i];
        }
        delete[] bag;

        for(unsigned int i=0; i<frame_idx; i++)
        {
            for(unsigned int j=0; j<next_curve_idx; j++)
            {
                delete[] matrix[i][j];
            }
            delete[] matrix[i];
        }
    }

    void new_curve(unsigned int len, enum Curve::inputDataType idt, const double amplitude=1, double noise=0.0f, const double* data=nullptr)
    {
        if(frame_idx != 0)
        {
            std::cerr << "Cannot add new curve after frame generation has started!" << std::endl;
        }else 
        {
            if(next_curve_idx >= bag_sz)
            {
                inflate_bag(block_size);
            }
            bag[next_curve_idx] = new Curve(len, idt, amplitude, data);
            if(noise>0)
            {
                bag[next_curve_idx]->addNoise(noise);
            }
            max_X = (max_X>len)? max_X : len;
            next_curve_idx++;
        }
    }

    unsigned int get_bag_sz()
    {
        return bag_sz;
    }

    unsigned int get_current_frame_idx()
    {
        return frame_idx;
    }

    void gen_frame()
    {

        if(frame_idx >= num_of_frames)
        {
            std::cerr << "Cannot generate more frames!" << std::endl;
        }else 
        {
            //if first, x axis and og curves
            if(frame_idx == 0)
            {
                matrix[frame_idx] = new double*[next_curve_idx];
                for(unsigned int i=0; i<next_curve_idx; i++)
                {
                    matrix[frame_idx][i] = new double[bag[i]->len()];
                    for(unsigned int j=0; j<bag[i]->len(); j++)
                    {
                        matrix[frame_idx][i][j] = (double)(j*max_X/bag[i]->len());
                        //std::cout<<matrix[frame_idx][i][j]<<" ";
                    }
                }
                frame_idx++;
                return;
            }

            matrix[frame_idx] = new double*[next_curve_idx];
            for(unsigned int i=0; i<next_curve_idx; i++)
            {
                matrix[frame_idx][i] = new double[bag[i]->len()];
                for(unsigned int j=0; j<bag[i]->len(); j++)
                {
                    matrix[frame_idx][i][j] = (*bag[i])[j];
                    //std::cout<<matrix[frame_idx][i][j]<<" ";
                }
            }
            frame_idx++;
        }
    }

    void view_frame(unsigned int frame_index)
    {
        if(frame_index >= frame_idx)
        {
            std::cerr << "Frame index {" << frame_index << "} out of bounds {" << frame_idx-1 << "}!" << std::endl;
        }else 
        {
            std::cout<< std::setprecision(2);
            std::cout << "Frame " << frame_index << ":" << std::endl;
            for(unsigned int c=0; c<next_curve_idx; c++)
            {
                std::cout<<"Curve "<<c<<": ";
                for(unsigned int j=0; j<bag[c]->len(); j++)
                {
                    std::cout << matrix[frame_index][c][j] << " ";
                }
                std::cout << std::endl;
            }
        }
    }

    Curve* get_curve_at(unsigned int curve_index)
    {
        if(curve_index >= next_curve_idx)
        {
            std::cerr << "Curve index {" << curve_index << "} out of bounds {" << next_curve_idx-1 << "}!" << std::endl;
            return nullptr;
        }else 
        {
            return bag[curve_index];
        }
    }

    void gen_gif()
    {
        using namespace std;

        std::string temp_file_path = "./temp/";
        std::string gif_name = "curvebag.gif";
        const int animationDelay = 300;
       
        for(int c = 0; c<next_curve_idx; c++)
        {
            ofstream curve_file(temp_file_path + "curve_" + to_string(c) + ".dat");
            for(int i=0; i<bag[c]->len(); i++)
            {
                for(int f = 0; f<frame_idx; f++)
                {
                    curve_file << matrix[f][c][i] << " ";
                }
                curve_file << endl;
            }
            curve_file.close();
        }

        std::ofstream gpscript("gpscript.txt");
        gpscript << "set yrange [-4:4]" << std::endl<<
"set terminal gif animate delay 300" << std::endl<<
"set terminal gif animate" << std::endl<<
"set output '" <<gif_name<<"'" << std::endl<<
"filename(n) = sprintf(\"temp/curve_%d.dat\",n)"<< std::endl<<
"do for [f=1:" <<frame_idx <<"] { " << std::endl<<
"plot for [c=0:" << next_curve_idx-1 <<"] filename(c) using 1:f with lines" << std::endl<<
"}";
        gpscript.close();
        GnuplotPipe gp;
        gp.sendLine("load \'gpscript.txt\'");
    }
    
};

#endif // __INCLUDED_CURVEBAG_H__
