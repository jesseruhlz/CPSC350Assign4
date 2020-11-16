#include "ListNode.h"

template <class T>
class Queue{
  public:
    ListNode<T> *front;
    ListNode<T> *back;
    unsigned int size;
    Queue();
    ~Queue();

    void enqueue(T d);
    T dequeue();

    T getFront();
    T getBack();
    void printQueue();
    unsigned int getSize();

    bool isEmpty()
    {
      return (size == 0);
    }
};

template <class T>
Queue<T>::Queue(){
  size = 0;
  front = NULL;
  back = NULL;
}

template <class T>
Queue<T>::~Queue(){

}

template <class T>
void Queue<T>::enqueue(T d){
  ListNode<T> * node = new ListNode<T>(d);
  if (size == 0){
    front = node;
  }
  else{
  back->next = node;
  node->prev = back;
  }
  back = node;
  ++size;
}

template <class T>
T Queue<T>::dequeue(){
  ListNode<T> *node = front;
  T old = node->data;
  if(front->next == NULL){
    front = NULL;
    back = NULL;
  }
  else{
    front->next->prev = NULL;
    front = front->next;
  }
  delete node;
  size--;
  return old;
}

template <class T>
T Queue<T>::getFront(){
  return front->data;
}

template <class T>
T Queue<T>::getBack(){
  return back->data;
}

template <class T>
void Queue<T>::printQueue(){
  ListNode<T> *current = front;
  while (true){
    if (current == NULL){
      break;
    }
    cout << current->data << endl;
    current = current->next;
  }
}

template <class T>
unsigned int Queue<T>::getSize(){
  return size;
}
