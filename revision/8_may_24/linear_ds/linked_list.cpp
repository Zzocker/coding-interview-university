#include <algorithm>
#include <cstddef>
#include <cassert>
using namespace std;

class ListNode{
    public:
        int val;
        ListNode* next;
        ListNode(int v): val{v}, next{NULL} {}
};

class LinkedList{
    private:
        ListNode* aux;
    public:
        LinkedList(): aux{new ListNode(0)} {}
        bool empty() const {
            return aux->next == NULL;
        }

        void push(int value){
            ListNode* node = new ListNode(value);
            node->next = aux->next;
            aux->next = node;
        }

        void pop(){
            if (empty()) return;
            ListNode* del_node = aux->next;
            aux->next = del_node->next;
            delete del_node;
        }

        int at(int index){
            auto itr = aux->next;
            while (index > 0){
                itr = itr->next;
                index--;
            }
            return itr->val;
        }

        void remove(int index){
            auto prev = aux;
            auto itr = aux->next;
            while (index > 0){
                prev = prev->next;
                itr = itr->next;
                index--;
            }
            ListNode* del_node = itr;
            prev->next = itr->next;
            delete del_node;
        }

        void reverse(){
            ListNode* new_head{NULL};
            for (auto itr = aux->next; itr != NULL; ){
                auto next = itr->next;
                itr->next = NULL;
                itr->next = new_head;
                new_head = itr;
                itr = next;
            }
            aux->next = new_head;
        }
};

int main(){
    // Create a linked list
    LinkedList list;

    // Test empty() function
    assert(list.empty());

    // Test push() function
    list.push(1);
    list.push(2);
    list.push(3);

    // Test at() function
    assert(list.at(0) == 3);
    assert(list.at(1) == 2);
    assert(list.at(2) == 1);

    // Test remove() function
    list.remove(1); // Removes element at index 1
    assert(list.at(1) == 1); // Check if the element at index 1 is 1 after removal

    // Test pop() function
    list.pop(); // Removes the last element
    assert(list.at(0) == 1); // Check if the first element is 3 after pop

    // Test empty() function again
    assert(!list.empty());

    list.push(2);
    list.push(3);
    list.push(4);
    list.reverse();
    assert(list.at(0) == 1);
    assert(list.at(1) == 2);
    assert(list.at(2) == 3);
    assert(list.at(3) == 4);
}