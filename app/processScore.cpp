#include "processScore.hpp"

std::string makeGrade(double score, double* cutpoints, char option)
//Uses a given score, a set of cutpoints, and a grading option to determine the student's grade
{
	std::string letters = "ABCDF";
	std::string grade;
	for(int i = 0; i < 5; i++)
	{
		if(i == 4)
		{
			grade = letters.substr(4,1);
			break;
		}
		if(score >= cutpoints[i])
		{
			grade = letters.substr(i,1);
			break;
		}
	}
	if(option == 'P')
	{
		if((grade == "D") || (grade == "F"))
			grade = "NP";
		else
			grade = "P";
	}
	return grade;
}

double sumScores(int* sectionPoints, int* relativeWeights, int* scores, int weightSum,int weightLength)
//Take a set of scores and makes a weighted score based on the point totals and grading weight for each category
{
	double sum = 0;
	for (int i = 1; i < weightLength + 1; i++)
	{
		sum = sum + ((((double) (scores[i]) / sectionPoints[i - 1] ) * (relativeWeights[i - 1])) / ((double) weightSum));
	}
	return sum;
}