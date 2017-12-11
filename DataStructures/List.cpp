#include "stdafx.h"
#include "List.h"

template<typename T>
List<T>::List() :
	phead(nullptr),
	ptail(nullptr)
{

}

template<typename T>
List<T>::List(std::initializer_list<T> args)
{
	// [TODO] copy intializer list
	// ? Would it be faster/better to just hang on to the initializer list
	//	until we need to modify it? (copy on write)
	// ? How does std::vector init from the initializer list?
}

template<typename T>
List<T>::List(const List<T>& rhs)
{
	// [TODO] copy list from rhs
}

template<typename T>
List<T>::List(List<T>&& rhs)
{
	// [TODO] copy and swap from rvalue ref
}

template<typename T>
List<T>::~List()
{
	// [TODO] cleanup nodes
}
