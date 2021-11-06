#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#include <iostream>
#include <assert.h>
#include <initializer_list>

  
template <typename T>
class LinkedList {
private:
  
class Node {
  friend class LinkedList;
  T data;
  Node* next;
  Node* prev;
public:
  Node(T data): data(data), next(nullptr){
  }
};  

public:
  
  class iterator {
  public:
    // standard algorithms(including std::find) require that the used iterator
    // meets the requirements of the Iterator concept.
    using value_type = Node;
    using reference = Node&;
    using pointer = Node*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
   
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
    LinkedList<T>::iterator& operator++()
    {
      iterNode = iterNode->next;
      return *this;
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
    
    /* PostFix increment returns an iterator to the previous node
     * but points to the next element in the LinkedList
     */
    iterator operator++(int)
    {
    iterator previous = *this;
    iterNode = iterNode->next; 
    return previous;
    }
    
    iterator& operator--()
    {
      iterNode = iterNode->previous;
      return *this;
    }
  };
  
  void push_front(const T& value)
  {
    Node* newNode = new Node(value);
    Node* oldHead = headNode;
    headNode = newNode;
    headNode->next = oldHead;
    m_size++;
  }
  
  void pop_front()
  {
    assert (m_size && "No elements in the list to pop");
    auto popped = headNode;
    headNode = headNode->next;
    delete popped;
    m_size--;
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
    m_size++;
  }
  
  size_t size() const
  {
    return m_size;
  }
  
  bool empty() const
  {
    return !m_size;
  }

  iterator begin() const
  {
    return iterator{headNode};
  }
  
  iterator end() const
  {
    return iterator{nullptr};
  }
  
  iterator erase(iterator it)
  {
    // If deleting the first node and this is the only element
    // mark headNode as nullptr and delete the element else make
    // the headNode point to the next element and delete.
    if (headNode == it.iterNode)
    {
      auto nodeToDelete = it;
      if (m_size == 1)
      {
        headNode = nullptr;
      }
      else
      {
        headNode = (++it).iterNode;
      }
      delete nodeToDelete.iterNode;
      m_size--;
      return headNode;
    }
    else
    {
      auto prev = begin();
      for (auto itr = begin(); itr!=end(); itr++)
      {
        if (itr == it)
        {
          prev.iterNode->next = (++itr).iterNode;
          delete it.iterNode;
          break;
        }
        prev = itr;
      }
      m_size--;
      return prev.iterNode->next;
    }
  }
public:
  LinkedList() = default;
  LinkedList(std::initializer_list<T> iList)
  {
    if (iList.size())
    {
      for (auto it = iList.begin(); it!=iList.end();it++)
      {
        push_back(*it);
      }
    }
  }
  // Rule of Five
  // copy constructor
  LinkedList(LinkedList const& other)
  {
    for (auto it = other.begin(); it!=other.end();it++)
    {
      push_back(*it);
    }
  }
  
  // Move constructor
  LinkedList(LinkedList &&other)
  {
    headNode = other.headNode;
    other.headNode = nullptr;
  }
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
  size_t m_size = 0;
  Node* headNode = nullptr;
};

#endif //LINKED_LIST_HPP



