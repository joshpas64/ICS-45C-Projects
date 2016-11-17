#include "interface.hpp"

Interface::Interface()
{
	hm = HashMap();
	debuggable = false;
}

Interface::Interface(HashFunction hashFunction)
{
	hm = HashMap(hashFunction);
	debuggable = false;
}

void Interface::run()
{
	int cont = 0;
	std::string command;
	do
	{
		std::getline(std::cin,command);
		cont = readCommand(command);
	}
	while(cont != -1);
	std::cout << "GOODBYE" << std::endl;
}

int Interface::readCommand(const std::string &command)
{
	std::stringstream stream;
	std::string first = "";
	std::string second = "";
	std::string third = "";
	std::string fourth = "";
	stream << command;
	stream >> first;
	stream >> second;
	stream >> third;
	stream >> fourth;
	if(fourth.compare("") != 0)
	{
		std::cout << "INVALID" << std::endl;
		return 0;
	}
	int result = -1;
	for(int i = 0; i < 9; i++)
	{
		if(first.compare(firstWords[i]) == 0)
		{
			result = i;
			break;
		}
	}
	if(second.compare("COUNT") == 0 && third.compare("") == 0)
	{
		if(result == 1)
			getSize();
		else if(result == 6)
			getBuckets();
	}
	else if(result == -1)
	{
		std::cout << "INVALID" << std::endl;
		return 0;
	}
	else if(second.compare("") != 0 && third.compare("") != 0)
	{
		if(result == 1)
			checkKey(second,third);
		if(result == 0)
			addHash(second,third);
	}
	else if(result == 2 && third.compare("") == 0)
	{
		removeKey(second);
	}
	else if(third.compare("") == 0 && second.compare("") == 0)
	{
		if(result == 3)
		{
			clearHashTable();
		}
		if(result == 4)
			return -1;
	}
	else if(first.compare("DEBUG") == 0 && third.compare("") == 0)
	{
		if(second.compare("OFF") == 0)
			setDebug(false);
		if(second.compare("ON") == 0)
			setDebug(true);
	}
	else if(third.compare("") == 0 && first.compare("LOAD") == 0 && second.compare("FACTOR") == 0)
	{
		getLoadFactor();	
	}
	else if(third.compare("SIZE") && second.compare("BUCKET") == 0 && first.compare("MAX") == 0)
	{
		getMaxBucket();
	}
	else
	{
		std::cout << "INVALID" << std::endl;
	}
	stream.clear();
	stream.str("");
	return 0;
}


void Interface::setDebug(bool state)
{
	if(state == true)
	{
		if(debuggable == true)
			std::cout << "ON ALREADY" << std::endl;
		else
		{
			debuggable = state;
			std::cout << "DEBUG ON" << std::endl;
		}
	}
	else
	{
		if(debuggable == false)
			std::cout << "OFF ALREADY" << std::endl;
		else
		{
			debuggable = state;
			std::cout << "DEBUG OFF" << std::endl;
		}
	}
}

void Interface::getSize() const
{
	if(debuggable == false)
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.size() << std::endl;
}

void Interface::getBuckets() const
{
	if(debuggable == false)
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.bucketCount() << std::endl;
}

void Interface::getMaxBucket() const
{
	if(debuggable == false)
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.maxBucketSize() << std::endl;
}

void Interface::getLoadFactor() const
{
	if(debuggable == false)
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.loadFactor() << std::endl;
}

void Interface::checkKey(const std::string &key, const std::string &value) const
{
	std::string result = "";
	result = hm.value(key);
	if(result.compare(value) == 0)
		std::cout << "SUCCEEDED" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}

void Interface::addHash(const std::string &key, const std::string &value)
{
	unsigned int currentSize = hm.size();
	hm.add(key,value);
	unsigned int newSize = hm.size();
	if(currentSize == newSize)
		std::cout << "EXISTS" << std::endl;
	else
		std::cout << "CREATED" << std::endl;
}

void Interface::removeKey(const std::string &key)
{
	unsigned int currentSize = hm.size();
	hm.remove(key);
	unsigned int newSize = hm.size();
	if(currentSize == newSize)
	{
		std::cout << "NONEXISTENT" << std::endl;
	}
	else
	{
		std::cout << "REMOVED" << std::endl;
	}
}

void Interface::clearHashTable()
{
	hm = HashMap();
}