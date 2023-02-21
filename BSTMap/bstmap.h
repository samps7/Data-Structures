//---------------------------------------------------------------------------
// NAME: Samuel Sovi
// FILE: bstmap.h
// DATE: Spring 2022
// DESC: my implementation of a binary search tree map
//---------------------------------------------------------------------------

#ifndef BSTMAP_H
#define BSTMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class BSTMap : public Map<K,V>
{
public:

  // default constructor
  BSTMap();

  // copy constructor
  BSTMap(const BSTMap& rhs);

  // move constructor
  BSTMap(BSTMap&& rhs);

  // copy assignment
  BSTMap& operator=(const BSTMap& rhs);

  // move assignment
  BSTMap& operator=(BSTMap&& rhs);  

  // destructor
  ~BSTMap();
  
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
  bool prev_key(const K& key, K& prev_key) const; 

  // Removes all key-value pairs from the map.
  void clear();

  // Returns the height of the binary search tree
  int height() const;
  
private:

  // node for linked-list separate chaining
  struct Node {
    K key;
    V value;
    Node* left;
    Node* right;
  };

  // number of key-value pairs in map
  int count = 0;

  // array of linked lists
  Node* root = nullptr;

  // clean up the tree and reset count to zero given subtree root
  void clear(Node* st_root);

  // copy assignment helper
  Node* copy(const Node* rhs_st_root) const;
  
  // erase helper
  Node* erase(const K& key, Node* st_root);

  // find_keys helper
  void find_keys(const K& k1, const K& k2, const Node* st_root,
                 ArraySeq<K>& keys) const;

  // sorted_keys helper
  void sorted_keys(const Node* st_root, ArraySeq<K>& keys) const;

  // height helper
  int height(const Node* st_root) const;
  
};


template<typename K, typename V>
BSTMap<K,V>::BSTMap()
{
}

// TODO: Implement the BST Map functions below. Note that you are not
// allowed to add any additional helper functions and must implement
// the functions as per the guidelines in the homework and lecture
// notes.

// copy constructor
template<typename K, typename V>
BSTMap<K,V>::BSTMap(const BSTMap& rhs)
{
  *this = rhs;
}

// move constructor
template<typename K, typename V>
BSTMap<K,V>::BSTMap(BSTMap&& rhs)
{
  *this = std::move(rhs);
}

// copy assignment
template<typename K, typename V>
BSTMap<K,V>& BSTMap<K,V>::operator=(const BSTMap& rhs)
{
  if(this != &rhs)
  {
    clear();
    root = copy(rhs.root);
    count = rhs.count;
  }
}

// move assignment
template<typename K, typename V>
BSTMap<K,V>& BSTMap<K,V>::operator=(BSTMap&& rhs)
{
  if(this != &rhs)
  {
    clear();
    root = rhs.root;
    count = rhs.count;
    rhs.root = nullptr;
    rhs.count = 0;
    return *this;
  }
}  

// destructor
template<typename K, typename V>
BSTMap<K,V>::~BSTMap()
{
  clear();
}

// Returns the number of key-value pairs in the map
template<typename K, typename V>
int BSTMap<K,V>::size() const
{
  return count;
}

