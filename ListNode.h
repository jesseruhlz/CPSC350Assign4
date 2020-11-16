#include <iostream>
using namespace std;

template <class T>
class ListNode{
  public:
    ListNode();
    ListNode(T d);
    ~ListNode();
    T data;
    ListNode<T> *next;
    //add this extra pointer to create a doubly linked list
    ListNode<T> *prev;
};

//under a different file .cpp
template <class T>
ListNode<T>::ListNode(){}

//overload constructor
template <class T>
ListNode<T>::ListNode(T d){
  data = d;
  next = NULL;
  prev = NULL;
}

//destructor
template <class T>
ListNode<T>::~ListNode(){
  if(next != NULL){
    next = NULL;
    prev = NULL;

    delete next;
    delete prev;
  }
  //figure out how to build some character and research this
}
