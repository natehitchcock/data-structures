/*
 * Implementation of a doubly-linked list with head and tail pointers
 *  Built with move semantics in mind
*/

#include <initializer_list>

// [TODO] handle custom allocator
// [TODO] handle generic iteration
// [TODO] evaluate using smart pointers instead of raw pointers
// [TODO] support for range-based for loop!
template<typename T>
class List
{
	template<typename U>
	struct Node
	{
		U* value;
		Node<U>* pnext;
		Node<U>* pprev;
		Node() :
			pnext(nullptr),
			pprev(nullptr),
			value(nullptr)
		{

		}
	};

	Node<T>* phead;
	Node<T>* ptail;

public:
	List() :
		phead(nullptr),
		ptail(nullptr)
	{

	}

	List(std::initializer_list<T> args)
	{
		// ? Would it be faster/better to just hang on to the initializer list
		//	until we need to modify it? (copy on write)
		// ? How does std::vector init from the initializer list?
		for (auto& e : args)
		{
			push_back(e);
		}
	}

	List(const List<T>& rhs)
	{
		Node<T>* pcur = rhs.phead;
		while (pcur != nullptr)
		{
			push_back(*(pcur->value));
			pcur = pcur->pnext;
		}
	}

	List(List<T>&& rhs)
	{
		std::swap(phead, rhs.phead);
		std::swap(ptail, rhs.ptail);
	}
	
	~List()
	{
		// [TODO] replace with range-based for loop
		Node<T>* pcur = phead;
		while (pcur != nullptr)
		{
			Node<T>* pnext = pcur->pnext;
			delete pcur->value;
			delete pcur;
			pcur = pnext;
		}

		phead = nullptr;
		ptail = nullptr;
	}
  
	// List modifying operations
	void push_front(const T& element)
	{
		Node<T>* oldHead = phead;

		Node<T>* newNode = new Node<T>();
		newNode->value = new T(element);
		newNode->pnext = oldHead;

		if (oldHead != nullptr)
		{
			oldHead->pprev = newNode;
		} 
		else
		{
			ptail = newNode;
		}

		phead = newNode;
	}
  
	void push_back(const T& element)
	{
		Node<T>* oldTail = ptail;

		Node<T>* newNode = new Node<T>();
		newNode->value = new T(element);
		newNode->pprev = oldTail;

		if (oldTail != nullptr)
		{
			oldTail->pnext = newNode;
		}
		else
		{
			phead = newNode;
		}

		ptail = newNode;
	}

	//T pop_front();
	//List<T> pop_front(unsigned count);
	//
	//T pop_back();
	//List<T> pop_back(unsigned count);
	//
	//void insert(const List<T>& rhs, unsigned index);
	//void insert(List<T> rhs, unsigned index);
	//
	//// Operator overloading for convenient operations
	//List<T>& operator=(const List<T>& rhs);
	//List<T>& operator+=(const List<T>& rhs);
	//List<T>& operator>>=(List<T>& rhs) const;
	//List<T>& operator<<=(const List<T>& rhs);
	//
	//List<T> operator+(const List<T>& rhs) const;
	//List<T> operator>>(const List<T>& rhs) const;
	//List<T> operator<<(const List<T>& rhs) const;
	//
	//// [NOTE] conversions ctor means that single T values will use non-ref versions
	//List<T>& operator=(List<T> rhs);
	//List<T>& operator+=(List<T> rhs);
	//List<T> operator>>=(List<T> rhs) const;
	//List<T>& operator<<=(List<T> rhs);
	//
	//List<T> operator+(List<T> rhs) const;
	//List<T> operator>>(List<T> rhs) const;
	//List<T> operator<<(List<T> rhs) const;
};