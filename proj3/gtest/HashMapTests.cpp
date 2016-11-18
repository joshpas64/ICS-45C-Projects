// HashMapTests.cpp
//
// ICS 45C Fall 2016
// Project #3: Maps and Legends
//
// Write unit tests for your HashMap class here.  I've provided one test already,
// though I've commented it out, because it won't compile until you've implemented
// three things: the HashMap constructor, the HashMap destructor, and HashMap's
// size() member function.

#include <gtest/gtest.h>
#include "HashMap.hpp"
#include "Hashfunction.hpp"

TEST(TestHashMap, sizeOfNewlyCreatedHashMapIsZero)
{
   HashMap empty;
   ASSERT_EQ(0, empty.size());
}
namespace
{
	unsigned int terribleHash(const std::string &str)
	{
		unsigned int result = str.length();
		result = result + 3;
		result = result * 12;
		return result;
	}
	unsigned int forceIntoSameBucket(const std::string &str)
	{
		return 2;
	}
}
TEST(TestHashMap, createWithHashFunction)
{
	HashMap empty = HashMap();
	HashMap empty2;
	HashMap simple = HashMap(simpleHash);
	HashMap elf = HashMap(ELFHash);
	HashMap djb = HashMap(DJBHash);
	HashMap awful = HashMap(terribleHash);
	HashMap reallyBad = HashMap(forceIntoSameBucket);
}

TEST(TestHashMap, messWithOneLinkedList)
{
	HashMap hm = HashMap(forceIntoSameBucket);
	hm.add("HELLO","THERE");
	unsigned int bCount = hm.bucketCount();
	unsigned int fSize = hm.maxBucketSize();
	ASSERT_EQ(1,fSize);
	hm.add("WHATS UP", "MY FRIEND");
	unsigned int bCoun1 = hm.bucketCount();
	unsigned int sSize = hm.maxBucketSize();
	ASSERT_EQ(10,bCount);
	ASSERT_EQ(10,bCoun1);
	ASSERT_EQ(2,sSize);
	ASSERT_EQ(2,hm.size());
}

TEST(TestHashMap, modifyOneNode)
{
	HashMap hm = HashMap(forceIntoSameBucket);
	hm.add("HELLO","THERE");
	hm.add("Your name", "your password");
	hm.add("HELLO", "MY FRIEND");
	ASSERT_EQ(2,hm.size());
	ASSERT_EQ(2,hm.maxBucketSize());
	ASSERT_EQ(10,hm.bucketCount());
	hm.remove("HELLO");
	ASSERT_EQ(1,hm.maxBucketSize());
	ASSERT_EQ(1,hm.size());
}

TEST(TestHashMap, searchOneNode)
{
	HashMap hm = HashMap(forceIntoSameBucket);
	hm.add("HELLO","THERE");
	hm.add("Your name", "your password");
	hm.add("HELLO", "MY FRIEND");
	ASSERT_EQ(2,hm.size());
	ASSERT_EQ(2,hm.maxBucketSize());
	ASSERT_EQ(10,hm.bucketCount());
	hm.remove("HELLO");
	ASSERT_EQ("your password",hm.value("Your name"));
	ASSERT_EQ("",hm.value("HELLO"));
	ASSERT_EQ(1,hm.size());
	ASSERT_EQ(false,hm.contains("HELLO"));
}

TEST(TestHashMap, testMultipleBuckets)
{
	HashMap hm = HashMap(terribleHash);
	hm.add("H","12");
	hm.add("OH","WE ARE");
	hm.add("JO","GETTOIN CRAXY");
	hm.add("MOKL","PL");
	ASSERT_EQ(0.4,hm.loadFactor());
	ASSERT_EQ(2,hm.maxBucketSize());
	ASSERT_EQ(4,hm.size());
}

TEST(TestHashMap, testMoreBuckets)
{
	HashMap hm = HashMap(terribleHash);
	hm.add("H","12");
	hm.add("OH","WE ARE");
	hm.add("JO","GETTOIN CRAXY");
	hm.add("MOKL","PL");
	hm.add("0123456789AB","BUCKET 2");
	ASSERT_EQ(0.5,hm.loadFactor());
	ASSERT_EQ(3,hm.maxBucketSize());
	ASSERT_EQ("GETTOIN CRAXY",hm.value("JO"));
	ASSERT_EQ(5,hm.size());
	ASSERT_EQ(10,hm.bucketCount());
	ASSERT_EQ(true,hm.contains("0123456789AB"));
}

