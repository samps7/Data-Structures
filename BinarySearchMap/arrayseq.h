//---------------------------------------------------------------------------
// NAME: Samuel Sovi
// FILE: arrayseq.h
// DATE: Spring 2022
// DESC: File with my implementation of a array sequence and
// the corresponding sorts
//----------------------------------------------------------------------


#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdexcept>
#include <ostream>
#include "sequence.h"


template<typename T>
class ArraySeq : public Sequence<T>
{
public:

  // Default constructor
  ArraySeq();

  // Copy constructor
  ArraySeq(const ArraySeq& rhs);

  // Move constructor
  ArraySeq(ArraySeq&& rhs);

  // Copy assignment operator
  ArraySeq& operator=(const ArraySeq& rhs);

  // Move assignment operator
  ArraySeq& operator=(ArraySeq&& rhs);
  
  // Destructor
  ~ArraySeq();
  
  // Returns the number of elements in the sequence
  int size() const;

  // Tests if the sequence is empty
  bool empty() const;

  // Removes all of the elements from the sequence
  void clear();
  
  // Returns a reference to the element at the index in the
  // sequence. Throws out_of_range if index is invalid (less than 0 or
  // greater than or equal to size()).
  T& operator[](int index);

  // Returns a constant address to the element at the index in the
  // sequence. Throws out_of_range if index is invalid (less than 0 or
  // greater than or equal to size()).
  const T& operator[](int index) const;

  // Extends the sequence by inserting the element at the given index.
  // Throws out_of_range if the index is invalid (less than 0 or
  // greater than size()).
  void insert(const T& elem, int index);

  // Shrinks the sequence by removing the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  void erase(int index);

  // Returns true if the element is in the sequence, and false
  // otherwise.
  bool contains(const T& elem) const;

  // Sorts the elements in the sequence in place using less than equal
  // (<=) operator. Uses quick sort with a randomly selected pivot
  // index.
  void sort(); 

  // Sorts the sequence in place using the merge sort algorithm.
  void merge_sort();

  // Sorts the sequence in place using the quick sort algorithm. Uses
  // first element for pivot values.
  void quick_sort();

  // Sorts the sequence in place using the quick sort algorithm. Uses
  // randomly selected indexes for pivot values.
  void quick_sort_random();

  
private:

  // resizable array
  T* array = nullptr;

  // size of list
  int count = 0;

  // max capacity of the array
  int capacity = 0;

  // helper to double the capacity of the array
  void resize();

  // sort function helpers
  void merge_sort(int start, int end);
  void quick_sort(int start, int end);
  void quick_sort_random(int start, int end);  

  // random seed for quick sort
  int seed = 22;
  
};


template<typename T>
std::ostream& operator<<(std::ostream& stream, const ArraySeq<T>& seq)
{
  int n = seq.size();
  for (int i = 0; i < n - 1; ++i) 
    stream << seq[i] << ", ";
  if (n > 0)
    stream << seq[n - 1];
  return stream;
}


template<typename T>
ArraySeq<T>::ArraySeq()
{
}




//copy constructor
template<typename T>
ArraySeq<T>::ArraySeq(const ArraySeq& rhs)
{
  *this = rhs;
}

// Move constructor
template<typename T>
ArraySeq<T>::ArraySeq(ArraySeq&& rhs)
{
  *this = std::move(rhs);
}

// Copy assignment operator
template<typename T>
ArraySeq<T>& ArraySeq<T>::operator=(const ArraySeq& rhs)
{
  if(this != &rhs)
  {
    if(capacity != rhs.capacity)
    {
      capacity = rhs.capacity;
      if(array != nullptr)
      {
        delete[] array;
      }
      array = new T[rhs.capacity];
    }
    count = rhs.count;
    for(int i = 0; i < rhs.capacity; ++i)
    {
      array[i] = rhs.array[i];
    }
    return *this;
  }
  
}

// Move assignment operator
template<typename T>
ArraySeq<T>& ArraySeq<T>::operator=(ArraySeq&& rhs)
{
  if(this != &rhs)
  {
    delete[] array;
    array = rhs.array;
    count = rhs.count;
    capacity = rhs.capacity;
    rhs.array = nullptr;
    rhs.count = 0;
    rhs.capacity = 0;
    return *this;
  }
  
}

// Destructor
template<typename T>
ArraySeq<T>::~ArraySeq()
{
  delete[] array;
}

// Returns the number of elements in the sequence
template<typename T>
int ArraySeq<T>::size() const
{
  return count;
}

// Tests if the sequence is empty
template<typename T>
bool ArraySeq<T>::empty() const
{
  //temp
  return size() == 0;
}

// Removes all of the elements from the sequence
template<typename T>
void ArraySeq<T>::clear()
{
  count = 0;
}

// Returns a reference to the element at the index in the
// sequence. Throws out_of_range if index is invalid (less than 0 or
// greater than or equal to size()).
template<typename T>
T& ArraySeq<T>::operator[](int index)
{
  if(index < 0 || index >= size())
  {
    throw(std::out_of_range("LinkedSeq<T>::insert(const T&, int)"));
  }
  else
  {
    return array[index];
  }
}

