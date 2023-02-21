//---------------------------------------------------------------------------
// NAME: Samuel Sovi
// FILE: hashmap.h
// DATE: Spring 2022
// DESC: This contains my implementation of a hash map
//---------------------------------------------------------------------------

#ifndef HASHMAP_H
#define HASHMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class HashMap : public Map<K,V>
{
public:

  // default constructor
  HashMap();

  // copy constructor
  HashMap(const HashMap& rhs);

  // move constructor
  HashMap(HashMap&& rhs);

  // copy assignment
  HashMap& operator=(const HashMap& rhs);

  // move assignment
  HashMap& operator=(HashMap&& rhs);  

  // destructor
  ~HashMap();
  
  // Returns the number of key-value pairs in the map
  int size() const;

  // Tests if the map is empty
  bool empty() const;

  // Allows values associated with a key to be updated. Throws
  // out_of_range if the given key is not in the collection.
  V& operator[](const K& key);

  // Returns the value for a given key. Throws out_of_range if the
  // given key is not in the collection. 
  const V& operator[](const K& key) const;

  // Extends the collection by adding the given key-value pair.
  // Expects key to not exist in map prior to insertion.
  void insert(const K& key, const V& value);

  // Shrinks the collection by removing the key-value pair with the
  // given key. Does not modify the collection if the collection does
  // not contain the key. Throws out_of_range if the given key is not
  // in the collection.
  void erase(const K& key);

  // Returns true if the key is in the collection, and false otherwise.
  bool contains(const K& key) const;

  // Returns the keys k in the collection such that k1 <= k <= k2
  ArraySeq<K> find_keys(const K& k1, const K& k2) const;

  // Returns the keys in the collection in ascending sorted order
  ArraySeq<K> sorted_keys() const;  

  // Gives the key (as an ouptput parameter) immediately after the
  // given key according to ascending sort order. Returns true if a
  // successor key exists, and false otherwise.
  bool next_key(const K& key, K& next_key) const; 

  // Gives the key (as an ouptput parameter) immediately before the
  // given key according to ascending sort order. Returns true if a
  // predecessor key exists, and false otherwise.
  bool prev_key(const K& key, K& next_key) const;

  // Removes all key-value pairs from the map. Does not change the
  // current capacity of the table.
  void clear();
  
  // statistics functions for the hash table implementation
  int min_chain_length() const;
  int max_chain_length() const;
  double avg_chain_length() const;
  
private:

  // node for linked-list separate chaining
  struct Node {
    K key;
    V value;
    Node* next;
  };

  // number of key-value pairs in map
  int count = 0;

  // max size of the (array) table
  int capacity = 16;

  // threshold for resize and rehash
  const double load_factor_threshold = 0.75;
  
  // array of linked lists
  Node** table = new Node*[capacity];

  // the hash function
  int hash(const K& key) const;

  // resize and rehash the table
  void resize_and_rehash();

  // initialize the table to all nullptr
  void init_table();
  
};

//constructor just initializes table
template<typename K, typename V>
HashMap<K,V>::HashMap()
{
  init_table();
}


// TODO: Implement the remaining public and private member functions
//       below.

// copy constructor
template<typename K, typename V>
HashMap<K,V>::HashMap(const HashMap& rhs)
{
  init_table();
  *this = rhs;
}

// move constructor
template<typename K, typename V>
HashMap<K,V>::HashMap(HashMap&& rhs)
{
  init_table();
  *this = std::move(rhs);
}

// copy assignment
template<typename K, typename V>
HashMap<K,V>& HashMap<K,V>::operator=(const HashMap& rhs)
{
  if(this != &rhs)
  {
    clear();
    delete[] table;
    Node** temp_table = new Node*[rhs.capacity];
    Node* temp = nullptr;
    Node* holder;
    capacity = rhs.capacity;
    count = rhs.count;
    {
      table = temp_table;
      init_table();
      for(int i = 0; i < rhs.capacity; i++)
      {
        temp = rhs.table[i];
        while(temp != nullptr)
        {
          holder = new Node();
          holder -> key = temp -> key;
          holder -> value = temp -> value;
          holder -> next = temp -> next;
          if(table[i] == nullptr)
          {
            table[i] = holder;
          }
          else
          {
            holder -> next = table[i];
            table[i] = holder;
          }
          temp = temp -> next;
        }
      }
    }
  }
  
}

