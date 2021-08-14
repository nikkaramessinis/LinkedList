#include <iostream>

template <typename T>
class LinkedList {
private:
  struct Node {
    Node* next;
    T data;
    Node(T data): data(data){
    }
  };

public:
  struct iterator {
    // this should probably be const or sth 
    Node* iterNode;
    iterator(){};
    iterator(Node* n): iterNode(n){}
    const T& operator*() const
    {
      return iterNode->data;
    }
    
    iterator* operator++()
    {
      iterNode = iterNode->next;
      return this;
    }
    
    bool operator !=(const iterator& other) const
    {
      return iterNode!= other.iterNode;
    }
    
    bool operator ==(const iterator& other) const
    {
      return iterNode!= other.iterNode;
    }
    
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
      headNode = newNode;
      endNode = newNode->next;
    }
    else
    {
      auto tmp = headNode;
      Node* prevTmp = nullptr;
      while (tmp)
      {
        prevTmp = tmp;
        tmp = tmp->next;
      }
      prevTmp->next = newNode;
    }
  }
  
  void insert(iterator it, const T& value)
  {
    Node* newNode = new Node(value);
    auto tmp = it.iterNode->next;
    it.iterNode->next = newNode;
    newNode->next = tmp;
  }

  iterator erase(iterator position)
  {
    
  }
  
  iterator begin()
  {
    return iterator(headNode);
  }
  
  iterator end()
  {
    return iterator(nullptr);
  }
public:
  LinkedList() : size(0), headNode(nullptr), endNode(nullptr){
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
  Node* endNode;
};




