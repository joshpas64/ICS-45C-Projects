#include "interface.hpp"

Interface::Interface()
{
	hm = HashMap(); //Start a new empty HashMap Object
	debuggable = false; //OFF by default
}

Interface::Interface(HashFunction hashFunction)
{
	hm = HashMap(hashFunction);//Start a new empty HashMap object with its hasher attr set to hashFunction
	debuggable = false;
}

void Interface::run()
{
	int cont = 0; //Actual continuous user interface of the program
	std::string command;
	do
	{
		std::getline(std::cin,command); //Retrieves users line of input
		cont = readCommand(command); //readCommand executes the command or if invalid, display INVALID and return 0
		//If QUIT was specified -1 is returned ending the while loop
	}
	while(cont != -1); //WHILE NOT QUIT
	std::cout << "GOODBYE" << std::endl; //Since program has terminated output GOODBYE
}

int Interface::readCommand(const std::string &command)
{
	std::stringstream stream; //Maximum words that user can use as input is 3
	std::string first = "";
	std::string second = "";
	std::string third = "";
	std::string fourth = "";
	stream << command;
	stream >> first;
	stream >> second;
	stream >> third;
	stream >> fourth;
	if(fourth.compare("") != 0) //If fourth is not empty, then too many parameters were entered, and is considered invalid
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
			break; //Determine if the first word retrieved could be the first word of the acceptable commands
		}
	}
	if(second.compare("COUNT") == 0 && third.compare("") == 0) //If second is COunt with no third option (user only entered two words)
	{
		if(result == 1) //If first word was LOGIN
			getSize(); //Then execute LOGIN COUNT and get hm.size()
		else if(result == 6) //If it was BUCKET
			getBuckets(); //THEN execute BUCKET COUNT and get hm.bucketCount()
		else
			std::cout << "INVALID" << std::endl; //Other cases where two words with COUNT as second word are invalid
	}
	else if(result == -1) //If the first word was invalid, then all following is invalid as well since every first word of every acceptable
		//command in this interface is listed in the firstWords array
	{
		std::cout << "INVALID" << std::endl;
		return 0;
	}
	else if(second.compare("") != 0 && third.compare("") != 0) //If there were three words in total 
	{
		if(result == 1) //If first word was LOGIN
			checkKey(second,third); //then do a login operation
		else if(result == 0) //If first word was CREATE
			addHash(second,third); // Then try to add into the HashMap with second as key and third as value
		else if(first.compare("MAX") == 0 && second.compare("BUCKETS") == 0 && third.compare("SIZE") == 0) 
			getMaxBucket();//If command was MAX BUCKET SIZE then output length of largest bucket
		else
			std::cout << "INVALID" << std::endl; //All other 3 word cases invalid
	}
	else if(result == 2) //If first word is REMOVE and the user only entered two words 
	{
		if(third.compare("") == 0 && second.compare("") != 0)
			removeKey(second); //Try to remove from the HashMap with second being the key
		else
			std::cout << "INVALID" << std::endl; //All other cases INVALID
	}
	else if(third.compare("") == 0 && second.compare("") == 0) //If only 1 word entered
	{
		if(result == 3) //If word was CLEAR
		{
			clearHashTable(); //clear whole HashMap's key,value pairs
		}
		else if(result == 4)
			return -1; //IF QUIT return -1 to calling program which would be negative flag to terminate
		else
			std::cout << "INVALID" << std::endl;
	}
	else if(first.compare("DEBUG") == 0 && third.compare("") == 0) //User entered two words with first one being DEBUG
	{
		if(second.compare("OFF") == 0) //IF OFF then set debuggable to off
			setDebug(false);
		else if(second.compare("ON") == 0) //if ON then set DEBUGGABLE to ON
			setDebug(true);
		else
			std::cout << "INVALID" << std::endl;
	}
	else if(third.compare("") == 0 && first.compare("LOAD") == 0 && second.compare("FACTOR") == 0) //User entered two words, being LOAD FACTOR
	{
		getLoadFactor();	//EXecute and output LoadFactor of HashMap
	}
	else
	{
		std::cout << "INVALID" << std::endl; //Any other cases considered Invalid input
	}
	stream.clear();
	stream.str("");//clear stream buffer
	return 0; //Return 0 which would be a positive flag to continue reading input in the run() method
}


void Interface::setDebug(bool state)
{
	if(state == true) 
	{
		if(debuggable == true)//If debuggable was already true then leave it alone and notify user
			std::cout << "ON ALREADY" << std::endl;
		else
		{
			debuggable = state; //Make debuggable true and allow user to access new Commands
			std::cout << "DEBUG ON" << std::endl;
		}
	}
	else
	{
		if(debuggable == false) // If already false, dont change it, just notify user
			std::cout << "OFF ALREADY" << std::endl;
		else
		{
			debuggable = state;//Set debuggable and restrict user access to certain commands
			std::cout << "DEBUG OFF" << std::endl;
		}
	}
}

void Interface::getSize() const
{
	if(debuggable == false) //If user does not have access terminate and notify
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.size() << std::endl; //If access is granted output number of key,value pairs in the HashMap
}

void Interface::getBuckets() const
{
	if(debuggable == false) //If user does not have access terminate and notify
		std::cout << "INVALID" << std::endl;
	else
		std::cout << hm.bucketCount() << std::endl; //If granted, output number of buckets currently in the HashMap
}

void Interface::getMaxBucket() const
{
	if(debuggable == false)//If user does not have access terminate and notify
		std::cout << "INVALID" << std::endl;
	else //If permission is granted, output the length of what is the currently largest linked list in the HashMap
		std::cout << hm.maxBucketSize() << std::endl;
}

void Interface::getLoadFactor() const
{
	if(debuggable == false) //If user does not have access terminate and notify, terminate means just get more input from run() method
		std::cout << "INVALID" << std::endl;
	else //If permission is granted, output the current LOAD FACTOR of the current HashMap
		std::cout << hm.loadFactor() << std::endl;
}

void Interface::checkKey(const std::string &key, const std::string &value) const
{
	std::string result = ""; //Default
	result = hm.value(key); //Get key's value if, the key actually exists 
	if(result.compare(value) == 0) //If the value, equivalent of a password, matches then Login has succeeded
		std::cout << "SUCCEEDED" << std::endl;
	else //If they dont match or key doesn't exist then login has failed
		std::cout << "FAILED" << std::endl;
}

void Interface::addHash(const std::string &key, const std::string &value)
{
	unsigned int currentSize = hm.size(); //Keep a note of what is the current size before trying to add
	hm.add(key,value); //Attempt to add key,value pair
	unsigned int newSize = hm.size();//If successful (i.e.) the key was not already in the current HashMap
	//, newSize == currentSize + 1, if not then currentSize == newSize
	if(currentSize == newSize)
		std::cout << "EXISTS" << std::endl; //No duplicate keys
	else
		std::cout << "CREATED" << std::endl; //Successful creation
}

void Interface::removeKey(const std::string &key)
{
	unsigned int currentSize = hm.size(); //Note of current HashMap's size before attempting to remove
	hm.remove(key); //Try to remove
	unsigned int newSize = hm.size();//If successful, meaning there was a key in the current HashMap that
	// matched the parameter, then
	// newSize == currentSize - 1, if not :     newSize == currentSize
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
	hm = HashMap(); //In = operator overload all of the contents that are currently in the (this) HashMap object get deallocated
	// and get set to the contents of whatever HashMap its assigned to
	// In this case hm's contents are properly deallocated and cleared and set to a new empty HashMap object
}
