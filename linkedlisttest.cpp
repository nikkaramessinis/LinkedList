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
