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
    ASSERT_EQ(*itr, counter);
    counter++;
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
  for (int i=2; i<=5; ++i) myList.push_back(i);
  
  it = myList.begin();
  auto counter = 2;
  // Ensure values are as expected
  for (auto itr = myList.begin(); itr!=myList.end();++itr)
  {
    ASSERT_EQ(*itr, counter);
    counter++;
  }
  
  // Deleting when is not the only node but is on the first place
  it = myList.begin();
  std::cout << "Failing case" << std::endl;
  myList.erase(it);
  counter = 3;
  // Ensure values are as expected
  for (auto itr = myList.begin(); itr!=myList.end();++itr)
  {
    ASSERT_EQ(*itr, counter);
    counter++;
  }

  it = myList.begin();
  it++;
  // Deleting an element from the middle and ensure everything is connected correctly
  myList.erase(it);
  counter = 3;
  for (auto itr = myList.begin(); itr!=myList.end();++itr)
  {
    if (counter == 4) counter++;
    ASSERT_EQ(*itr, counter);
    counter++;
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
    ASSERT_EQ(i, counter);
    counter++;
  }
}

TEST(LinkedListTest, InsertTestPlain)
{
  LinkedList<int> myList;
  LinkedList<int>::iterator it;
  it = myList.begin();
  myList.insert(it, 2);
  std::cout << "Insert second" << std::endl;
  myList.insert(it, 3);
  myList.insert(it, 4);
  myList.insert(it, 5);
  
  int counter = 2;
  
  for (auto i : myList)
  {
    ASSERT_EQ(i, counter);
    counter++;
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
    std::cout << "i "<<itr << "counter " <<  i << std::endl;
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
    std::cout << "lala" << std::endl;
  
//  myList.pop_front();
  
}
