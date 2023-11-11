#include <iostream>
using namespace std;

class EmptyLinkedListException{
    public:
        EmptyLinkedListException(){}
};

typedef int Elem;
class Node{
    public:
        Elem elem;
        Node* next;
};

class CircularlyLinkedList{
    public:
        CircularlyLinkedList();
        ~CircularlyLinkedList();
        bool empty() const;
        const Elem& front() const;
        const Elem& back() const;
        void advance();
        void add(const Elem& elem);
        void remove();
    private:
        Node* cursor;
};

CircularlyLinkedList::CircularlyLinkedList(): cursor{NULL} {}
CircularlyLinkedList::~CircularlyLinkedList() {
    while (!empty()){
        remove();
    }
}
bool CircularlyLinkedList::empty() const {
    return cursor == NULL;
}

const Elem& CircularlyLinkedList::front() const {
    if (empty()) throw(EmptyLinkedListException());
    return cursor->elem;
}

const Elem& CircularlyLinkedList::back() const {
    if (empty()) throw(EmptyLinkedListException());
    return cursor->next->elem;
}

void CircularlyLinkedList::advance() {
    if (empty()) return;
    cursor = cursor->next;
}

void CircularlyLinkedList::add(const Elem& elem){
    Node* node = new Node;
    node->elem = elem;
    if (cursor == NULL){
        node->next = node;
        cursor = node;
    }else {
        node->next = cursor->next;
        cursor->next = node;
    }
}

void CircularlyLinkedList::remove(){
    if (cursor == NULL) return;
    else if (cursor->next == cursor){
        delete cursor;
        cursor = NULL;
    }else {
        Node* node = cursor->next;
        cursor->next = cursor->next->next;
        delete node;
    }
}


int main(){
    CircularlyLinkedList list;
    list.add(1);list.add(2);
    list.advance();
    list.advance();
    list.remove();
    list.remove();
    cout << list.empty() << endl;
    list.add(5);
    cout << list.front() << endl;
}