#include "Student.hpp"

void makeStudent(Student &student)
// Takes a stream of input and creates a student object from it
// Uses spaces between data to match it to the corresponding attributes of a student object
{
	std::stringstream stream;
	std::string tempString;
	std::getline(std::cin,tempString);
	stream << tempString;
	stream >> student.id >> student.option;
	std::getline(stream, student.name);
	student.totalScore = 0;
}

int isAStudent(int id, Student* students,int length) // Takes an id and a list of students and determines which index in the list has the corresponding id
// Returns -1 if there were no matches
{
	for(int i = 0; i < length; i++)
	{
		if(id == students[i].id)
			return i;
	}
	return -1;
}

void outputStudent(const Student &student)
// Formal output of a student object
{
	std::cout << student.id << " " << student.option << " " << student.name << " " << student.totalScore << std::endl;
}


