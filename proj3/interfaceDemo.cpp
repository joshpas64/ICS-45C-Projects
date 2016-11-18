#include "interfaceDemo.hpp"

InterfaceDemo::InterfaceDemo()
{
	hm = HashMap();
	debuggable = false;
}

InterfaceDemo::InterfaceDemo(HashFunction hashFunction)
{
	hm = HashMap(hashFunction);
	debuggable = false;
}

void InterfaceDemo::run()
{
	int cont = 0;
	std::string command;
	do
	{
		std::getline(std::cin,command);
		cont = readCommand(command);
		if(cont == 0)
			std::cout << "INVALID" << std::endl;
	}
	while(cont != -1);
	std::cout << "GOODBYE" << std::endl;
}

int InterfaceDemo::readCommand(const std::string &command) //interpret
{
	std::stringstream stream;
	std::string command1 = "";
	std::string command2 = "";
	std::string command3 = "";
	std::string command4 = "";
	stream << command;
	stream >> command1;
	stream >> command2;
	stream >> command3;
	stream >> command4;
	if(command4.compare("") != 0)
	{
		return 0;
	}
	int result = -1;
	int flag = 0;
	for(int i = 0; i < 9; i++)
	{
		if (command1.compare(firstWords[i]) == 0)
		{
			result = i;
			break;
		}
	}
	if(result == -1)
		return flag;
	if(result == 8 && command2.compare("BUCKET") == 0 && command3.compare("SIZE") == 0)
	{
		flag = 11;
		getMaxBucket();
		return flag;
	}
	switch(result)
	{
		case 0:
			flag = parseCommand(0,command2,command3);
			break;
		case 1:
			flag = parseCommand(1,command2,command3);
			break;
		case 2:
			flag = parseCommand(2,command2,command3);
			break;
		case 3:
			flag = parseCommand(3,command2,command3);
			break;
		case 4:
			flag = parseCommand(4,command2,command3);
			break;
		case 5:
			flag = parseCommand(5,command2,command3);
			break;
		case 6:
			flag = parseCommand(6,command2,command3);
			break;
		case 7:
			flag = parseCommand(7,command2,command3);
			break;
		default:
			break;
	}
	stream.clear();
	stream.str("");
	return flag;
}

int InterfaceDemo::parseCommand(int start, const std::string &str2, const std::string &str3) //Chech valid
{
	if(start == 0)
	{
		if(str3.compare("") != 0 && str2.compare("") != 0)
		{
			addHash(str2,str3);
			return 1;
		}
	}
	if(start == 1)
	{
		if(str2.compare("COUNT") == 0 && str3.compare("") == 0)
		{
			getSize();
			return 6;
		}
		else if(str3.compare("") != 0 && str2.compare("") != 0)
		{
			checkKey(str2,str3);
			return 2;
		}
	}
	if(str3.compare("") == 0)
	{
		if(start == 2)
		{
			removeKey(str2);
			return 3;
		}
		else if(start == 5)
		{
			if(str2.compare("ON") == 0)
			{
				setDebug(true);
				return 7;
			}
			else if(str2.compare("OFF") == 0)
			{
				setDebug(false);
				return 8;
			}
		}
		else if(start == 6 && str2.compare("COUNT") == 0)
		{
			getBuckets();
			return 9;
		}
		else if(start == 7 && str2.compare("FACTOR") == 0)
		{
			getLoadFactor();
			return 10;
		}
	}
	if(str2.compare("") == 0)
	{
		if(start == 3)
		{
			clearHashTable();
			return 4;
		}
		if(start == 4)
			return -1;
	}
	return 0;
}

void InterfaceDemo::setDebug(bool state)
{
	if(state == true)
	{
		if(debuggable == true)
			std::cout << "ON ALREADY" << std::endl;
		else
		{
			debuggable = state;
			std::cout << "ON NOW" << std::endl;
		}
	}
	else
	{
		if(debuggable == false)
			std::cout << "OFF ALREADY" << std::endl;
		else
		{
			debuggable = state;
			std::cout << "OFF NOW" << std::endl;
		}
	}
}

void InterfaceDemo::getSize() const
{
	if(debuggable == false)
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.size() << std::endl;
}

void InterfaceDemo::getBuckets() const
{
	if(debuggable == false)
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.bucketCount() << std::endl;
}

void InterfaceDemo::getMaxBucket() const
{
	if(debuggable == false)
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.maxBucketSize() << std::endl;
}

void InterfaceDemo::getLoadFactor() const
{
	if(debuggable == false)
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.loadFactor() << std::endl;
}

void InterfaceDemo::checkKey(const std::string &key, const std::string &value) const
{
	std::string result = "";
	result = hm.value(key);
	if(result.compare(value) == 0)
		std::cout << "SUCCEEDED" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
}

void InterfaceDemo::addHash(const std::string &key, const std::string &value)
{
	unsigned int currentSize = hm.size();
	hm.add(key,value);
	unsigned int newSize = hm.size();
	if(currentSize == newSize)
		std::cout << "EXISTS" << std::endl;
	else
		std::cout << "CREATED" << std::endl;
}

void InterfaceDemo::removeKey(const std::string &key)
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

void InterfaceDemo::clearHashTable()
{
	hm = HashMap();
}