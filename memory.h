#pragma once

#include <iostream>
#include <cstdint>

namespace Memory::Containers {



//  ________________________________________________________________________________
// /--------------------------------------------------------------------------------\
// |-                                                                              -|
// |-                                                                              -|
// |-                              << STACK ARRAY >>                               -|
// |-                                                                              -|
// |-                                                                              -|
// \--------------------------------------------------------------------------------/


/*
 * The stack_array Container is supose to act like a collection of elements 
 * contiguious in memory (I know its obvious smartass). The memory is allocated in 
 * the stack and it can be specify how big it should be, in order to optimize space.
 *
 */

//////////////////////////////
// ____  DECLARATION  ____ //
/////////////////////////////

template <typename T, uint32_t N>
struct stack_array
{
  
  typedef       T* iterator;
  typedef const T* const_iterator;

  inline iterator       begin() { return &p_items[0]; }
  inline iterator       end()   { return &p_items[size]; }
  inline const_iterator begin() const { return &p_items[0]; }
  inline const_iterator end()   const { return &p_items[size]; }

  
  inline const T& operator[](uint32_t index) const;
  inline       T& operator[](uint32_t index); 
  inline stack_array&  operator=(const stack_array& other);  

 

  T p_items[N]; 
  uint32_t size;

  stack_array();
  stack_array(stack_array& other);
   

};


//////////////////////////////
// ____ IMPLEMENTATION ____ //
/////////////////////////////

template<typename T, uint32_t N>
stack_array<T, N>::stack_array()
{
    //p_items = static_cast<T*>(alloca(N  * sizeof(T)));
    size = N;

}

template<typename T, uint32_t N>
stack_array<T, N>::stack_array(stack_array& other)
{
    if (size != other.size) { /* DEBUG ASSERT */}
  
    for (uint32_t i = 0; i < other.size; i++)
    {
      p_items[i] = other.p_items[i];
    }
    size = other.size;
}


template <typename T, uint32_t N>
inline const T& stack_array<T,N>::operator[](uint32_t index) const 
{
  if (index < 0 || index >= size) { /* DEBUG TRACE */ }
  return p_items[index];
}


template <typename T, uint32_t N>
inline T& stack_array<T, N>::operator[](uint32_t index) 
{
  if (index < 0 || index >= size) { /* DEBUG TRACE */ }
  return p_items[index];
}


template <typename T, uint32_t N>
inline stack_array<T, N>&  stack_array<T, N>::operator=(const stack_array& other)
{
  if (size != other.size ) { /* DEBUG ASSERT */  }

  for(uint32_t i = 0; i < other.size; ++i)
  {
     p_items[i] = other.p_items[i]; 
  }
  size = other.size;
  
  return *this;
}

// END OF MEMORY::CONTAINER::stack_array<>




//  ________________________________________________________________________________
// /--------------------------------------------------------------------------------\
// |-                                                                              -|
// |-                                                                              -|
// |-                                 << VECTOR >>                                 -|
// |-                                                                              -|
// |-                                                                              -|
// \--------------------------------------------------------------------------------/



/*  
 *  The vector Container is a generic array with the ability to change 
 *  size to acomodate new data. 
 *  The maximum size of this array is 2^32 = 4.294.967.296 (~4.3 billion items)
 * ºbut it is likely that you run out of memory way before reaching such
 *  number.
 *
 *  TODO:
 *  - implementation of srinking capabilities
 *  - implementation of policies for srinking and growing
 *  - fix the fuckass std::string implementation god I hate that shit dude
 *  - optimize for small vectors -> up to a certain threshold allocate on the stack
 *
 */

//////////////////////////////
// ____  DECLARATION  ____ //
/////////////////////////////

static const uint32_t s_default_vector_size {10};

template <typename T>
struct vector
{
 
  typedef       T* iterator;
  typedef const T* const_iterator;

  inline iterator       begin() { return &p_items[0]; }
  inline iterator       end()   { return &p_items[size]; }
  inline const_iterator begin() const { return &p_items[0]; }
  inline const_iterator end()   const { return &p_items[size]; }


  inline const T& operator[](uint32_t index) const;
  inline       T& operator[](uint32_t index); 
  inline vector&  operator=(const vector& other);  
  inline vector&  operator=(const vector&& other);
 

  // constructor / destructor
  vector();
  vector(uint32_t init_size);
  vector(vector& other);
  vector(vector&& other);
  
  ~vector();
  
  template <typename... Args>
  T& emplace_back(Args&&... item);
  void push_back(T& item);
  void push_back(T&& item);
  void pop_back();
  void clear();
  void resize(uint32_t newCapacity);
  inline void change_growth_ratio(float newRatio) { growth_ratio = newRatio; }
  
  // Members

