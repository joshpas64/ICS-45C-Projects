#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <iostream>
#include <sstream>
#include "HashMap.hpp"

class Interface
{
	private:
		HashMap hm; //HashMap that user interacts with
		std::string firstWords[9] = {"CREATE","LOGIN","REMOVE","CLEAR","QUIT","DEBUG","BUCKET","LOAD","MAX"}; //Array of first words used to parse commands
		bool debuggable;//Debuggable state determines how many commands the user has access to
	public:
		Interface(); //Default constructor
		Interface(HashFunction hashFunction); //If want to test with specific hashFunction
		void run(); //Starts and runs interface until user chooses to quit
		int readCommand(const std::string &command); //Parses the users line of input and sees which command to execute, if any
		void setDebug(bool state); //Changes debug state, and hence, access to certain commands
		void addHash(const std::string &key, const std::string &value); //Adds a key value pair to the HashMap user interacts with
		void checkKey(const std::string &key, const std::string &value) const; //Checks the validity of a key, value pair in the HashMap
		//A wrong value will be considered the same as a nonexistent key
		void clearHashTable(); //Clears all key,value pairs in the Hashtable
		void getBuckets() const; //Gets number of buckets, DEBUG must be on to access
		void getSize() const; //Get number of key,value pairs DEBUG must be ON to access
		void removeKey(const std::string &key); //Removes a key from the hashMap
		void getMaxBucket() const; //Gets the size of the largest bucket in HashMap, DEBUG must be ON to access
		void getLoadFactor() const;//Get current Load Factor in HashMap, DEBUG must ON to access
};

#endif
