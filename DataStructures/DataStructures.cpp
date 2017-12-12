// DataStructures.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"
#include <iostream> 

List<int> makeList()
{
	// RVO!
	return List<int>({1, 3, 5, 7, 9, 11});
}

int main()
{
	// Ad-hoc testing
	// [TODO] get some real unit testing framework

	// default ctor
	{
		List<int> defaultList;
	}
	std::cout << "defaultList constructed";

	// init list ctor
	{
		List<int> listctorList({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
	}
	std::cout << "listctorList constructed";

	// copy ctor
	{
		List<int> listctorList({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
		List<int> copiedList(listctorList);
	}
	std::cout << "copiedList constructed";

	// move ctor
	{
		List<int> movedList(makeList());
	}
	std::cout << "movedList constructed";

	std::cout << "done...";
	std::getchar();
    return 0;
}

