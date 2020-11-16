#include <iostream>
using namespace std;
#include "ListNode.h"

//seperate file, .h file for my single linked list
template <class T>
class DoublyList{
  private:
    ListNode<T> *front;
    ListNode<T> *back;
    //pointing to front and back

    unsigned int size;
  public:
    DoublyList();
    ~DoublyList();
    void insertFront(T d);
    void insertBack(T d);
    T removeFront();
    T find(T value);
    T deletePos(T pos);

    /* new function for double linked list*/
    T removeNode(T key); // key represents value going to search for and delete

    //helper functions
    void printList();
    bool isEmpty();
    unsigned int getSize();
};

//seperate file .cpp, implementation
template <class T>
DoublyList<T>::DoublyList(){
  front = NULL;
  back = NULL;
  size = 0;
}

template <class T>
DoublyList<T>::~DoublyList(){
  //build some character, research
}

template <class T>
void DoublyList<T>::insertFront(T d){
  ListNode<T> *node = new ListNode<T>(d);
  // we need to update the back pointer as well
  if(size == 0){
    back = node;
  }
  else{
    front->prev = node;
    node->next = front;
  }
  front = node;
  ++size;
}

template <class T>
void DoublyList<T>::insertBack(T d){
  ListNode<T>* node = new ListNode<T>(d);
  if(front == NULL)
    front = node;
  else{
    back->next = node;
    node->prev = back;
  }
  back = node;
  ++size;
}

//you have removeFront
template <class T>
T DoublyList<T>::removeFront()
{
  ListNode<T> *node = front;
  if (front == NULL)
  {
    back = NULL;
  }
  else{
    front->next->prev = NULL;
  }
  front = front->next;
  --size;
  node->next = 0;
  int temp = node->data;
  delete node;
  return temp;
}

//we need to implement removeBack()
template <class T>
void DoublyList<T>::printList(){
  ListNode<T> *curr = front;
  while(curr != NULL){
    cout << curr->data << endl;
    curr = curr->next;
  }
}

template <class T>
T DoublyList<T>::find(T value){
  int pos = -1;
  ListNode<T> *curr = front;
  while(curr != NULL){
    ++pos;
    if(curr->data == value)
      break;
    curr = curr->next;
  }
  //did not find our value
  if(curr = NULL)
    pos = -1;
  return pos;

}

template <class T>
T DoublyList<T>::deletePos(T pos){
  int p = 0;
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;

  //iterate to the correct position
  while(p != pos){
    //iterate and update my pointers
    prev = curr;
    curr = curr->next;
    p++;
  }
  //weve found out target, all pointers should in the correct locations
  prev->next = curr->next;
  curr->next = NULL;
  int temp = curr->data;
  size--;

  delete curr;
  return temp;
}

template <class T>
T DoublyList<T>::removeNode(T key)
{
  ListNode<T> *curr = front;

  //now i need to loop through list to find the key/value
  while(curr->data != key)
  {
    curr = curr->next;

    if(curr == NULL)
      return -1;
  }

  //now if we get here, we found it, let's proceed to delete
  //let's start with front
  if(curr == front)
  {
    front = curr->next;
    front->prev = NULL;
  }
  else if (curr == back)
  {
    back = curr->prev;
    back->next = NULL;
  }
  else
  {
    //if we get here, then we are dealing with a node
    //somewhere between front and back
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
  }
  curr->next = NULL;
  curr->prev = NULL;

  int temp = curr->data;
  delete curr;
  size--;
  return temp;
}
