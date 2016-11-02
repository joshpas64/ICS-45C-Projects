#include <string>
#include <cmath>
//This header files contains the struct Destination which handles the main aspects of a location its
// latitude, longitude, and name
#ifndef DESTINATION_HPP
#define DESTINATION_HPP
struct Destination
{
	double lat; //Latitude and longitude of a location to be used in the haversine formula
	double longt;
	std::string latstring; // Latitude and longitude have a string form for easy output
	std::string longstring;
	std::string name;

};
//These functions are used to initialize a Destination struct's field from user  input and to use those fields
//for finding distances from another destination or to be used for a formatted output
void parseCoordinates(Destination &dest); //Turns string coordinates and converts them into the appropriate numerical values 
										  //for the Destination to use
void makeDestination(Destination &dest, std::string location); //Makes a Destination object from the users input string 

double findDistance(Destination &dest, std::string location); //Finds the distance between a Destination object(starting point) to a
std::string strDestination(Destination &dest); // Makes a unique format to represent a Destination object (Somewhat equivalent of Java's toString method)
#endif