#include "Hashfunction.hpp"

unsigned int simpleHash(const std::string &key)
{
	unsigned int value  = 0;
	for(int i = 0; i < key.length(); i++)
	{
		value += key[i];
	}
	value  = value * key.length();
	return value;
}

unsigned int ELFHash(const std::string &key)
{
	unsigned int hash = 0;
	unsigned int x = 0;
	unsigned int i = 0;
	unsigned int len = key.length();
	for( i = 0; i < len ; i++)
	{
		hash = (hash << 4) + key[i];
		if((x = hash & 0xF0000000) != 0)
		{
			hash ^= (x >> 24);
		}
		hash &= ~x;
	}
	return hash;
}

unsigned int DJBHash(const std::string &key)
{
	unsigned int val = 265; //5381 had overflow runtime error
	int c = 0;
	int len = key.length();
	while((c < len))
	{
		val = ((val << 5) + val) + key[c];
	}
	return val;
}