#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#include <iostream>


  
template <typename T>
class LinkedList {
private:
class Node {
  friend class LinkedList;
  Node* next;
  Node* prev;
  T data;
public:
  Node(T data): data(data), next(nullptr){
  }
};  

public:
  class iterator {
    friend class LinkedList;
    Node* iterNode;
  public:
    /*! Default constructor  */
    iterator(): iterNode(nullptr)
    {
    }
    
    /*!  Constructor from a node */
    iterator(Node* n) : iterNode(n)
    {
    }

    /*! Dereferences and gets the value of the node */
    T& operator*() const
    {
      return iterNode->data;
    }
    
    /*! Prefix Increment points to the next element in the LinkedList */
    iterator* operator++()
    {
      iterNode = iterNode->next;
      return this;
    }
    
    /* Compares the two nodes of each iterator */
    bool operator !=(const iterator& other) const
    {
      return iterNode!= other.iterNode;
    }
    
    /* Is the one nodes of the iterator equal to other iterator's node */
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
    return iterator{previous};
    }
    
    iterator& operator--()
    {
      Node* current = iterNode;
      iterNode = iterNode->previous;
      return iterator(current);
    }
/*
    iterator operator--(int);
    value_type& operator*() const;
*/
  };
  
  void push_front(const T& value)
  {
    Node* newNode = new Node(value);
    Node* oldHead = headNode;
    headNode = newNode;
    headNode->next = oldHead;
  }
  
  void push_back(const T& value)
  {
    Node* newNode = new Node(value);
    if (!headNode)
    {
      headNode = newNode;
    }
    else
    {
      auto tmp = headNode;
      while (tmp->next)
      {
        tmp = tmp->next;
      }
      tmp->next = newNode;
    }
    size++;
  }
  
  void insert(iterator& it, const T& value)
  {
    
    Node* newNode = new Node(value);
    // Something is wrong here still figuring it out
    if (!headNode)
    {
      std::cout <<" headNode isempty" << std::endl;
      headNode = newNode;
      it = iterator{headNode};
    }
    else
    { 
      auto oldItNext = it.iterNode->next;
      if (oldItNext)
      {
        std::cout <<" oldItNext"<<  oldItNext << std::endl;
      }
      it.iterNode->next = newNode;
      newNode->next = oldItNext;
      newNode->prev = it.iterNode;
    }
    
    size++;
  }
  
  iterator begin()
  {
    return iterator{headNode};
  }
  
  iterator end()
  {
    return iterator{nullptr};
  }

  iterator erase(iterator it)
  {
    // If deleting the first node then if this is the only element
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
  LinkedList() = default;
  // Rule of Five
  // copy constructor
  LinkedList(LinkedList const& other) = delete;
  // Move constructor
  LinkedList(LinkedList &&other) = delete;
  // assignment operator
  LinkedList& operator=(LinkedList& other) = delete;
  
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
  int size = 0;
  Node* headNode = nullptr;
  Node* lastNode = nullptr;
};

#endif //LINKED_LIST_HPP



