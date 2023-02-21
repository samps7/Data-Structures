//---------------------------------------------------------------------------
// NAME: S. Bowers
// FILE: hw10_test.cpp
// DATE: Fall 2021
// DESC: Basic unit tests for HW-10
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "arrayseq.h"
#include "btreemap.h"

using namespace std;


//----------------------------------------------------------------------
// Basic Tests for the (2-3-4) BTreeMap implementation of Map
//----------------------------------------------------------------------

TEST(BasicBTreeMapTests, EmptyCheck)
{
  BTreeMap<char,int> m;
  ASSERT_EQ(true, m.empty());
  ASSERT_EQ(0, m.size());
}

TEST(BasicBTreeMapTests, InOrderInsertAndContainsCheck)
{
  BTreeMap<char,int> m;
  m.insert('a', 0);
  m.insert('b', 10);
  m.insert('c', 20);
  m.insert('d', 30);
  m.insert('e', 40);
  m.insert('f', 50);
  m.insert('g', 60);
  m.insert('h', 70);
  m.insert('i', 80);
  m.insert('j', 90);
  ASSERT_EQ(10, m.size());
  for (int i = 0; i < m.size(); ++i)
    ASSERT_EQ(true, m.contains('a' + i));
  ASSERT_EQ(3, m.height());
}

TEST(BasicBTreeMapTests, ReverseOrderInsertAndContainsCheck)
{
  BTreeMap<char,int> m;
  m.insert('j', 90);
  m.insert('i', 80);
  m.insert('h', 70);
  m.insert('g', 60);
  m.insert('f', 50);
  m.insert('e', 40);  
  m.insert('d', 30);
  m.insert('c', 20);
  m.insert('b', 10);
  m.insert('a', 0);
  ASSERT_EQ(10, m.size());
  for (int i = 0; i < m.size(); ++i)
    ASSERT_EQ(true, m.contains('a' + i));
  ASSERT_EQ(3, m.height());
}

TEST(BasicBTreeMapTests, OutOfOrderInsertAndContainsCheck)
{
  BTreeMap<char,int> m;
  m.insert('h', 70);
  m.insert('c', 20);
  m.insert('g', 60); 
  m.insert('d', 30);
  m.insert('i', 80);
  m.insert('b', 10);  
  m.insert('j', 90);
  m.insert('a', 0);
  m.insert('f', 50);
  m.insert('e', 40);
  ASSERT_EQ(false, m.empty());
  ASSERT_EQ(10, m.size());
  for (int i = 0; i < m.size(); ++i)
    ASSERT_EQ(true, m.contains('a' + i));
  ASSERT_EQ(2, m.height());
}

TEST(BasicBTreeMapTests, RValueAccessCheck)
{
  BTreeMap<char,int> m;
  m.insert('c', 30);
  m.insert('a', 10);
  m.insert('b', 20);
  m.insert('d', 40);
  ASSERT_EQ(4, m.size());
  ASSERT_EQ(10, m['a']);
  ASSERT_EQ(20, m['b']);
  ASSERT_EQ(30, m['c']);
  ASSERT_EQ(40, m['d']);
}

