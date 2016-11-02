#include "generalfunc.hpp"


double toRadians(double deg)
{
	double pi = 3.1459265;
	double radians = pi * (deg/180.0); //Converts lat and long coordinates (in degrees) to be used in the trig function in the haversine  formula
	return radians;
}

void distanceloop(void)
{
	Destination start, far, close; //The three locations we need that will be outputted in the end
	std::string farthest, shortest, current; //String variables that will store the farthest and shortest location string so far while the user is still inputting
											// current is user's input string
	int counter;	//Number of locations to calculate distance from
	double distance; //distance used for output
	double max = 0; // The current maximum and minimum distances
	double min = 0;
	std::getline(std::cin,current);
	makeDestination(start,current); //Make a Destination object from the user input to be used as reference for calculating distance
	std::cin >> counter;
	std::cin.ignore(1); //Discard the newline character
	for(int i = 0; i < counter; i++)
	{
		std::getline(std::cin,current); //Make current location string from input and find its distance from the starting location
		distance = findDistance(start, current); 
		if(min == 0)
		{
			min = distance;
			shortest = current;
		}
		if(distance > max) //If farther than the current max distance make this instance of current the farthest location string
		{
			max = distance;
			farthest = current;
		}
		if(distance < min) //If closer than the current minimum distance make this instance of current the closest location string
		{
			min = distance;
			shortest = current;
		}
	}
	makeDestination(far, farthest); //Make farthest string a destination object for easier output below
	makeDestination(close, shortest); // Make closest string a destination object for easier output below
	std::cout << "Starting Location: " << strDestination(start) << std::endl; //Destination can be outputted quickly and easily (without calling all its fields)
																				// since it can be shown as a string that the terminal can easily output
	std::cout << "Closest Location: " << strDestination(close) << " (" << min << "miles)" << std::endl; //Display destination and its distance
	std::cout << "Farthest Location: " << strDestination(far) << " (" << max << "miles)" << std::endl;
}
