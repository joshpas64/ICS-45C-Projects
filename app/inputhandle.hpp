#ifndef INPUTHANDLE_HPP
#define INPUTHANDLE_HPP
//main input and output handles for the main program
// See inputhandle.cpp for more detail on each function

#include "processScore.hpp"
#include "Student.hpp"

void inputAssign(int* fieldInputs, int length); //input header file later
void inputAssign(double* fieldInputs, int length);
void outputCutpoint(int n,Student* students, int length);

#endif