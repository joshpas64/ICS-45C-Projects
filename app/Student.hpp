#include <iostream>
#include <string>
#include <sstream>

#ifndef STUDENT_HPP
#define STUDENT_HPP
//Declares the student objects and the functions that make use of them in the main program
// See Student.cpp for more function detail
struct Student
// Students have four fields relative to them:
// Name for output 
// Id to match them with a line of scores
// Their total score which will be used with a cutpoint to give them their grade
// Their grading option
{
	std::string name;
	int id;
	double totalScore;
	char option;
};

void makeStudent(Student &student); //Student function
int isAStudent(int id, Student* students,int length); //Student Function
void outputStudent(const Student &student); //Student Function

#endif