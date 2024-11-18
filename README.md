# SingleNeuron
Started as a neural network using a single neuron but has now extended to explore classical statistical based ML.
- Currently focusing on linear regression.

# Curve Fitting Outputs:
## Fitting a curve of order 1 to a line.
![Demo of the application: line  Fitting](README_assets/order_1_incline_regression.gif)

## Fitting a curve of order 4 to a sine wave.
![Demo of the application: Sine Curve Fitting](README_assets/order_4_sine_regression.gif)



# How To Build
- Prereqs include gnuplot, gnuplot-cpp library (in extrlibs folder), cmake, gcc or clang compiler.
- Clone this repository and switch to model_selection branch.
- make and goto build folder.
- run cmd 'cmake ..'
- If it goes all correct, then you can build the the application using the command ' cmake --build . --target model_selection'
- run the application to make the gif.

# FAQ
1. gnuplot-cpp library not found?
 - If the folder extrlibs/ or extrlibs/gnuplot-cpp is empty, add the library using the cmd 'git submodule add https://github.com/martinruenz/gnuplot-cpp.git extrlibs/gnuplot-cpp'