TEST(BasicBTreeMapTests, LValueAccessCheck)
{
  BTreeMap<char,int> m;
  m.insert('c', 30);
  m.insert('a', 10);
  m.insert('b', 20);
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

//----------------------------------------------------------------------
// ERASE ROOT
//---------------------------------------------------------------------- 

TEST(BasicBTreeMapTests, RootEraseTest)
{
  BTreeMap<char, int> m;
  m.insert('a', 10);
  ASSERT_EQ(1, m.size());
  ASSERT_EQ(1, m.height());
  m.erase('a');
  ASSERT_EQ(false, m.contains('a'));
  ASSERT_EQ(0, m.size());
  ASSERT_EQ(0, m.height());  
}

//----------------------------------------------------------------------
// ERASE CASE 1
//---------------------------------------------------------------------- 

TEST(BasicBTreeMapTests, Case1EraseTest)
{
  BTreeMap<char, int> m;
  m.insert('a', 10);
  m.insert('b', 20);
  ASSERT_EQ(2, m.size());
  ASSERT_EQ(1, m.height());
  // erase one root key
  m.erase('a');
  ASSERT_EQ(false, m.contains('a'));
  ASSERT_EQ(1, m.size());
  ASSERT_EQ(1, m.height());  
  m.insert('a', 10);
  // erase other root key
  ASSERT_EQ(true, m.contains('a'));
  ASSERT_EQ(2, m.size());
  ASSERT_EQ(1, m.height());  
  m.erase('b');
  ASSERT_EQ(false, m.contains('b'));
  ASSERT_EQ(1, m.size());
  ASSERT_EQ(1, m.height());
  // add another level
  m.insert('c', 30);
  m.insert('e', 50);
  m.insert('b', 20);
  m.insert('d', 40);
  ASSERT_EQ(5, m.size());
  ASSERT_EQ(2, m.height());
  // erase key from leaf level
  m.erase('b');
  ASSERT_EQ(false, m.contains('b'));
  ASSERT_EQ(4, m.size());
  ASSERT_EQ(2, m.height());
}

//----------------------------------------------------------------------
// ERASE CASE 3 (a)
//----------------------------------------------------------------------

TEST(BasicBTreeMapTests, Case3ALeftHas2BothLeavesEraseTest)
{
  BTreeMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);  
  m.insert('c', 30);
  m.insert('e', 50);  
  m.insert('f', 60);
  m.insert('d', 40);  
  ASSERT_EQ(6, m.size());
  ASSERT_EQ(2, m.height());
  ASSERT_EQ(true, m.contains('f'));
  // erase the key (requires rebalance)
  m.erase('f');
  ASSERT_EQ(5, m.size());
  ASSERT_EQ(2, m.height());
  ASSERT_EQ(false, m.contains('f'));
}

TEST(BasicBTreeMapTests, Case3ALeftHas2BothInternalNodesEraseTest)
{
  BTreeMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);  
  m.insert('c', 30);
  m.insert('d', 40);
  m.insert('e', 50);
  m.insert('f', 60);  
  m.insert('g', 70);
  m.insert('h', 80);
  m.insert('i', 90);
  m.insert('j', 100);
  m.insert('k', 110);
  ASSERT_EQ(11, m.size());
  ASSERT_EQ(3, m.height());
  ASSERT_EQ(true, m.contains('j'));
  // erase the key (requires rebalance)
  m.erase('j');
  ASSERT_EQ(10, m.size());
  ASSERT_EQ(3, m.height());
  ASSERT_EQ(false, m.contains('j'));
}

TEST(BasicBTreeMapTests, Case3ARightHas2BothLeavesEraseTest)
{
  BTreeMap<char,int> m;
  m.insert('z', 10);
  m.insert('y', 20);  
  m.insert('x', 30);
  m.insert('v', 50);  
  m.insert('u', 60);
  m.insert('w', 40);  
  ASSERT_EQ(6, m.size());
  ASSERT_EQ(2, m.height());
  ASSERT_EQ(true, m.contains('u'));
  // erase the key (requires rebalance)
  m.erase('u');
  ASSERT_EQ(5, m.size());
  ASSERT_EQ(2, m.height());
  ASSERT_EQ(false, m.contains('u'));
}

TEST(BasicBTreeMapTests, Case3ARightHas2BothInternalNodesEraseTest)
{
  BTreeMap<char,int> m;
  m.insert('a', 10);
  m.insert('c', 30);
  m.insert('d', 40);
  m.insert('b', 20);  
  m.insert('e', 50);
  m.insert('f', 60);  
  m.insert('g', 70);
  m.insert('h', 80);
  m.insert('i', 90);
  m.insert('j', 100);
  m.insert('k', 110);
  ASSERT_EQ(11, m.size());
  ASSERT_EQ(3, m.height());
  ASSERT_EQ(true, m.contains('a'));
  // erase the key (requires rebalance)
  m.erase('a');
  ASSERT_EQ(10, m.size());
  ASSERT_EQ(3, m.height());
  ASSERT_EQ(false, m.contains('a'));
}