  T       *p_items {};
  float    growth_ratio { 0.5f };
  uint32_t size         { 0 };
  uint32_t capacity     { 0 };
  uint32_t explicit_padding; // 32 bits -> 4

};


//////////////////////////////
// ____ IMPLEMENTATION ____ //
/////////////////////////////


template <typename T>
vector<T>::vector()
{

  resize(s_default_vector_size);
  size     = 0;
  capacity = s_default_vector_size;

}

template <typename T>
vector<T>::vector(uint32_t init_size)
{

  resize(init_size);
  size     = 0;
  capacity = init_size;

}

template <typename T>
vector<T>::vector(vector& other)
{
  
  T *p_newMem = static_cast<T*>(::operator new (other.capacity * sizeof(T)));

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

template <typename T>
vector<T>::vector(vector&& other)
{
 
  T *p_newMem = static_cast<T*>(::operator new (other.capacity * sizeof(T)));

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


template <typename T>
vector<T>::~vector()
{
  clear();
  ::operator delete(p_items, sizeof(T) * capacity); 
}


template <typename T>
void vector<T>::push_back(T& item)
{
  if (size >= capacity)
    resize(capacity + capacity * growth_ratio);

  p_items[size] = item;
  ++size;
}


template <typename T>
void vector<T>::push_back(T&& item)
{
  if (size >= capacity)
    resize(capacity + capacity * growth_ratio);

  p_items[size] = std::move(item);
  ++size;

}


template <typename T> template<typename... Args>
T& vector<T>::emplace_back(Args&&... args)
{

  if (size >= capacity)
    resize(capacity + capacity * growth_ratio);

  new (&p_items[size]) T(std::forward<Args>(args)...);
  return p_items[size++];

}


template <typename T>
void vector<T>::pop_back()
{
  if (size > 0) 
    p_items[size--].~T();

}


template <typename T>
void vector<T>::resize(uint32_t newCapacity)
{

  T *p_newMem = static_cast<T*>(::operator new (newCapacity * sizeof(T)));

  for (uint32_t i = 0; i < size; ++i)
    p_newMem[i] = std::move(p_items[i]);
    
  for (uint32_t i = 0; i < size; ++i)
    p_items[i].~T();

  ::operator delete(p_items, sizeof(T) * capacity);
  p_items = p_newMem;
  capacity = newCapacity;

}


template <typename T>
void vector<T>::clear()
{

  for (uint32_t i = 0; i < size; ++i)
    p_items[i].~T();

  size = 0; 

}


template <typename T>
inline const T& vector<T>::operator[](uint32_t index) const
{
  if (index >= size || index < 0) { /*DEBUG TRACE*/ }
  
  return p_items[index];
}
  

template <typename T>
inline T& vector<T>::operator[](uint32_t index) 
{
  if (index >= size || index < 0) { /*DEBUG TRACE*/ }

  return p_items[index];
}


template <typename T>
inline vector<T>& vector<T>::operator=(const vector& other)
{

  T *p_newMem= static_cast<T*>(::operator new (other.capacity * sizeof(T)));

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
inline vector<T>& vector<T>::operator=(const vector&& other)
{

  T *p_newMem= static_cast<T*>(::operator new (other.capacity * sizeof(T)));

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
// fuckass constructors that fucks with my fuckass mallocs and throws errors everywhere

template <>
vector<std::string>::~vector()
{
  delete[] p_items;
}


template <>
void vector<std::string>::pop_back()
{
  if (size > 0)
    size--;
}


template <>
void vector<std::string>::resize(uint32_t newCapacity)
{
  std::string *p_newMem =  new std::string[newCapacity];

  for (uint32_t i = 0; i < size; ++i)
    p_newMem[i] = std::move(p_items[i]);
    
  delete[] p_items;

  p_items = p_newMem;
  capacity = newCapacity;

}

// END OF MEMORY::CONTAINERS::vector<>  


//  ________________________________________________________________________________
// /--------------------------------------------------------------------------------\
// |-                                                                              -|
// |-                                                                              -|
// |-                              << ARRAY LIST >>                                -|
// |-                                                                              -|
// |-                                                                              -|
// \--------------------------------------------------------------------------------/



static const uint64_t s_default_list_size {100};

template <typename T>
struct ListNode
{
  ListNode *p_next     {nullptr};
  ListNode *p_previous {nullptr};
  T value {};

  // Default Constructor
  ListNode(T _value)
  {
    value = _value;
  }

  ListNode(T _value, ListNode *next)
  {
    value  = _value;
    p_next = next;
  }

  ListNode(T _value, ListNode *previous, ListNode *next)
  {
    value      = _value;
    p_previous = previous;
    p_next     = next;
  }

};

template <typename T>
struct arrayList
{

  ListNode<T> *p_list {};

  uint64_t size     {0};
  uint64_t capacity {0};
 
  typedef T* iterator;
  typedef const T* const_iterator;

  inline iterator begin() { return &p_list[0]; }
  inline iterator end()   { return &p_list[size-1]; }
  inline const_iterator begin() const { return &p_list[0]; }
  inline const_iterator end()   const { return &p_list[size-1]; }

  // Default Constructor
  arrayList();
  arrayList(uint64_t item_count);

  // Methods

  uint8_t add(T value);
  uint8_t remove(T value);
  uint8_t resize();

};

//////////////////////////////
// ____ IMPLEMENTATION ____ //
/////////////////////////////


template <typename T>
arrayList<T>::arrayList(){

    p_list = static_cast<ListNode<T>*>(::operator new(sizeof(ListNode<T>) * s_default_list_size));
    size = 0;
    capacity = s_default_list_size;

}

template <typename T>
arrayList<T>::arrayList(uint64_t item_count){

    p_list = static_cast<ListNode<T>*>(::operator new(sizeof(ListNode<T>) * item_count));
    size = 0;
    capacity = item_count;

}

template <typename T>
uint8_t arrayList<T>::add(T val)
{

  ++size;
  if (capacity <= size)
    arrayList<T>::resize();



}



} // end Memory::Containers

namespace Memory::Arenas {



} // en Memory::Arenas

