#include "linkedlist.hpp"
#include <gtest/gtest.h>

TEST(LinkedListTest, PushBackTest) 
{
  LinkedList<int> myList;
  LinkedList<int>::iterator it;
  for (int i=1; i<=5; ++i) myList.push_back(i);
  
  it = myList.begin();
  ASSERT_EQ(*it, 1);
  
  auto counter = 1;
  for (auto itr = myList.begin(); itr!=myList.end();++itr)
  {
    ASSERT_EQ(*itr, counter++);
  }
}

TEST(LinkedListTest, EraseTest) 
{
  LinkedList<int> myList;
  LinkedList<int>::iterator it;
  myList.push_back(1);
  it = myList.begin();
  // Deleting when is the only node and on the first place
  myList.erase(it);
  ASSERT_EQ(myList.size(), 0);
  
  for (int i=2; i<=5; ++i)
  {
    myList.push_back(i);
  }
  
  it = myList.begin();
  auto counter = 2;
  for (auto itr = myList.begin(); itr!=myList.end();++itr)
  {
    ASSERT_EQ(*itr, counter++);
  }
  
  // Deleting when is not the only node but is on the first place
  it = myList.begin();
  myList.erase(it);
  counter = 3;
  for (auto itr = myList.begin(); itr!=myList.end();++itr)
  {
    ASSERT_EQ(*itr, counter);
    counter++;
  }

  // Deleting an element from the middle and ensure everything is connected correctly
  it = myList.begin();
  it++;
  myList.erase(it);
  counter = 3;
  for (auto itr = myList.begin(); itr!=myList.end();++itr)
  {
    if (counter == 4) counter++;
    ASSERT_EQ(*itr, counter++);
  }
}

TEST(LinkedListTest, RangeBasedLoop)
{
  LinkedList<int> myList;
  
  myList.push_back(2);
  myList.push_back(3);
  myList.push_back(4);
  myList.push_back(5);
  
  int counter = 2;
  for (auto i : myList)
  {
    ASSERT_EQ(i, counter++);
  }
}

TEST(LinkedListTest, PushFront)
{
  LinkedList<int> myList;
  LinkedList<int>::iterator it;
  
  int i = 0;
  for (; i<=10; i+=2)
  {
    myList.push_front(i);
  }
  
  for (auto itr : myList)
  {  
    i-=2;
    ASSERT_EQ(itr, i);
  }
}

TEST(LinkedListTest, PopFront)
{
  LinkedList<int> myList;
  LinkedList<int>::iterator it;
  
  myList.push_front(0);
  myList.pop_front();

  for (auto i=0; i<5; i++)
  {
    myList.push_front(i);
    myList.pop_front();
    EXPECT_TRUE(myList.empty());
  }

  for (auto& itr : myList)
  {
    (void)itr;
    ASSERT_TRUE(0); 
  }  
}

TEST(LinkedListTest, InitializerList)
{
  LinkedList<int> myList{1, 2, 3, 4, 5};
  int counter = 1;
  for (auto& itr : myList)
  {
    ASSERT_EQ(itr, counter++);
  } 
}

TEST(LinkedListTest, Iterators)
{
  auto is_even = [](int i){ return i%2 == 0; };

  LinkedList<int> myList{1, 2, 3, 4, 5};
  auto result1 = std::find(myList.begin(), myList.end(), 3);
  auto result2 = std::find(myList.begin(), myList.end(), 1);
  auto result3 = std::find_if(myList.begin(), myList.end(), is_even);
  auto result4 = std::find(myList.begin(), myList.end(), 7);
  
  ASSERT_TRUE(result1 != myList.end());
  ASSERT_TRUE(result2 != myList.end());
  ASSERT_TRUE(result3 != myList.end());
  ASSERT_TRUE(result4 == myList.end());  
}
               
TEST(LinkedListTest, CopyConstructor)
{
  LinkedList<std::string> words1 {"the", "frogurt", "is", "also", "cursed"};
  LinkedList<std::string> words2 = words1;
  
  auto it1 = words1.begin();
  auto it2 =words2.begin();
  
  // Assert one element is not different than the other
  while( it1 != words1.end() && it2 != words2.end() )
  {
    if( *it1 != *it2 )
    {
      ASSERT_TRUE(0);
    }
    else
    {
      it1++;
      it2++;
    }
  }
  
  // Assert one list is not bigger than the other
  while( it1 != words1.end() ) ASSERT_TRUE(0); 
  while( it2 != words2.end() ) ASSERT_TRUE(0); 
  
}

TEST(LinkedListTest, MoveConstructor)
{
  // Making sure it doesn't free up memory twice.
  LinkedList<int> l1 {1,2,3,4,5,6};
  LinkedList<int> l2(std::move(l1));
  
  l2.push_back(7);
  
  int counter = 0;
  for (auto& itr : l2)
  {
    ASSERT_EQ(itr, ++counter);  
  }
  
  ASSERT_EQ(counter, 7);  
}
