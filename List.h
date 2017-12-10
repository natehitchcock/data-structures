/*
 * Implementation of a doubly-linked list with head and tail pointers
 *  Built with move semantics in mind
*/

template<typename T>
class List<T> 
{
  struct Node<T> 
  {
    T* value;
    Node<T>* pnext;
    Node<T>* pprev;
  }
  Node<T>* phead;
  Node<T>* ptail;
public:
  List<T>();// [TODO] ? covered by variadic ctor
  List<T>(... args);// [TODO] ? variadic ctor
  List<T>(List<T>& rhs);
  // [TODO] ? move semantics
  ~List<T>();
  
  // List modifying operations
  void push_front(const List<T>& rhs);
  void push_front(List<T> rhs);
  
  void push_back(const List<T>& rhs);
  void push_back(List<T> rhs);
  
  T pop_front();
  List<T> pop_front(unsigned count);
  
  T pop_back();
  List<T> pop_back(unsigned count);
  
  void insert(const List<T>& rhs, unsigned index);
  void insert(List<T> rhs, unsigned index);
  
  // Operator overloading for convenient operations
  List<T>& operator=(const List<T>& rhs);
  List<T>& operator+=(const List<T>& rhs);
  List<T>& operator>>=(List<T>& rhs) const;
  List<T>& operator<<=(const List<T>& rhs);
  
  List<T> operator+(const List<T>& rhs) const;
  List<T> operator>>(const List<T>& rhs) const;
  List<T> operator<<(const List<T>& rhs) const;
  
  // [NOTE] conversions ctor means that single T values will use non-ref versions
  List<T>& operator=(List<T> rhs);
  List<T>& operator+=(List<T> rhs);
  List<T> operator>>=(List<T> rhs) const;
  List<T>& operator<<=(List<T> rhs);
  
  List<T> operator+(List<T> rhs) const;
  List<T> operator>>(List<T> rhs) const;
  List<T> operator<<(List<T> rhs) const;
};