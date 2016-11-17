#include "HashMap.hpp"
HashMap::HashMap()
{
	bucketTotal = initialBucketCount;
	hasher = ELFHash;
	tableSize = 0;
	setBuckets();
}
HashMap::HashMap(HashFunction hasher)
{
	this->hasher = hasher;
	bucketTotal = initialBucketCount;
	tableSize = 0;
	setBuckets();
}

HashMap::HashMap(const HashMap &hm)
{
	bucketTotal = hm.bucketTotal;
	tableSize = 0;
	hasher = hm.hasher;
	setBuckets();
	for(unsigned int i = 0; i < bucketTotal; i++)
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
				add(node->key,node->value);
				node = node->next;
			}
		}
	}
}

HashMap& HashMap::operator=(const HashMap &hm)
{
	if(this != &hm)
	{
		unsigned int oldTotal = bucketTotal;
		bucketTotal = hm.bucketTotal;
		tableSize = 0;
		hasher = hm.hasher;
		HashMap::Node **oldBuckets = buckets;
		setBuckets();
		for(unsigned int i = 0; i < bucketTotal; i++)
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
					add(node->key,node->value);
					node = node->next;
				}
			}
		}
		for(unsigned int i = 0; i < oldTotal; i++)
		{
			destroyNode(oldBuckets[i]);
		}
		delete[] oldBuckets;
	}
	return *this;
}
HashMap::~HashMap()
{
	for(int i = 0; i < bucketTotal; i++)
	{
		destroyNode(buckets[i]);
	}
	delete[] buckets;
}

void HashMap::setBuckets()
{
	buckets = new HashMap::Node*[bucketTotal];
	for(unsigned int i = 0; i < bucketTotal; i++)
	{
		buckets[i] = nullptr;
	}
}
unsigned int HashMap::bucketCount() const
{
	return bucketTotal;
}

double HashMap::loadFactor() const
{
	double loadfactor;
	loadfactor = ((double) size())/ bucketCount();
	return loadfactor;
}



unsigned int HashMap::size() const
{
	return tableSize;
}
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
	bool found = false;
	unsigned int bucketIndex = applyHash(key);
	HashMap::Node *node = buckets[bucketIndex];
	while(node != nullptr)
	{
		if(node->key.compare(key) == 0)
		{
			found = true;
			break;
		}
		else
		{
			node = node->next;
		}
	}
	return found;
}

void HashMap::add(const std::string &key, const std::string &value)
{
	unsigned int bucketIndex = applyHash(key);
	HashMap::Node *node = buckets[bucketIndex];
	HashMap::Node *prev = node;
	while(node != nullptr)
	{
		if(node->key.compare(key) == 0)
		{
			return;
		}
		else
		{
			prev = node;
			node = node->next;
		}
	}
	HashMap::Node *newNode = new HashMap::Node;
	newNode->key = key;
	newNode->value = value;
	newNode->next = nullptr;
	if(prev == nullptr)
	{
		buckets[bucketIndex] = newNode;
	}
	else
	{ 
		prev->next = newNode;
	}
	tableSize++;
	double currentLoad = loadFactor();
	if(currentLoad > 0.8)
	{
		reHash();
	}
}

void HashMap::reHash()
{
	unsigned int oldTotal = bucketTotal;
	tableSize = 0;
	bucketTotal = ((bucketTotal * 2) + 1);
	HashMap::Node **oldNotes = buckets;
	buckets = new HashMap::Node* [bucketTotal];
	for(unsigned int j = 0; j < bucketTotal; j++)
	{
		buckets[j] = nullptr;
	}
	for(unsigned int i = 0; i < oldTotal; i++)
	{
		HashMap::Node *node = oldNotes[i];
		if(node == nullptr)
			continue;
		HashMap::Node *temp = node->next;
		while(node != nullptr)
		{
			add(node->key,node->value);
			temp = node;
			node = node->next;
			delete temp;
		}
	}
	delete[] oldNotes;

}
void HashMap::remove(const std::string& key)
{
	unsigned int bucketIndex = applyHash(key);
	HashMap::Node *node = buckets[bucketIndex];
	HashMap::Node *prev = node;
	while(node != nullptr)
	{
		if(node->key.compare(key) == 0)
		{
			if(prev->key.compare(key) == 0)
			{
				delete node;
				buckets[bucketIndex] = nullptr;
			}
			else
			{
				prev->next = node->next;
				delete node;
			}
			tableSize--;
			break;
		}
		else
		{
			prev = node;
			node = node->next;
		}
	}
}

unsigned int HashMap::applyHash(const std::string &key) const
{
	unsigned int hashKey = hasher(key);
	unsigned int bucket = hashKey % bucketTotal;
	return bucket;
}

unsigned int HashMap::getBucketLength(unsigned int index) const
{
	unsigned int length = 0;
	HashMap::Node *node = buckets[index];
	while(node != nullptr)
	{
		length++;
		node = node->next;
	}
	return length;
}
std::string HashMap::value(const std::string &key) const
{
	std::string val = "";
	unsigned int bucket = applyHash(key);
	HashMap::Node *node = buckets[bucket];
	while(node != nullptr)
	{
		if(node->key.compare(key) == 0)
		{
			val = node->value;
			break;
		}
		else
		{
			node = node->next;
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
			currentMax = currentLength;
		}
	}
	return currentMax;
}

void HashMap::destroyNode(HashMap::Node *node)
{
	if(node == nullptr)
		return;
	HashMap::Node *currNode = node;
	HashMap::Node *temp = currNode->next;
	while(currNode != nullptr)
	{
		temp = currNode;
		currNode = currNode->next;
		delete temp;
	}
}

void HashMap::output() const
{
	for(unsigned int i = 0; i < bucketTotal; i++)
	{
		std::cout << "AT NODE " << (i+1) << ":" << std::endl;
		HashMap::Node *node = buckets[i];
		if(node == nullptr)
		{
			std::cout << "Just a nullptr so far" << std::endl;
			continue;
		}
		while(node != nullptr)
		{
			std::cout << "Key of: " << node->key;
			std::cout << " with value of: " << node->value << std::endl;
			node = node->next;
		}
	}
}

