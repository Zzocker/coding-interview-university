#include <cstddef>
#include "linked_list.h"
#include "node.h"

LinkedList::LinkedList() : size{0}, head{NULL} {
    head = new Node;
}

LinkedList::~LinkedList(){
    while (!is_empty()) pop_front();
    delete head;
}

int LinkedList::get_size() const {
    return size;
}

bool LinkedList::is_empty() const {
    return head->next == NULL;
}

int LinkedList::value_at(int index) const {
    if (index < 0 || index >= size) throw(LinkedListException("index out of bound"));
    Node* ptr = head->next;
    while (index > 0){
        ptr = ptr->next;
        index--;
    }
    return ptr->elem;
}

void LinkedList::push_front(int item){
    Node* node = new Node;
    node->elem = item;
    node->next = head->next;
    head->next = node;
    size++;
}

int LinkedList::pop_front() {
    if (is_empty()) throw(LinkedListException("empty linked list"));
    Node* node = head->next;
    int elem = node->elem;
    head->next = head->next->next;
    delete node;
    size--;
    return elem;
}

void LinkedList::push_back(int item) {
    Node* before = head;
    while (before->next != NULL) before = before->next;
    Node* node = new Node;
    node->elem = item;
    node->next = NULL;
    before->next = node;
    size++;
}

int LinkedList::pop_back() {
    if (is_empty()) throw(LinkedListException("empty linked list"));
    Node* before = head;
    while (before->next->next != NULL) before = before->next;
    Node* node = before->next;
    before->next = NULL;
    int item = node->elem;
    delete node;
    size--;
    return item;
}

int LinkedList::front() const {
    if (is_empty()) throw(LinkedListException("empty linked list"));
    return head->next->elem;
}

int LinkedList::back() const {
    if (is_empty()) throw(LinkedListException("empty linked list"));
    Node* ptr = head->next;
    while (ptr->next != NULL) ptr = ptr->next;
    return ptr->elem;
}

void LinkedList::insert(int index, int elem) {
    if (index < 0 || index >= size) throw(LinkedListException("index out of bound"));
    Node* before = head;
    while (index > 0) {
        before = before->next;
        index--;
    }
    Node* node = new Node;
    node->elem = elem;
    node->next = before->next;
    before->next = node;
    size++;
}

void LinkedList::erase(int index) {
    if (index < 0 || index >= size) throw(LinkedListException("index out of bound"));
    Node* before = head;
    while (index > 0 ){
        before = before->next;
        index--;
    }
    Node* node = before->next;
    before->next = before->next->next;
    delete node;
    size--;
}

int LinkedList::value_n_from_end(int n) const {
    if (n < 1 || n > size) throw(LinkedListException("index out of bound"));
    return value_at(size - n);
}

void LinkedList::reverse(){
    Node* new_head = NULL;
    Node* ptr = head->next;
    while (ptr != NULL) {
        Node* next = ptr->next;
        ptr->next = NULL;
        ptr->next = new_head;
        new_head = ptr;
        ptr = next;
    }
    head->next = new_head;
}

void LinkedList::remove_value(int value) {
    Node* before = head;
    while (before->next != NULL && before->next->elem != value) {
        before = before->next;
    }
    if (before->next != NULL){
        Node* node = before->next;
        before->next = before->next->next;
        delete node;
        size--;
    }
}