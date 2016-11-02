#include "Destination.hpp"


double findDistance(Destination &dest, std::string location)
{
	double RADIUS = 3959.9;
	double dlat, dlong, a, c, dist;
	double lat2 = getLatitude(getField(location,1)); //Make latitude number from location string without needing reserve memory for a struct
	double long2 = getLongitude(getField(location,2)); //Make longitude number from location string without needing reserve memory for a struct
	dlat = dest.lat - lat2; //Latitude difference between locations
	dlong = dest.longt - long2; //Longitude difference between locations
	a = ((sin(toRadians(dlat/2.0)))*(sin(toRadians(dlat/2.0)))) + (cos(toRadians(dest.lat))*cos(toRadians(lat2)) //haversine formula
		*sin(toRadians(dlong/2.0))*sin(toRadians(dlong/2.0))); //Cmaths trig functions use radians so the coordinates must be converted to radians to be used
	c = 2 * atan2(sqrt(a),sqrt(1-a));
	dist = RADIUS * c; //Radius is radius of the Earth
	return dist;
}

std::string strDestination(Destination &dest)
{
	std::string prtString;
	prtString = dest.latstring + " " + dest.longstring + " (" + dest.name + ")"; //String representation of a Destination to be used for output
	return prtString;
}

void parseCoordinates(Destination &dest) //Set the destinations latitude and longitude numerical fields from their string representations
{
	dest.lat = getLatitude(dest.latstring);	
	dest.longt = getLongitude(dest.longstring);
}