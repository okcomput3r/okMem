#pragma once

#include <cstdint>
#include <iostream>

namespace Memory::Containers {

//  ________________________________________________________________________________
// /--------------------------------------------------------------------------------\
<<<<<<< HEAD
// |- -|
// |- -|
// |-                              << STACK ARRAY >> -|
// |- -|
// |- -|
// \--------------------------------------------------------------------------------/

/*
 * The stack_array Container is supose to act like a collection of elements
 * contiguious in memory (I know its obvious smartass). The memory is allocated
 * in the stack and it can be specify how big it should be, in order to optimize
 * space.
=======
// |-                                                                              -|
// |-                              << STACK ARRAY >>                               -|
// |-                                                                              -|
// \--------------------------------------------------------------------------------/


/***
 *
 * The stack_array Container is supose to act like a collection of elements 
 * contiguious in memory. The memory is allocated in the stack and it can 
 * be specify how big it should be, in order to optimize space.
>>>>>>> 9eac27e (array implementation)
 *
 */

//////////////////////////////
// ____  DECLARATION  ____ //
/////////////////////////////

template <typename T, uint32_t N> struct stack_array {

  typedef T *iterator;
  typedef const T *const_iterator;

  inline iterator begin() { return &p_items[0]; }
  inline iterator end() { return &p_items[size]; }
  inline const_iterator begin() const { return &p_items[0]; }
  inline const_iterator end() const { return &p_items[size]; }

  inline const T &operator[](uint32_t index) const;
  inline T &operator[](uint32_t index);
  inline stack_array &operator=(const stack_array &other);

  T p_items[N];
  uint32_t size;

  stack_array();
  stack_array(stack_array &other);
};

//////////////////////////////
// ____ IMPLEMENTATION ____ //
/////////////////////////////

template <typename T, uint32_t N> stack_array<T, N>::stack_array() {
  // p_items = static_cast<T*>(alloca(N  * sizeof(T)));
  size = N;
}

template <typename T, uint32_t N>
stack_array<T, N>::stack_array(stack_array &other) {
  if (size != other.size) { /* DEBUG ASSERT */
  }

  for (uint32_t i = 0; i < other.size; i++) {
    p_items[i] = other.p_items[i];
  }
  size = other.size;
}

template <typename T, uint32_t N>
inline const T &stack_array<T, N>::operator[](uint32_t index) const {
  if (index < 0 || index >= size) { /* DEBUG TRACE */
  }
  return p_items[index];
}

template <typename T, uint32_t N>
inline T &stack_array<T, N>::operator[](uint32_t index) {
  if (index < 0 || index >= size) { /* DEBUG TRACE */
  }
  return p_items[index];
}

template <typename T, uint32_t N>
inline stack_array<T, N> &
stack_array<T, N>::operator=(const stack_array &other) {
  if (size != other.size) { /* DEBUG ASSERT */
  }

  for (uint32_t i = 0; i < other.size; ++i) {
    p_items[i] = other.p_items[i];
  }
  size = other.size;

  return *this;
}

// END OF MEMORY::CONTAINER::stack_array<>

//  ________________________________________________________________________________
// /--------------------------------------------------------------------------------\
<<<<<<< HEAD
// |- -|
// |- -|
// |-                                 << VECTOR >> -|
// |- -|
// |- -|
// \--------------------------------------------------------------------------------/

/*
 *  The vector Container is a generic array with the ability to change
 *  size to acomodate new data.
=======
// |-                                                                              -|
// |-                                 << VECTOR >>                                 -|
// |-                                                                              -|
// \--------------------------------------------------------------------------------/



/*** 
 *
 *  The vector Container is a generic array with the ability to change 
 *  size to acomodate new data. 
>>>>>>> 9eac27e (array implementation)
 *  The maximum size of this array is 2^32 = 4.294.967.296 (~4.3 billion items)
 * ºbut it is likely that you run out of memory way before reaching such
 *  number.
 *
 *  Usage:
 *
 *    -> There are two ways to create a vector:
 *        1. Calling the defalut constructor, wich allocates <s_default_vector_size> elements into 
 *           the vector.
 *           ej.. vector<int> default_vec {};
 *
 *        2. Calling the constructor and specifying the number of elements that needs allocation.
 *           ej.. vector<int> custom_vec {10}; <-- this allocates 10 ints;
 *
 *    ->  To push an item into the array, there are two ways:
 *        1. By calling the push_back() function, witchs moves (if posible) the element into the
 *           next position of the array.
 *
 *        2. By calling the emplace_back() function, witchs creates the object inside the desired
 *           position of the vector, thus avoiding an extra construction and posible memory allocation.
 *           To call this function, you need to give to the function the parameters required to 
 *           create that structure.
 *           ej.. 
 *
 *            struct int&float
 *            {
 *              int   int_number;
 *              float float_number;
 *
 *              int&float(int a, float b)
 *               : int_number(a), float_number(b) {}
 *            }
 *
 *            int main()
 *            {
 *                vector<int&float> newVec {}
 * 
 *                // push_back
 *                newVec.push_back(int&float(1, 0.0f)) <-- creates the object and then moves it to the vector
 *
 *               // emplace_back
 *                newVec.emplace_back(1, 0.0f);        <-- passes the argument to the vector directly
 *            }
 *
 *    ->  By default, the vector grows half its size each time it needs to resize, this can be changed
 *        by calling the function change_growth_ratio(float newRatio).
 *
 *  TODO:
 *  - implementation of srinking capabilities
 *  - implementation of policies for srinking and growing
 *  - fix the fuckass std::string implementation god I hate that shit dude
 *  - optimize for small vectors -> up to a certain threshold allocate on the
 * stack
 *
 */

//////////////////////////////
// ____  DECLARATION  ____ //
/////////////////////////////

static const uint32_t s_default_vector_size{10};

template <typename T> struct vector {

  typedef T *iterator;
  typedef const T *const_iterator;

  inline iterator begin() { return &p_items[0]; }
  inline iterator end() { return &p_items[size]; }
  inline const_iterator begin() const { return &p_items[0]; }
  inline const_iterator end() const { return &p_items[size]; }

  inline const T &operator[](uint32_t index) const;
  inline T &operator[](uint32_t index);
  inline vector &operator=(const vector &other);
  inline vector &operator=(const vector &&other);

  // constructor / destructor
  vector();
  vector(uint32_t init_size);
  vector(vector &other);
  vector(vector &&other);

  ~vector();

  template <typename... Args> T &emplace_back(Args &&...item);
  void push_back(T &item);
  void push_back(T &&item);
  void pop_back();
  void clear();
  void resize(uint32_t newCapacity);
  inline void change_growth_ratio(float newRatio) { growth_ratio = newRatio; }

  // Members

  T *p_items{};
  float growth_ratio{0.5f};
  uint32_t size{0};
  uint32_t capacity{0};
  uint32_t explicit_padding; // 32 bits -> 4
};

//////////////////////////////
// ____ IMPLEMENTATION ____ //
/////////////////////////////

template <typename T> vector<T>::vector() {

  resize(s_default_vector_size);
  size = 0;
  capacity = s_default_vector_size;
}

template <typename T> vector<T>::vector(uint32_t init_size) {

  resize(init_size);
  size = 0;
  capacity = init_size;
}

template <typename T> vector<T>::vector(vector &other) {

  T *p_newMem = static_cast<T *>(::operator new(other.capacity * sizeof(T)));

  for (int i = 0; i < other.size; ++i)
    p_newMem[i] = other.p_items[i];

  for (int i = 0; i < size; i++)
    p_items[i].~T();

  ::operator delete(p_items, sizeof(T) * capacity);

  p_items = p_newMem;
  size = other.size;
  capacity = other.capacity;
  growth_ratio = other.growth_ratio;
}

template <typename T> vector<T>::vector(vector &&other) {

  T *p_newMem = static_cast<T *>(::operator new(other.capacity * sizeof(T)));

  for (int i = 0; i < other.size; ++i)
    p_newMem[i] = std::move(other.p_items[i]);

  for (int i = 0; i < size; ++i)
    p_items[i].~T();

  ::operator delete(p_items, sizeof(T) * capacity);

  p_items = p_newMem;
  size = other.size;
  capacity = other.capacity;
  growth_ratio = other.growth_ratio;
}

template <typename T> vector<T>::~vector() {
  clear();
  ::operator delete(p_items, sizeof(T) * capacity);
}

template <typename T> void vector<T>::push_back(T &item) {
  if (size >= capacity)
    resize(capacity + capacity * growth_ratio);

  p_items[size] = item;
  ++size;
}

template <typename T> void vector<T>::push_back(T &&item) {
  if (size >= capacity)
    resize(capacity + capacity * growth_ratio);

  p_items[size] = std::move(item);
  ++size;
}

template <typename T>
template <typename... Args>
T &vector<T>::emplace_back(Args &&...args) {

  if (size >= capacity)
    resize(capacity + capacity * growth_ratio);

  new (&p_items[size]) T(std::forward<Args>(args)...);
  return p_items[size++];
}

template <typename T> void vector<T>::pop_back() {
  if (size > 0)
    p_items[size--].~T();
}

template <typename T> void vector<T>::resize(uint32_t newCapacity) {

  T *p_newMem = static_cast<T *>(::operator new(newCapacity * sizeof(T)));

  for (uint32_t i = 0; i < size; ++i)
    p_newMem[i] = std::move(p_items[i]);

  for (uint32_t i = 0; i < size; ++i)
    p_items[i].~T();

  ::operator delete(p_items, sizeof(T) * capacity);
  p_items = p_newMem;
  capacity = newCapacity;
}

template <typename T> void vector<T>::clear() {

  for (uint32_t i = 0; i < size; ++i)
    p_items[i].~T();

  size = 0;
}

template <typename T>
inline const T &vector<T>::operator[](uint32_t index) const {
  if (index >= size || index < 0) { /*DEBUG TRACE*/
  }

  return p_items[index];
}

template <typename T> inline T &vector<T>::operator[](uint32_t index) {
  if (index >= size || index < 0) { /*DEBUG TRACE*/
  }

  return p_items[index];
}

template <typename T>
inline vector<T> &vector<T>::operator=(const vector &other) {

  T *p_newMem = static_cast<T *>(::operator new(other.capacity * sizeof(T)));

  for (uint32_t i = 0; i < other.size; ++i)
    p_newMem[i] = other.p_items[i];

  for (uint32_t i = 0; i < size; i++)
    p_items[i].~T();

  ::operator delete(p_items, sizeof(T) * capacity);

  p_items = p_newMem;
  size = other.size;
  capacity = other.capacity;
  growth_ratio = other.growth_ratio;

  return *this;
}

template <typename T>
inline vector<T> &vector<T>::operator=(const vector &&other) {

  T *p_newMem = static_cast<T *>(::operator new(other.capacity * sizeof(T)));

  for (uint32_t i = 0; i < other.size; ++i)
    p_newMem[i] = std::move(other.p_items[i]);

  for (uint32_t i = 0; i < size; ++i)
    p_items[i].~T();

  ::operator delete(p_items, sizeof(T) * capacity);

  p_items = p_newMem;
  size = other.size;
  capacity = other.capacity;
  growth_ratio = other.growth_ratio;

  return *this;
}

// cute little std::string boilerplate because it has its own
// fuckass constructors that fucks with my fuckass mallocs and throws errors
// everywhere

template <> vector<std::string>::~vector() { delete[] p_items; }

template <> void vector<std::string>::pop_back() {
  if (size > 0)
    size--;
}

template <> void vector<std::string>::resize(uint32_t newCapacity) {
  std::string *p_newMem = new std::string[newCapacity];

  for (uint32_t i = 0; i < size; ++i)
    p_newMem[i] = std::move(p_items[i]);

  delete[] p_items;

  p_items = p_newMem;
  capacity = newCapacity;
}

// END OF MEMORY::CONTAINERS::vector<>

//  ________________________________________________________________________________
// /--------------------------------------------------------------------------------\
<<<<<<< HEAD
// |- -|
// |- -|
// |-                              << ARRAY LIST >> -|
// |- -|
// |- -|
// \--------------------------------------------------------------------------------/

static const uint64_t s_default_list_size{100};
=======
// |-                                                                              -|
// |-                              << FLAT LIST >>                                 -|
// |-                                                                              -|
// \--------------------------------------------------------------------------------/

/***
 *
 *  flat_list is (suposedly) an Implementation of a linked list, where all its nodes 
 *  are contiguious in memory. 
 *  This approach eliminates the venefit of disperse memory allocation, in favor of a
 *  faster iteration thought its nodes. Hopefully, if the implementation makes sense
 *  and in the end is done right, this structure is suposed to serve as fundation to 
 *  build tools that allows for fast herachy trees transversation, meant for real time 
 *  applications.
 *
 *  Now, in my head, this structure needs to acomplish a coupple of things:
 *    -> fast Addition and Deleting : O(1)
 *    -> optimized iteration throught the container : contiguious memory O(n)
 * 
 *  If it gets lucky, we might even get SIMD instrucctions hanging arround, but probably not.
 *
 *  The downside to this trade is that, unlike in a linked list where, when a node is 
 *  removed, the memory management is usually trivial, with this structure we cannot
 *  free the memory of a single node, so we are left with an empty space in between nodes,
 *  wich would lead to internal fragmentation over time.
 *  To mitigate this, all the addresses to the deleted nodes will be stored into an auxiliar
 *  buffer, so that when a new node is needed, an existing allocated memory address will be 
 *  used.
 *  Sadly, this comes as a space penalty, where as the spatial cost of a linked list would come 
 *  as O(n * sizeof(T)), here given our duplicate vector, this will leave us with a wors case 
 *  scenario of O(n * sizeof(T) + n * 8) on most 64 bit machines, given that a pointer should
 *  be 8 bits long.
 *
 */
>>>>>>> 9eac27e (array implementation)

template <typename T> struct ListNode {
  ListNode *p_next{nullptr};
  ListNode *p_previous{nullptr};
  T value{};

<<<<<<< HEAD
  /*
   * 8 bit mask that represets:
   *  [0] -> hasNext
   *  [1] -> hasPrevious
   *  [2] ->
   *  [3] ->
   *  [4] ->
   *  [5] ->
   *  [6] ->
   *  [7] ->
   *
   */
  uint8_t state_mask{0};

  // Default Constructor
  ListNode(T _value) { value = _value; }

  ListNode(T _value, ListNode *next) {
    value = _value;
=======
static const uint64_t s_default_list_size {10};

template <typename T>
struct list_node
{
  list_node *p_next     {nullptr};
  list_node *p_previous {nullptr};
  T value {};

  // Default Constructor
  list_node(T _value)
  {
    value = _value;
  }

  list_node(T _value, list_node *next)
  {
    value  = _value;
>>>>>>> 9eac27e (array implementation)
    p_next = next;
    state_mask |= (1);
  }

<<<<<<< HEAD
  ListNode(T _value, ListNode *previous, ListNode *next) {
    value = _value;
=======
  list_node(T _value, list_node *previous, list_node *next)
  {
    value      = _value;
>>>>>>> 9eac27e (array implementation)
    p_previous = previous;
    p_next = next;
    state_mask |= (1);
    state_mask |= (1 << 1);
  }

  // shifts the value 8 bits to get the correct bit
  inline bool hasNext() { return state_mask & (1); }
  inline bool hasPrevious() { return state_mask & (1 << 1); }
};

<<<<<<< HEAD
template <typename T> struct arrayList {

  ListNode<T> *p_list{};

  uint64_t size{0};
  uint64_t capacity{0};

  typedef T *iterator;
  typedef const T *const_iterator;

  inline iterator begin() { return &p_list[0]; }
  inline iterator end() { return &p_list[size - 1]; }
  inline const_iterator begin() const { return &p_list[0]; }
  inline const_iterator end() const { return &p_list[size - 1]; }
=======
template <typename T>
struct flat_list
{



  typedef T* iterator;
  typedef const T* const_iterator;

  inline iterator begin() { return &p_nodeList[0]; }
  inline iterator end()   { return &p_nodeList[p_nodeList.size]; }
  inline const_iterator begin() const { return &p_nodeList[0]; }
  inline const_iterator end()   const { return &p_nodeList[p_nodeList.size]; }
>>>>>>> 9eac27e (array implementation)

  // Default Constructor
  flat_list();
  flat_list(uint32_t item_count);
  
  ~flat_list();

  // Methods

<<<<<<< HEAD
  uint8_t add(T value);
  uint8_t remove(T value);
  uint8_t resize();
=======
  void add(T value);
  void add(list_node<T> node);
  T remove(T value);
  void clear();

  inline const bool empty()    { return p_nodeList.size == 0 ? true : false; }
  inline const uint32_t size() { return p_nodeList.size; }

  vector<list_node<T>>  p_nodeList {};
  vector<list_node<T>*> p_freeNodeList {};

>>>>>>> 9eac27e (array implementation)
};

//////////////////////////////
// ____ IMPLEMENTATION ____ //
/////////////////////////////

template <typename T> arrayList<T>::arrayList() {

<<<<<<< HEAD
  p_list = static_cast<ListNode<T> *>(
      ::operator new(sizeof(ListNode<T>) * s_default_list_size));
  size = 0;
  capacity = s_default_list_size;
}

template <typename T> arrayList<T>::arrayList(uint64_t item_count) {
=======
template <typename T>
flat_list<T>::flat_list(){

    p_nodeList.resize(s_default_list_size);
    p_freeNodeList.resize(s_default_list_size / 2);
     

}

template <typename T>
flat_list<T>::flat_list(uint32_t item_count){

    p_nodeList.resize(item_count);
    p_freeNodeList.resize(item_count/2);
>>>>>>> 9eac27e (array implementation)

  p_list = static_cast<ListNode<T> *>(
      ::operator new(sizeof(ListNode<T>) * item_count));
  size = 0;
  capacity = item_count;
}

<<<<<<< HEAD
template <typename T> uint8_t arrayList<T>::add(T val) {

  ++size;
  if (capacity <= size)
    arrayList<T>::resize();
=======
template <typename T>
flat_list<T>::~flat_list()
{

}

template <typename T>
void flat_list<T>::add(T value)
{





>>>>>>> 9eac27e (array implementation)
}

} // namespace Memory::Containers

namespace Memory::Arenas {} // namespace Memory::Arenas
