#include "HashMap.hpp"
//As Thornton stated, these are the big three along with two overloaded constructors
HashMap::HashMap()
{
	bucketTotal = initialBucketCount; //InitialBuckets amount will always start at 10
	hasher = ELFHash; //Default Hash Function
	tableSize = 0; //Always start with no key value pairs
	setBuckets(); //Initialize dynamic array of null Node pointers
}
HashMap::HashMap(HashFunction hasher)//Same as empty constructor just with alternate hash function
{
	this->hasher = hasher; //Make the hasher attribute that will later be used to find the buckets for keys when adding Nodes
	//Used this keyword to avoid confusion possibly caused by self referencing i.e hasher = hasher
	// this is a POINTER to the actual object *this is object itself
	bucketTotal = initialBucketCount;
	tableSize = 0;
	setBuckets();
}

HashMap::HashMap(const HashMap &hm)
{
	//Set attributes to hm attributes
	bucketTotal = hm.bucketTotal;
	tableSize = 0; // Since using add increments tablesize, then restart at 0 and after adding every node
	// this->tablesize == hm.tablesize
	hasher = hm.hasher;
	setBuckets(); //start with empty array of linked lists with new bucketTotal
	for(unsigned int i = 0; i < bucketTotal; i++)
	{
		HashMap::Node *node = hm.buckets[i]; //Point to first Node in the linkedlist
		if(node == nullptr)
		{
			buckets[i] = nullptr; //Make any empty linked list in hm will become an empty linked list in (this)
			// as well at corresponding index, since null can move to next index in array
			continue;
		}
		else
		{
			while(node != nullptr) //Iterate through linked list
			{
				add(node->key,node->value); // Add Node to the linked list (this will also increment table Size)
				node = node->next;//Move to the next node
			}
		}
	}
}

HashMap& HashMap::operator=(const HashMap &hm)
{
	if(this != &hm) //Ensure that *this is not referring to itself (self assignment)
	{
		unsigned int oldTotal = bucketTotal; 
		bucketTotal = hm.bucketTotal;
		tableSize = 0;
		hasher = hm.hasher;
		HashMap::Node **oldBuckets = buckets; //Keep the old array of linked lists to reassign
		setBuckets(); //Make a new array of linked lists of size hm.bucketTotal
		for(unsigned int i = 0; i < bucketTotal; i++) //Make the new buckets array of linked lists
		{
			HashMap::Node *node = hm.buckets[i];
			if(node == nullptr)
			{
				buckets[i] = nullptr;
				continue;
			}
			else
			{
				while(node != nullptr)
				{
					add(node->key,node->value); //add each of hm's *Node s to the new buckets array in its corresponding
					//index
					node = node->next;
				}
			}
		}
		for(unsigned int i = 0; i < oldTotal; i++)
		{
			destroyNode(oldBuckets[i]); //Now that hm new array of linked lists is set, deallocate the old array 
			//And any nodes each linked lists pointed to
		}
		delete[] oldBuckets; //Delete all the old pointers
	}
	return *this;
}
HashMap::~HashMap()
{
	for(int i = 0; i < bucketTotal; i++)
	{
		destroyNode(buckets[i]); //Deallocate all the Nodes that are pointed by each Linked List
	}
	delete[] buckets; //Delete the array contents since it is just filled with nullptr's now
}

void HashMap::setBuckets()
{
	buckets = new HashMap::Node*[bucketTotal]; //Make a dynamically allocated array of Node pointers based on the current number
	// of buckets
	for(unsigned int i = 0; i < bucketTotal; i++)
	{
		buckets[i] = nullptr; //Initialize each linked list to a nullptr
	}
}
unsigned int HashMap::bucketCount() const
{
	return bucketTotal; //bucketTotal getMethod
}

double HashMap::loadFactor() const
{
	double loadfactor;
	loadfactor = ((double) size())/ bucketCount(); //Fraction determining how filled up a hashmap is 
	//The current threshold that cannot be exceeded is 0.8
	return loadfactor;
}



