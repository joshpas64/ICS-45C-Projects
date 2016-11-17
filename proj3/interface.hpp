#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <iostream>
#include <sstream>
#include "HashMap.hpp"

class Interface
{
	private:
		HashMap hm;
		std::string firstWords[9] = {"CREATE","LOGIN","REMOVE","CLEAR","QUIT","DEBUG","BUCKET","LOAD","MAX"};
		bool debuggable;
	public:
		Interface();
		Interface(HashFunction hashFunction);
		void run();
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