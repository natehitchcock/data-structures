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
	ASSERT_TRUE(false) << "Unimplemented";
}

TEST(ListConstruction, Copied) {
	ASSERT_TRUE(false) << "Unimplemented";
}

TEST(ListConstruction, Moved) {
	ASSERT_TRUE(false) << "Unimplemented";
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