unsigned int HashMap::size() const
{
	return tableSize;//tableSize getMethod
}
//Below was an inefficient way to retrieve a hashmap's size by iterating through all of its linked lists
//Would have a polynomial (Around O(n^2)) time complexity just to retrieve size
/*
unsigned int HashMap::size()
{
	unsigned int total = 0;
	for(unsigned int i = 0; i < bucketTotal; i++)
	{
		unsigned nodeTotal = 0;
		HashMap::Node* node = buckets[i];
		while(node != nullptr)
		{
			nodeTotal++;
			node = node->next;
		}
		total += nodeTotal;
	}
	return total;
}
*/
bool HashMap::contains(const std::string &key) const
{
	bool found = false; //Assume false
	unsigned int bucketIndex = applyHash(key); //Get bucketIndex since the hash of a key is always supposed to return the same hash value
	HashMap::Node *node = buckets[bucketIndex]; //Start at the index, need only to traverse one linked list given a good hash function
	while(node != nullptr)
	{
		if(node->key.compare(key) == 0)//If the key is found
		{
			found = true;//Make Found true and break out of the loop, no more iteration needed
			break;
		}
		else
		{
			node = node->next; //If not found, continue traversing linked list
		}
	}
	return found;
}

void HashMap::add(const std::string &key, const std::string &value)
{
	unsigned int bucketIndex = applyHash(key); //Index that determines which linked list to traverse
	HashMap::Node *node = buckets[bucketIndex]; //Find the start of said Linked List
	HashMap::Node *prev = node; 
	while(node != nullptr)
	{
		if(node->key.compare(key) == 0)//If key already exists break out of the method, no more iteration needed
		{
			return;
		}
		else
		{
			prev = node; //Point to the current node, which will be the previous node in the next iteration
			node = node->next;//Move to next node
		}
	}
	HashMap::Node *newNode = new HashMap::Node; //Make a new Node object with key and values set to the parameters
	//By default adding a Node to the linked list, adds it to its tail, or at the end, where its next attribute should 
	//always be a nullptr
	newNode->key = key;
	newNode->value = value;
	newNode->next = nullptr;
	if(prev == nullptr) //In the case we are adding to an empty linked list
	{
		buckets[bucketIndex] = newNode; //Make the index of buckets array point to the newNode object instead of a nullptr
	}
	else
	{ 
		prev->next = newNode; //If not, make the now second-to-last-node's next attr point to the newNode
	}
	tableSize++;//Since there was a value added the size has increased by one
	double currentLoad = loadFactor(); //Check load factor before terminating
	if(currentLoad > 0.8)
	{
		reHash();
	}
}

void HashMap::reHash()
{
	unsigned int oldTotal = bucketTotal; //Store a value of the old bucketTotal
	tableSize = 0;
	bucketTotal = ((bucketTotal * 2) + 1); //Increase the bucketTotal 
	HashMap::Node **oldNotes = buckets; //Save a pointer to the old buckets array (the one that had the load factor above 0.8
	//    that called rehHash() to be called in the first place
	buckets = new HashMap::Node* [bucketTotal]; //Make an initialize a new array of empty linked lists with a now increased size
	for(unsigned int j = 0; j < bucketTotal; j++)
	{
		buckets[j] = nullptr; //Initialize each linked list in buckets to be a nullptr
	}
	for(unsigned int i = 0; i < oldTotal; i++) //Iterate through the old buckets array and add each key,value pair to the new
		// buckets array, deleting each node along the way
	{
		HashMap::Node *node = oldNotes[i]; //Current start of each Linked List
		if(node == nullptr) //Skip to next linked list if the current linked list is empty
			continue;
		HashMap::Node *temp = node->next; //Have a temp pointer that will point to the current Node being added to the new array
		// of linked lists, and later delete
		while(node != nullptr)
		{
			add(node->key,node->value); //Add the key,value pair to new array of linked lists
			temp = node; //Point to current node
			node = node->next; //Prepare to move to the next node
			delete temp; //Delete the current node
		}
	}
	delete[] oldNotes; //All pointers in the oldarray are just nullptrs so the content of oldNotes can be deallocated
}
void HashMap::remove(const std::string& key) //Removes a Node from a HashMap object
{
	unsigned int bucketIndex = applyHash(key); //Get its potential index in the linked list array
	HashMap::Node *node = buckets[bucketIndex]; //Start at that linked list's first node
	HashMap::Node *prev = node; //Will act as pointer to previous nodes
	while(node != nullptr)
	{
		if(node->key.compare(key) == 0) //If the key is found
		{
			if(prev->key.compare(key) == 0) //Only case where prev's key is the same node's key is if the node is the first one in the llist
			{
				delete node; //Delete Node's contents
				buckets[bucketIndex] = prev->next; //Have the start of the linked list point to the second Node instead
			}
			else
			{
				prev->next = node->next; //In any other case make the previous node point instead to the next node of the node that's
				// being removed
				delete node;
			}
			tableSize--; //Since a Node was removed tableSize decreased by one and no more iteration is needed so BREAK
			break;
		}
		else
		{
			prev = node; // Make current node the previous
			node = node->next; // Move to the next Node
		}
	}
}

