//----------------------------------------------------------------------
// NAME: Samuel Sovi
// FILE: linkedlist.h
// DATE: Spring 2022
// DESC: File with my implementation of a linked sequence and
// the corresponding sorts
//----------------------------------------------------------------------


#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include <ostream>
#include "sequence.h"


template<typename T>
class LinkedSeq : public Sequence<T>
{
public:

  // Default constructor
  LinkedSeq();

  // Copy constructor
  LinkedSeq(const LinkedSeq& rhs);

  // Move constructor
  LinkedSeq(LinkedSeq&& rhs);

  // Copy assignment operator
  LinkedSeq& operator=(const LinkedSeq& rhs);

  // Move assignment operator
  LinkedSeq& operator=(LinkedSeq&& rhs);
  
  // Destructor
  ~LinkedSeq();
  
  // Returns the number of elements in the sequence
  int size() const override;

  // Tests if the sequence is empty
  bool empty() const override;

  // Removes all of the elements from the sequence
  void clear() override;
  
  // Returns a reference to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  T& operator[](int index) override;

  // Returns a constant address to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  const T& operator[](int index) const override;

  // Extends the sequence by inserting the element at the given
  // index. Throws out_of_range if the index is invalid.
  void insert(const T& elem, int index) override;

  // Shrinks the sequence by removing the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  void erase(int index) override;

  // Returns true if the element is in the sequence, and false
  // otherwise.
  bool contains(const T& elem) const override;

  // Sorts the elements in the sequence in place using less than equal
  // (<=) operator. Uses merge sort.
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

  // linked list node
  struct Node {
    T value;
    Node* next = nullptr;
  };

  // head pointer
  Node* head = nullptr;

  // tail pointer
  Node* tail = nullptr;

  // size of list
  int node_count = 0;

  // sort function helpers
  Node* merge_sort(Node* left, int len);
  Node* quick_sort(Node* start, int len);
  Node* quick_sort_random(Node* start, int len);

  // random seed for quick sort
  int seed = 22;

};


template<typename T>
std::ostream& operator<<(std::ostream& stream, const LinkedSeq<T>& seq)
{
  int n = seq.size();
  for (int i = 0; i < n - 1; ++i) 
    stream << seq[i] << ", ";
  if (n > 0)
    stream << seq[n - 1];
  return stream;
}


template<typename T>
LinkedSeq<T>::LinkedSeq()
{
}

/*
Copy Constructor initializes object as a copy of
rhs 
*/
template<typename T>
LinkedSeq<T>::LinkedSeq(const LinkedSeq<T>& rhs)
{
  *this = rhs;
}

/*
Move Constructor moves object from rhs
into lhs
*/
template<typename T>
LinkedSeq<T>::LinkedSeq(LinkedSeq<T>&& rhs)
{
  *this = std::move(rhs);
}

/*
Copy Assignment Operator sets object as a copy of
rhs 
*/
template<typename T>
LinkedSeq<T>& LinkedSeq<T>::operator=(const LinkedSeq<T>& rhs)
{
  if(this != &rhs)
  {
    clear();
    Node* temp = rhs.head;
    while (temp != nullptr)
    {
      insert( temp -> value, size() );
      temp = temp -> next;
    }
  }

}

/*
Move Assignment Operator moves object from rhs
into lhs
*/
template<typename T>
LinkedSeq<T>& LinkedSeq<T>::operator=(LinkedSeq<T>&& rhs)
{
  if(this != &rhs)
  {
    clear();
    head = rhs.head;
    tail = rhs.tail;
    rhs.head = nullptr;
    rhs.tail = nullptr;
    node_count = rhs.node_count;
    rhs.node_count = 0;
    return *this;
  }

}

/*
Destructor destroys object by calling clear
*/
template<typename T>
LinkedSeq<T>::~LinkedSeq()
{
  clear();
}

/*
Returns true if the Linked List is empty
*/
template<typename T>
bool LinkedSeq<T>::empty() const
{
  return size() == 0;
}

/*
clears all elements of the linked list from
head to tail
*/
template<typename T>
void LinkedSeq<T>::clear()
{
  while(!empty())
  {
    erase(0);
  }
}

// Returns a reference to the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template<typename T>
T& LinkedSeq<T>::operator[](int index)
{
  
  if(index < 0 || index >= size())
  {
    throw(std::out_of_range("LinkedSeq<T>::insert(const T&, int)"));
  }
  else
  {
    if(index == 0)
    { 
      return (head -> value);
    }
    else if(index == size()-1)
    {
      return (tail -> value);
    }
    else
    {
      Node* node_ptr = head->next;
      for(int i = 1; i < size(); i++)
      {
        if(i == index)
        {
          return (node_ptr -> value);
        }
        node_ptr = node_ptr -> next;
      }
    }
  }
}

