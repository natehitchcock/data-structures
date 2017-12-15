/*
 * Implementation of a doubly-linked list with head and tail pointers
 *  Built with move semantics in mind
*/

#include <initializer_list>

// [TODO] handle custom allocator
// [TODO] handle generic iteration
// [TODO] evaluate using smart pointers instead of raw pointers
// [TODO] support for range-based for loop!
// [TODO] replace size type with template parameter to allow for larger sizes
template<typename T>
class List
{
	template<typename U>
	struct Node
	{
		U* value;
		Node<U>* next;
		Node<U>* prev;
		Node() :
			next(nullptr),
			prev(nullptr),
			value(nullptr)
		{

		}
	};

	Node<T>* head;
	Node<T>* tail;
	int size;

public:
    /***
     * Default ctor
     */
    List() :
		head(nullptr),
		tail(nullptr),
		size(0) // ? would size be 0 initialized in all cases, without this?
	{

	}

    /***
     * Initializer list ctor
     */
	List(std::initializer_list<T> args)
	{
		// ? Would it be faster/better to just hang on to the initializer list
		//	until we need to modify it? (copy on write)
		// ? How does std::vector init from the initializer list?
		// ? How should we handle exceptions here?
		// ? are initializer lists rvalues when passed in with the new syntax? maybe not relevant, but interesting
		for (auto& e : args)
		{
			PushBack(e);
		}

		size = args.size();
	}

    /***
     * Copy ctor
     */
	List(const List<T>& rhs)
	{
		// ? what happens if we throw an exception (like OOM) in here
		Node<T>* pcur = rhs.head;
		while (pcur != nullptr)
		{
			PushBack(*(pcur->value));
			pcur = pcur->next;
		}
		size = rhs.size;
	}

    /***
     * Move ctor
     */
	List(List<T>&& rhs)
	{
		std::swap(head, rhs.head);
		std::swap(tail, rhs.tail);
		size = rhs.size;
	}
    
    /***
     * Dtor
     */
	~List()
	{
		// [TODO] replace with range-based for loop
		Node<T>* pcur = head;
		while (pcur != nullptr)
		{
			Node<T>* pnext = pcur->next;
			delete pcur->value;
			delete pcur;
			pcur = pnext;
		}

		head = nullptr;
		tail = nullptr;
	}

	int Size() 
	{
		return size;
	}
  
	/***
     * Copies a value and adds it to the front of the list
     */
	void PushFront(const T& element)
	{
		Node<T>* oldHead = head;

		Node<T>* newNode = new Node<T>();
		newNode->value = new T(element);
		newNode->next = oldHead;

		if (oldHead != nullptr)
		{
			oldHead->prev = newNode;
		} 
		else
		{
			tail = newNode;
		}

		head = newNode;
		++size;
	}
  
    /***
     * Copies a value and adds it to the end of the list
     */
	void PushBack(const T& element)
	{
		// ? maybe this could be re-written as node operations and nodes could
		//	have a prepend/postpend operation?
		//	might not help reduce this code size, but could be useful
		//  in the future.
		Node<T>* oldTail = tail;

		Node<T>* newNode = new Node<T>();
		newNode->value = new T(element);
		newNode->prev = oldTail;

		if (oldTail != nullptr)
		{
			oldTail->next = newNode;
		}
		else
		{
			head = newNode;
		}

		tail = newNode;
		++size;
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