// Returns a constant address to the element at the index in the
// sequence. Throws out_of_range if index is invalid (less than 0 or
// greater than or equal to size()).
template<typename T>
const T& ArraySeq<T>::operator[](int index) const
{
  if(index < 0 || index >= size())
  {
    throw(std::out_of_range("LinkedSeq<T>::insert(const T&, int)"));
  }
  else
  {
    return array[index];
  }
}

// Extends the sequence by inserting the element at the given index.
// Throws out_of_range if the index is invalid (less than 0 or
// greater than size()).
template<typename T>
void ArraySeq<T>::insert(const T& elem, int index)
{
  
  if(index < 0 || index > size())
  {
    throw(std::out_of_range("LinkedSeq<T>::insert(const T&, int)"));
  }
  else
  {
    if(count == capacity)
    {
      if(capacity == 0)
      {
        array = new T[1];
        capacity = 1;
      }
      else
      {
        resize();
      }
    }
    
    for(int i = count; i > index; --i)
    {
      array[i] = array[i-1];
    }
    
    array[index] = elem;
    ++count;
  }
  
}

// Shrinks the sequence by removing the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template<typename T>
void ArraySeq<T>::erase(int index)
{
  
  if(index < 0 || index >= size())
  {
    throw(std::out_of_range("LinkedSeq<T>::insert(const T&, int)"));
  }
  else
  {
    for(int i = index; i < count - 1; i++)
    {
      array[i] = array[i+1];
    }
    --count;
  }
  
}

// Returns true if the element is in the sequence, and false
// otherwise.
template<typename T>
bool ArraySeq<T>::contains(const T& elem) const
{
  for(int i = 0; i < count; i++)
  {
    if(array[i] == elem)
    {
      return true;
    }
  }
  return false;
}

//resizes array
template<typename T>
void ArraySeq<T>::resize()
{
  T* arr2 = new T[capacity*2];
  for(int i = 0; i < count; i++)
  {
    arr2[i] = array[i];
  }
  capacity = 2*capacity;
  delete[] array;
  array = arr2;
}

//defaults sort() to quick_sort_random
template<typename T>
void ArraySeq<T>::sort()
{
  quick_sort_random();
}

//calls merge sort
template<typename T>
void ArraySeq<T>::merge_sort()
{

  merge_sort(0,size() - 1);
  
}

//calls quick sort
template<typename T>
void ArraySeq<T>::quick_sort()
{

  quick_sort(0,size()-1);
  
}

//calls quick sort random
template<typename T>
void ArraySeq<T>::quick_sort_random()
{
  // seed the pseudo-random number generator
  std::srand(seed);            

  quick_sort_random(0,size()-1);
  
}

//merge sort
template<typename T>
void ArraySeq<T>::merge_sort(int start, int end)
{
  
  int mid;
  if(start < end)
  {
    mid = (start+end)/2;
    merge_sort(start, mid);
    merge_sort(mid + 1, end);
    T tmp[(end - start) + 1];
    int first1 = start;
    int first2 = mid + 1;
    int i = 0;
    while(first1 <= mid && first2 <= end)
    {
      if(array[first1] < array[first2])
      {
        tmp[i++] = array[first1++];
      }
      else
      {
        tmp[i++] = array[first2++];
      }
    }
    while(first1 <= mid)
    {
      tmp[i++] = array[first1++];
    }
    while(first2 <= end)
    {
      tmp[i++] = array[first2++];
    }
    for(int a = 0; a <= (end - start); a++)
    {
      array[start + a] = tmp[a];
    }
  }
  
}

//quick sort with start as the pivot
template<typename T>
void ArraySeq<T>::quick_sort(int start, int end)
{
  if(start < end)
  {
    T pivot_val = array[start];
    int end_p1 = start;
    for(int i = start + 1; i <= end; i++ )
    {
      if(array[i] < pivot_val)
      {
        end_p1 = end_p1 + 1;
        //swap
        T temp  = array[i];
        array[i] = array[end_p1];
        array[end_p1] = temp;
      }
    }
    //swap
    T temp  = array[start];
    array[start] = array[end_p1];
    array[end_p1] = temp;
    quick_sort(start, end_p1 - 1);
    quick_sort(end_p1 + 1, end);
  }

}

//quick sort with random index on each pass
template<typename T>
void ArraySeq<T>::quick_sort_random(int start, int end)
{
  if(start < end)
  {
    int rand_index = std::rand() % (end - start + 1) + start;
    //swap
    T val  = array[start];
    array[start] = array[rand_index];
    array[rand_index] = val;

    T pivot_val = array[start];
    int end_p1 = start;
    for(int i = start + 1; i <= end; i++ )
    {
      if(array[i] < pivot_val)
      {
        end_p1 = end_p1 + 1;
        //swap
        T temp  = array[i];
        array[i] = array[end_p1];
        array[end_p1] = temp;
      }
    }
    //swap
    T temp  = array[start];
    array[start] = array[end_p1];
    array[end_p1] = temp;
    quick_sort_random(start, end_p1 - 1);
    quick_sort_random(end_p1 + 1, end);
  }
}


#endif
