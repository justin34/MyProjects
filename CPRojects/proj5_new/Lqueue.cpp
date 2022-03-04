#ifndef LQUEUE_CPP
#define LQUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated Node class used in templated linked list
template <class T>
class Node {
   public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue<T>& operator= (Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  void Push(const T&);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front 
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  bool IsEmpty();
  // Name: size
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  int size();
  // Name: Find()
  // Preconditions: Requires a lqueue
  // Postconditions: Iterates through lqueue and if it finds the thing, returns index, else -1
  int Find(T&);
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  void Clear();
  //Name: Overloaded [] operator
  //Precondition: Existing Lqueue
  //Postcondition: Returns object from Lqueue using []
  //Desc: Iterates to node x and returns data from Lqueue
  T& operator[] (int x);//Overloaded [] operator to pull data from Lqueue
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};
//***********IMPLEMENT LQUEUE HERE***********************
template<class T>
Lqueue<T>::Lqueue() { // basic constructor (initialises everything)
    m_head = nullptr;
    m_size = 0;
    m_tail = nullptr;
}

template<class T>
Lqueue<T>::Lqueue(const Lqueue<T>& source) { // copy constructor
    if (source.m_size == 0) {
        m_head = nullptr;
        m_size = 0;
        m_tail = nullptr;
        return;
    } // if the size of the copied list is zero just do a basic constuctor

    // sets up the head node, size and the multiple current vars
    m_size = source.m_size;
    m_head = new Node<T>(source.m_head->GetData());
    Node<T>* current1 = m_head;
    Node<T>* current2 = source.m_head->GetNext();


    while(current2 != nullptr){ // loops until we reach the end of the source list
        current1->SetNext(new Node<T>(current2->GetData())); // sets the current source variable to the next local var
        current1 = current1->GetNext();
        current2 = current2->GetNext();
    }
    // sets tail to the last node if there is more than one node
    if(m_size > 1)
        m_tail = current1;
    else
        m_tail = nullptr;
}

template<class T>
Lqueue<T>::~Lqueue<T>() {  // deconstuctor
    Node<T>* current = m_head;
    Node<T>* next;

    while (current != nullptr) { // deletes each node
        next = current->GetNext();
        delete current;
        current = next;
    }

    m_head = nullptr;
    m_tail = nullptr;
}

template<class T>
Lqueue<T> &Lqueue<T>::operator=(Lqueue<T> & source) { // overloaded assignment operator
    Clear(); // clears the list to make sure there are no free pointers

    // loops through adding each new source node to the end;
    Node<T>* current = source.m_head;

    while (current != nullptr){
        Push(current->GetData());
        current = current->GetNext();
    }

    // returns the new "this"
    return *this;


}

template <class T>
void Lqueue<T>::Push(const T & obj) {
    if (m_head == nullptr){ // if the list is empty add the node as head
        m_head = new Node<T>(obj);
        m_size++;
        return;
    }

    Node<T>* temp = m_head;
    while (temp->GetNext() != nullptr){ // get to the end of the list
        temp = temp->GetNext();
    }
    temp->SetNext(new Node<T>(obj)); // add it to the end
    m_size++;

    m_tail = temp->GetNext();
}

template <class T>
T Lqueue<T>::Pop() {
    T none;
    if(m_head == nullptr) // if there is nothing in the list return an empty obj
        return none;

    Node<T>* first = m_head; // store old head
    m_head = m_head->GetNext(); // set the new head to be the next one after the old head
    delete first;// delete the old first head
    m_size--; // decement size
    if (m_head != nullptr)
        return m_head->GetData(); // return the new head's data
    m_tail = nullptr;
    return nullptr;
}

template<class T>
bool Lqueue<T>::IsEmpty() { // check is size is zero
    if (m_size == 0)
        return true;
    return false;
}

template<class T>
T Lqueue<T>::Front() { // returns head
    return m_head->GetData();
}

template<class T>
void Lqueue<T>::Swap(int index) {
    if (index >= m_size) // if the index its asking for is out of bounds then abort
        return;
    Node<T>* previousNode1 = nullptr; // store previous node
    Node<T>* current = m_head;

    int i = 0;
    while (i <= index-1){ // finds the right index
        previousNode1 = current;
        current = current->GetNext();
        i++;
    }

    // swap node node 1 with node2
    Node<T>* node1 = current;
    Node<T>* node2 = current->next;
    Node<T>* node2Next = node2->GetNext();
    node2->SetNext(node1);
    node1->SetNext(node2Next);

    // if there is a previous node point it to node2 otherwise set node2 to be the head
    if (previousNode1 != nullptr){
        previousNode1->SetNext(node2);
    }else{
        m_head = node2;
    }

    // if the node after node1 is now null set it to tail
    if(node1->GetNext() == nullptr){
        m_tail = node1;
    }



}

template<class T>
int Lqueue<T>::Find(T & obj) {
    Node<T>* current = m_head;
    int i = 0;
    while (current != nullptr){ // loops threw the linked list until it finds data matching obj
        if(current->GetData() == obj){
            return i; // returns index
        }
        current = current->GetNext();
        i++;
    }
    return -1;
}

template<class T>
void Lqueue<T>::Clear() { // frees the entire liked list
    Node<T>* current = m_head;
    Node<T>* next;

    while (current != nullptr) {
        next = current->GetNext();
        delete current;
        current = next;
    }
    // sets everything to default
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

template<class T>
void Lqueue<T>::Display() {
    Node<T>* current = m_head;

    int counter = 1;
    while (current != nullptr){ // displays each node with a number in front
        cout << counter << ". ";
        cout << *current->GetData() << endl;

        counter++;
        current = current->GetNext();
    }
}

template<class T>
int Lqueue<T>::size() { // returns size
    return m_size;
}

template<class T>
T &Lqueue<T>::operator[](int x) {
    Node<T>* current = m_head;
    int i = 0;
    while (current != nullptr){ // loops threw list untill it finds a matching index
        if(i == x){
            return current->GetData(); // returns data
        }
        current = current->GetNext();
        i++;
    }
    T none;
    return none;
}
#endif