// Returns a constant address to the element at the index in the
// sequence. Throws out_of_range if index is invalid.
template<typename T>
const T& LinkedSeq<T>::operator[](int index) const
{
  if(index < 0 || index >= size())
  {
    throw(std::out_of_range("LinkedSeq<T>::insert(const T&, int)"));
  }
  else
  {
    if(index == 0)
    { 
      return (head -> value);
    }
    else if(index == size()-1)
    {
      return (tail -> value);
    }
    else
    {
      Node* node_ptr = head->next;
      for(int i = 1; i < size(); i++)
      {
        if(i == index)
        {
          return (node_ptr -> value);
        }
        node_ptr = node_ptr -> next;
      }
    }
  }
}


/*
Inserts an element at a specific index including after the
last element
*/
template<typename T>
void LinkedSeq<T>::insert(const T& elem, int index)
{
  if(index < 0 || index > size())
  {
    throw(std::out_of_range("LinkedSeq<T>::insert(const T&, int)"));
  }
  else
  {
    Node* node1 = new Node;
    node1 -> value = elem;
    if(index == 0)
    {
      
      if(head == nullptr)
      {
        tail = node1;
      }
      
      node1 -> next = head;
      
      head = node1;
      
      
    }
    else if(index == size())
    {
      
      node1 -> next = nullptr;
      tail -> next = node1;
      
      
      tail = node1;
    }
    
    else
    {
      
      if(size() > 1)
      {
        Node* temp = head;
        for(int i = 1; i <= index; i++)
        {
            if(i == index)
            {
              node1 -> next = temp -> next;
              temp -> next = node1;
              
            }
            temp = temp -> next;
        }
        
      }
    }
    
    
    
    node_count++;
    
    
  }

}

/*
Erases a target node from the linked list
*/
template<typename T>
void LinkedSeq<T>::erase(int index)
{
  if(index < 0 || index >= size())
  {
    throw(std::out_of_range("LinkedSeq<T>::insert(const T&, int)"));
  }
  else
  {
    Node* temp = head;
    Node* temp2;
    if(index == 0)
    {
      if(head -> next != nullptr)
      {
        temp = head;
        head = head -> next;
        delete temp;
      }
      else if(head -> next == nullptr)
      {
        temp = head;
        head = nullptr;
        tail = nullptr;
        delete temp;
      }
    }
    else
    {
      
      if(size() > 1)
      {
        for(int i = 1; i < size(); i++)
        {
          
          
          if(i == index)
          {
            temp2 = temp -> next;
            temp -> next = temp2 -> next;
            delete temp2;
            //break;
            if(temp->next == nullptr)
            {
              tail = temp;
            }
            
            node_count--;
            return;
            //break;
          }
          
          temp = temp -> next;
          
        }
        delete temp;
      }
    }
    node_count--;
    
  }
  
}

/*
checks if an element is contained in the linked list
*/
template<typename T>
bool LinkedSeq<T>::contains(const T& elem) const
{
  if(head != nullptr)
  {
    Node* temp = head;
    
    if(head -> value == elem)
    {
      return true;
    }
    
    else if(tail -> value == elem)
    {
      return true;  
    }
    
    else
    {
      if(size() > 1)
      {
        temp = temp -> next;
        for(int i = 1; i < size(); ++i)
        {
          if(temp -> value == elem)
          {
            return true;
          }
          temp = temp -> next;
        }
      }
    }
  }
  return false;
}

/*
returns the size of the linked sequence
*/

template<typename T>
int LinkedSeq<T>::size() const
{
  return node_count;
}

//defaults sort() to merge sort
template<typename T>
void LinkedSeq<T>::sort()
{
  merge_sort();
}

//calls merge sort
template<typename T>
void LinkedSeq<T>::merge_sort()
{
  if(head != nullptr)
  {
    head = merge_sort(head, size());
    Node* temp = head;
    
    while(temp -> next != nullptr)
    {
      temp = temp -> next;
    }
    tail = temp;
    
  }
}

//calls quick sort
template<typename T>
void LinkedSeq<T>::quick_sort()
{
  if(head != nullptr)
  {
    head = quick_sort(head, size());
    Node* temp = head;
    while(temp -> next != nullptr)
    {
      temp = temp -> next;
    }
    tail = temp;
  }
}


template<typename T>
void LinkedSeq<T>::quick_sort_random()
{
  // seed the pseudo-random number generator
  std::srand(seed);
  if(head != nullptr)
  {
    head = quick_sort_random(head, size());
    Node* temp = head;
    while(temp -> next != nullptr)
    {
      temp = temp -> next;
    }
    tail = temp;
  }
}


