//---------------------------------------------------------------------------
// NAME: 
// FILE: avlmap.h
// DATE: Spring 2022
// DESC: 
//---------------------------------------------------------------------------

#ifndef AVLMAP_H
#define AVLMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class AVLMap : public Map<K,V>
{
public:

  // default constructor
  AVLMap();

  // copy constructor
  AVLMap(const AVLMap& rhs);

  // move constructor
  AVLMap(AVLMap&& rhs);

  // copy assignment
  AVLMap& operator=(const AVLMap& rhs);

  // move assignment
  AVLMap& operator=(AVLMap&& rhs);  

  // destructor
  ~AVLMap();
  
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

  // helper to print the tree for debugging
  void print() const;

private:

  // node for linked-list separate chaining
  struct Node {
    K key;
    V value;
    int height;
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

  // insert helper
  Node* insert(const K& key, const V& value, Node* st_root);
  
  // erase helper
  Node* erase(const K& key, Node* st_root);

  // find_keys helper
  void find_keys(const K& k1, const K& k2, const Node* st_root,
                 ArraySeq<K>& keys) const;

  // sorted_keys helper
  void sorted_keys(const Node* st_root, ArraySeq<K>& keys) const;

  // rotations
  Node* rotate_right(Node* k2);
  Node* rotate_left(Node* k2);

  // rebalance
  Node* rebalance(Node* st_root);

  // print helper
  void print(std::string indent, const Node* st_root) const;
};


template<typename K, typename V>
void AVLMap<K,V>::print() const
{
  print(std::string(""), root);
}


template<typename K, typename V>
void AVLMap<K,V>::print(std::string indent, const Node* st_root) const
{
  if (!st_root)
    return;
  std::cout << st_root->key << " (" << st_root->height << ")" <<  std::endl;
  if (st_root->left) {
    std::cout << indent << " lft: ";
    print(indent + " ", st_root->left);
  }
  if (st_root->right) {
    std::cout << indent << " rgt: ";
    print(indent + " ", st_root->right);
  }
}


template<typename K, typename V>
AVLMap<K,V>::AVLMap()
{
}

// TODO: Finish the remaining functions below. Many of the functions
// for this assignment can be taken from HW8. Note that for helper
// functions that return Node*, you must include the template
// information for the type, e.g.:
//   template<typename K, typename V>
//   typename AVLMap<K,V>::Node* AVLMap<K,V>::rotate_right(Node* k2)



// copy constructor
template<typename K, typename V>
AVLMap<K,V>::AVLMap(const AVLMap& rhs)
{
  *this = rhs;
}

// move constructor
template<typename K, typename V>
AVLMap<K,V>::AVLMap(AVLMap&& rhs)
{
  *this = std::move(rhs);
}

// copy assignment
template<typename K, typename V>
AVLMap<K,V>& AVLMap<K,V>::operator=(const AVLMap& rhs)
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
AVLMap<K,V>& AVLMap<K,V>::operator=(AVLMap&& rhs)
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
AVLMap<K,V>::~AVLMap()
{
  clear();
}

// Returns the number of key-value pairs in the map
template<typename K, typename V>
int AVLMap<K,V>::size() const
{
  return count;
}

// Tests if the map is empty
template<typename K, typename V>
bool AVLMap<K,V>::empty() const
{
  return count == 0;
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& AVLMap<K,V>::operator[](const K& key)
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
const V& AVLMap<K,V>::operator[](const K& key) const
{
  if(root == nullptr)
  {
    throw(std::out_of_range("AVLMap<K,V>::operator[](const K& key)"));
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
  throw(std::out_of_range("AVLMap<K,V>::operator[](const K& key)"));
}

// Extends the collection by adding the given key-value pair.
// Expects key to not exist in map prior to insertion.
template<typename K, typename V>
void AVLMap<K,V>::insert(const K& key, const V& value)//////////////////////////////////skipped
{
  root = insert(key, value, root);
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template<typename K, typename V>
void AVLMap<K,V>::erase(const K& key)//////////////////////////////////skipped
{
  root = erase(key,root);
}

// Returns true if the key is in the collection, and false otherwise.
template<typename K, typename V>
bool AVLMap<K,V>::contains(const K& key) const
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
ArraySeq<K> AVLMap<K,V>::find_keys(const K& k1, const K& k2) const
{
  ArraySeq<K> keys;
  find_keys(k1,k2,root,keys);
  return keys;
}

// Returns the keys in the collection in ascending sorted order
template<typename K, typename V>
ArraySeq<K> AVLMap<K,V>::sorted_keys() const
{
  ArraySeq<K> keys;
  sorted_keys(root, keys);
  return keys;
}  

// Gives the key (as an ouptput parameter) immediately after the
// given key according to ascending sort order. Returns true if a
// successor key exists, and false otherwise.
template<typename K, typename V>
bool AVLMap<K,V>::next_key(const K& key, K& next_key) const
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
bool AVLMap<K,V>::prev_key(const K& key, K& prev_key) const
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
void AVLMap<K,V>::clear()
{
  clear(root);
}

// Returns the height of the binary search tree
template<typename K, typename V>
int AVLMap<K,V>::height() const
{
  if(root != nullptr)
  {
    return root -> height;
  }
  return 0;
}

// clear function
template<typename K, typename V>
void AVLMap<K,V>::clear(Node* st_root)
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
typename AVLMap<K,V>::Node* AVLMap<K,V>::copy(const Node* rhs_st_root) const
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

// insert helper
template<typename K, typename V>
typename AVLMap<K,V>::Node* AVLMap<K,V>::insert(const K& key, const V& value, Node* st_root)//////skipped
{
  if (st_root == nullptr)
  {
    count++;
    Node* node1 = new Node();
    node1 -> key = key;
    node1 -> value = value;
    node1 -> left = nullptr;
    node1 -> right = nullptr;
    node1 -> height = 1;
    return node1;
  }
  else if(key < st_root -> key)
  {
    st_root -> left = insert(key, value, st_root -> left);
  }
  else
  {
    st_root -> right = insert(key, value, st_root-> right);
  }

  //here we are checking the height
  if(st_root -> left == nullptr && st_root -> right == nullptr)
  {
    st_root -> height = 1;
  }
  else
  {
    if(st_root -> left == nullptr)
    {
      st_root -> height = 1 + st_root -> right -> height;
    }
    else if(st_root -> right == nullptr)
    {
      st_root -> height = 1 + st_root -> left -> height;
    }
    else
    {
      if(st_root -> left -> height > st_root -> right -> height)
      {
        st_root -> height = 1 + st_root -> left -> height;
      }
      else
      {
        st_root -> height = 1 + st_root -> right -> height;
      }
    }
  }
  return rebalance(st_root);
}

// erase helper
template<typename K, typename V>
typename AVLMap<K,V>::Node* AVLMap<K,V>::erase(const K& key, Node* st_root)//////skipped
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
    Node* temp = st_root;
    
    if(st_root -> left == nullptr)
    {
      temp = st_root -> right;
      delete st_root;
      count--;
      return temp;
    }
    else if(st_root -> right == nullptr)
    {
      temp = st_root -> left;
      delete st_root;
      count--;
      return temp;
    }
    else
    {
      Node* temp = st_root -> right;

      while(temp -> left != nullptr)
      {
        temp = temp -> left;
      }
      st_root -> key = temp -> key;
      st_root -> value = st_root -> value;
      st_root -> right = erase(temp -> key, st_root -> right);
    }
  }
  if(st_root -> left == nullptr && st_root -> right == nullptr)
  {
    st_root -> height = 1;
  }
  else
  {
    if(st_root -> left == nullptr)
    {
      st_root -> height = 1 + st_root -> right -> height;
    }
    else if(st_root -> right == nullptr)
    {
      st_root -> height = 1 + st_root -> left -> height;
    }
    else
    {
      if(st_root -> left -> height > st_root -> right -> height)
      {
        st_root -> height = 1 + st_root -> left -> height;
      }
      else
      {
        st_root -> height = 1 + st_root -> right -> height;
      }
    }

  }
  return rebalance(st_root);
}

// find_keys helper
template<typename K, typename V>
void AVLMap<K,V>::find_keys(const K& k1, const K& k2, const Node* st_root, ArraySeq<K>& keys) const
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
        keys.insert(st_root -> key, keys.size());
        find_keys(k1,k2,st_root -> right, keys);
      }
      else if(st_root -> key == k2)
      {
        find_keys(k1,k2,st_root -> left, keys);
        keys.insert(st_root -> key, keys.size());
      }
      else
      {
        find_keys(k1,k2,st_root -> left, keys);
        keys.insert(st_root -> key, keys.size());
        find_keys(k1,k2,st_root -> right, keys);
      }
    }
  }
}

