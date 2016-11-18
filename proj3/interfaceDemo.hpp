#ifndef INTERFACEDEMO_HPP
#define INTERFACEDEMO_HPP

#include "HashMap.hpp"
//#include "interfaceFunctions.hpp"
#include <iostream>
#include <sstream>

class InterfaceDemo
{
public:
	InterfaceDemo();
	InterfaceDemo(HashFunction hashFunction);
	void run();
private:
	const std::string firstWords[9] = {"CREATE","LOGIN","REMOVE","CLEAR","QUIT","DEBUG","BUCKET","LOAD","MAX"};
	HashMap hm;
	bool debuggable;
	int parseCommand(int start, const std::string &str2, const std::string &str3);
	int readCommand(const std::string &command);
	void setDebug(bool state);
	void addHash(const std::string &key, const std::string &value);
	void checkKey(const std::string &key, const std::string &value) const;
	void clearHashTable();
	void getBuckets() const;
	void getSize() const;
	void removeKey(const std::string &key);
	void getMaxBucket() const;
	void getLoadFactor() const;
};

#endif