template<typename T>
typename LinkedSeq<T>::Node* LinkedSeq<T>::merge_sort(Node* left, int len)
{
  if(len <= 1)
  {
    return left;
  }
  int mid = len / 2;
  Node* left_head = left;
  Node* right_head = left;
  for( int i = 0; i < mid; i++)
  {
    right_head = right_head -> next;
  }
  left_head = merge_sort(left_head, mid);
  right_head = merge_sort(right_head, len - mid);
  Node* tmp = nullptr;
  Node* tmp_head = nullptr;

  int left_count = mid;
  int right_count = len-mid;

  while(left_count > 0 && right_count > 0)
  {
    if(left_head -> value < right_head -> value)
    {
      if(tmp == nullptr)
      {
        tmp = left_head;
        tmp_head = left_head;
      }
      else
      {
        tmp -> next = left_head;
        tmp = tmp -> next;
      }
      left_head = left_head -> next;
      left_count--;
    }
    else
    {
      if(tmp == nullptr)
      {
        tmp = right_head;
        tmp_head = right_head;
      }
      else
      {
        tmp -> next = right_head;
        tmp = tmp -> next;
      }
      right_head = right_head -> next;
      right_count--;
    }
  }

  // Note: I am cycling all the way through to cut ties
  // with nodes at the end of the mini linked lists
  while(left_count > 0)
  {
    if(tmp == nullptr)
    {
      tmp = left_head;
      tmp_head = left_head;
    }
    else
    {
      tmp -> next = left_head;
      tmp = tmp -> next;
    }
    left_head = left_head -> next;
    left_count--;
  }
  
  while(right_count > 0)
  {
    if(tmp == nullptr)
    {
      tmp = right_head;
      tmp_head = right_head;
    }
    else
    {
      tmp -> next = right_head;
      tmp = tmp -> next;
    }
    right_head = right_head -> next;
    right_count--;
  }
  tmp -> next = nullptr;
  return tmp_head;
}

//quick sort with pivot as start
template<typename T>
typename LinkedSeq<T>::Node* LinkedSeq<T>::quick_sort(Node* start, int len)
{
  if(len <= 1)
  {
    return start;
  }

  Node* pivot = start;
  Node* smaller_head = nullptr;
  Node* smaller = nullptr;
  int smaller_count = 0;

  Node* larger_head = nullptr;
  Node* larger = nullptr;
  int larger_count = 0;
  
  while(pivot -> next != nullptr)
  {
    if(pivot -> next -> value < pivot -> value)
    {
      
      if(smaller == nullptr)
      {
        smaller = pivot -> next;
        smaller_head = pivot -> next;
      }
      else
      {
        smaller -> next = pivot -> next;
        smaller = smaller -> next;
      }
      smaller_count++;
      pivot -> next = pivot -> next -> next;
      smaller -> next = nullptr;
    }
    else
    {
      if(larger == nullptr)
      {
        larger = pivot -> next;
        larger_head = pivot -> next;
      }
      else
      {
        larger -> next = pivot -> next;
        larger = larger -> next;
      }
      larger_count++;
      pivot -> next = pivot -> next -> next;
      larger -> next = nullptr;
    }
  }
  smaller_head = quick_sort(smaller_head, smaller_count);
  larger_head = quick_sort(larger_head, larger_count);

  Node* current = nullptr;

  if(smaller_count == 0)
  {
    pivot -> next = larger_head;
    return pivot;
  }
  else
  {
    current = smaller_head;
    while(current -> next != nullptr)
    {
      current = current -> next;
    }

    current -> next = pivot;
    pivot -> next = larger_head;
    return smaller_head;
  }

}


//quick sort with random pivot
template<typename T>
typename LinkedSeq<T>::Node* LinkedSeq<T>::quick_sort_random(Node* start, int len)
{

  if(len <= 1)
  {
    return start;
  }
  Node* pivot = nullptr;
  int random_index = std::rand() % (len);

  //get random pivot
  if(random_index != 0)
  {
    Node* temp_node = start;
    for(int i = 0; i < random_index - 1; i++)
    {
      temp_node = temp_node-> next;
    }
    pivot = temp_node -> next;
    temp_node -> next = pivot -> next;
    pivot->next = start;
  }
  else
  {
    pivot = start;
  }

  Node* smaller_head = nullptr;
  Node* smaller = nullptr;
  int smaller_count = 0;

  Node* larger_head = nullptr;
  Node* larger = nullptr;
  int larger_count = 0;
  
  while(pivot -> next != nullptr)
  {
    if(pivot -> next -> value < pivot -> value)
    {
      
      if(smaller == nullptr)
      {
        smaller = pivot -> next;
        smaller_head = pivot -> next;
      }
      else
      {
        smaller -> next = pivot -> next;
        smaller = smaller -> next;
      }
      smaller_count++;
      pivot -> next = pivot -> next -> next;
      smaller -> next = nullptr;
    }
    else
    {
      if(larger == nullptr)
      {
        larger = pivot -> next;
        larger_head = pivot -> next;
      }
      else
      {
        larger -> next = pivot -> next;
        larger = larger -> next;
      }
      larger_count++;
      pivot -> next = pivot -> next -> next;
      larger -> next = nullptr;
    }
  }
  smaller_head = quick_sort_random(smaller_head, smaller_count);
  larger_head = quick_sort_random(larger_head, larger_count);

  Node* current = nullptr;

  if(smaller_count == 0)
  {
    pivot -> next = larger_head;
    return pivot;
  }
  else
  {
    current = smaller_head;
    while(current -> next != nullptr)
    {
      current = current -> next;
    }

    current -> next = pivot;
    pivot -> next = larger_head;
    return smaller_head;
  }

}


#endif