//----------------------------------------------------------------------
// ERASE CASE 3 (b)
//----------------------------------------------------------------------

TEST(BasicBTreeMapTests, Case3BRightHas1BothLeavesEraseTest)
{
  // note: 
  BTreeMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);  
  m.insert('c', 30);
  m.insert('d', 40);
  m.erase('d');
  ASSERT_EQ(3, m.size());
  ASSERT_EQ(2, m.height());
  ASSERT_EQ(true, m.contains('a'));
  // erase the key (requires rebalance)
  m.erase('a');
  ASSERT_EQ(2, m.size());
  ASSERT_EQ(1, m.height());
  ASSERT_EQ(false, m.contains('a'));
}

TEST(BasicBTreeMapTests, Case3BRightHas1BothInternalNodesEraseTest)
{
  BTreeMap<char,int> m;
  m.insert('i', 90);
  m.insert('h', 80);
  m.insert('g', 70);
  m.insert('f', 60);
  m.insert('e', 50);
  m.insert('d', 40);  
  m.insert('c', 30);
  m.insert('b', 20);  
  m.insert('a', 10);
  ASSERT_EQ(9, m.size());
  ASSERT_EQ(3, m.height());
  ASSERT_EQ(true, m.contains('b'));
  // erase the key (requires rebalance)
  m.erase('b');
  ASSERT_EQ(8, m.size());
  ASSERT_EQ(2, m.height());
  ASSERT_EQ(false, m.contains('b'));
}

TEST(BasicBTreeMapTests, Case3BLeftHas1BothLeavesEraseTest)
{
  BTreeMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);  
  m.insert('c', 30);
  m.insert('d', 40);
  m.erase('d');
  ASSERT_EQ(3, m.size());
  ASSERT_EQ(2, m.height());
  ASSERT_EQ(true, m.contains('c'));
  // erase the key (requires rebalance)
  m.erase('c');
  ASSERT_EQ(2, m.size());
  ASSERT_EQ(1, m.height());
  ASSERT_EQ(false, m.contains('c'));
}

TEST(BasicBTreeMapTests, Case3BLeftHas1BothInternalNodesEraseTest)
{
  BTreeMap<char,int> m;
  m.insert('a', 10);
  m.insert('b', 20);  
  m.insert('c', 30);
  m.insert('d', 40);
  m.insert('e', 50);
  m.insert('f', 60);  
  m.insert('g', 70);
  m.insert('h', 80);
  m.insert('i', 90);
  ASSERT_EQ(9, m.size());
  ASSERT_EQ(3, m.height());
  ASSERT_EQ(true, m.contains('g'));
  // erase the key (requires rebalance)
  m.erase('g');
  ASSERT_EQ(8, m.size());
  ASSERT_EQ(2, m.height());
  ASSERT_EQ(false, m.contains('g'));
}

//----------------------------------------------------------------------
// ERASE CASE 2(a)
//----------------------------------------------------------------------

TEST(BasicBTreeMapTests, Case2AEraseTest)
{
  BTreeMap<char,int> m;
  for (int i = 11; i >= 0; --i)
    m.insert('a' + i, 10*i);
  ASSERT_EQ(12, m.size());
  ASSERT_EQ(3, m.height());
  ASSERT_EQ(true, m.contains('c'));
  m.erase('c');
  ASSERT_EQ(11, m.size());
  ASSERT_EQ(3, m.height());
  ASSERT_EQ(false, m.contains('c'));
}

//----------------------------------------------------------------------
// ERASE CASE 2(b)
//----------------------------------------------------------------------

TEST(BasicBTreeMapTests, Case2BEraseTest)
{
  BTreeMap<char,int> m;
  for (int i = 0; i < 12; ++i)
    m.insert('a' + i, 10*i);
  ASSERT_EQ(12, m.size());
  ASSERT_EQ(3, m.height());
  ASSERT_EQ(true, m.contains('j'));
  m.erase('j');
  ASSERT_EQ(11, m.size());
  ASSERT_EQ(3, m.height());
  ASSERT_EQ(false, m.contains('j'));
}

