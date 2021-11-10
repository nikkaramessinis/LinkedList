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
  Node(const Node&) = delete;
  Node& operator=(const Node&) = delete;
};  

public:
  
  class const_iterator {
    // standard algorithms(including std::find) require that the used iterator
    // meets the requirements of the Iterator concept.
    using value_type = Node;
    using reference = Node&;
    using pointer = Node*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    
    Node* _ptr;
    friend class LinkedList;
    
  public:
    /*! Default constructor  */
    const_iterator(): _ptr(nullptr)
    {
    }
    
    /*!  Constructor from a node */
    const_iterator(Node* n) : _ptr(n)
    {
    }
    
    T& operator*() const {
        return _ptr->data;
    }
    
    const_iterator& operator++()
    {
      _ptr = _ptr->next;
      return *this;
    }
    
    const_iterator operator++(int)
    {
    const_iterator previous = *this;
    _ptr = _ptr->next; 
    return previous;
    }

    bool operator==(const const_iterator& other) const
    {
      return _ptr = other._ptr;
    }
    
    bool operator!=(const const_iterator& other) const
    {
      return !(_ptr == other._ptr);
    }    
  };
  class iterator : public const_iterator {
  public:
    // standard algorithms(including std::find) require that the used iterator
    // meets the requirements of the Iterator concept.
     using value_type = Node;
    using reference = Node&;
    using pointer = Node*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
   
    friend class LinkedList;
    Node* _ptr;
    
  public:
    /*! Default constructor  */
    iterator(): _ptr(nullptr)
    {
    }
    
    /*!  Constructor from a node */
    iterator(Node* n) : _ptr(n)
    {
    }

    /*! Dereferences and gets the value of the node */
    T& operator*() const
    {
      return _ptr->data;
    }
    
    /*! Prefix Increment points to the next element in the LinkedList */
    LinkedList<T>::iterator& operator++()
    {
      _ptr = _ptr->next;
      return *this;
    }
    
    /* Compares the two nodes of each iterator */
    bool operator !=(const iterator& other) const
    {
      return _ptr!= other._ptr;
    }
    
    /* Is the one nodes of the iterator equal to other iterator's node */
    bool operator ==(const iterator& other) const
    {
      return _ptr == other._ptr;
    }
    
    /* PostFix increment returns an iterator to the previous node
     * but points to the next element in the LinkedList
     */
    iterator operator++(int)
    {
    iterator previous = *this;
    _ptr = _ptr->next; 
    return previous;
    }
    
    iterator& operator--()
    {
      _ptr = _ptr->previous;
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

  const_iterator begin() const
  {
    return const_iterator{headNode};
  }
  
  iterator begin()
  {
    return iterator{headNode};
  }  
  
  const_iterator cbegin() const
  {
    return const_iterator{headNode};
  }
  
  const_iterator end() const
  {
    return const_iterator{nullptr};
  }
  
  iterator end()
  {
    return iterator{nullptr};
  }
  
  const_iterator cend() const
  {
    return const_iterator{nullptr};
  }
  
  iterator erase(iterator it)
  {
    // If deleting the first node and this is the only element
    // mark headNode as nullptr and delete the element else make
    // the headNode point to the next element and delete.
    if (headNode == it._ptr)
    {
      auto nodeToDelete = it;
      if (m_size == 1)
      {
        headNode = nullptr;
      }
      else
      {
        headNode = (++it)._ptr;
      }
      delete nodeToDelete._ptr;
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
          prev._ptr->next = (++itr)._ptr;
          delete it._ptr;
          break;
        }
        prev = itr;
      }
      m_size--;
      return prev._ptr->next;
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
