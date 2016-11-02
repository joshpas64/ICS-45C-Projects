

#ifndef PROCESSSCORE_HPP
#define PROCESSSCORE_HPP

#include <iostream>
//Declaration of main calculation functions of the grading program 
// see processScore.cpp for more details on each function
double sumScores(int* sectionPoints, int* relativeWeights, 
			int* scores, int weightSum,int weightLength);
std::string makeGrade(double score, double* cutpoints, char option);

#endif