unsigned int HashMap::applyHash(const std::string &key) const
{
	unsigned int hashKey = hasher(key); //HashValue may be greater than bucketTotal
	unsigned int bucket = hashKey % bucketTotal; //Offset it with % operator
	return bucket;
}

unsigned int HashMap::getBucketLength(unsigned int index) const
{
	unsigned int length = 0; //Default of 0
	HashMap::Node *node = buckets[index]; //Start at current Node
	while(node != nullptr)
	{
		length++; //Add to next such that each node's next does point to NULL
		node = node->next; // Move to next Node
	}
	return length;
}
std::string HashMap::value(const std::string &key) const
{
	std::string val = ""; //Default of empty string
	unsigned int bucket = applyHash(key); //Get potential index in bucket array
	HashMap::Node *node = buckets[bucket]; //Start at the head of the corresponding Linked List
	while(node != nullptr)
	{
		if(node->key.compare(key) == 0) //If the key is found
		{
			val = node->value; //Get its value
			break;
		}
		else
		{
			node = node->next; //If not, move to next node
		}
	}
	return val; 
}
unsigned int HashMap::maxBucketSize() const
{
	unsigned int currentMax = getBucketLength(0);
	for(unsigned int i = 1; i < bucketTotal; i++)
	{
		unsigned int currentLength = getBucketLength(i);
		if(currentMax < currentLength)
		{
			currentMax = currentLength;//Compare all the lengths of the linked lists in the array and
			// if one length is higher than the currentMax, set it to the new value
		}
	}
	return currentMax; //Return Max length
}

void HashMap::destroyNode(HashMap::Node *node) //Deallocate a Singly Linked List
{
	if(node == nullptr) //Since all nullptrs get deallocated at the end of HashMap in its destructor 
		return;
	HashMap::Node *currNode = node; //Start at the First Node of Linked List
	HashMap::Node *temp = currNode->next;
	while(currNode != nullptr)
	{
		temp = currNode; //Store a pointer to the current Node
		currNode = currNode->next;//Move to the next Node
		delete temp; //Delete the contents of the current Node
	}
}

void HashMap::output() const //Was only for testing purposes will remove function once, it is finalized
{
	for(unsigned int i = 0; i < bucketTotal; i++)
	{
		std::cout << "AT NODE " << (i+1) << ":" << std::endl; //Indicate which linked list that is being outputted
		HashMap::Node *node = buckets[i]; //Start at its first Node
		if(node == nullptr) //If its empty output and move to the next LinkedList
		{
			std::cout << "Just a nullptr so far" << std::endl;
			continue;
		}
		while(node != nullptr)
		{
			std::cout << "Key of: " << node->key; //Indicate Nodes Key
			std::cout << " with value of: " << node->value << std::endl; //Indicate Nodes value
			node = node->next;//Move to next value
		}
	}
}

