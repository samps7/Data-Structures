//---------------------------------------------------------------------------
// NAME: Samuel Sovi
// FILE: hw4_test.cpp
// DATE: Spring 2022
// DESC: implements tests to check if my sorts are working
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "linkedseq.h"
#include "arrayseq.h"

using namespace std;


//----------------------------------------------------------------------
// ArraySeq Merge Sort Tests
//----------------------------------------------------------------------

TEST(BasicArraySeqTests, EmptySeqMergeSort)
{
  ArraySeq<int> seq;
  ASSERT_EQ(true, seq.empty());
  seq.merge_sort();
  ASSERT_EQ(true, seq.empty());
}

TEST(BasicArraySeqTests, OneElemMergeSort)
{
  ArraySeq<int> seq;
  seq.insert(10, 0);
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
  seq.merge_sort();
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
}

TEST(BasicArraySeqTests, TwoElemInOrderMergeSort)
{
  ArraySeq<int> seq;
  seq.insert(10, 0);
  seq.insert(20, 1);
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
  seq.merge_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}


TEST(BasicArraySeqTests, TwoElemReverseMergeSort)
{
  ArraySeq<int> seq;
  seq.insert(20, 0);
  seq.insert(10, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(20, seq[0]);
  ASSERT_EQ(10, seq[1]);
  seq.merge_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

// three element tests
TEST(BasicArraySeqTests, ThreeElemMergeSortCases)
{
  ArraySeq<int> seq1; // <10,20,30>
  ArraySeq<int> seq2; // <20,30,10>
  ArraySeq<int> seq3; // <30,10,20>
  seq1.insert(10, 0);
  seq1.insert(20, 1);
  seq1.insert(30, 2);
  seq2.insert(20, 0);
  seq2.insert(30, 1);
  seq2.insert(10, 2);
  seq3.insert(30, 0);
  seq3.insert(10, 1);
  seq3.insert(20, 2);
  seq1.merge_sort();
  seq2.merge_sort();
  seq3.merge_sort();
  for (int i = 1; i <= 3; ++i) {
    ASSERT_EQ(i*10, seq1[i-1]);
    ASSERT_EQ(i*10, seq2[i-1]);
    ASSERT_EQ(i*10, seq3[i-1]);
  }
}


//----------------------------------------------------------------------
// LinkedSeq Merge Sort Tests
//----------------------------------------------------------------------

TEST(BasicLinkedSeqTests, EmptySeqMergeSort)
{
  LinkedSeq<int> seq;
  ASSERT_EQ(true, seq.empty());
  seq.merge_sort();
  ASSERT_EQ(true, seq.empty());
}

TEST(BasicLinkedSeqTests, OneElemMergeSort)
{
  LinkedSeq<int> seq;
  seq.insert(10, 0);
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
  seq.merge_sort();
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
}

TEST(BasicLinkedSeqTests, TwoElemInOrderMergeSort)
{
  LinkedSeq<int> seq;
  seq.insert(10, 0);
  seq.insert(20, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
  seq.merge_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}


TEST(BasicLinkedSeqTests, TwoElemReverseMergeSort)
{
  LinkedSeq<int> seq;
  seq.insert(20, 0);
  seq.insert(10, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(20, seq[0]);
  ASSERT_EQ(10, seq[1]);
  seq.merge_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

// three element tests
TEST(BasicLinkedSeqTests, ThreeElemMergeSortCases)
{
  LinkedSeq<int> seq1; // <10,20,30>
  LinkedSeq<int> seq2; // <20,30,10>
  LinkedSeq<int> seq3; // <30,10,20>
  seq1.insert(10, 0);
  seq1.insert(20, 1);
  seq1.insert(30, 2);
  seq2.insert(20, 0);
  seq2.insert(30, 1);
  seq2.insert(10, 2);
  seq3.insert(30, 0);
  seq3.insert(10, 1);
  seq3.insert(20, 2);
  seq1.merge_sort();
  seq2.merge_sort();
  seq3.merge_sort();
  for (int i = 1; i <= 3; ++i) {
    ASSERT_EQ(i*10, seq1[i-1]);
    ASSERT_EQ(i*10, seq2[i-1]);
    ASSERT_EQ(i*10, seq3[i-1]);
  }
}


//----------------------------------------------------------------------
// ArraySeq Quick Sort Tests
//----------------------------------------------------------------------

TEST(BasicArraySeqTests, EmptySeqQuickSort)
{
  ArraySeq<int> seq;
  ASSERT_EQ(true, seq.empty());
  seq.quick_sort();
  ASSERT_EQ(true, seq.empty());
}

TEST(BasicArraySeqTests, OneElemQuickSort)
{
  ArraySeq<int> seq;
  seq.insert(10, 0);
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
  seq.quick_sort();
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
}

TEST(BasicArraySeqTests, TwoElemInOrderQuickSort)
{
  ArraySeq<int> seq;
  seq.insert(10, 0);
  seq.insert(20, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
  seq.quick_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}


TEST(BasicArraySeqTests, TwoElemReverseQuickSort)
{
  ArraySeq<int> seq;
  seq.insert(20, 0);
  seq.insert(10, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(20, seq[0]);
  ASSERT_EQ(10, seq[1]);
  seq.quick_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

// three element tests
TEST(BasicArraySeqTests, ThreeElemQuickSortCases)
{
  ArraySeq<int> seq1; // <10,20,30>
  ArraySeq<int> seq2; // <20,30,10>
  ArraySeq<int> seq3; // <30,10,20>
  seq1.insert(10, 0);
  seq1.insert(20, 1);
  seq1.insert(30, 2);
  seq2.insert(20, 0);
  seq2.insert(30, 1);
  seq2.insert(10, 2);
  seq3.insert(30, 0);
  seq3.insert(10, 1);
  seq3.insert(20, 2);
  seq1.quick_sort();
  seq2.quick_sort();
  seq3.quick_sort();
  for (int i = 1; i <= 3; ++i) {
    ASSERT_EQ(i*10, seq1[i-1]);
    ASSERT_EQ(i*10, seq2[i-1]);
    ASSERT_EQ(i*10, seq3[i-1]);
  }
}

//----------------------------------------------------------------------
// LinkedSeq Quick Sort Tests
//----------------------------------------------------------------------

TEST(BasicLinkedSeqTests, EmptySeqQuickSort)
{
  LinkedSeq<int> seq;
  ASSERT_EQ(true, seq.empty());
  seq.quick_sort();
  ASSERT_EQ(true, seq.empty());
}

TEST(BasicLinkedSeqTests, OneElemQuickSort)
{
  LinkedSeq<int> seq;
  seq.insert(10, 0);
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
  seq.quick_sort();
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
}

TEST(BasicLinkedSeqTests, TwoElemInOrderQuickSort)
{
  LinkedSeq<int> seq;
  seq.insert(10, 0);
  seq.insert(20, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
  seq.quick_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

TEST(BasicLinkedSeqTests, TwoElemReverseQuickSort)
{
  LinkedSeq<int> seq;
  seq.insert(20, 0);
  seq.insert(10, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(20, seq[0]);
  ASSERT_EQ(10, seq[1]);
  seq.quick_sort();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

// three element tests
TEST(BasicLinkedSeqTests, ThreeElemQuickSortCases)
{
  LinkedSeq<int> seq1; // <10,20,30>
  LinkedSeq<int> seq2; // <20,30,10>
  LinkedSeq<int> seq3; // <30,10,20>
  seq1.insert(10, 0);
  seq1.insert(20, 1);
  seq1.insert(30, 2);
  seq2.insert(20, 0);
  seq2.insert(30, 1);
  seq2.insert(10, 2);
  seq3.insert(30, 0);
  seq3.insert(10, 1);
  seq3.insert(20, 2);
  seq1.quick_sort();
  seq2.quick_sort();
  seq3.quick_sort();
  
  for (int i = 1; i <= 3; ++i) {
    ASSERT_EQ(i*10, seq1[i-1]);
    ASSERT_EQ(i*10, seq2[i-1]);
    ASSERT_EQ(i*10, seq3[i-1]);
  }
  
}



//----------------------------------------------------------------------
// ArraySeq Random-Pivot Quick Sort Tests
//----------------------------------------------------------------------

TEST(BasicArraySeqTests, EmptySeqRandQuickSort)
{
  ArraySeq<int> seq;
  ASSERT_EQ(true, seq.empty());
  seq.quick_sort_random();
  ASSERT_EQ(true, seq.empty());
}

TEST(BasicArraySeqTests, OneElemRandQuickSort)
{
  ArraySeq<int> seq;
  seq.insert(10, 0);
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
  seq.quick_sort_random();
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
}

TEST(BasicArraySeqTests, TwoElemInOrderRandQuickSort)
{
  ArraySeq<int> seq;
  seq.insert(10, 0);
  seq.insert(20, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
  seq.quick_sort_random();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}


TEST(BasicArraySeqTests, TwoElemReverseRandQuickSort)
{
  ArraySeq<int> seq;
  seq.insert(20, 0);
  seq.insert(10, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(20, seq[0]);
  ASSERT_EQ(10, seq[1]);
  seq.quick_sort_random();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

// three element tests
TEST(BasicArraySeqTests, ThreeElemRandQuickSortCases)
{
  ArraySeq<int> seq1; // <10,20,30>
  ArraySeq<int> seq2; // <20,30,10>
  ArraySeq<int> seq3; // <30,10,20>
  seq1.insert(10, 0);
  seq1.insert(20, 1);
  seq1.insert(30, 2);
  seq2.insert(20, 0);
  seq2.insert(30, 1);
  seq2.insert(10, 2);
  seq3.insert(30, 0);
  seq3.insert(10, 1);
  seq3.insert(20, 2);
  seq1.quick_sort_random();
  seq2.quick_sort_random();
  seq3.quick_sort_random();
  for (int i = 1; i <= 3; ++i) {
    ASSERT_EQ(i*10, seq1[i-1]);
    ASSERT_EQ(i*10, seq2[i-1]);
    ASSERT_EQ(i*10, seq3[i-1]);
  }
}

//----------------------------------------------------------------------
// LinkedSeq Random-Pivot Quick Sort Tests
//----------------------------------------------------------------------

TEST(BasicLinkedSeqTests, EmptySeqRandQuickSort)
{
  LinkedSeq<int> seq;
  ASSERT_EQ(true, seq.empty());
  seq.quick_sort_random();
  ASSERT_EQ(true, seq.empty());
}

TEST(BasicLinkedSeqTests, OneElemRandQuickSort)
{
  LinkedSeq<int> seq;
  seq.insert(10, 0);
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
  seq.quick_sort_random();
  ASSERT_EQ(1, seq.size());
  ASSERT_EQ(10, seq[0]);
}

TEST(BasicLinkedSeqTests, TwoElemInOrderRandQuickSort)
{
  LinkedSeq<int> seq;
  seq.insert(10, 0);
  seq.insert(20, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
  seq.quick_sort_random();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}


TEST(BasicLinkedSeqTests, TwoElemReverseRandQuickSort)
{
  LinkedSeq<int> seq;
  seq.insert(20, 0);
  seq.insert(10, 1);
  ASSERT_EQ(2, seq.size());
  ASSERT_EQ(20, seq[0]);
  ASSERT_EQ(10, seq[1]);
  seq.quick_sort_random();
  ASSERT_EQ(10, seq[0]);
  ASSERT_EQ(20, seq[1]);
}

// three element tests
TEST(BasicLinkedSeqTests, ThreeElemRandQuickSortCases)
{
  LinkedSeq<int> seq1; // <10,20,30>
  LinkedSeq<int> seq2; // <20,30,10>
  LinkedSeq<int> seq3; // <30,10,20>
  seq1.insert(10, 0);
  seq1.insert(20, 1);
  seq1.insert(30, 2);
  seq2.insert(20, 0);
  seq2.insert(30, 1);
  seq2.insert(10, 2);
  seq3.insert(30, 0);
  seq3.insert(10, 1);
  seq3.insert(20, 2);
  seq1.quick_sort_random();
  seq2.quick_sort_random();
  seq3.quick_sort_random();
  for (int i = 1; i <= 3; ++i) {
    ASSERT_EQ(i*10, seq1[i-1]);
    ASSERT_EQ(i*10, seq2[i-1]);
    ASSERT_EQ(i*10, seq3[i-1]);
  }
}


//----------------------------------------------------------------------
// 4-Element Merge and Quick Sort Tests
//----------------------------------------------------------------------

//four elem tests (quick sort) (linkedseq)
TEST(BasicLinkedSeqTests, FourElemQuickSortCases)
{
  LinkedSeq<int> seq1; // <10,20,30,40>
  LinkedSeq<int> seq2; // <40,30,20,10>
  LinkedSeq<int> seq3; // <20,40,30,10>
  LinkedSeq<int> seq4; // <10,20,20,10> (testing duplicates)
  
  for(int i = 1; i < 5; i++)
  {
    seq1.insert(10*i, i-1);
  }
  for(int a = 1; a < 5; a++)
  {
    seq2.insert(10*a, 0);
  }
  seq3.insert(20, 0);
  seq3.insert(40, 1);
  seq3.insert(30, 2);
  seq3.insert(10, 3);

  seq4.insert(10, 0);
  seq4.insert(20, 1);
  seq4.insert(20, 2);
  seq4.insert(10, 3);

  seq1.quick_sort();
  seq2.quick_sort();
  seq3.quick_sort();
  seq4.quick_sort();
  
  for(int i = 1; i < 5; i++)
  {
    ASSERT_EQ(10*i, seq1[i-1]);
    ASSERT_EQ(10*i, seq2[i-1]);
    ASSERT_EQ(10*i, seq3[i-1]);
  }
  ASSERT_EQ(10, seq4[0]);
  ASSERT_EQ(10, seq4[1]);
  ASSERT_EQ(20, seq4[2]);
  ASSERT_EQ(20, seq4[3]);
}

//four elem tests (quick sort rand) (linkedseq)
TEST(BasicLinkedSeqTests, FourElemRandQuickSortCases)
{
  LinkedSeq<int> seq1; // <10,20,30,40>
  LinkedSeq<int> seq2; // <40,30,20,10>
  LinkedSeq<int> seq3; // <20,40,30,10>
  LinkedSeq<int> seq4; // <10,20,20,10> (testing duplicates)
  
  for(int i = 1; i < 5; i++)
  {
    seq1.insert(10*i, i-1);
  }
  for(int a = 1; a < 5; a++)
  {
    seq2.insert(10*a, 0);
  }
  seq3.insert(20, 0);
  seq3.insert(40, 1);
  seq3.insert(30, 2);
  seq3.insert(10, 3);

  seq4.insert(10, 0);
  seq4.insert(20, 1);
  seq4.insert(20, 2);
  seq4.insert(10, 3);

  seq1.quick_sort_random();
  seq2.quick_sort_random();
  seq3.quick_sort_random();
  seq4.quick_sort_random();
  
  for(int i = 1; i < 5; i++)
  {
    ASSERT_EQ(10*i, seq1[i-1]);
    ASSERT_EQ(10*i, seq2[i-1]);
    ASSERT_EQ(10*i, seq3[i-1]);
  }
  ASSERT_EQ(10, seq4[0]);
  ASSERT_EQ(10, seq4[1]);
  ASSERT_EQ(20, seq4[2]);
  ASSERT_EQ(20, seq4[3]);
}

//four elem tests (merge sort) (linkedseq)
TEST(BasicLinkedSeqTests, FourElemMergeSortCases)
{
  LinkedSeq<int> seq1; // <10,20,30,40>
  LinkedSeq<int> seq2; // <40,30,20,10>
  LinkedSeq<int> seq3; // <20,40,30,10>
  LinkedSeq<int> seq4; // <10,20,20,10> (testing duplicates)
  
  for(int i = 1; i < 5; i++)
  {
    seq1.insert(10*i, i-1);
  }
  for(int a = 1; a < 5; a++)
  {
    seq2.insert(10*a, 0);
  }
  seq3.insert(20, 0);
  seq3.insert(40, 1);
  seq3.insert(30, 2);
  seq3.insert(10, 3);

  seq4.insert(10, 0);
  seq4.insert(20, 1);
  seq4.insert(20, 2);
  seq4.insert(10, 3);

  seq1.merge_sort();
  seq2.merge_sort();
  seq3.merge_sort();
  seq4.merge_sort();
  
  for(int i = 1; i < 5; i++)
  {
    ASSERT_EQ(10*i, seq1[i-1]);
    ASSERT_EQ(10*i, seq2[i-1]);
    ASSERT_EQ(10*i, seq3[i-1]);
  }
  ASSERT_EQ(10, seq4[0]);
  ASSERT_EQ(10, seq4[1]);
  ASSERT_EQ(20, seq4[2]);
  ASSERT_EQ(20, seq4[3]);
}

//four elem tests (quick sort) (arrayseq)
TEST(BasicArraySeqTests, FourElemQuickSortCases)
{
  ArraySeq<int> seq1; // <10,20,30,40>
  ArraySeq<int> seq2; // <40,30,20,10>
  ArraySeq<int> seq3; // <20,40,30,10>
  ArraySeq<int> seq4; // <10,20,20,10> (testing duplicates)
  
  for(int i = 1; i < 5; i++)
  {
    seq1.insert(10*i, i-1);
  }
  for(int a = 1; a < 5; a++)
  {
    seq2.insert(10*a, 0);
  }
  seq3.insert(20, 0);
  seq3.insert(40, 1);
  seq3.insert(30, 2);
  seq3.insert(10, 3);

  seq4.insert(10, 0);
  seq4.insert(20, 1);
  seq4.insert(20, 2);
  seq4.insert(10, 3);

  seq1.quick_sort();
  seq2.quick_sort();
  seq3.quick_sort();
  seq4.quick_sort();
  
  for(int i = 1; i < 5; i++)
  {
    ASSERT_EQ(10*i, seq1[i-1]);
    ASSERT_EQ(10*i, seq2[i-1]);
    ASSERT_EQ(10*i, seq3[i-1]);
  }
  ASSERT_EQ(10, seq4[0]);
  ASSERT_EQ(10, seq4[1]);
  ASSERT_EQ(20, seq4[2]);
  ASSERT_EQ(20, seq4[3]);
}

//four elem tests (quick sort rand) (arrayseq)
TEST(BasicArraySeqTests, FourElemRandQuickSortCases)
{
  ArraySeq<int> seq1; // <10,20,30,40>
  ArraySeq<int> seq2; // <40,30,20,10>
  ArraySeq<int> seq3; // <20,40,30,10>
  ArraySeq<int> seq4; // <10,20,20,10> (testing duplicates)
  
  for(int i = 1; i < 5; i++)
  {
    seq1.insert(10*i, i-1);
  }
  for(int a = 1; a < 5; a++)
  {
    seq2.insert(10*a, 0);
  }
  seq3.insert(20, 0);
  seq3.insert(40, 1);
  seq3.insert(30, 2);
  seq3.insert(10, 3);

  seq4.insert(10, 0);
  seq4.insert(20, 1);
  seq4.insert(20, 2);
  seq4.insert(10, 3);

  seq1.quick_sort_random();
  seq2.quick_sort_random();
  seq3.quick_sort_random();
  seq4.quick_sort_random();
  
  for(int i = 1; i < 5; i++)
  {
    ASSERT_EQ(10*i, seq1[i-1]);
    ASSERT_EQ(10*i, seq2[i-1]);
    ASSERT_EQ(10*i, seq3[i-1]);
  }
  ASSERT_EQ(10, seq4[0]);
  ASSERT_EQ(10, seq4[1]);
  ASSERT_EQ(20, seq4[2]);
  ASSERT_EQ(20, seq4[3]);
}

//four elem tests (merge sort) (arrayseq)
TEST(BasicArraySeqTests, FourElemMergeSortCases)
{
  ArraySeq<int> seq1; // <10,20,30,40>
  ArraySeq<int> seq2; // <40,30,20,10>
  ArraySeq<int> seq3; // <20,40,30,10>
  ArraySeq<int> seq4; // <10,20,20,10> (testing duplicates)
  
  for(int i = 1; i < 5; i++)
  {
    seq1.insert(10*i, i-1);
  }
  for(int a = 1; a < 5; a++)
  {
    seq2.insert(10*a, 0);
  }
  seq3.insert(20, 0);
  seq3.insert(40, 1);
  seq3.insert(30, 2);
  seq3.insert(10, 3);

  seq4.insert(10, 0);
  seq4.insert(20, 1);
  seq4.insert(20, 2);
  seq4.insert(10, 3);

  seq1.merge_sort();
  seq2.merge_sort();
  seq3.merge_sort();
  seq4.merge_sort();
  
  for(int i = 1; i < 5; i++)
  {
    ASSERT_EQ(10*i, seq1[i-1]);
    ASSERT_EQ(10*i, seq2[i-1]);
    ASSERT_EQ(10*i, seq3[i-1]);
  }
  ASSERT_EQ(10, seq4[0]);
  ASSERT_EQ(10, seq4[1]);
  ASSERT_EQ(20, seq4[2]);
  ASSERT_EQ(20, seq4[3]);
}



//----------------------------------------------------------------------
// Main
//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
