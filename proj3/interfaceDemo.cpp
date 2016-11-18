#include "interfaceDemo.hpp"

InterfaceDemo::InterfaceDemo()
{
	hm = HashMap(); // Start with an empty HashMap
	debuggable = false; /// User doesnt have full access by default
}

InterfaceDemo::InterfaceDemo(HashFunction hashFunction)
{
	hm = HashMap(hashFunction); //Start an empty HashMap with chosen HashFunction
	debuggable = false;
}

void InterfaceDemo::run()
{
	int cont = 0; //Continue flag
	std::string command; //User Input
	do
	{
		std::getline(std::cin,command); //Get commands
		cont = readCommand(command); //Interpret commands
		if(cont == 0) //A flag of 0 means none of what the user entered fit any of the 11 possible commands
			std::cout << "INVALID" << std::endl;
	}
	while(cont != -1); //When the user enters quit readCommand return -1 ending the interface runthrough
	std::cout << "GOODBYE" << std::endl;
}

int InterfaceDemo::readCommand(const std::string &command) //interpret
{
	std::stringstream stream; //Used to separate line of words into separate words where each word can be assigned to a 
	//    variable
	// The most words a user can enter are 3
	std::string command1 = "";
	std::string command2 = "";
	std::string command3 = "";
	std::string command4 = "";
	stream << command;
	stream >> command1;
	stream >> command2;
	stream >> command3;
	stream >> command4;
	if(command4.compare("") != 0) //If there was a fourth word or more command4 would not equal "" making the input invalid
	{
		return 0;
	}
	int result = -1;
	int flag = 0; //Default INVALID
	for(int i = 0; i < 9; i++)
	{
		if (command1.compare(firstWords[i]) == 0)
		{
			result = i;
			break;
		}
	}
	if(result == -1) //If the first word was not any of the possible first word of any of the 11 commands, automatically invalid
		return flag;
	if(result == 8 && command2.compare("BUCKET") == 0 && command3.compare("SIZE") == 0) //If command was MAX BUCKET SIZE
	{
		flag = 11; //Give positive flag so the interface does NOT output invalid
		getMaxBucket(); //Execute the method
		return flag;
	}
	switch(result) //Other cases
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
	return flag; //If the user input was valid then parseCommand will return a value >0
}

int InterfaceDemo::parseCommand(int start, const std::string &str2, const std::string &str3) //Chech validity
{
	if(start == 0) //IF create
	{
		if(str3.compare("") != 0 && str2.compare("") != 0) //Make sure there are two other words
		{
			addHash(str2,str3); //Create or attempt to create a key,value pair
			return 1; //Return a positive flag
		}
	}
	if(start == 1) //If first word was LOGIN
	{
		if(str2.compare("COUNT") == 0 && str3.compare("") == 0) //If there was only one other word and it was COUNT
		{
			getSize(); //Get HashMap's size
			return 6;
		}
		else if(str3.compare("") != 0 && str2.compare("") != 0) //If there were two other words
		{
			checkKey(str2,str3); //Make a login attempt to the HashMap
			return 2;
		}
	}
	if(str3.compare("") == 0) //If the user entered two words total not being CREATE or LOGIN
	{
		if(start == 2) //If the first word was REMOVE
		{
			removeKey(str2); //REMOVE the key from the HashMap
			return 3;
		}
		else if(start == 5) //If it was DEBUG
		{
			if(str2.compare("ON") == 0) //If second word was ON
			{
				setDebug(true);//Give user access to all 11 commands
				return 7;
			}
			else if(str2.compare("OFF") == 0) //If second word was OFF
			{
				setDebug(false); //Restrict user from LOGIN COUNT,MAX BUCKET SIZE,LOAD FACTOR,BUCKET COUNT 
				return 8;
			}
		}
		else if(start == 6 && str2.compare("COUNT") == 0) //If first was BUCKET and second was COUNT
		{
			getBuckets(); //Execute getBucketCount
			return 9;
		}
		else if(start == 7 && str2.compare("FACTOR") == 0) //If first was LOAD and second was FACTOR
		{
			getLoadFactor(); //Get load factor
			return 10;
		}
	}
	if(str2.compare("") == 0) //If there was only one word entered
	{
		if(start == 3) //If CLEAR
		{
			clearHashTable(); //RESET Hash Map
			return 4;
		}
		if(start == 4) // IF QUIT
			return -1; //Return a negative flag indicating a time to quit out of run()
	}
	return 0; //If none of the inputs were valid then the method would have continued to this point making input
	// invalid making the method return invalid flag, 0
}

void InterfaceDemo::setDebug(bool state)
{
	if(state == true)
	{
		if(debuggable == true) //If debug already true, do nothing and notify user
			std::cout << "ON ALREADY" << std::endl;
		else
		{
			debuggable = state; //Change debug to true and notify
			std::cout << "ON NOW" << std::endl;
		}
	}
	else //Same as above case, just with debuggable == false
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
	if(debuggable == false) //If user has access to this command output the HashMap's size, if not output INVALID
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.size() << std::endl;
}

void InterfaceDemo::getBuckets() const
{
	if(debuggable == false) //If user has access to this command output the HashMap's number of linked lists, if not output INVALID
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.bucketCount() << std::endl;
}

void InterfaceDemo::getMaxBucket() const
{
	if(debuggable == false)//If user has access to this command output the length of the HashMap's
		// largest linked list, if not output INVALID
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.maxBucketSize() << std::endl;
}

void InterfaceDemo::getLoadFactor() const
{
	if(debuggable == false) //If user has access to this command output the HashMap's load factor, if not output INVALID
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.loadFactor() << std::endl;
}

void InterfaceDemo::checkKey(const std::string &key, const std::string &value) const
{
	std::string result = "";
	result = hm.value(key); //Get the ACTUAL VALUE of the key in the HashMap, if it exists
	if(result.compare(value) == 0) //If the user's input for value is the same as the actual one
		std::cout << "SUCCEEDED" << std::endl; //Display size
	else
		std::cout << "FAILED" << std::endl; //Display failure
}

void InterfaceDemo::addHash(const std::string &key, const std::string &value)
{
	unsigned int currentSize = hm.size();//Keep a note of the HashMap size before the add call
	hm.add(key,value); //Try to add the pair
	unsigned int newSize = hm.size(); //Get the HashMap Size again
	//If there was a successful add hm.tableSize would be incremented making newSize == currentSize + 1
	//If not tableSize would be unchanged
	if(currentSize == newSize)
		std::cout << "EXISTS" << std::endl; //Indicate duplicate key
	else
		std::cout << "CREATED" << std::endl; //Indicate HashMap creation
}

void InterfaceDemo::removeKey(const std::string &key)
{
	unsigned int currentSize = hm.size(); //Take note of the HashMap's size before attempting to remove
	hm.remove(key);//Attempt to remove the key
	unsigned int newSize = hm.size(); //Get the new HashMap Size
	//If the remove was successful tableSize in hm would be decremented making newSize == currentSize - 1
	//If not hm.tableSize is unchanged
	if(currentSize == newSize)
	{
		std::cout << "NONEXISTENT" << std::endl; //Indicate nonexistent key
	}
	else
	{
		std::cout << "REMOVED" << std::endl;//Indicate removal
	}
}

void InterfaceDemo::clearHashTable()
{
	hm = HashMap();
	//In HashMap's operator overload for ( = ) the contents in the HashMap are properly deallocated and cleared before
	// being reassigned. So assigning hm to a newly initialized HashMap, it will clear its contents and give it a new
	// empty HashMap for the user to keep interacting with
}
