#include <gtest/gtest.h>
#include <string>
#include "BSTSet.hpp"


TEST(BSTSetTest, canDefaultConstruct)
{
	BSTSet<int> bs;
	ASSERT_EQ(0, bs.size());
}

namespace
{
	template <typename T>
	void takeBSTByValue(BSTSet<T> bs)
	{
	}
}

TEST(BSTSetTest, canCopyConstruct)
{
	BSTSet<int> bs1;
	bs1.add(1);
	bs1.add(3);
	bs1.add(2);
	bs1.add(11);
	bs1.add(31);
	bs1.add(21);
	bs1.add(12);
	bs1.add(33);
	bs1.add(26);
	bs1.add(15);
	bs1.add(38);
	bs1.add(28);

	BSTSet<int> bs2 = bs1;
	BSTSet<int> bs3 {bs1};
	takeBSTByValue(bs1);

	std::cout << bs1.toString() << "\n";
	std::cout << bs2.toString() << "\n";

	ASSERT_EQ(bs1.size(), 12);
	ASSERT_EQ(bs2.size(), 12);
	ASSERT_EQ(bs1.size(), bs2.size());
	ASSERT_EQ(bs1.size(), bs3.size());
}


TEST(BSTSetTest, canAssign) {
	// BSTSet<int> bs1;
	// BSTSet<int> bs2;
	// bs1 = bs2;
	// ASSERT_EQ(bs1.size(), bs2.size());
}


TEST(BSTSetTest, canAdd) {
	BSTSet<int> bs1;
	bs1.add(1);
	bs1.add(1); // duplicate
	bs1.add(2);
	bs1.add(4);
	bs1.add(3);
	bs1.add(5);
	ASSERT_EQ(bs1.size(), 5);
	
	std::cout << bs1.toString() << "\n";
}

TEST(BSTSetTest, checkContains) {
	BSTSet<int> bs;
	bs.add(1);
	bs.add(2);
	bs.add(3);
	bs.add(4);
	bs.add(5);
	ASSERT_TRUE(bs.contains(1));
	ASSERT_TRUE(bs.contains(2));
	ASSERT_TRUE(bs.contains(3));
	ASSERT_FALSE(bs.contains(9));
	ASSERT_FALSE(bs.contains(10));
}


// TEST(BSTSetTest, toString) {
// 	HashSet<int> hs1 (someHashFunction);
// 	std::cout << hs1.toString() << "\n";
// }

