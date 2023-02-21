//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: hw6_test.cpp
// DATE: Spring 2022
// DESC: Basic unit tests for binary search array-based implementation
//       of map
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "arrayseq.h"
#include "arraymap.h"
#include "binsearchmap.h"

using namespace std;


//----------------------------------------------------------------------
// Basic Tests for the ArraySeq implementation of Map
//----------------------------------------------------------------------

TEST(BasicBinSearchMapTests, EmptyCheck)
{
  BinSearchMap<char,int> m;
  ASSERT_EQ(true, m.empty());
  ASSERT_EQ(0, m.size());
}

TEST(BasicBinSearchMapTests, InsertCheck)
{
  BinSearchMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);
  m.insert('c', 30);
  m.insert('d', 40);
  ASSERT_EQ(false, m.empty());
  ASSERT_EQ(4, m.size());
}

TEST(BasicBinSearchMapTests, RValueAccessCheck)
{
  BinSearchMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);
  m.insert('c', 30);
  m.insert('d', 40);
  ASSERT_EQ(4, m.size());
  ASSERT_EQ(10, m['a']);
  ASSERT_EQ(20, m['b']);
  ASSERT_EQ(30, m['c']);
  ASSERT_EQ(40, m['d']);
}

TEST(BasicBinSearchMapTests, LValueAccessCheck)
{
  BinSearchMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);
  m.insert('c', 30);
  m.insert('d', 40);
  m['a'] = 40;
  m['b'] = 30;
  m['c'] = 20;
  m['d'] = 10;
  ASSERT_EQ(40, m['a']);
  ASSERT_EQ(30, m['b']);
  ASSERT_EQ(20, m['c']);
  ASSERT_EQ(10, m['d']);
}

TEST(BasicBinSearchMapTests, SimpleContainsCheck)
{
  BinSearchMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);
  m.insert('c', 30);
  m.insert('d', 40);
  ASSERT_EQ(true, m.contains('a'));
  ASSERT_EQ(true, m.contains('b'));
  ASSERT_EQ(true, m.contains('c'));
  ASSERT_EQ(true, m.contains('d'));
  ASSERT_EQ(false, m.contains('e'));
}

TEST(BasicBinSearchMapTests, MoreInvolvedContainsCheck)
{
  BinSearchMap<char,int> m;
  for (int i = 'z'; i >= 'a'; --i) 
    m.insert(i, (int)i);
  for (int i = 'a'; i <= 'z'; ++i)
    ASSERT_EQ(true, m.contains(i));
}


TEST(BasicBinSearchMapTests, EraseCheck)
{
  BinSearchMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);
  m.insert('c', 30);
  m.insert('d', 40);
  ASSERT_EQ(4, m.size());
  m.erase('a');
  ASSERT_EQ(3, m.size());
  ASSERT_EQ(false, m.contains('a'));
  m.erase('c');
  ASSERT_EQ(2, m.size());
  ASSERT_EQ(false, m.contains('c'));
  m.erase('d');
  ASSERT_EQ(1, m.size());
  ASSERT_EQ(false, m.contains('d'));
  m.erase('b');
  ASSERT_EQ(0, m.size());
  ASSERT_EQ(false, m.contains('b'));
}

TEST(BasicBinSearchMapTests, KeyRangeCheck)
{
  BinSearchMap<char,int> m;
  m.insert('b', 10);
  m.insert('c', 20);
  m.insert('d', 30);
  m.insert('e', 40);
  ArraySeq<char> k;
  k = m.find_keys('b', 'd');
  ASSERT_EQ(3, k.size());
  ASSERT_EQ(true, k.contains('b') and k.contains('c') and k.contains('d'));
  k = m.find_keys('a', 'c');
  ASSERT_EQ(2, k.size());
  ASSERT_EQ(true, k.contains('b') and k.contains('c'));
  k = m.find_keys('d', 'f');
  ASSERT_EQ(2, k.size());
  ASSERT_EQ(true, k.contains('d') and k.contains('e'));
}

TEST(BasicBinSearchMapTests, SortedKeyCheck)
{
  BinSearchMap<char,int> m;
  m.insert('e', 50);
  m.insert('a', 10);
  m.insert('c', 30);
  m.insert('b', 20);
  m.insert('d', 40);
  ArraySeq<char> k;
  k = m.sorted_keys();
  ASSERT_EQ(5, k.size());
  ASSERT_EQ('a', k[0]);
  ASSERT_EQ('b', k[1]);
  ASSERT_EQ('c', k[2]);  
  ASSERT_EQ('d', k[3]);  
  ASSERT_EQ('e', k[4]);  
}

TEST(BasicBinSearchMapTests, InvalidKeyCheck)
{
  BinSearchMap<char,int> m;
  int x = 10;
  EXPECT_THROW(m['a'] = x, std::out_of_range);
  EXPECT_THROW(x = m['a'], std::out_of_range);
  EXPECT_THROW(m.erase('a'), std::out_of_range);
  m.insert('a', 10);
  m.insert('c', 30);
  EXPECT_THROW(m['b'] = x, std::out_of_range);
  EXPECT_THROW(x = m['b'], std::out_of_range);
  EXPECT_THROW(m.erase('b'), std::out_of_range);
}

TEST(BasicBinSearchMapTests, NextKeyCheck)
{
  BinSearchMap<char,int> m;
  m.insert('e', 50);
  m.insert('a', 10);
  m.insert('c', 30);
  m.insert('d', 40);
  m.insert('g', 70);
  char next_key = 0;
  ASSERT_EQ(true, m.next_key('a', next_key));
  ASSERT_EQ('c', next_key);
  next_key = 0;
  ASSERT_EQ(true, m.next_key('b', next_key));
  ASSERT_EQ('c', next_key);
  next_key = 0;
  ASSERT_EQ(true, m.next_key('c', next_key));
  ASSERT_EQ('d', next_key);
  next_key = 0;
  ASSERT_EQ(true, m.next_key('e', next_key));
  ASSERT_EQ('g', next_key);
  next_key = 0;
  ASSERT_EQ(true, m.next_key('f', next_key));
  ASSERT_EQ('g', next_key);
  next_key = 0;
  ASSERT_EQ(false, m.next_key('g', next_key));
  ASSERT_EQ(false, m.next_key('h', next_key));
}

TEST(BasicBinSearchMapTests, PrevKeyCheck)
{
  BinSearchMap<char,int> m;
  m.insert('f', 50);
  m.insert('b', 10);
  m.insert('d', 30);
  m.insert('e', 40);
  m.insert('h', 70);
  char prev_key = 0;
  ASSERT_EQ(true, m.prev_key('h', prev_key));
  ASSERT_EQ('f', prev_key);
  prev_key = 0;
  ASSERT_EQ(true, m.prev_key('g', prev_key));
  ASSERT_EQ('f', prev_key);
  prev_key = 0;
  ASSERT_EQ(true, m.prev_key('d', prev_key));
  ASSERT_EQ('b', prev_key);
  prev_key = 0;
  ASSERT_EQ(true, m.prev_key('e', prev_key));
  ASSERT_EQ('d', prev_key);
  prev_key = 0;
  ASSERT_EQ(true, m.prev_key('c', prev_key));
  ASSERT_EQ('b', prev_key);
  ASSERT_EQ(false, m.prev_key('b', prev_key));
  ASSERT_EQ(false, m.prev_key('a', prev_key));
}


//----------------------------------------------------------------------
// Main
//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