//----------------------------------------------------------------------
// ERASE CASE 2(c)
//----------------------------------------------------------------------

TEST(BasicBTreeMapTests, CaseTwoCEraseTest)
{
  BTreeMap<char,int> m;
  for (int i = 0; i < 12; ++i)
    m.insert('a' + i, 10*i);
  ASSERT_EQ(12, m.size());
  ASSERT_EQ(3, m.height());
  ASSERT_EQ(true, m.contains('h'));
  m.erase('h');
  ASSERT_EQ(11, m.size());
  ASSERT_EQ(3, m.height());
  ASSERT_EQ(false, m.contains('h'));
}

//----------------------------------------------------------------------
// ERASE GENERAL CASE 
//----------------------------------------------------------------------

TEST(BasicBTreeMapTests, ExtendedEraseCheck)
{
  BTreeMap<char,int> m;
  // create map with all lowercase letters
  for (int i = 0; i < 26; ++i)
    m.insert('a' + i, 10*i);
  ASSERT_EQ(26, m.size());
  ASSERT_EQ(4, m.height());
  // check that all lowercase letters are there
  for (int i = 0; i < 26; ++i)
    ASSERT_EQ(true, m.contains('a' + i));
  // erase and check
  for (int i = 0; i < 26; ++i) {
    m.erase('a' + i);
    ASSERT_EQ(25 - i, m.size());
    ASSERT_EQ(false, m.contains('a' + i));
    for (int j = i + 1; j < 26; ++j)
      ASSERT_EQ(true, m.contains('a' + j));
    
  }
  // check final height
  ASSERT_EQ(0, m.height());
}

//----------------------------------------------------------------------
// Find Keys Tests
//----------------------------------------------------------------------

TEST(BasicBTreeMapTests, FindKeysTests)
{
  BTreeMap<char,int> m;
  m.insert('e', 40);
  m.insert('c', 20);
  m.insert('b', 10);
  m.insert('d', 30);
  m.insert('g', 60);
  m.insert('f', 50);
  m.insert('h', 70);
  ASSERT_EQ(7, m.size());  
  
  ArraySeq<char> k;
  k = m.find_keys('c', 'g');
  ASSERT_EQ(5, k.size());
  for (int i = 0; i < 5; ++i)
    ASSERT_EQ('c' + i, k[i]);
  k = m.find_keys('d', 'f');
  ASSERT_EQ(3, k.size());
  for (int i = 0; i < 3; ++i)
    ASSERT_EQ('d' + i, k[i]);
  k = m.find_keys('a', 'd');
  ASSERT_EQ(3, k.size());
  for (int i = 0; i < 3; ++i)
    ASSERT_EQ('b' + i, k[i]);
  k = m.find_keys('f', 'i');
  ASSERT_EQ(3, k.size());
  for (int i = 0; i < 3; ++i)
    ASSERT_EQ('f' + i, k[i]);
  k = m.find_keys('a', 'i');
  ASSERT_EQ(7, k.size());
  for (int i = 0; i < 7; ++i)
    ASSERT_EQ('b' + i, k[i]);
}

TEST(BasicBTreeMapTests, SortedKeyCheck)
{
  BTreeMap<char,int> m;
  m.insert('e', 40);
  m.insert('c', 20);
  m.insert('b', 10);
  m.insert('d', 30);
  m.insert('g', 60);
  m.insert('f', 50);
  m.insert('h', 70);
  ASSERT_EQ(7, m.size());  
  ArraySeq<char> k;
  k = m.sorted_keys();
  ASSERT_EQ(7, k.size());  
  for (int i = 0; i < 7; ++i)
    ASSERT_EQ('b' + i, k[i]);
}

