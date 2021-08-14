#include "linkedlist.hpp"
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
/*  LinkedList<int> myList;
  LinkedList<int>::iterator it;
  for (int i=1; i<=5; ++i) myList.push_back(i);
  
  it = myList.begin();
  std::cout << *it << std::endl;

  for (auto i = myList.begin(); i!=myList.end();++i)
  {
    std::cout << *i << std::endl;
  }
  ++it;
  myList.insert(it, 10);
  std::cout << *it << std::endl;
  for (auto i = myList.begin(); i!=myList.end();i++)
  {
    std::cout << *i << std::endl;
    }*/
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  
}
