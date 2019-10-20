#include <gtest/gtest.h>
#include <string>
#include "AVLSet.hpp"


TEST(AVLSetTest, canDefaultConstruct)
{
	AVLSet<int> a;
	ASSERT_EQ(0, a.size());
}

namespace
{
	template <typename T>
	void takeBSTByValue(AVLSet<T> a)
	{
	}
}

TEST(AVLSetTest, canCopyConstruct)
{
	AVLSet<int> a1;
	a1.add(1);
	a1.add(3);
	a1.add(2);
	a1.add(11);
	a1.add(31);
	a1.add(21);
	a1.add(12);
	a1.add(33);
	a1.add(26);
	a1.add(15);
	a1.add(38);
	a1.add(28);

	AVLSet<int> a2 = a1;
	AVLSet<int> a3 {a1};
	takeBSTByValue(a1);

	ASSERT_EQ(a1.size(), 12);
	ASSERT_EQ(a2.size(), 12);
	ASSERT_EQ(a1.size(), a2.size());
	ASSERT_EQ(a1.size(), a3.size());
}


TEST(AVLSetTest, canAssign) {
	// AVLSet<int> a1;
	// AVLSet<int> a2;
	// a1 = a2;
	// ASSERT_EQ(a1.size(), a2.size());
}


TEST(AVLSetTest, canAdd) {
	AVLSet<int> a;
	a.add(1);
	a.add(1); // duplicate
	a.add(2);
	a.add(3);
	a.add(4);
	a.add(5);
	ASSERT_EQ(a.size(), 5);
	std::cout << a.height() << "\n";
}

TEST(AVLSetTest, checkContains) {
	AVLSet<int> a;
	a.add(4);
	a.add(5);
	a.add(1);
	a.add(2);
	a.add(3);
	ASSERT_TRUE(a.contains(1));
	ASSERT_TRUE(a.contains(2));
	ASSERT_TRUE(a.contains(3));
	ASSERT_FALSE(a.contains(9));
	ASSERT_FALSE(a.contains(10));
}


TEST(AVLSetTest, checkHeight) {
	AVLSet<int> a;
	a.add(1);
	a.add(2);
	a.add(3);
	a.add(4);
	a.add(5);
	std::cout << "height is " << a.height() << "\n";
	ASSERT_EQ(a.height(), 3);

	AVLSet<int> a2;
	a2.add(1);
	a2.add(3);
	a2.add(2);
	a2.add(11);
	a2.add(31);
	a2.add(21);
	a2.add(12);
	a2.add(33);
	a2.add(26);
	a2.add(15);
	a2.add(38);
	a2.add(28);
	std::cout << "height is " << a2.height() << "\n";
	ASSERT_EQ(a.height(), 3);
}