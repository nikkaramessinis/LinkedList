#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#include <iostream>

template <typename T>
class LinkedList {
private:
  struct Node {
    Node* next;
    T data;
    Node(T data): data(data), next(nullptr){
    }
  };

public:
  struct iterator {
    // this should probably be const or sth 
    Node* iterNode;
    // Default constructor 
    iterator(): iterNode(nullptr)
    {
    }
    
    // Constructor from a node
    iterator(Node* n) : iterNode(n)
    {
    }

    // Dereferences and gets the value of the node
    const T& operator*() const
    {
      return iterNode->data;
    }
    
    // Prefix Increment points to the next element in the LinkedList
    iterator* operator++()
    {
      iterNode = iterNode->next;
      return this;
    }
    
    // Compares the two nodes of each iterator
    bool operator !=(const iterator& other) const
    {
      return iterNode!= other.iterNode;
    }
    
    // Is the one nodes of the iterator equal to other iterator's node
    bool operator ==(const iterator& other) const
    {
      return iterNode== other.iterNode;
    }
    
    // postFix increment returns an iterator to the previous node
    // but points to the next element in the LinkedList
    iterator operator++(int)
    { 
    Node* previous = iterNode;
    iterNode = iterNode->next; 
    return iterator(previous);
    }
/*
    iterator& operator--();
    iterator operator--(int);
    value_type& operator*() const;
*/
  };
  
  void push_back(const T& value)
  {
    Node* newNode = new Node(value);
    if (!headNode)
    {
      std::cout << "!headNode" << std::endl;
      headNode = newNode;
    }
    else
    {
      auto tmp = headNode;
      Node* prevTmp = nullptr;
      std::cout << "tmp" << std::endl;
      while (tmp)
      {
        prevTmp = tmp;
        tmp = tmp->next;
      }
      prevTmp->next = newNode;
    }
    size++;
  }
  
  void insert(iterator it, const T& value)
  {
    Node* newNode = new Node(value);
    auto tmp = it.iterNode->next;
    it.iterNode->next = newNode;
    newNode->next = tmp;
  }
  
  iterator begin()
  {
    return iterator(headNode);
  }
  
  iterator end()
  {
    return iterator(nullptr);
  }

  iterator erase(iterator it)
  {
    // if deleting the first node then if this is the only element
    // mark headNode as nullptr and delete the element else make
    // the headNode point to the next element and delete the previous one.
    if (headNode == it.iterNode)
    {
      std::cout << "headNode == it.iterNode" << std::endl;
      auto nodeToDelete = it;
      if (size == 1)
      {
        std::cout << "size == 1 " << std::endl;
        headNode = nullptr;
      }
      else
      {
        std::cout << "size != 1 " << std::endl;
        headNode = (++it)->iterNode;
      }
      std::cout << "deleting" << nodeToDelete.iterNode->data << std::endl;
      delete nodeToDelete.iterNode;
    }
    else
    {
    
      auto prev = begin();
      for (auto itr = begin(); itr!=end();itr++)
      {
        if (itr == it)
        {
          prev.iterNode->next = (++itr)->iterNode;
          delete it.iterNode;
          break;
        }
        prev = itr;
      }
    }
  }
public:
  LinkedList() : size(0), headNode(nullptr){
  }
  
  ~LinkedList()
  {
    Node* current = headNode;
    while (current)
    {
      Node* next = current->next;
      delete current;
      current = next;
    }
  }

private:
  int size;
  Node* headNode;
};

#endif //LINKED_LIST_HPP



