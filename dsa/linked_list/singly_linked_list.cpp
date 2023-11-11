#include <iostream>
#include <cstddef> // to define NULL

using namespace std;

template <typename T> class Node {
    public:
        T elem;
        Node<T>* next;
};

template <typename T> class LinkedList{
    public:
        LinkedList();
        ~LinkedList();
        bool empty() const;
        const T& front() const;
        void add_front(const T& e);
        void remove_front();
        void debug() const;
        void reverse();
    private:
        Node<T>* head;
};

template <typename T> LinkedList<T>::LinkedList() : head{NULL} {}
template <typename T> LinkedList<T>::~LinkedList() {
    while (!empty()){
        remove_front();
    }
}
template <typename T> bool LinkedList<T>::empty() const {return head == NULL;}
template <typename T> const T& LinkedList<T>::front() const {
    if (empty())return NULL;
    return head->elem;
}
template <typename T> void LinkedList<T>::add_front(const T& e) {
    Node<T>* node = new Node<T>;
    node->elem = e;
    node->next = head;
    head = node;
}
template <typename T> void LinkedList<T>::remove_front(){
    Node<T>* node = head;
    head = head->next;
    delete node;
}
template <typename T> void LinkedList<T>::debug() const{
    Node<T>* ptr = head;
    while (ptr != NULL){
        cout << ptr->elem << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

template <typename T> void LinkedList<T>::reverse() {
    Node<T>* ptr = head;
    head = NULL;
    while (ptr != NULL){
        Node<T>* next = ptr->next;
        ptr->next = NULL;
        ptr->next = head;
        head = ptr;
        ptr = next;
    }
}

int main(){
    cout << "Singly Linked list" << endl;
    LinkedList<int> list;
    list.add_front(1);
    list.add_front(2);
    list.add_front(3);list.add_front(4);list.add_front(5);
    // list.remove_front();
    list.reverse();
    list.debug();
}