TEST(BasicBTreeMapTests, InvalidKeyCheck)
{
  BTreeMap<char,int> m;
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

TEST(BasicBTreeMapTests, DestructorCheck)
{
  BTreeMap<char,int>* m = new BTreeMap<char,int>;
  EXPECT_NO_THROW(delete m);
  m = new BTreeMap<char,int>;
  m->insert('a', 1);
  EXPECT_NO_THROW(delete m);
  m = new BTreeMap<char,int>;
  for (char c = 'a'; c <= 'z'; ++c)
    m->insert(c, (int)(c - 'a'));
  EXPECT_NO_THROW(delete m);
  m = new BTreeMap<char,int>;
  m->insert('e', 40);
  m->insert('c', 20);
  m->insert('b', 10);
  m->insert('d', 30);
  m->insert('g', 60);
  m->insert('f', 50);
  m->insert('h', 70);
  EXPECT_NO_THROW(delete m);  
}

TEST(BasicBTreeMapTests, CopyConstructorCheck)
{
  // copy empty seq
  BTreeMap<char,int> m1;
  BTreeMap<char,int> m2(m1);
  ASSERT_EQ(m1.size(), m2.size());
  // copy one-element seq
  m1.insert('a', 1);
  ASSERT_NE(m1.size(), m2.size());
  m2.insert('c', 3);
  m2.insert('b', 2);
  m2.insert('d', 4);
  BTreeMap<char,int> m3(m2);
  ASSERT_EQ(m2.size(), m3.size());
  // remove item and check two seqs are different
  m3.erase('c');
  ASSERT_NE(m2.size(), m3.size());
  ASSERT_EQ(true, m2.contains('c'));
  ASSERT_EQ(false, m3.contains('c'));
}

TEST(BasicBTreeMapTests, CopyAssignmentCheck)
{
  BTreeMap<char,int> m1;
  BTreeMap<char,int> m2;
  // both empty
  m2 = m1;                
  ASSERT_EQ(0, m1.size());
  ASSERT_EQ(0, m2.size());
  // add to m1 (shouldn't change m2)
  m1.insert('a', 0);
  m1.insert('b', 1);
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(0, m2.size());
  ASSERT_EQ(true, m1.contains('a') and m1.contains('b'));
  // assign m 1 to itself (shouldn't change anything)
  m1 = m1;
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(true, m1.contains('a') and m1.contains('b'));
  // add items to m2 and assign m2 to m1
  m2.insert('d', 1);
  m2.insert('c', 0);
  m2.insert('e', 2);
  m1 = m2;
  ASSERT_EQ(3, m2.size());
  ASSERT_EQ(3, m1.size());
  ASSERT_EQ(true, m1.contains('c') and m2.contains('c'));
  ASSERT_EQ(true, m1.contains('d') and m2.contains('d'));
  ASSERT_EQ(true, m1.contains('e') and m2.contains('e'));
  // add to m1 (shouldn't change m2)
  m1.insert('f', 3);
  ASSERT_EQ(4, m1.size());
  ASSERT_EQ(3, m2.size());
  ASSERT_EQ(true, not m2.contains('f') and m1.contains('f'));
}

TEST(BasicBTreeMapTests, MoveConstructorCheck)
{
  // move empty map
  BTreeMap<char,int> m1;
  BTreeMap<char,int> m2(std::move(m1));
  ASSERT_EQ(0, m1.size());
  ASSERT_EQ(0, m2.size());
  // move one-element ma[
  BTreeMap<char,int> m3;
  m3.insert('a', 1);
  ASSERT_EQ(1, m3.size());
  ASSERT_EQ(true, m3.contains('a'));
  BTreeMap<char,int> m4(std::move(m3));
  ASSERT_EQ(0, m3.size());
  ASSERT_EQ(1, m4.size());
  ASSERT_EQ(true, m4.contains('a'));
  // add item to new m (to ensure correct move)
  m4.insert('b', 2);
  ASSERT_EQ(0, m3.size());
  ASSERT_EQ(2, m4.size());
  ASSERT_EQ(true, m4.contains('a') and m4.contains('b'));
}

TEST(BasicBTreeMapTests, MoveAssignmentCheck)
{
  // create a map
  BTreeMap<char,int> m1;
  m1.insert('b', 2);
  m1.insert('a', 1);
  m1.insert('c', 3);
  ASSERT_EQ(3, m1.size());
  // and another
  BTreeMap<char,int> m2;
  m2.insert('d', 4);
  ASSERT_EQ(1, m2.size());
  // move first to second
  m2 = std::move(m1);
  ASSERT_EQ(0, m1.size());
  ASSERT_EQ(3, m2.size());
  ASSERT_EQ(true, m2.contains('a') && m2.contains('b') && m2.contains('c'));
  m1.insert('f', 6);
  m1.insert('e', 5);
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(true, m1.contains('e') && m1.contains('f'));
  ASSERT_EQ(false, m2.contains('e') || m2.contains('f'));
  // create an empty map
  BTreeMap<char,int> m3;
  ASSERT_EQ(0, m3.size());
  // move second to third
  m3 = std::move(m2);
  ASSERT_EQ(3, m3.size());
  ASSERT_EQ(0, m2.size());
  ASSERT_EQ(2, m1.size());
  ASSERT_EQ(true, m3.contains('a') && m3.contains('b') && m3.contains('c'));
}

TEST(BasicBTreeMapTests, NextKeyCheck)
{
  char next = 'a';

  BTreeMap<char,int> m;
  m.insert('a', 0);
  m.insert('b', 10);
  m.insert('c', 20);
  m.insert('d', 30);
  m.insert('e', 40);
  m.insert('f', 50);
  m.insert('g', 60);
  m.insert('h', 70);
  m.insert('i', 80);
  m.insert('j', 90);
  
  m.next_key('j', next);
  ASSERT_EQ('a', next);

  m.next_key('i', next);
  ASSERT_EQ('j', next);

  m.next_key('c', next);
  ASSERT_EQ('d', next);

  m.next_key('e', next);
  ASSERT_EQ('f', next);

  BTreeMap<char,int> m1;
  m1.insert('j', 90);
  m1.insert('i', 80);
  m1.insert('h', 70);
  m1.insert('g', 60);
  m1.insert('f', 50);
  m1.insert('e', 40);  
  m1.insert('d', 30);
  m1.insert('c', 20);
  m1.insert('b', 10);
  m1.insert('a', 0);

  m.next_key('j', next);
  ASSERT_EQ('f', next);

  m.next_key('i', next);
  ASSERT_EQ('j', next);

  m.next_key('c', next);
  ASSERT_EQ('d', next);

  m.next_key('e', next);
  ASSERT_EQ('f', next);
}

TEST(BasicBTreeMapTests, PrevKeyCheck)
{
  char next = 'a';

  BTreeMap<char,int> m;
  m.insert('a', 0);
  m.insert('b', 10);
  m.insert('c', 20);
  m.insert('d', 30);
  m.insert('e', 40);
  m.insert('f', 50);
  m.insert('g', 60);
  m.insert('h', 70);
  m.insert('i', 80);
  m.insert('j', 90);
  
  m.prev_key('a', next);
  ASSERT_EQ('a', next);

  m.prev_key('i', next);
  ASSERT_EQ('h', next);

  m.prev_key('c', next);
  ASSERT_EQ('b', next);

  m.prev_key('e', next);
  ASSERT_EQ('d', next);

  BTreeMap<char,int> m1;
  m1.insert('j', 90);
  m1.insert('i', 80);
  m1.insert('h', 70);
  m1.insert('g', 60);
  m1.insert('f', 50);
  m1.insert('e', 40);  
  m1.insert('d', 30);
  m1.insert('c', 20);
  m1.insert('b', 10);
  m1.insert('a', 0);

  m.prev_key('a', next);
  ASSERT_EQ('d', next);

  m.prev_key('i', next);
  ASSERT_EQ('h', next);

  m.prev_key('c', next);
  ASSERT_EQ('b', next);

  m.prev_key('e', next);
  ASSERT_EQ('d', next);
}

//----------------------------------------------------------------------
// Main
//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
