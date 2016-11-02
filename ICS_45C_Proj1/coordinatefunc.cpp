#include "coordinatefunc.hpp"

std::string getField(std::string location, int field) //Make a string that will later be used as one of the string fields of a destination object
//The spaces will separate the long string into one of the three string variables
//Field == 1 will make return a latitude string of the destination
//Field == 2 will return longitude string
// Field == 3 will return the name
{
	int mark = 0;
	int start = 0;
	int end = -1;
	std::string data;
	for(int i = 0; i < location.length(); i++)
	{
		if(location[i] == ' ')
		{
			mark++;
			start = end + 1; //Start at the index after the space character
			end = i; //ending will be at the space character since substr is noninclusive
		}
		if(mark == field)
		{
			if(field > 2)
			{
				data = location.substr(start,location.length());
				return data; //Since name is last field just take the remainder of the string
			}
			else
			{
				data = location.substr(start, end - start); //Take substring between the spaces
				return data;
			}

		}
	}
}

double getLatitude(std::string latit)
{
	char dir = latit.at(latit.length() - 1 ); //Determine sign by last character
	double lat;
	if (dir == 'S') //South is negative convention
		lat = -1 * std::stod(latit.substr(0,latit.length() - 2));
	else
		lat = std::stod(latit.substr(0,latit.length() - 2));
	return lat;
}

double getLongitude(std::string longit)
{
	double longt; //Determine sign by last character
	char dir = longit.at(longit.length() - 1);
	if (dir == 'E') // East is positive convention
		longt = std::stod(longit.substr(0,longit.length() - 2));
	else
		longt = -1 * std::stod(longit.substr(0,longit.length() - 2));
	return longt;
}