TEST(TestHashMap, removeAndReplaceHead)
{
	HashMap hm = HashMap(terribleHash);
	hm.add("H","12");
	hm.add("OH","WE ARE");
	hm.add("JO","GETTOIN CRAXY");
	hm.add("MOKL","PL");
	hm.add("0123456789AB","BUCKET 2");
	hm.remove("H");
	ASSERT_EQ(4,hm.size());
	ASSERT_EQ(false,hm.contains("H"));
	hm.add("J","13");
	ASSERT_EQ(5,hm.size());
}

TEST(TestHashMap, removeAndReplaceTail)
{
	HashMap hm = HashMap(terribleHash);
	hm.add("H","12");
	hm.add("OH","WE ARE");
	hm.add("JO","GETTOIN CRAXY");
	hm.add("MOKL","PL");
	hm.add("0123456789AB","BUCKET 2");
	ASSERT_EQ(3,hm.maxBucketSize());
	hm.remove("0123456789AB");
	ASSERT_EQ(2, hm.maxBucketSize());
	ASSERT_EQ(false,hm.contains("0123456789AB"));
	hm.add("1234567890BA","BUCKET 2");
	ASSERT_EQ(3,hm.maxBucketSize());
	ASSERT_EQ(5,hm.size());
}

TEST(TestHashMap, removeAndReplaceMiddle)
{
	HashMap hm = HashMap(terribleHash);
	hm.add("H","12");
	hm.add("OH","WE ARE");
	hm.add("JO","GETTOIN CRAXY");
	hm.add("MOKL","PL");
	hm.add("0123456789AB","BUCKET 2");
	hm.remove("JO");
	ASSERT_EQ(false,hm.contains("JO"));
	ASSERT_EQ(true,hm.contains("0123456789AB"));
	ASSERT_EQ(true,hm.contains("OH"));
	ASSERT_EQ(2,hm.maxBucketSize());
	hm.add("IT","FOLLOWS");
	ASSERT_EQ(3,hm.maxBucketSize());
	ASSERT_EQ(5,hm.size());
}

TEST(TestHashMap, forceRehash)
{
	HashMap hm = HashMap(terribleHash);
	hm.add("H","12");
	hm.add("OH","WE ARE");
	hm.add("JO","GETTOIN CRAXY");
	hm.add("MOKL","PL");
	hm.add("0123456789AB","BUCKET 2");
	hm.add("123","OTHER BUCKET");
	hm.add("A","First letter");
	ASSERT_EQ(10,hm.bucketCount());
	ASSERT_EQ(7,hm.size());
	hm.add("fivel","GARFIELD");
	hm.add("FROM","Your truly");
	ASSERT_EQ(21,hm.bucketCount());
	ASSERT_EQ(9,hm.size());
	ASSERT_EQ(true,hm.contains("0123456789AB"));
	bool check = hm.loadFactor() < 0.8;
	ASSERT_EQ(true,check);
}

// 1 + 3 = 4 * 12 = 48 % 10 = 8  11 + 3 = 14 * 12 = 168 % 10 = 8; 48 % 21 = 6 ; 168 % 21 = 0
// 4 + 3 = 7 * 12 = 84 % 21 = 0  6+3 = 9 * 12 = 108 % 21 = 3
TEST(TestHashMap, checkRehashedBuckets)
{
	HashMap hm = HashMap(terribleHash);
	hm.add("A","BUCKET 8 to 6");
	hm.add("B","BUCKET 8 to 6");
	hm.add("C","BUCKET 8 to 6");
	hm.add("D","BUCKET 8 to 6");
	hm.add("E","BUCKET 8 to 6");
	hm.add("F31","BUCKET 2 to 9");
	hm.add("1234567890A","BUCKET 8 to Bucket 0");
	ASSERT_EQ(6,hm.maxBucketSize());
	ASSERT_EQ(7,hm.size());
	ASSERT_EQ(0.7,hm.loadFactor());
	hm.add("1234","some bucket to buck 0");
	hm.add("letters","another bucket to buck 3");
	ASSERT_EQ(9,hm.size());
	ASSERT_EQ(21,hm.bucketCount());
	ASSERT_EQ(5,hm.maxBucketSize());
	hm.add("some new vkey","some new val");
	ASSERT_EQ(21,hm.bucketCount());
	ASSERT_EQ(10,hm.size());
	ASSERT_EQ(true,hm.contains("D"));
	ASSERT_EQ(true,hm.contains("some new vkey"));
}

