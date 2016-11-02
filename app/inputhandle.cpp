#include "inputhandle.hpp"

void inputAssign(int* fieldInputs, int length) //This method takes an a line of user inputs and makes each entered number
// a corresponding index in the fieldInputs list. The resultant list contains only integers
{
	std::stringstream stream;
	std::string tempString;
	std::getline(std::cin, tempString);
	stream << tempString;
	for(int i = 0; i < length; i++)
	{
		stream >> *(fieldInputs + i);
	}
	stream.clear(); //Possible Delete?
	stream.str("");
}

void inputAssign(double* fieldInputs, int length)
// Logically equivalent to the above inputAssign but creates a list of doubles rather than integers
{
	std::stringstream stream;
	std::string tempString;
	std::getline(std::cin, tempString);
	stream << tempString;
	for(int i = 0; i < length; i++)
	{
		stream >> *(fieldInputs + i);
	}
	stream.clear();
	stream.str("");

}

void outputCutpoint(int n,Student* students, int length)
//Second half of the main program
// Creates list of doubles from user input and uses the scores from each student in the studentlist
// and outputs their grade
// Also identifies itself as which cutpoint set it is in the sequence
{
	double* cutpoints = new double[4];
	inputAssign(cutpoints,4);
	std::cout << "CUTPOINT SET " << n << std::endl;
	for(int i = 0; i < length ; i++)
	{
		std::cout << students[i].id << " " << students[i].option << " " << students[i].name << " " 
		 << makeGrade(students[i].totalScore,cutpoints,students[i].option) << std::endl;
	}
	delete[] cutpoints;
}