//---------------------------------------------------------------------------
// NAME: Samuel Sovi
// FILE: binsearchmap.h
// DATE: 3/23/22
// DESC:implementation of a binary search map.
//---------------------------------------------------------------------------

#ifndef BINSEARCHMAP_H
#define BINSEARCHMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class BinSearchMap : public Map<K,V>
{
public:

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

  // Extends the collection by adding the given key-value
  // pair. Assumes the key being added is not present in the
  // collection. Insert does not check if the key is present.
  void insert(const K& key, const V& value);

  // Shrinks the collection by removing the key-value pair with the
  // given key. Does not modify the collection if the collection does
  // not contain the key. Throws out_of_range if the given key is not
  // in the collection.
  void erase(const K& key);

  // Returns true if the key is in the collection, and false
  // otherwise.
  bool contains(const K& key) const;

  // Returns the keys k in the collection such that k1 <= k <= k2
  ArraySeq<K> find_keys(const K& k1, const K& k2) const;

  // Returns the keys in the collection in ascending sorted order.
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
  

private:

  // If the key is in the collection, bin_search returns true and
  // provides the key's index within the array sequence (via the index
  // output parameter). If the key is not in the collection,
  // bin_search returns false and provides the last index checked by
  // the binary search algorithm. 
  bool bin_search(const K& key, int& index) const;
  
  // implemented as a resizable array of (key-value) pairs
  ArraySeq<std::pair<K,V>> seq;

};

// TODO: Implement the functions above. Be sure to read over the
// requirements in the homework and lecture notes. Note that you must
// use the bin search helper function throughout and not just for
// contains (see lecture notes).

// Returns the number of key-value pairs in the map
template<typename K, typename V>
int BinSearchMap<K,V>::size() const
{
  return seq.size();
}

// Tests if the map is empty
template<typename K, typename V>
bool BinSearchMap<K,V>::empty() const
{
  return seq.size() == 0;
}

// Allows values associated with a key to be updated. Throws
// out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& BinSearchMap<K,V>::operator[](const K& key)
{
  int index = -1;
  if(bin_search(key, index) == false)
  {
    throw(std::out_of_range("BinSearchMap<K,V>::operator[](const K& key)"));
  }
  else
  {
    return seq[index].second;
  }
}

// Returns the value for a given key. Throws out_of_range if the
// given key is not in the collection.
template<typename K, typename V> 
const V& BinSearchMap<K,V>::operator[](const K& key) const
{
  int index = -1;
  if(bin_search(key, index) == false)
  {
    throw(std::out_of_range("BinSearchMap<K,V>::operator[](const K& key)"));
  }
  else
  {
    return seq[index].second;
  }
}

// Extends the collection by adding the given key-value
// pair. Assumes the key being added is not present in the
// collection. Insert does not check if the key is present.
template<typename K, typename V>
void BinSearchMap<K,V>::insert(const K& key, const V& value)
{
  int index = 0;
  std::pair<K,V> p {key,value};
  if(empty())
  {
    seq.insert(p, index);
  }
  else
  {
    bin_search(key, index);
    if(key > seq[index].first)
    {
      seq.insert(p, index+1);
    }
    else
    {
      seq.insert(p, index);
    }
  }
}

// Shrinks the collection by removing the key-value pair with the
// given key. Does not modify the collection if the collection does
// not contain the key. Throws out_of_range if the given key is not
// in the collection.
template<typename K, typename V>
void BinSearchMap<K,V>::erase(const K& key)
{
  int index = 0;
  if(bin_search(key, index))
  {
    seq.erase(index);
  }
  else
  {
    throw(std::out_of_range("BinSearchMap<K,V>::erase(const K& key)"));
  }
}

// Returns true if the key is in the collection, and false
// otherwise.
template<typename K, typename V>
bool BinSearchMap<K,V>::contains(const K& key) const
{
  int index = 0;
  
  return bin_search(key, index);
}

// Returns the keys k in the collection such that k1 <= k <= k2
template<typename K, typename V>
ArraySeq<K> BinSearchMap<K,V>::find_keys(const K& k1, const K& k2) const
{
  ArraySeq<K> temp;
  if(empty())
  {
    return temp;
  }
  int index = 0;
  bin_search(k1, index);
  if(index != -1 && seq[index].first < k1)
  {
    index++;
  }
  for(int i = index; i < seq.size(); i++)
  {
    if(seq[i].first > k2)
    {
      break;
    }
    temp.insert(seq[i].first, temp.size());
  }
  return temp;
}

// Returns the keys in the collection in ascending sorted order.
template<typename K, typename V>
ArraySeq<K> BinSearchMap<K,V>::sorted_keys() const
{
  ArraySeq<K> temp;
  for(int i=0; i < seq.size(); i++)
  {
    temp.insert(seq[i].first, temp.size());
  }
  return temp;
}

// Gives the key (as an ouptput parameter) immediately after the
// given key according to ascending sort order. Returns true if a
// successor key exists, and false otherwise.
template<typename K, typename V>
bool BinSearchMap<K,V>::next_key(const K& key, K& next_key) const
{
  int index = -1;
  bin_search(key, index);
  if(index == -1)
  {
    return false;
  }
  if(seq[index].first > key)
  {
    next_key = seq[index].first;
    return true;
  }
  else
  {
    if(index < seq.size() - 1)
    {
      next_key = seq[index+1].first;
      return true;
    }
  }
  return false;
}

// Gives the key (as an ouptput parameter) immediately before the
// given key according to ascending sort order. Returns true if a
// predecessor key exists, and false otherwise.
template<typename K, typename V>
bool BinSearchMap<K,V>::prev_key(const K& key, K& prev_key) const
{
  int index = -1;
  bin_search(key, index);
  if(index == -1)
  {
    return false;
  }
  if(seq[index].first < key)
  {
    prev_key = seq[index].first;
    return true;
  }
  else
  {
    if(index > 0)
    {
      prev_key = seq[index-1].first;
      return true;
    }
  }
  return false;
} 

template<typename K, typename V>
void BinSearchMap<K,V>::clear()
{
  seq.clear();
}

// If the key is in the collection, bin_search returns true and
// provides the key's index within the array sequence (via the index
// output parameter). If the key is not in the collection,
// bin_search returns false and provides the last index checked by
// the binary search algorithm.
template<typename K, typename V> 
bool BinSearchMap<K,V>::bin_search(const K& key, int& index) const
{
  if(seq.size() > 0)
  {
    int left = 0;
    int right = seq.size() - 1;
    index = -1;
    K temp;
    while(left <= right)
    {
      index = (left + right)/2;
      temp = seq[index].first;
      if(temp == key)
      {
        return true;
      }

      if(key > temp)
      {
        left = index + 1;
      }

      else
      {
        right = index - 1;
      }
    }
  }
  return false;
}

#endif
