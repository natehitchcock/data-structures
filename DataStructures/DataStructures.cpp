// DataStructures.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"
#include "gtest/gtest.h"
#include <iostream> 

TEST(ListConstruction, Default) 
{
	List<int> list;
}

TEST(ListConstruction, InitializerList) 
{
	List<int> list = { 1, 2, 3, 4, 5, 6, 7 };
	ASSERT_EQ(list.Size(), 7);
}

TEST(ListConstruction, Copied) 
{
	List<int> list = { 1, 2, 3, 4, 5};
	ASSERT_EQ(list.Size(), 5);
	List<int> copy(list);
	ASSERT_EQ(copy.Size(), list.Size()) << "Copied list was a different size than original";
}

List<int> make_list() 
{
	return { 1, 2, 3 };
}

TEST(ListConstruction, Moved) 
{
	List<int> moved(make_list());
	ASSERT_EQ(moved.Size(), 3);
}

TEST(ListAssignment, Copied)
{
	List<int> list = {1, 2, 3, 4};
	List<int> copied = list;
	ASSERT_EQ(copied.Size(), 4);
}

TEST(ListAssignment, Moved)
{
	List<int> copied = make_list();
	ASSERT_EQ(copied.Size(), 3);
}

TEST(ListReading, At) 
{
	List<int> list = {12345, 54321, 666, 69};

	ASSERT_EQ(list.Size(), 4);
	ASSERT_EQ(list.At(0), 12345);
	ASSERT_EQ(list.At(1), 54321);
	ASSERT_EQ(list.At(2), 666);
	ASSERT_EQ(list.At(3), 69);
}

TEST(ListWriting, At)
{
	List<int> list = { 12345, 54321, 666, 69 };

	ASSERT_EQ(list.At(1), 54321);
	list.At(1) = 789;
	ASSERT_EQ(list.At(1), 789);
}

TEST(ListGrowing, PushFront) 
{
	List<int> list;
	
	ASSERT_EQ(list.Size(), 0);
	list.PushFront(1);
	ASSERT_EQ(list.Size(), 1);
}

TEST(ListGrowing, PushFrontList) 
{
	List<int> list;

	List<int> newFront = { 4, 4, 4, 4 };
	ASSERT_EQ(list.Size(), 0);
	list.PushFront(newFront);
	ASSERT_EQ(list.Size(), 4);
}

TEST(ListGrowing, PushFrontListOrder) 
{
	List<int> list = { 7 };

	List<int> newFront = { 1, 2, 3, 4 };
	ASSERT_EQ(list.Size(), 1);
	list.PushFront(newFront);
	ASSERT_EQ(list.Size(), 5);
	ASSERT_EQ(list.At(0), 1);
	ASSERT_EQ(list.At(4), 7);
	ASSERT_EQ(list.At(3), 4);
}

TEST(ListGrowing, PushBack) 
{
	List<int> list;

	ASSERT_EQ(list.Size(), 0);
	list.PushBack(1);
	ASSERT_EQ(list.Size(), 1);
}

TEST(ListGrowing, PushBackList) 
{
	List<int> list;

	List<int> newBack = { 4, 4, 4, 4 };
	ASSERT_EQ(list.Size(), 0);
	list.PushBack(newBack);
	ASSERT_EQ(list.Size(), 4);
}

TEST(ListGrowing, PushEmptyLists)
{
	List<int> list;

	List<int> empty;
	// If any exceptions occur, test will fail
	list.PushFront(empty);
	list.PushBack(empty);

	auto makeEmptyList = [=]() -> List<int> {return List<int>();};
	list.PushBack(makeEmptyList());
	list.PushFront(makeEmptyList());

	// Now push empty lists onto non-empty lists
	list.PushBack(1);
	list.PushFront(empty);
	list.PushBack(empty);
	list.PushBack(makeEmptyList());
	list.PushFront(makeEmptyList());
}

TEST(ListShrinking, PopFront) 
{
	List<int> list = { 1, 2, 3, 4 };

	ASSERT_EQ(list.Size(), 4);
	int i = list.PopFront();
	ASSERT_EQ(list.Size(), 3);
	ASSERT_EQ(i, 1);
	i = list.PopFront();
	ASSERT_EQ(list.Size(), 2);
	ASSERT_EQ(i, 2);
}

TEST(ListShrinking, PopFrontList)
{
	List<int> list = { 1, 2, 3, 4 };

	ASSERT_EQ(list.Size(), 4);
	List<int> popped = list.PopFront(2);
	ASSERT_EQ(list.Size(), 2);
	ASSERT_EQ(popped.At(0), 1);
	ASSERT_EQ(popped.At(1), 2);
	popped = list.PopFront(1);
	ASSERT_EQ(list.Size(), 1);
	ASSERT_EQ(popped.At(0), 3);
}