// move assignment
template<typename K, typename V>
HashMap<K,V>& HashMap<K,V>::operator=(HashMap&& rhs)
{
  if(this != &rhs)
  {
    clear();
    delete[] table;
    table = rhs.table;
    count = rhs.count;
    capacity = rhs.capacity;
    rhs.table = new Node*[16];
    rhs.count = 0;
    rhs.capacity = 16;
    rhs.init_table();
    return *this;
  }
}  

// destructor
template<typename K, typename V>
HashMap<K,V>::~HashMap()
{
  clear();
  delete[] table;
}

// Returns the number of key-value pairs in the map
template<typename K, typename V>
int HashMap<K,V>::size() const
{
  return count;
}

// Tests if the map is empty
template<typename K, typename V>
bool HashMap<K,V>::empty() const
{
  return size() == 0;
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& HashMap<K,V>::operator[](const K& key)
{
  int index = hash(key);
  Node* temp = table[index];
  while(temp != nullptr)
  {
    if(temp -> key == key)
    {
      return temp -> value;
    }
    
    temp = temp -> next;
  }
  throw(std::out_of_range("HashMap<K,V>::operator[](const K& key)"));
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection.
template<typename K, typename V> 
const V& HashMap<K,V>::operator[](const K& key) const
{
  int index = hash(key);
  Node* temp = table[index];
  while(temp != nullptr)
  {
    if(temp -> key == key)
    {
      return temp -> value;
    }
    
    temp = temp -> next;
  }
  throw(std::out_of_range("HashMap<K,V>::operator[](const K& key)"));
}

// Extends the collection by adding the given key-value pair.
// Expects key to not exist in map prior to insertion.
template<typename K, typename V>
void HashMap<K,V>::insert(const K& key, const V& value)
{
  if(count/capacity >= load_factor_threshold)
  {
    resize_and_rehash();
  }
  int index = hash(key);
  Node* temp = new Node();
  temp -> key = key;
  temp -> value = value;
  temp -> next = table[index];
  table[index] = temp;
  count++;
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template<typename K, typename V>
void HashMap<K,V>::erase(const K& key)
{
  int index = hash(key);
  Node* temp = table[index];
  Node* prev = nullptr;
  if(temp == nullptr)
  {
    throw(std::out_of_range("HashMap<K,V>::erase(const K& key)"));
  }
  if(temp -> key == key)
  {
    table[index] = table[index] -> next;
    delete temp;
    count--;
    return;
  }
  prev = temp;
  temp = temp -> next;
  while(temp != nullptr)
  {
    if(temp -> key == key)
    {
      prev -> next = temp -> next;
      delete temp;
      count--;
      delete prev;
      return;
    }
    
    temp = temp -> next;
    prev = prev -> next;
  }
  throw(std::out_of_range("HashMap<K,V>::erase(const K& key)"));
}

// Returns true if the key is in the collection, and false otherwise.
template<typename K, typename V>
bool HashMap<K,V>::contains(const K& key) const
{
  int index = hash(key);
  Node* temp = table[index];
  while(temp != nullptr)
  {
    if(temp -> key == key)
    {
      return true;
    }
    
    temp = temp -> next;
  }

  return false;
}

// Returns the keys k in the collection such that k1 <= k <= k2
template<typename K, typename V>
ArraySeq<K> HashMap<K,V>::find_keys(const K& k1, const K& k2) const
{
  Node* temp = nullptr;
  ArraySeq<K> seq;

  for(int i = 0; i < capacity; i++)
  {
    temp = table[i];
    while(temp!=nullptr)
    {
      if(temp -> key >= k1 && temp -> key <= k2)
      {
        seq.insert(temp -> key, seq.size());
      }

      temp = temp -> next;
    }
  }
  return seq;
}

// Returns the keys in the collection in ascending sorted order
template<typename K, typename V>
ArraySeq<K> HashMap<K,V>::sorted_keys() const
{
  ArraySeq<K> seq;
  Node* temp = nullptr;
  for(int i = 0; i < capacity; i++)
  {
    temp = table[i];
    while(temp != nullptr)
    {
      seq.insert(temp -> key, seq.size());
      temp = temp -> next;
    }
  }
  seq.sort();
  return seq;
}  

// Gives the key (as an ouptput parameter) immediately after the
// given key according to ascending sort order. Returns true if a
// successor key exists, and false otherwise.
template<typename K, typename V>
bool HashMap<K,V>::next_key(const K& key, K& next_key) const
{
  Node* temp = nullptr;
  bool found = false;
  for(int i = 0; i < capacity; i++)
  {
    temp = table[i];
    while(temp != nullptr)
    {
      if(found == false)
      {
        if(temp -> key > key)
        {
          next_key = temp -> key;
          found = true;
        }
      }
      else
      {
        if(temp -> key < next_key && temp -> key > key)
        {
          next_key = temp -> key;
        }
      }
      temp = temp -> next;
    }
  }
  return found;
} 

// Gives the key (as an ouptput parameter) immediately before the
// given key according to ascending sort order. Returns true if a
// predecessor key exists, and false otherwise.
template<typename K, typename V>
bool HashMap<K,V>::prev_key(const K& key, K& next_key) const
{
  Node* temp = nullptr;
  bool found = false;
  for(int i = 0; i < capacity; i++)
  {
    temp = table[i];
    while(temp != nullptr)
    {
      if(found == false)
      {
        if(temp -> key < key)
        {
          next_key = temp -> key;
          found = true;
        }
      }
      else
      {
        if(temp -> key > next_key && temp -> key < key)
        {
          next_key = temp -> key;
        }
      }
      temp = temp -> next;
    }
  }
  return found;
}

// Removes all key-value pairs from the map. Does not change the
// current capacity of the table.
template<typename K, typename V>
void HashMap<K,V>::clear()
{
  Node* temp = nullptr;
  Node* next = nullptr;
  for(int i = 0; i < capacity; i++)
  {
    temp = table[i];
    while(temp != nullptr)
    {
      next = temp -> next;
      delete temp;
      temp = next;
    }
  }
  count = 0;
}

// statistics functions for the hash table implementation
template<typename K, typename V>
int HashMap<K,V>::min_chain_length() const
{
  int min = count;
  int temp_min;
  Node* temp;
  for(int i = 0; i < capacity; i++)
  {
    temp_min = 0;
    temp = table[i];
    while(temp != nullptr)
    {
      temp = temp -> next;
      temp_min++;
    }
    if(temp_min < min && temp_min > 0)
    {
      min = temp_min;
    }
  }
  return min;
}

template<typename K, typename V>
int HashMap<K,V>::max_chain_length() const
{
  int max = 0;
  int temp_max;
  Node* temp;
  for(int i = 0; i < capacity; i++)
  {
    temp_max = 0;
    temp = table[i];
    while(temp != nullptr)
    {
      temp = temp -> next;
      temp_max++;
    }
    if(temp_max > max)
    {
      max = temp_max;
    }
  }
  return max;
}

template<typename K, typename V>
double HashMap<K,V>::avg_chain_length() const
{
  int total = 0;
  int chain_count = 0;
  Node* temp;
  for(int i = 0; i < capacity; i++)
  {
    temp = table[i];
    if(temp != nullptr)
    {
      chain_count++;
    }
    while(temp != nullptr)
    {
      temp = temp -> next;
      total++;
    }
  }
  if(total == 0)
  {
    return total;
  }
  return total/1.0/chain_count;
}

template<typename K, typename V>
int HashMap<K,V>::hash(const K& key) const
{
  std::hash<K> hash_code;
  int code = hash_code(key);
  return code % capacity;
}

// resize and rehash the table

template<typename K, typename V>
void HashMap<K,V>::resize_and_rehash()
{
  capacity = capacity * 2;
  Node** temp_table = new Node*[capacity];
  for(int i = 0; i < capacity; i++)
  {
    temp_table[i] = nullptr;
  }
  for(int i = 0; i < capacity/2; i++)
  {
    Node* temp = table[i];
    while(temp != nullptr)
    {
      Node* holder = temp;
      temp = temp -> next;
      int index = hash(holder->key);
      if(temp_table[index] == nullptr)
      {
        holder -> next = nullptr;
        temp_table[index] = holder;
      }
      else
      {
        holder -> next = temp_table[index];
        temp_table[index] = holder;
      }
    }
  }
  delete[] table;
  table = temp_table;
}

// initialize the table to all nullptr

template<typename K, typename V>
void HashMap<K,V>::init_table()
{
  for(int i = 0; i < capacity; i++)
  {
    table[i] = nullptr;
  }
}

#endif