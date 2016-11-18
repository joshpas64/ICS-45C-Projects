#ifndef INTERFACEDEMO_HPP
#define INTERFACEDEMO_HPP

#include "HashMap.hpp"
#include <iostream>
#include <sstream>
// Iostream and sstream are needed to display the program and easily parse spaced words as commands

class InterfaceDemo
{
public:
	InterfaceDemo(); //Initializes the interface 
	InterfaceDemo(HashFunction hashFunction);
	void run(); //This runs the main interface continuously until the users chooses to QUIT
private:
	//Beginning are private member variables 
	const std::string firstWords[9] = {"CREATE","LOGIN","REMOVE","CLEAR","QUIT","DEBUG","BUCKET","LOAD","MAX"};
	//Above is an array of words that can be used to figure out what command the user may want to execute
	HashMap hm; //HashMap that user interacts with
	bool debuggable; //Determines Access to certain commands by the user
	//Begins private methods used by run() or the methods it calls
	int parseCommand(int start, const std::string &str2, const std::string &str3);
	//If the first is a valid word (in firstWords) meaning it could be one of the 11 possible commands, this method
	// will check the rest of the user input and determine if it is valid and execute accordingly
	int readCommand(const std::string &command); //Takes the line of user input and determinesby first word if it could
	// even be valid
	void setDebug(bool state); //Change access to debug methods that reveal details of the HashMap
	void addHash(const std::string &key, const std::string &value); //Add key,value to HashMap
	void checkKey(const std::string &key, const std::string &value) const; //Make Login attempt to HashMap
	void clearHashTable(); //Reset HashMap to an empty HashMap deleting all data it previously held
	void getBuckets() const; //Get Bucket count or number of linked lists
	void getSize() const; // Get number of key,value pairs
	void removeKey(const std::string &key); //Remove a key,value pair
	void getMaxBucket() const; //Get length of largest linked list
	void getLoadFactor() const; //Get load factor
};
#endif