// sorted_keys helper
template<typename K, typename V>
void AVLMap<K,V>::sorted_keys(const Node* st_root, ArraySeq<K>& keys) const
{
  if(st_root != nullptr)
  {
    sorted_keys(st_root -> left, keys);
    keys.insert(st_root -> key, keys.size());
    sorted_keys(st_root -> right, keys);
  }
}

// rotations
template<typename K, typename V>
typename AVLMap<K,V>::Node* AVLMap<K,V>::rotate_right(Node* k2)//////////skipped
{
  Node* k1 = k2 -> left;
  k2 -> left = k1 -> right;
  k1 -> right = k2;
  if(k2 -> left == nullptr && k2 -> right == nullptr)
  {
    k2 -> height = 1;
  }
  else
  {
    if(k2 -> left == nullptr)
    {
      k2 -> height = 1 + k2 -> right -> height;
    }
    else if(k2 -> right == nullptr)
    {
      k2 -> height = 1 + k2 -> left -> height;
    }
    else
    {
      if(k2 -> left -> height > k2 -> right -> height)
      {
        k2 -> height = 1 + k2 -> left -> height;
      }
      else
      {
        k2 -> height = 1 + k2 -> right -> height;
      }
    }

  }
  if(k1 -> left == nullptr && k1 -> right == nullptr)
  {
    k1 -> height = 1;
  }
  else
  {
    if(k1 -> left == nullptr)
    {
      k1 -> height = 1 + k1 -> right -> height;
    }
    else if(k1 -> right == nullptr)
    {
      k1 -> height = 1 + k1 -> left -> height;
    }
    else
    {
      if(k1 -> left -> height > k1 -> right -> height)
      {
        k1 -> height = 1 + k1 -> left -> height;
      }
      else
      {
        k1 -> height = 1 + k1 -> right -> height;
      }
    }
  }
  return k1;
}