TEST(TestHashMap,operationalAfterRehash)
{
	HashMap hm = HashMap(terribleHash);
	hm.add("A","BUCKET 8 to 6");
	hm.add("B","BUCKET 8 to 6");
	hm.add("C","BUCKET 8 to 6");
	hm.add("D","BUCKET 8 to 6");
	hm.add("E","BUCKET 8 to 6,");
	hm.add("F31","BUCKET 2 to 9");
	hm.add("1234567890A","BUCKET 8 to Bucket 0");
	hm.add("1234","some bucket to buck 0");
	hm.add("letters","another bucket to buck 3");
	hm.add("some new vkey","some new val");
	ASSERT_EQ(false,hm.contains("ab testing"));
	hm.remove("F31");
	ASSERT_EQ(9,hm.size());
	ASSERT_EQ(false,hm.contains("F31"));
	hm.remove("C");
	ASSERT_EQ(8,hm.size());
	ASSERT_EQ(4,hm.maxBucketSize());
	ASSERT_EQ(false,hm.contains("C"));
	hm.add("F","L");
	ASSERT_EQ(9,hm.size());
	ASSERT_EQ(5,hm.maxBucketSize());
	ASSERT_EQ("BUCKET 8 to 6,",hm.value("E"));
	ASSERT_EQ("",hm.value("F31"));
}

TEST(TestHashMap, testReassignment)
{
	HashMap hm = HashMap(terribleHash);
	hm.add("A","BUCKET 8 to 6");
	hm.add("B","BUCKET 8 to 6");
	hm.add("C","BUCKET 8 to 6");
	hm.add("D","BUCKET 8 to 6");
	hm.add("E","BUCKET 8 to 6,");
	hm.add("F31","BUCKET 2 to 9");
	hm.add("1234567890A","BUCKET 8 to Bucket 0");
	hm.add("1234","some bucket to buck 0");
	hm.add("letters","another bucket to buck 3");
	hm.add("some new vkey","some new val");
	HashMap newHm = HashMap();
	newHm.add("Val","key");
	newHm.add("key1","val1");
	ASSERT_EQ(2,newHm.size());
	ASSERT_EQ(10,newHm.bucketCount());
	newHm = hm;
	ASSERT_EQ(10, newHm.size());
	ASSERT_EQ(21, newHm.bucketCount());
	ASSERT_EQ(true,newHm.contains("F31"));
	ASSERT_EQ(false,newHm.contains("key1"));
	hm.add("key1","val1");
	hm.add("key2","val2");
	newHm.add("key3","val3");
	ASSERT_EQ(12,hm.size());
	ASSERT_EQ(11,newHm.size());
	ASSERT_EQ(false,newHm.contains("key1"));
	ASSERT_EQ(false,hm.contains("key3"));
	newHm = hm;
	ASSERT_EQ(12,newHm.size());
	ASSERT_EQ(true,newHm.contains("key2"));
	ASSERT_EQ(false,newHm.contains("key3"));
}

TEST(TestHashMap, testOtherConstructor)
{
	HashMap hm = HashMap(terribleHash);
	hm.add("A","BUCKET 8 to 6");
	hm.add("B","BUCKET 8 to 6");
	hm.add("C","BUCKET 8 to 6");
	hm.add("D","BUCKET 8 to 6");
	hm.add("E","BUCKET 8 to 6,");
	hm.add("F31","BUCKET 2 to 9");
	hm.add("1234567890A","BUCKET 8 to Bucket 0");
	hm.add("1234","some bucket to buck 0");
	hm.add("letters","another bucket to buck 3");
	hm.add("some new vkey","some new val");
	HashMap newHm = HashMap(hm);
	ASSERT_EQ(10,hm.size());
	ASSERT_EQ(21,hm.bucketCount());
	newHm.add("G","Value");
	ASSERT_EQ(false,hm.contains("G"));
	ASSERT_EQ(11,newHm.size());
	newHm.remove("A");
	ASSERT_EQ(true,hm.contains("A"));
	ASSERT_EQ(false,newHm.contains("A"));
}