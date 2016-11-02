#include "generalFunctions.hpp"
//These are the general functions used in the context of the main file and have no relation to the other cpp files

int makeSum(int* weights, int length) //This functions takes an integer list and returns the sums of all its items,
/// The length is assumed to be given and it is in the context of the grade reader program
{
	int sum = 0;
	for(int i = 0; i < length; i++)
	{
		sum += weights[i];
	}
	return sum;
}


void mainLoop(void)
// Main function that provides the interface for making a weighted grading rubric and using that rubric 
//    in conjunction with students and scores to provide them with grade results and output it to the 
//    the screen in a formatted manner
{
	int weightInput;
	std::cin >> weightInput; //How many areas are the students being graded in
	std::cin.ignore(1);
	int* relativeWeights = new int[weightInput];
	int* sectionPoints = new int[weightInput];
	inputAssign(sectionPoints,weightInput); //The total point possible for each section
	inputAssign(relativeWeights, weightInput); //The corresponding weight of each graded area
	int weightSum = makeSum(relativeWeights, weightInput); 
	int studentCount; //Number of students to be graded
	std::cin >> studentCount;
	std::cin.ignore(1);
	Student* students = new Student[studentCount];
	for(int i = 0; i < studentCount; i++)
	{
		makeStudent(students[i]); //Make user inputs into corresponding student structs
	}
	int numScores;
	std::cin >> numScores; //How many scores are there to judge
	std::cin.ignore(1);
	for(int i = 0; i < numScores; i++)
	{
		int* scores = new int[weightInput + 1]; //Each score line also has an ID to identify it as belonging to a specific student
		inputAssign(scores,weightInput + 1);
		int searchResult = isAStudent(scores[0],students,studentCount); //Find the student with the corresponding scores
		if(searchResult == -1) //If the scores dont belong to an enrolled student delete them and continue on with the loop
		{
			delete[] scores;
		}
		else
		{
			students[searchResult].totalScore = 100.0 * sumScores(sectionPoints, relativeWeights,scores, weightSum,weightInput); 
			//Use scores and weights to create a weighted total
			delete[] scores;
		}

	}
	delete[] relativeWeights;
	delete[] sectionPoints;
	//Remove unneeded pointers
	//Only thing needed are the students themselves since we have now updated them with their score
	std::cout << "TOTAL SCORES" << std::endl;
	for(int i = 0; i < studentCount; i++)
		outputStudent(students[i]);
	//FOrmatted output of a student
	//Closest equivalent to cout operator overload or java.toString() method for a struct
	int cutpointCount; //Number of cutpoints
	std::cin >> cutpointCount;
	std::cin.ignore(1);
	for(int i = 1; i < cutpointCount + 1; i++)
	{
		outputCutpoint(i,students,studentCount); //Calculate grades and output them to the screen for each cutpoint set
	}
	delete[] students;
	//Remove unneeded heap memory
}