#pragma once

#include <cstdlib>
#include <cstdint>

#include <iostream>

namespace Memory::Containers {

static const uint64_t s_default_vector_size {100};

// VECTOR

template <typename T>
struct vector
{
  T *p_items {};
  uint64_t size {0};
  uint64_t capacity {0};
 
  typedef T* iterator;
  typedef const T* const_iterator;

  inline iterator begin() { return &p_items[0]; }
  inline iterator end()   { return &p_items[size-1]; }
  inline const_iterator begin() const { return &p_items[0]; }
  inline const_iterator end()   const { return &p_items[size-1]; }

  // constructor
  vector();
  vector(uint64_t init_size);

  uint8_t add(T item);
  uint8_t remove(uint64_t index);
  uint8_t resize();


};


template <typename T>
vector<T>::vector()
{

  p_items  = static_cast<T*>(malloc(sizeof(T) * s_default_vector_size));
  size     = 0;
  capacity = s_default_vector_size;

}

template <typename T>
vector<T>::vector(uint64_t init_size)
{

  p_items  = static_cast<T*>(malloc(sizeof(T) * init_size));
  size     = 0;
  capacity = init_size;

}

static const uint64_t s_default_list_size {100};

// ARRAY LIST

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

    p_list = static_cast<ListNode<T>*>(malloc(sizeof(ListNode<T>) * s_default_list_size));
    size = 0;
    capacity = s_default_list_size;

}

template <typename T>
arrayList<T>::arrayList(uint64_t item_count){

    p_list = static_cast<ListNode<T>*>(malloc(sizeof(ListNode<T>) * item_count));
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

