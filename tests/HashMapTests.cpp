// HashMapTests.cpp
//
// ICS 45C Fall 2015
// Project #3: Maps and Legends
//
// Write unit tests for your HashMap class here.  I've provided one test already,
// though I've commented it out, because it won't compile until you've implemented
// three things: the HashMap constructor, the HashMap destructor, and HashMap's
// size() member function.

#include <gtest/gtest.h>

#include "HashMap.hpp"


TEST(TestHashMap, sizeOfNewlyCreatedHashMapIsZero)
{
    HashMap empty;
    ASSERT_EQ(0, empty.size());
}


TEST(TestHashMapEqualsOperation, hashmapEqualsAnother)
{   
HashMap first;
first.add("A", "A");

HashMap second;
second.add("B", "B");

first = second;

ASSERT_EQ(first.contains("B"), second.contains("B"));
ASSERT_EQ(first.value("B"), second.value("B"));
}


TEST(TestHashMapAddItem, addKeyValuePairs)
{
HashMap empty;
empty.add("A", "A");
empty.add("B", "B");
empty.add("C", "C");
empty.add("D", "D");

ASSERT_EQ(empty.size(), 4);

}


TEST(TestHashMapRemoveItem, addAndRemoveFromHashMap)
{
HashMap empty;
empty.add("A", "A");
empty.remove("A");

ASSERT_EQ(empty.size(), 0);
}

TEST(TestHashMapContainItem, checkIfMapContainsItem)
{
HashMap empty;
empty.add("A", "A");

ASSERT_EQ(empty.contains("A"), true);

}

TEST(TestValue, valueOfItemEqual)
{
    HashMap empty;
empty.add("A", "A");

    ASSERT_EQ("A", empty.value("A"));

}


TEST(TestSize, sizeIsTwo)
{
HashMap empty;
empty.add("A", "A");
empty.add("B", "B");

ASSERT_EQ(2, empty.size());
}


TEST(TestBucketCount, countIsOne)
{
HashMap empty;
empty.add("A", "A");
empty.add("B", "B");

ASSERT_EQ(1, empty.bucketCount());
}




TEST(TestLoadFactor, loadFactorEqualToNum)
{
HashMap empty;
empty.add("A", "A");
empty.add("Boo", "Perfect");
empty.add("Me", "Notperfect");


ASSERT_EQ( 0.3, empty.loadFactor() );

}

TEST(TestMaxBucketSize, maximumIsZero)
{
HashMap empty;

ASSERT_EQ(0, empty.maxBucketSize());

}