template<typename K, typename V>
typename AVLMap<K,V>::Node* AVLMap<K,V>::rotate_left(Node* k2)//////////skipped
{
  Node* k1 = k2 -> right;
  k2 -> right = k1 -> left;
  k1 -> left = k2;
  if(k2 -> left == nullptr && k2 -> right == nullptr)
  {
    k2 -> height = 1;
  }
  else
  {
    if(k2 -> left == nullptr)
    {
      k2 -> height = 1 + k2 -> right -> height;
    }
    else if(k2 -> right == nullptr)
    {
      k2 -> height = 1 + k2 -> left -> height;
    }
    else
    {
      if(k2 -> left -> height > k2 -> right -> height)
      {
        k2 -> height = 1 + k2 -> left -> height;
      }
      else
      {
        k2 -> height = 1 + k2 -> right -> height;
      }
    }

  }
  if(k1 -> left == nullptr && k1 -> right == nullptr)
  {
    k1 -> height = 1;
  }
  else
  {
    if(k1 -> left == nullptr)
    {
      k1 -> height = 1 + k1 -> right -> height;
    }
    else if(k1 -> right == nullptr)
    {
      k1 -> height = 1 + k1 -> left -> height;
    }
    else
    {
      if(k1 -> left -> height > k1 -> right -> height)
      {
        k1 -> height = 1 + k1 -> left -> height;
      }
      else
      {
        k1 -> height = 1 + k1 -> right -> height;
      }
    }

  }
  return k1;
}

// rebalance
template<typename K, typename V>
typename AVLMap<K,V>::Node* AVLMap<K,V>::rebalance(Node* st_root)
{
  
  if(st_root == nullptr)
  {
    return st_root;
  }

  Node* lptr = st_root -> left;
  Node* rptr = st_root -> right;

  if(lptr != nullptr && rptr == nullptr && lptr->height > 1)
  {
    if(st_root -> left -> right != nullptr)
    {
      st_root -> left = rotate_left(st_root -> left);
    }
    return rotate_right(st_root);
  }
  else if(lptr == nullptr && rptr != nullptr && rptr->height > 1)
  {
    if(st_root -> right -> left != nullptr)
    {
      st_root -> right = rotate_right(st_root -> right);
    }
    return rotate_left(st_root);
  }
  else if(lptr != nullptr && rptr != nullptr)
  {
    if(lptr -> height - rptr -> height > 1)
    {
      // case 3
      if(st_root -> left -> right != nullptr && st_root -> left -> left != nullptr)
      {
        if(st_root -> left -> right -> height > st_root -> left -> left -> height)
        {
          st_root -> left = rotate_left(st_root -> left);
        }
      }
      
      return rotate_right(st_root);
    }
    else if(lptr -> height - rptr -> height < -1)
    {
      // case 4
      if(st_root -> right -> right != nullptr && st_root -> right -> left != nullptr)
      {
        if(st_root -> right -> left -> height > st_root -> right -> right -> height)
        {
          st_root -> right = rotate_right(st_root -> right);
        }
      }
      return rotate_left(st_root);
    }
  }
  return st_root;
}
#endif
