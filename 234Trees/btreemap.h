//---------------------------------------------------------------------------
// NAME: Samuel Sovi
// FILE: btreemap.h
// DATE: Spring 2022
// DESC: Map implementation using a 2-3-4 B-Tree 
//---------------------------------------------------------------------------

#ifndef BTreeMAP_H
#define BTreeMAP_H

#include "map.h"
#include "arrayseq.h"



template<typename K, typename V>
class BTreeMap : public Map<K,V>
{
public:

  // default constructor
  BTreeMap();

  // copy constructor
  BTreeMap(const BTreeMap& rhs);

  // move constructor
  BTreeMap(BTreeMap&& rhs);

  // copy assignment
  BTreeMap& operator=(const BTreeMap& rhs);

  // move assignment
  BTreeMap& operator=(BTreeMap&& rhs);  

  // destructor
  ~BTreeMap();
  
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

  // Removes all key-value pairs from the map.
  void clear();
  
  // Returns the height of the binary search tree
  int height() const;

  // for debugging the tree
  void print() const {
    print("  ", root, height());
  }

  
private:

  // node for 2-3-4 tree
  struct Node {
    ArraySeq<std::pair<K,V>> keyvals;
    ArraySeq<Node*> children;
    // helper functions
    bool full() const {return keyvals.size() == 3;}
    bool leaf() const {return children.empty();}
    K key(int i) const {return keyvals[i].first;}
    V& val(int i) {return keyvals[i].second;}
    Node* child(int i) const {return children[i];}
  };

  // number of key-value pairs in map
  int count = 0;

  // root node
  Node* root = nullptr;

  // print helper function
  void print(std::string indent, Node* st_root, int levels) const;
  
  // clean up the tree memory 
  void clear(Node* st_root);

  // helper function for copy assignment
  Node* copy(const Node* rhs_st_root) const;

  // split the parent's i-th child
  void split(Node* parent, int i);
  
  // erase helpers
  void erase(Node* st_root, const K& key);
  void remove_internal(Node* st_root, int key_idx);
  void rebalance(Node* st_root, int key_idx, int& child_idx);
  
  // find_keys helper
  void find_keys(const K& k1, const K& k2, const Node* st_root,
                 ArraySeq<K>& keys) const;

  // sorted_keys helper
  void sorted_keys(const Node* st_root, ArraySeq<K>& keys) const;

  // height helper
  int height(const Node* st_root) const;
  
};


template<typename K, typename V>
void BTreeMap<K,V>::print(std::string indent, Node* st_root, int levels) const {
  if (levels == 0)
    return;
  if (!st_root)
    return;
  std::cout << indent << "("; 
  for (int i = 0; i < 3; ++i) {
    if (i != 0)
      std::cout << ",";
    if (st_root->keyvals.size() > i)
      std::cout << st_root->key(i); 
    else
      std::cout << "-";
  }
  std::cout << ")" << std::endl;
  if (levels > 1) {
    for (int i = 0; i < st_root->children.size(); ++i)
      print(indent + " ", st_root->child(i), levels - 1);
  }
}


// TODO: Implement the (2-3-4) BTree Map's functions below. See the
// lecture notes for additional details. 

// default constructor
template<typename K, typename V>
BTreeMap<K,V>::BTreeMap()
{
}

// copy constructor
template<typename K, typename V>
BTreeMap<K,V>::BTreeMap(const BTreeMap& rhs)
{
  *this = rhs;
}

// move constructor
template<typename K, typename V>
BTreeMap<K,V>::BTreeMap(BTreeMap&& rhs)
{
  *this = std::move(rhs);
}

// copy assignment
template<typename K, typename V>
BTreeMap<K,V>& BTreeMap<K,V>::operator=(const BTreeMap& rhs)
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
BTreeMap<K,V>& BTreeMap<K,V>::operator=(BTreeMap&& rhs)
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
BTreeMap<K,V>::~BTreeMap()
{
  clear();
}

// Returns the number of key-value pairs in the map
template<typename K, typename V>
int BTreeMap<K,V>::size() const
{
  return count;
}

