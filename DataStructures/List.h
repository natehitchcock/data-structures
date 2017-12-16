/*
 * Implementation of a doubly-linked list with head and tail pointers
 *  Built with move semantics in mind
*/

#include <initializer_list>

// [TODO] handle custom allocator
// [TODO] handle generic iteration
// [TODO] evaluate using smart pointers instead of raw pointers
// [TODO] support for range-based for loop!
// [TODO] const correctness pass
template<typename T, typename SizeT = int>
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
	SizeT size;

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
	
	// [TODO] alias away List<T> to avoid defaulting SizeT on passed back types
	// [TODO] replace copy/move ctor with perfect-forwarded ctor that uses
	//	the assigment operator
	/***
	 * Assignment operator for lvalue refs
	 */
	List<T> operator=(const List<T>& rhs)
	{
		Node<T>* pcur = rhs.head;
		while (pcur != nullptr)
		{
			PushBack(*(pcur->value));
			pcur = pcur->next;
		}
		size = rhs.size;
	}

	/***
	 * Assignment operator for rvalue refs
	 */
	List<T> operator=(List<T>&& rhs)
	{
		std::swap(head, rhs.head);
		std::swap(tail, rhs.tail);
		size = rhs.size;
	}

	/////
	//	List Reading Operations
	/////

	/***
	 * Getter for size of list
	 */
	SizeT Size()
	{
		return size;
	}

	/***
	 * Retrieves a copy of the element at the given index
	 *	Allows read and write of the returned element
	 *	- Does not currently handle exceptions for out of range access
	 */
	T& At(SizeT index) {
		Node<T>* curr = head;

		for (SizeT i = 0; i < index; ++i)
		{
			// ? what happens if the index is out of range
			//	Could just ignore the exception for now, let it get passed up to the caller
			// [TODO] add iterator types
	
			curr = curr->next;
		}

		return *(curr->value);
	}

	/////
	//	List Modifying Operations
	/////

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
	* Copies a list and adds it to the front of the list
	*/
	void PushFront(const List<T>& other)
	{
		Node<T>* curr = other.tail;

		while (curr != nullptr)
		{
			PushFront(*(curr->value));
			curr = curr->prev;
		}
	}

	/***
	* Copies a list and adds it to the front of the list
	*/
	void PushFront(List<T>&& other)
	{
		// If the other list is empty, just bailout
		if (other.tail == nullptr)
			return;

		if (head == nullptr)
		{
			std::swap(head, other.head);
			std::swap(tail, other.tail);
			std::swap(size, other.size);
		}
		else
		{
			head->prev = other.tail;
			other.tail->next = head;

			head = other.head;

			other.head = nullptr;
			other.tail = nullptr;
		}
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

	/***
	* Copies a list and adds it to the end of the list
	*/
	void PushBack(const List<T>& other)
	{
		Node<T>* curr = other.head;

		while (curr != nullptr)
		{
			PushBack(*(curr->value));
			curr = curr->next;
		}
	}

	/***
	* Moves a list to the end of the list
	*/
	void PushBack(List<T>&& other)
	{
		// If other list is empty, bailout
		if (other.head == nullptr)
			return;

		if (tail == nullptr)
		{
			std::swap(head, other.head);
			std::swap(tail, other.tail);
			std::swap(size, other.size);
		} 
		else
		{
			tail->next = other.head;
			other.head->prev = tail;

			tail = other.tail;

			other.head = nullptr;
			other.tail = nullptr;
		}
	}

	
};