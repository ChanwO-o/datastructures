#include <gtest/gtest.h>
#include <string>
#include "HashSet.hpp"


TEST(HashSetTest, canConstructWithLambdaFunction) 
{
	HashSet<int> hs ([](const int i) { return 0; });
	ASSERT_EQ(0, hs.size());
}

namespace
{
	unsigned int someHashFunction(const int& i)
	{
		return (10 + i) / 3;
	}
}

namespace
{
	unsigned int anotherHashFunction(const std::string& s)
	{
		return (10 + s.length()) / 3;
	}
}

namespace
{
	template <typename T>
	void takeHashSetByValue(HashSet<T> hs)
	{
	}
}

TEST(HashSetTest, canCopyConstruct) {
	HashSet<int> hs1 (someHashFunction);
	HashSet<int> hs2 = hs1;
	HashSet<int> hs3 {hs1};
	takeHashSetByValue(hs3);
	ASSERT_EQ(hs1.size(), hs2.size());
	ASSERT_EQ(hs1.size(), hs3.size());
}

TEST(HashSetTest, canConstructWithFunction) {
	HashSet<int> hs (someHashFunction);
	ASSERT_EQ(0, hs.size());
}

TEST(HashSetTest, canAssign) {
	HashSet<int> hs1 (someHashFunction);
	HashSet<int> hs2 (someHashFunction);
	hs1 = hs2;
	ASSERT_EQ(hs1.size(), hs2.size());
}

TEST(HashSetTest, canAdd) {
	HashSet<int> hs1 (someHashFunction);
	hs1.add(1);
	hs1.add(1); // duplicate
	hs1.add(2);
	hs1.add(3);
	hs1.add(4);
	hs1.add(5);
	hs1.add(6);
	hs1.add(7);
	hs1.add(8);
	hs1.add(9);
	hs1.add(10);
	hs1.add(11);
	hs1.add(1);
	hs1.add(10);
	ASSERT_EQ(hs1.size(), 11);
	std::cout << hs1.toString() << "\n";
}

TEST(HashSetTest, checkContains) {
	HashSet<int> hs (someHashFunction);
	hs.add(1);
	hs.add(2);
	hs.add(3);
	hs.add(4);
	hs.add(5);
	// std::cout << hs.toString() << "\n";
	ASSERT_TRUE(hs.contains(1));
	ASSERT_TRUE(hs.contains(2));
	ASSERT_TRUE(hs.contains(3));
	ASSERT_FALSE(hs.contains(9));
	ASSERT_FALSE(hs.contains(10));


	HashSet<std::string> hs2 (anotherHashFunction);
	hs2.add("1");
	hs2.add("2");
	hs2.add("3");
	hs2.add("4");
	hs2.add("5");
	// std::cout << hs2.toString() << "\n";
	ASSERT_TRUE(hs2.contains("1"));
	ASSERT_TRUE(hs2.contains("2"));
	ASSERT_TRUE(hs2.contains("3"));
	ASSERT_FALSE(hs2.contains("9"));
	ASSERT_FALSE(hs2.contains("10"));
}

TEST(HashSetTest, needsRehash) {
	HashSet<int> hs1 (someHashFunction);
	ASSERT_FALSE(hs1.needsRehashing());
}

TEST(HashSetTest, toString) {
	HashSet<int> hs1 (someHashFunction);
	// std::cout << hs1.toString() << "\n";
	ASSERT_EQ("[] [] [] [] [] [] [] [] [] [] ", hs1.toString());
	hs1.add(1); // duplicate
	hs1.add(2);
	hs1.add(3);
	ASSERT_EQ("[] [] [] [1 ] [3 2 ] [] [] [] [] [] ", hs1.toString());
	// std::cout << hs1.toString() << "\n";
}

