// DataStructures.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"
#include "gtest/gtest.h"
#include <iostream> 

TEST(ListConstruction, Default) {
	List<int> list;
}

TEST(ListConstruction, InitializerList) {
	List<int> list = { 1, 2, 3, 4, 5, 6, 7 };
	ASSERT_EQ(list.Size(), 7);
}

TEST(ListConstruction, Copied) {
	List<int> list = { 1, 2, 3, 4, 5};
	ASSERT_EQ(list.Size(), 5);
	List<int> copy(list);
	ASSERT_EQ(copy.Size(), list.Size()) << "Copied list was a different size than original";
}

List<int> make_list() {
	return { 1, 2, 3 };
}

TEST(ListConstruction, Moved) {
	List<int> moved(make_list());
	ASSERT_EQ(moved.Size(), 3);
}

TEST(ListReading, At) {
	List<int> list = {12345, 54321, 666, 69};

	ASSERT_EQ(list.Size(), 4);
	ASSERT_EQ(list.At(0), 12345);
	ASSERT_EQ(list.At(1), 54321);
	ASSERT_EQ(list.At(2), 666);
	ASSERT_EQ(list.At(3), 69);
}

TEST(ListGrowing, PushFront) {
	List<int> list;
	
	ASSERT_EQ(list.Size(), 0);
	list.PushFront(1);
	ASSERT_EQ(list.Size(), 1);
}

TEST(ListGrowing, PushFrontList) {
	List<int> list;

	List<int> newFront = { 4, 4, 4, 4 };
	ASSERT_EQ(list.Size(), 0);
	list.PushFront(newFront);
	ASSERT_EQ(list.Size(), 4);
}

TEST(ListGrowing, PushFrontListOrder) {
	List<int> list = { 7 };

	List<int> newFront = { 1, 2, 3, 4 };
	ASSERT_EQ(list.Size(), 1);
	list.PushFront(newFront);
	ASSERT_EQ(list.Size(), 5);
	ASSERT_EQ(list.At(0), 1);
	ASSERT_EQ(list.At(4), 7);
	ASSERT_EQ(list.At(3), 4);
}

TEST(ListGrowing, PushBack) {
	List<int> list;

	ASSERT_EQ(list.Size(), 0);
	list.PushBack(1);
	ASSERT_EQ(list.Size(), 1);
}

TEST(ListGrowing, PushBackList) {
	List<int> list;

	List<int> newBack = { 4, 4, 4, 4 };
	ASSERT_EQ(list.Size(), 0);
	list.PushBack(newBack);
	ASSERT_EQ(list.Size(), 4);
}

GTEST_API_ int main(int argc, char **argv) {
	printf("Running main() from DataStructures.cpp\n");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

