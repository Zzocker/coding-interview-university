#include <iostream>
using namespace std;

typedef int Elem;

class Node{
    public:
        Elem elem;
        Node* prev;
        Node* next;
};

class LinkedList{
    public:
        LinkedList();
        ~LinkedList();
        bool empty() const;
        const Elem& front() const;
        const Elem& back() const;
        void add_front(const Elem& e);
        void add_back(const Elem& e);
        void remove_front();
        void remove_back();
        void debug() const;
    private:
        Node* head;
        Node* tail;
    protected:
        // Add element next to v
        void add(Node* v, const Elem& e);
        // remove node
        void remove(Node* w);
};

LinkedList::LinkedList() {
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}
LinkedList::~LinkedList() {
    while (!empty()){
        remove_front();
    }
    delete head;
    delete tail;
}

bool LinkedList::empty() const {
    return head->next == tail;
}

const Elem& LinkedList::front() const {
    if (empty()) return NULL;
    return head->next->elem;
}

const Elem& LinkedList::back() const {
    if (empty()) return NULL;
    return tail->prev->elem;
}

void LinkedList::add_front(const Elem& elem){
    add(head, elem);
}

void LinkedList::add_back(const Elem& elem){
    add(tail->prev, elem);
}

void LinkedList::remove_front(){
    remove(head->next);
}

void LinkedList::remove_back(){
    remove(tail->prev);
}

void LinkedList::debug() const {
    for (Node* ptr = head->next;ptr != tail;ptr = ptr->next){
        cout << ptr->elem <<" ";
    }
    cout << endl;
}

void LinkedList::add(Node* v, const Elem& e){
    Node* node = new Node;
    node->elem = e;
    node->next = v->next;
    node->prev = v;
    v->next->prev = node;
    v->next = node;
}

void LinkedList::remove(Node* w){
    w->prev->next = w->next;
    w->next->prev = w->prev;
    delete w;
}


int main(){
    cout << "Doubly linked list" << endl;
    LinkedList list;
    list.add_front(1);
    list.add_back(2);
    list.add_back(3);
    list.add_front(0);
    list.remove_back();
    list.remove_back();
    list.remove_back();
    list.remove_back();
    list.add_back(5);
    list.add_front(4);
    list.add_front(3);
    list.debug();
}