// Tests if the map is empty
template<typename K, typename V>
bool BSTMap<K,V>::empty() const
{
  return count == 0;
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& BSTMap<K,V>::operator[](const K& key)
{
  if(root == nullptr)
  {
    throw(std::out_of_range("BSTMap<K,V>::operator[](const K& key)"));
  }
  else
  {
    Node* temp = root;
    while(temp != nullptr)
    {
      if(temp -> key == key)
      {
        return temp -> value;
      }
      else if(key < temp -> key)
      {
        temp = temp -> left;
      }
      else
      {
        temp = temp -> right;
      }
    }
  }
  throw(std::out_of_range("BSTMap<K,V>::operator[](const K& key)"));
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection. 
template<typename K, typename V>
const V& BSTMap<K,V>::operator[](const K& key) const
{
  if(root == nullptr)
  {
    throw(std::out_of_range("BSTMap<K,V>::operator[](const K& key)"));
  }
  else
  {
    Node* temp = root;
    while(temp != nullptr)
    {
      if(temp -> key == key)
      {
        return temp -> value;
      }
      else if(key < temp -> key)
      {
        temp = temp -> left;
      }
      else
      {
        temp = temp -> right;
      }
    }
  }
  throw(std::out_of_range("BSTMap<K,V>::operator[](const K& key)"));
}

// Extends the collection by adding the given key-value pair.
// Expects key to not exist in map prior to insertion.
template<typename K, typename V>
void BSTMap<K,V>::insert(const K& key, const V& value)
{
  Node* node1 = new Node();
  node1 -> key = key;
  node1 -> value = value;
  node1 -> left = nullptr;
  node1 -> right = nullptr;
  //count = 0;
  if(root == nullptr)
  {
    root = node1;
    count++;
    return;
  }
  else
  {
    Node* temp = root;
    while(temp != nullptr)
    {
      if(key < temp -> key)
      {
        if(temp -> left != nullptr)
        {
          temp = temp -> left;
        }
        else
        {
          temp -> left = node1;
          count++;
          return;
        }
      }
      else
      {
        if(temp -> right != nullptr)
        {
          temp = temp -> right;
        }
        else
        {
          temp -> right = node1;
          count++;
          return;
        }
      }
    }
  }
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template<typename K, typename V>
void BSTMap<K,V>::erase(const K& key)
{
  root = erase(key, root);
}

// Returns true if the key is in the collection, and false otherwise.
template<typename K, typename V>
bool BSTMap<K,V>::contains(const K& key) const
{
  if(root == nullptr)
  {
    return false;
  }
  else
  {
    Node* temp = root;
    while(temp != nullptr)
    {
      if(temp -> key == key)
      {
        return true;
      }
      else if(key < temp -> key)
      {
        temp = temp -> left;
      }
      else
      {
        temp = temp -> right;
      }
    }
  }
  return false;
}

// Returns the keys k in the collection such that k1 <= k <= k2
template<typename K, typename V>
ArraySeq<K> BSTMap<K,V>::find_keys(const K& k1, const K& k2) const
{
  ArraySeq<K> keys;
  find_keys(k1,k2,root,keys);
  return keys;
}

// Returns the keys in the collection in ascending sorted order
template<typename K, typename V>
ArraySeq<K> BSTMap<K,V>::sorted_keys() const
{
  ArraySeq<K> keys;
  sorted_keys(root, keys);
  return keys;
}  

// Gives the key (as an ouptput parameter) immediately after the
// given key according to ascending sort order. Returns true if a
// successor key exists, and false otherwise.
template<typename K, typename V>
bool BSTMap<K,V>::next_key(const K& key, K& next_key) const
{
  if(root == nullptr)
  {
    return false;
  }
  else
  {
    K next = root -> key;
    Node* temp = root;
    while(temp != nullptr)
    {
      if(temp -> key == key)
      {
        if(temp -> right == nullptr)
        {
          if(next > key)
          {
            next_key = next;
            return true;
          }
          return false;
        }
        else
        {
          temp = temp -> right;
          while(temp != nullptr)
          {
            next = temp -> key;
            temp = temp -> left;
          }
          next_key = next;
          return true;
        }
      }
      else if(key < temp -> key)
      {
        next = temp -> key;
        temp = temp -> left;
      }
      else
      {
        temp = temp -> right;
      }
    }
    if(next > key)
    {
      next_key = next;
      return true;
    }
  }
  return false;
} 

// Gives the key (as an ouptput parameter) immediately before the
// given key according to ascending sort order. Returns true if a
// predecessor key exists, and false otherwise.
template<typename K, typename V>
bool BSTMap<K,V>::prev_key(const K& key, K& prev_key) const
{
  if(root == nullptr)
  {
    return false;
  }
  else
  {
    K prev = root -> key;
    Node* temp = root;
    while(temp != nullptr)
    {
      if(temp -> key == key)
      {
        if(temp -> left == nullptr)
        {
          if(prev < key)
          {
            prev_key = prev;
            return true;
          }
          return false;
        }
        else
        {
          temp = temp -> left;
          while(temp != nullptr)
          {
            prev = temp -> key;
            temp = temp -> right;
          }
          prev_key = prev;
          return true;
        }
      }
      else if(key > temp -> key)
      {
        prev = temp -> key;
        temp = temp -> right;
      }
      else
      {
        temp = temp -> left;
      }
    }
    if(prev < key)
    {
      prev_key = prev;
      return true;
    }
  }
  return false;
} 

// Removes all key-value pairs from the map.
template<typename K, typename V>
void BSTMap<K,V>::clear()
{
  clear(root);
}

// Returns the height of the binary search tree
template<typename K, typename V>
int BSTMap<K,V>::height() const
{
  height(root);
}

// clear helper
template<typename K, typename V>
void BSTMap<K,V>::clear(Node* st_root)
{
  if(st_root != nullptr)
  {
    clear(st_root -> left);
    clear(st_root -> right);
    delete st_root;
  }
}

// copy assignment helper
template<typename K, typename V>
typename BSTMap<K,V>::Node* BSTMap<K,V>::copy(const Node* rhs_st_root) const
{
  if(rhs_st_root == nullptr)
  {
    return nullptr;
  }
  else
  {
    Node* temp = new Node();
    temp -> key = rhs_st_root -> key;
    temp -> value = rhs_st_root -> value;
    temp -> left = copy(rhs_st_root -> left);
    temp -> right = copy(rhs_st_root -> right);
    return temp;
  }
}

// erase helper
template<typename K, typename V>
typename BSTMap<K,V>::Node* BSTMap<K,V>::erase(const K& key, Node* st_root)//need to delete
{
  if(st_root == nullptr)
  {
    throw(std::out_of_range("BSTMap<K,V>::erase(const K& key)"));
  }
  if(key < st_root -> key)
  {
    st_root -> left = erase(key, st_root -> left);
  }
  else if(key > st_root -> key)
  {
    st_root -> right = erase(key, st_root -> right);
  }
  else
  {
    count--;
    Node* temp = st_root;
    
    if(st_root -> left == nullptr)
    {
      temp = st_root -> right;
      delete st_root;
      return temp;
    }
    else if(st_root -> right == nullptr)
    {
      temp = st_root -> left;
      delete st_root;
      return temp;
    }
    else
    {
      Node* temp = st_root -> right;
      Node* prev = st_root;
      while(temp -> left != nullptr)
      {
        prev = temp;
        temp = temp -> left;
      }
      if(prev == st_root)
      {
        st_root -> right = temp -> right;
      }
      else
      {
        prev -> left = temp -> right;
      }
      temp -> left = st_root -> left;
      temp -> right = st_root -> right;
      delete st_root;
      st_root = temp;
    }
  }
  return st_root;
}

// find_keys helper
template<typename K, typename V>
void BSTMap<K,V>::find_keys(const K& k1, const K& k2, const Node* st_root, ArraySeq<K>& keys) const
{
  if(st_root != nullptr)
  {
    if(st_root -> key > k2)
    {
      find_keys(k1, k2, st_root -> left, keys);
    }
    else if(st_root -> key < k1)
    {
      find_keys(k1, k2, st_root -> right, keys);
    }
    else
    {
      if(st_root -> key == k1)
      {
        //find_keys(k1,k2,st_root -> left,keys);
        keys.insert(st_root -> key, keys.size());
        find_keys(k1,k2,st_root -> right, keys);
      }
      else if(st_root -> key == k2)
      {
        find_keys(k1,k2,st_root -> left, keys);
        keys.insert(st_root -> key, keys.size());
        //find_keys(k1,k2,st_root -> right,keys);
      }
      else
      {
        find_keys(k1,k2,st_root -> left, keys);
        keys.insert(st_root -> key, keys.size());
        find_keys(k1,k2,st_root -> right, keys);
      }
      
      
      /*
      find_keys(k1,k2,st_root -> left,keys);
      keys.insert(st_root -> key, keys.size());
      find_keys(k1,k2,st_root -> right,keys);
      */
    }
    
    /*
    find_keys(k1,k2,st_root -> left,keys);
    if(st_root -> key >= k1 && st_root -> key <= k2)
    {
      keys.insert(st_root -> key, keys.size());
    }
    find_keys(k1,k2,st_root -> right,keys);
    */
  }
}

// sorted_keys helper
template<typename K, typename V>
void BSTMap<K,V>::sorted_keys(const Node* st_root, ArraySeq<K>& keys) const
{
  if(st_root != nullptr)
  {
    sorted_keys(st_root -> left, keys);
    keys.insert(st_root -> key, keys.size());
    sorted_keys(st_root -> right, keys);
  }
}

// height helper
template<typename K, typename V>
int BSTMap<K,V>::height(const Node* st_root) const
{
  if(st_root == nullptr)
  {
    return 0;
  }
  int left = height(st_root -> left);
  int right = height(st_root -> right);
  if(left > right)
  {
    return left + 1;
  }
  return right + 1;
}


#endif
