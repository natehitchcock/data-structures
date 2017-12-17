/*
 * Implementation of a doubly-linked list with head and tail pointers
 *  Built with move semantics in mind
*/

#include <initializer_list>

// [NOTE] There is a lot of redundancy with a doubly linked list, specifically
//	with the directionality of an operation (pushFRONT vs pushBACK).
//	I wonder if there is a better way to write this that re-uses some code
//	between those operations. Maybe the solution is generalizing iteration?
//	Maybe generalizing list operations to node operations?

// [NOTE] There is also redundancy with functions that take a single item and
//	a list of items. A conversion ctor from T -> ListT would solve this,
//	removing the need for functions that take a single item in lieu of their
//	list-taking counterparts


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
	// ? is typedef better, or alias?
	typedef List<T, SizeT> ListT;

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
	List(std::initializer_list<T> args):
		head(nullptr),
		tail(nullptr),
		size(0)
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
	List(const ListT& rhs) :
		head(nullptr),
		tail(nullptr),
		size(0)
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
	List(ListT&& rhs) :
		head(nullptr),
		tail(nullptr),
		size(0)
	{
		std::swap(head, rhs.head);
		std::swap(tail, rhs.tail);
		std::swap(size, rhs.size);
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
	
	// [TODO] replace copy/move ctor with perfect-forwarded ctor that uses
	//	the assigment operator
	/***
	 * Assignment operator for lvalue refs
	 */
	ListT& operator=(const ListT& rhs)
	{
		Node<T>* pcur = rhs.head;
		while (pcur != nullptr)
		{
			PushBack(*(pcur->value));
			pcur = pcur->next;
		}
		size = rhs.size;

		return *this;
	}

	/***
	 * Assignment operator for rvalue refs
	 */
	ListT& operator=(ListT&& rhs)
	{
		std::swap(head, rhs.head);
		std::swap(tail, rhs.tail);
		size = rhs.size;

		return *this;
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
	void PushFront(const ListT& other)
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
	void PushFront(ListT&& other)
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
	void PushBack(const ListT& other)
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
	void PushBack(ListT&& other)
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

	/***
	 * Removes the front element from the list and returns a copy
	 */
	T PopFront() 
	{
		// ? what happens on an empty list?
		//	maybe a wrapper class could be useful here, to avoid copying
		//	and allow special return values (like 'none')
		// ? what would std::vector do (WWSVD, kind of a mantra at this point)

		// For now, allow exception to be passed up when operating on an empty list
		T ret = *(head->value);
		Node<T>* oldHead = head;
		head = head->next;
		head->prev = nullptr;

		if (oldHead == tail)
		{
			tail = tail->next;
		}

		delete oldHead->value;
		delete oldHead;

		--size;
		return ret;
	}

	/***
	 * Removes a sublist from the front of the list
	 *	count must be positive
	 */
	ListT PopFront(SizeT count)
	{
		if (count <= 0) return ListT();

		Node<T>* oldHead = head;
		Node<T>* curr = oldHead;

		for (SizeT i = 0; i < count - 1; ++i)
		{
			// If we try to pop more than the list has, exception will occur
			curr = curr->next;
		}

		// Make the new list
		ListT newList;
		newList.head = oldHead;
		newList.tail = curr;
		newList.size = count;

		// Update the current list head and tail
		head = curr->next;
		head->prev = nullptr;
		if (curr == tail)
		{
			tail = tail->next;
		}
		
		// Finish severing the new list from the old
		curr->next = nullptr;

		size -= count;

		return newList;
	}

	/***
	 * Removes the last item in the list and returns a copy of it
	 */
	T PopBack()
	{
		T ret = *(tail->value);
		Node<T>* oldTail = tail;
		tail = tail->prev;
		tail->next = nullptr;

		if (oldTail == head)
		{
			head = head->prev;// nullptr op, guaranteed
		}

		delete oldTail->value;
		delete oldTail;

		--size;

		return ret;
	}

	/***
	 * Removes a sublist from the back of the list
	 *	count must be positive
	 */
	ListT PopBack(SizeT count)
	{
		if (count <= 0) return ListT();
		Node<T>* oldTail = tail;
		Node<T>* curr = oldTail;

		for (SizeT i = 0; i < count - 1; ++i)
		{
			// If we try to pop more than the list has, exception will occur
			curr = curr->prev;
		}

		// Make the new list
		ListT newList;
		newList.head = curr;
		newList.tail = oldTail;
		newList.size = count;

		// Update the current list head and tail
		tail = curr->prev;
		tail->next = nullptr;
		if (curr == head)
		{
			head = head->prev;
		}

		// Finish severing the new list from the old
		curr->prev = nullptr;

		size -= count;

		return newList;
	}

	/***
	 * Inserts an element into the list
	 *	element is a copy of the item
	 *	index must be between 0 and list size
	 */
	// [NOTE] this could be done a lot better with move ction and in-place new
	//	current implementation leaves a lot to be desired
	void Insert(T element, SizeT index)
	{
		if (index == size)
		{
			PushBack(element);
			return;
		}
		else if (index == 0)
		{
			PushFront(element);
			return;
		}

		// [TODO] encapsulate resource mgmt in case of exception
		Node<T>* newNode = new Node<T>();
		newNode->value = new T(element);

		// The insertion point is somewhere in the body of the list
		Node<T>* curr = head;
		for (SizeT i = 0; i < index; ++i)
		{
			curr = curr->next;
		}

		curr->prev->next = newNode;
		newNode->prev = curr->prev;
		newNode->next = curr;
		curr->prev = newNode;

		++size;
	}

	/***
	 * Inserts a list into the list, copying every item
	 *	list is the list to insert, by copy
	 *	index must be [0, list.Size()]
	 */
	// [NOTE] could use a move version
	void Insert(ListT list, SizeT index)
	{
		if (index == size)
		{
			PushBack(list);
			return;
		}
		else if (index == 0)
		{
			PushFront(list);
			return;
		}

		Node<T>* curr = head;
		for (SizeT i = 0; i < index; ++i)
		{
			curr = curr->next;
		}
		Node<T>* before = curr->prev;

		Node<T>* otherCurr = list.head;
		for (SizeT i = 0; i < list.size; ++i)
		{
			Node<T>* newNode = new Node<T>();
			newNode->value = new T(*(otherCurr->value));

			before->next = newNode;
			newNode->prev = before;
			before = newNode;

			otherCurr = otherCurr->next;
		}

		size += list.size;

		curr->prev = before;
		before->next = curr;
	}

	/***
	 * Removes a sublist from the list and returns it
	 *	start must be [0, list.Size()]
	 *	count must be [0, list.Size() - start]
	 */
	ListT Slice(SizeT start, SizeT count)
	{
		Node<T>* newListHead = head;
		for (SizeT i = 0; i < start; ++i)
		{
			newListHead = newListHead->next;
		}

		// [TODO] remove redundant iteration
		Node<T>* newListTail = newListHead;
		for (SizeT i = 0; i < count - 1; ++i)
		{
			newListTail = newListTail->next;
		}

		if (newListHead == head)
		{
			head = newListTail->next;
		}
		else
		{
			newListHead->prev->next = newListTail->next;
		}

		if (newListTail == tail)
		{
			tail = newListHead->prev;
		}
		else
		{
			newListTail->next->prev = newListHead->prev;
		}

		newListHead->prev = nullptr;
		newListTail->next = nullptr;

		ListT newList;
		newList.head = newListHead;
		newList.tail = newListTail;
		newList.size = count;

		size -= count;

		return newList;
	}
};