TEST(ListShrinking, PopBack) 
{
	List<int> list = { 1, 2, 3, 4 };

	ASSERT_EQ(list.Size(), 4);
	int i = list.PopBack();
	ASSERT_EQ(list.Size(), 3);
	ASSERT_EQ(i, 4);
	i = list.PopBack();
	ASSERT_EQ(list.Size(), 2);
	ASSERT_EQ(i, 3);
}

TEST(ListShrinking, PopBackList)
{
	List<int> list = { 1, 2, 3, 4 };

	ASSERT_EQ(list.Size(), 4);
	List<int> popped = list.PopBack(2);
	ASSERT_EQ(list.Size(), 2);
	ASSERT_EQ(popped.At(0), 3);
	ASSERT_EQ(popped.At(1), 4);
	popped = list.PopBack(1);
	ASSERT_EQ(list.Size(), 1);
	ASSERT_EQ(popped.At(0), 2);
}

TEST(ListInsert, SingleElement)
{
	List<int> list = {1, 2, 3, 4};

	ASSERT_EQ(list.Size(), 4);
	list.Insert(99, 2);
	ASSERT_EQ(list.Size(), 5);
	ASSERT_EQ(list.At(2), 99);
	list.Insert(666, 0);
	ASSERT_EQ(list.Size(), 6);
	ASSERT_EQ(list.At(0), 666);
	list.Insert(7777, 6);
	ASSERT_EQ(list.Size(), 7);
	ASSERT_EQ(list.At(6), 7777);
}

TEST(ListInsert, List)
{
	List<int> list = {1, 2, 3, 4};

	ASSERT_EQ(list.Size(), 4);
	List<int> sublist = { 99, 98, 97 };
	list.Insert(sublist, 2);
	ASSERT_EQ(list.Size(), 7);
	ASSERT_EQ(list.At(3), 98);
	ASSERT_EQ(list.At(4), 97);
	ASSERT_EQ(list.At(5), 3);
	sublist = {100, 101, 102};
	list.Insert(sublist, 0);
	ASSERT_EQ(list.Size(), 10);
	ASSERT_EQ(list.At(0), 100);
	ASSERT_EQ(list.At(1), 101);
	ASSERT_EQ(list.At(2), 102);
	ASSERT_EQ(list.At(3), 1);
}

TEST(ListInsert, EmptyList)
{
	List<int> list = { 1, 2, 3, 4 };

	ASSERT_EQ(list.Size(), 4);
	List<int> sublist;
	list.Insert(sublist, 2);
	ASSERT_EQ(list.Size(), 4);
	ASSERT_EQ(list.At(0), 1);
	ASSERT_EQ(list.At(1), 2);
	ASSERT_EQ(list.At(2), 3);
	ASSERT_EQ(list.At(3), 4);
}

TEST(ListSlice, SingleElement)
{
	List<int> list = { 1, 2, 3, 4 };

	ASSERT_EQ(list.Size(), 4);
	List<int> element = list.Slice(0, 1);
	ASSERT_EQ(list.Size(), 3);
	ASSERT_EQ(element.Size(), 1);
	ASSERT_EQ(element.At(0), 1);
}

TEST(ListSlice, List)
{
	List<int> list = { 1, 2, 3, 4 };

	ASSERT_EQ(list.Size(), 4);
	List<int> sublist = list.Slice(0, 3);
	ASSERT_EQ(list.Size(), 1);
	ASSERT_EQ(sublist.Size(), 3);
	ASSERT_EQ(sublist.At(0), 1);
	ASSERT_EQ(sublist.At(1), 2);
	ASSERT_EQ(sublist.At(2), 3);
}

TEST(ListSlice, EntireList)
{
	List<int> list = { 1, 2, 3, 4 };

	ASSERT_EQ(list.Size(), 4);
	List<int> sublist = list.Slice(0, 4);
	ASSERT_EQ(list.Size(), 0);
	ASSERT_EQ(sublist.Size(), 4);
	ASSERT_EQ(sublist.At(0), 1);
	ASSERT_EQ(sublist.At(1), 2);
	ASSERT_EQ(sublist.At(2), 3);
	ASSERT_EQ(sublist.At(3), 4);
}

TEST(ListSlice, NoElements)
{
	List<int> list = { 1, 2, 3, 4 };

	ASSERT_EQ(list.Size(), 4);
	List<int> sublist = list.Slice(0, 0);
	ASSERT_EQ(list.Size(), 4);
	ASSERT_EQ(sublist.Size(), 0);
}

GTEST_API_ int main(int argc, char **argv) {
	printf("Running main() from DataStructures.cpp\n");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