// Tests if the map is empty
template<typename K, typename V>
bool BTreeMap<K,V>::empty() const
{
  return count == 0;
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& BTreeMap<K,V>::operator[](const K& key)
{
  Node* temp = root;
  if(temp == nullptr)
  {
    throw(std::out_of_range("BTreeMap<K,V>::operator[](const K& key)"));
  }
  while(!(temp -> leaf()))
  {
    for(int i = 0; i < temp -> keyvals.size(); i++)
    {
      if(key < temp -> key(i))
      {
        temp = temp -> child(i); 
        break;
      }
      else if(key == temp -> key(i))
      {
        return temp -> val(i);
      }
      else if(i == temp -> keyvals.size() - 1)
      {
        temp = temp -> child(i + 1);
        break;
      }
    }
  }
  for(int i = 0; i < temp -> keyvals.size(); i++)
  {
    if(key == temp->key(i))
    {
      return temp-> val(i);
    }
  }
  throw(std::out_of_range("BTreeMap<K,V>::operator[](const K& key)"));
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection.
template<typename K, typename V>
const V& BTreeMap<K,V>::operator[](const K& key) const
{
  
}

// Extends the collection by adding the given key-value pair.
// Expects key to not exist in map prior to insertion.
template<typename K, typename V>
void BTreeMap<K,V>::insert(const K& key, const V& value)
{
  count++;
  if(root == nullptr)
  {
    root = new Node();
    std::pair<K,V> pair1;
    pair1.first = key;
    pair1.second = value;
    root -> keyvals.insert(pair1, 0);
  }
  else
  {
    if(root -> full())
    {
      Node* left = root;
      root = new Node();
      root -> children.insert(left, 0);
      split(root, 0);
    }

    Node* prev = root;
    Node* curr = root;

    while(!(curr -> leaf()) || curr -> full())
    {
      if(curr -> full())
      {
        for(int i = 0; i < prev -> keyvals.size(); i++)
        {
          if(key < prev -> key(i))
          {
            split(prev, i);
            i = prev -> children.size();
          }
          else if(i == (prev -> keyvals.size() - 1))
          {
            split(prev, i+1);
            i = prev -> children.size();
          }
        }
        curr = prev;
      }
      prev = curr;

      for(int i = 0; i < curr -> keyvals.size(); i++)
      {
        if(key < curr -> key(i))
        {
          curr = curr -> child(i);
          i = curr -> keyvals.size();
        }
        else if (i == curr -> keyvals.size() - 1)
        {
          curr = curr -> child(i + 1);
          i = curr -> keyvals.size();
        }
      }
    }
    std::pair<K,V> pair1;
    pair1.first = key;
    pair1.second = value;
    int k_count = curr -> keyvals.size();
    for(int i = 0; i < k_count; i++)
    {
      if(key < curr -> key(i))
      {
        curr -> keyvals.insert(pair1, i);
        return;
      }
      else if(i == curr -> keyvals.size() - 1)
      {
        curr -> keyvals.insert(pair1, i + 1);
        return;
      }
    }
  }
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template<typename K, typename V>
void BTreeMap<K,V>::erase(const K& key)
{
  
  erase(root, key);
  if(root -> keyvals.empty())
  {
    Node* left_child = nullptr;
    if(root -> children.size() > 0)
    {
      left_child = root -> child(0);
    }
    delete root;
    root = left_child;
  }
  count--;
}

// Returns true if the key is in the collection, and false otherwise.
template<typename K, typename V>
bool BTreeMap<K,V>::contains(const K& key) const
{
  Node* temp = root;
  if(temp == nullptr)
  {
    return false;
  }
  while(!(temp -> leaf()))
  {
    for(int i = 0; i < temp -> keyvals.size(); i++)
    {
      if(key < temp -> key(i))
      {
        temp = temp -> child(i); 
        break;
      }
      else if(key == temp -> key(i))
      {
        return true;
      }
      else if(i == temp -> keyvals.size() - 1)
      {
        temp = temp -> child(i + 1);
        break;
      }
    }
  }
  for(int i = 0; i < temp -> keyvals.size(); i++)
  {
    if(key == temp->key(i))
    {
      return true;
    }
  }
  return false;
}

// Returns the keys k in the collection such that k1 <= k <= k2
template<typename K, typename V>
ArraySeq<K> BTreeMap<K,V>::find_keys(const K& k1, const K& k2) const
{
  ArraySeq<K> keys;
  find_keys(k1,k2,root,keys);
  return keys;
}

// Returns the keys in the collection in ascending sorted order
template<typename K, typename V>
ArraySeq<K> BTreeMap<K,V>::sorted_keys() const
{
  ArraySeq<K> keys;
  sorted_keys(root, keys);
  return keys;
}  

// Gives the key (as an ouptput parameter) immediately after the
// given key according to ascending sort order. Returns true if a
// successor key exists, and false otherwise.
template<typename K, typename V>
bool BTreeMap<K,V>::next_key(const K& key, K& next_key) const
{
  if(root == nullptr)
    return false;
  Node* temp = root;
  while(!(temp->leaf()))
  {
    for(int i = 0; i < temp -> keyvals.size(); i++)
    {
      if(temp -> key(i) <= key)
      {
        if(i == temp-> keyvals.size() - 1)
        {
          temp = temp -> child(i + 1);
          i = temp -> keyvals.size();
        }
      }
      else if(key < temp->key(i))
      {
        next_key = temp -> key(i);
        temp = temp -> child(i);
        i = temp -> keyvals.size();
        return true;
      }
    }
  }
  for(int i = 0; i < temp -> keyvals.size(); i++)
  {
    if(temp -> key(i) > key)
    {
      next_key = temp -> key(i);
      i = temp -> keyvals.size();
      return true;
    }
  }
} 

// Gives the key (as an ouptput parameter) immediately before the
// given key according to ascending sort order. Returns true if a
// predecessor key exists, and false otherwise.
template<typename K, typename V>
bool BTreeMap<K,V>::prev_key(const K& key, K& next_key) const
{
  
  if(root == nullptr)
  {
    return false;
  }

  Node* temp = root;
  bool found = false;
  while(!(temp -> leaf()))
  {
    for(int i = 0; i < temp -> keyvals.size(); i++)
    {
      if(temp -> key(i) >= key)
      {
        temp = temp -> child(i);
      }
      
      else if(key > temp ->key(i))
      {
        next_key = temp -> key(i);
        found = true;
        if(i == temp -> keyvals.size() - 1)
        {
          temp = temp -> child(i + 1);
          i = temp -> keyvals.size();
        }
      }
    }
  }

  for(int i = 0; i < temp->keyvals.size(); i++)
  {
    if(key > temp -> key(i))
    {
      next_key = temp -> key(i);
      return true;
    }
  }
  return found;
  
} 

// Removes all key-value pairs from the map.
template<typename K, typename V>
void BTreeMap<K,V>::clear()
{
  clear(root);
}

// Returns the height of the binary search tree
template<typename K, typename V>
int BTreeMap<K,V>::height() const
{
  return height(root);
}

//helper functions:

  
// clean up the tree memory 
template<typename K, typename V>
void BTreeMap<K,V>::clear(Node* st_root)
{
  if(st_root == nullptr)
  {
    return;
  }
  if(!(st_root -> leaf()))
  {
    for(int i = 0; i < st_root -> children.size(); i++)
    {
      clear(st_root -> child(i));
    }
  }
  delete st_root;
  count = 0;
}

// helper function for copy assignment
template<typename K, typename V>
typename BTreeMap<K,V>::Node* BTreeMap<K,V>::copy(const Node* rhs_st_root) const
{
  if(rhs_st_root == nullptr)
  {
    return nullptr;
  }
  else
  {
    Node* temp = new Node();
    for(int i = 0; i < rhs_st_root -> keyvals.size(); i++)
    {
      std::pair<K,V> pair1;
      pair1.first = rhs_st_root -> keyvals[i].first;
      pair1.second = rhs_st_root -> keyvals[i].second;
      temp -> keyvals.insert(pair1, temp -> keyvals.size());
    }
    for(int i = 0; i < rhs_st_root -> children.size(); i++)
    {
      temp -> children.insert(copy(rhs_st_root -> child(i)), i);
    }
    return temp;
  }
}

// split the parent's i-th child
template<typename K, typename V>
void BTreeMap<K,V>::split(Node* parent, int i)
{
  // moving up to parent
  std::pair<K,V> pair1;
  pair1.first = parent -> child(i) -> key(1);
  pair1.second = parent -> child(i) -> val(1);
  parent -> keyvals.insert(pair1, i);

  //moving to right
  std::pair<K,V> pair2;
  pair2.first = parent -> child(i) -> key(2);
  pair2.second = parent -> child(i) -> val(2);
  parent -> children.insert(new Node(), i + 1);
  parent -> child(i+1) ->keyvals.insert(pair2, 0);
  parent -> child(i) -> keyvals.erase(2);
  parent -> child(i) -> keyvals.erase(1);
  if(parent ->child(i) -> children.size() >= 3)
  {
    parent -> child(i+1) -> children.insert(parent ->child(i) -> child(2), 0);
    parent ->child(i) -> children.erase(2);

    if(parent ->child(i) -> children.size() >= 3)
    {
      parent -> child(i+1) -> children.insert(parent ->child(i) -> child(2), 1);
      parent ->child(i) -> children.erase(2);
    }
  }
}

// erase helpers
template<typename K, typename V>
void BTreeMap<K,V>::erase(Node* st_root, const K& key)
{
  while(st_root != nullptr)
  {
    if(st_root -> leaf())
    {
      for(int i = 0; i < st_root -> keyvals.size(); i++)
      {
        if(st_root -> key(i) == key)
        {
          st_root -> keyvals.erase(i);
          return;
        }
      }
      break;
    }
    else
    {
      for(int i = 0; i < st_root->keyvals.size(); i++)
      {
        if(key< st_root->key(i))
        {
          int num = i;
          rebalance(st_root, i, num);
          //3a, 3b check
          st_root = st_root->child(num);
          break;
        }
        else if(key == st_root->key(i))
        {
          remove_internal(st_root, i);
          return;
        }
        else if (i == st_root->keyvals.size() -1)
        {
          int num = i + 1;
          rebalance(st_root, i, num);
          st_root = st_root->child(num);
          break;
        }
      }
    }
  }
  throw std::out_of_range("BTreeMap<K,V>::erase(const K&)");
}

template<typename K, typename V>
void BTreeMap<K,V>::remove_internal(Node* st_root, int key_idx)
{
  Node* left = st_root -> child(key_idx);
  Node* right = st_root -> child(key_idx + 1);
  if(left -> keyvals.size() > 1)
  {
    st_root -> keyvals.erase(key_idx);
    st_root -> keyvals.insert(left -> keyvals[left -> keyvals.size() - 1], key_idx);
    if(!(right -> leaf()))
    {
      right -> children.insert(left -> child(left -> children.size() - 1), 0);
      left -> children.erase(left -> children.size() - 1);
    }
    left->keyvals.erase(left -> keyvals.size() - 1);
  }
  else if(right -> keyvals.size() > 1)
  {
    st_root -> keyvals.erase(key_idx);
    st_root -> keyvals.insert(right -> keyvals[0], key_idx);
    if(!(left -> leaf()))
    {
      left -> children.insert(right -> child(0), left -> children.size());
      right -> children.erase(0);
    }
    right->keyvals.erase(0);
  }
  else
  {
    left -> keyvals.insert(st_root -> keyvals[key_idx], 1);
    st_root -> keyvals.erase(key_idx);
    if(!(left -> leaf()))
    {
      left -> children.insert(right -> child(0), left -> children.size());
      left -> children.insert(right -> child(1), left -> children.size());
    }
    left -> keyvals.insert(right -> keyvals[0], 2);
    right -> keyvals.erase(0);
    if((left -> leaf()))
    {
      left -> keyvals.erase(1);
    }
    else
    {
      remove_internal(left, 1);
    }

  }
}

template<typename K, typename V>
void BTreeMap<K,V>::rebalance(Node* st_root, int key_idx, int& child_idx)
{
  if(key_idx >= child_idx)
  {
    Node* right = st_root -> child(child_idx + 1);
    Node* left = st_root -> child(child_idx);
    if(left -> keyvals.size() == 1)
    {
      //if right neighbor has more than 1
      if(right -> keyvals.size() > 1)
      {
        // move root key to left
        left -> keyvals.insert(st_root -> keyvals[key_idx], 1);

        //erase moved root key
        st_root -> keyvals.erase(key_idx);
        if(!(right-> leaf()))
        {
          left -> children.insert(right -> child(0), left -> children.size());
          right -> children.erase(0);
        }
        //move right child to top
        st_root -> keyvals.insert(right -> keyvals[0], key_idx);
        
        //erase moved child
        right -> keyvals.erase(0);
      }
      //if left neighbor has more than 1
      else if(child_idx != 0 && st_root -> child(child_idx - 1) -> keyvals.size() > 1)
      {
        Node* lefter = st_root -> child(child_idx - 1);
        // move root key to right
        left -> keyvals.insert(st_root -> keyvals[key_idx-1], 0);

        //erase moved root key
        st_root -> keyvals.erase(key_idx-1);

        if(!(lefter-> leaf()))
        {
          left -> children.insert(lefter -> child(lefter -> children.size() - 1), 0);
          lefter -> children.erase(lefter -> children.size() - 1);
        }

        //move left child to top
        st_root -> keyvals.insert(lefter -> keyvals[(lefter -> keyvals.size() -1)], key_idx - 1);
        
        //erase moved child
        lefter -> keyvals.erase(lefter -> keyvals.size() - 1);
      }
      else
      {
        //case 3b
        left -> keyvals.insert(st_root -> keyvals[key_idx], 1);
        left -> keyvals.insert(right -> keyvals[0], 2);
        if(!(right -> leaf()))
        {
          for(int i = 0; i < right -> children.size(); i++)
          {
            left -> children.insert(right->child(i), left -> children.size());
          }
        }
        st_root -> keyvals.erase(key_idx);
        delete right;
        st_root -> children.erase(child_idx + 1);
      }
    }
  }
  else if(key_idx < child_idx) // rightmost child (check kids)
  {
    Node* left = st_root -> child(child_idx - 1); // in this case left is -1
    Node* right = st_root -> child(child_idx);
    if(right -> keyvals.size() == 1)
    {
      if(left -> keyvals.size() > 1)
      {
        // move root key to right
        right -> keyvals.insert(st_root -> keyvals[key_idx], 0);

        //erase moved root key
        st_root -> keyvals.erase(key_idx);

        //need to move left's rightmost child right (NOTE: THIS WAS JUST ADDED)
        if(!(left -> leaf()))
        {
          right -> children.insert(left -> child(left -> children.size() -1), 0);
          left -> children.erase(left -> children.size() -1);
        }

        //move left child to top
        st_root -> keyvals.insert(left -> keyvals[(left -> keyvals.size() -1)], key_idx);

        //erase moved child
        left -> keyvals.erase(left -> keyvals.size() -1);
      }
      else
      {
        left -> keyvals.insert(st_root -> keyvals[key_idx], 1);
        left -> keyvals.insert(right -> keyvals[0], 2);
        if(!(right -> leaf()))
        {
          for(int i = 0; i < right -> children.size(); i++)
          {
            left -> children.insert(right->child(i), left -> children.size());
          }
        }
        st_root -> keyvals.erase(key_idx);
        delete right;
        st_root -> children.erase(child_idx);
        child_idx--;
      }
    }
    
  }
}

// find_keys helper
template<typename K, typename V>
void BTreeMap<K,V>::find_keys(const K& k1, const K& k2, const Node* st_root, ArraySeq<K>& keys) const
{
  if(st_root != nullptr)
  {
    if(!(st_root -> leaf()))
    {
      for(int i = 0; i < st_root -> keyvals.size(); i++)
      {
        if(st_root -> key(i) > k1)
        {
          find_keys(k1, k2, st_root -> child(i), keys);
        }
        if(st_root -> key(i) <= k2 && st_root -> key(i) >= k1)
        {
          keys.insert(st_root -> key(i), keys.size());
        }
      }
      if(st_root -> key(st_root -> keyvals.size() - 1) < k2)
      {
        find_keys(k1, k2, st_root -> child(st_root -> keyvals.size()), keys);
      }
    }
    else
    {
      for(int i = 0; i < st_root -> keyvals.size(); i++)
      {
        if(st_root -> key(i) <= k2 && st_root -> key(i) >= k1)
        {
          keys.insert(st_root -> key(i), keys.size());
        }
      }
      
    }
  }
  
}

// sorted_keys helper
template<typename K, typename V>
void BTreeMap<K,V>::sorted_keys(const Node* st_root, ArraySeq<K>& keys) const
{
  if(!(root == nullptr))
  {
    if(!(st_root -> leaf()))
    {
      for(int i = 0; i < st_root -> keyvals.size(); i++)
      {
        sorted_keys(st_root -> child(i), keys);
        keys.insert(st_root -> key(i), keys.size());
      }
      sorted_keys(st_root -> child(st_root -> keyvals.size()), keys);
    }
    else
    {
      for(int i = 0; i < st_root -> keyvals.size(); i++)
      {
        keys.insert(st_root -> key(i), keys.size());
      }
    }
  }
}

// height helper
template<typename K, typename V>
int BTreeMap<K,V>::height(const Node* st_root) const
{
  if(root == nullptr)
  {
    return 0;
  }
  int height = 0;
  Node* temp = root;
  while(!(temp -> leaf()))
  {
    height++;
    temp = temp -> child(0);
  }
  height++;
  return height;
}

#endif
