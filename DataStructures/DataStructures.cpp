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

TEST(ListGrowing, PushFrontCopy) {
	ASSERT_TRUE(false) << "Unimplemented";
}

TEST(ListGrowing, PushFrontMove) {
	ASSERT_TRUE(false) << "Unimplemented";
}

TEST(ListGrowing, PushBackCopy) {
	ASSERT_TRUE(false) << "Unimplemented";
}

TEST(ListGrowing, PushBackMove) {
	ASSERT_TRUE(false) << "Unimplemented";
}

GTEST_API_ int main(int argc, char **argv) {
	printf("Running main() from DataStructures.cpp\n");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

