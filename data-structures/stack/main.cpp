#include "stack.h"
#include <cassert>

using namespace std;

int main(){
    Stack stack;
    assert(stack.is_empty());

    try {
        stack.pop();
        assert(false);
    }catch (const StackException& e){
        assert(e.get_message() == "empty stack");
    }

    try {
        stack.top();
        assert(false);
    }catch (const StackException& e){
        assert(e.get_message() == "empty stack");
    }

    stack.push(1);
    assert(stack.top() == 1);
    assert(!stack.is_empty());
    assert(stack.size() == 1);

    stack.pop();
    assert(stack.is_empty());
    assert(stack.size() == 0);

    const int test_size = 16;
    for (int i=0;i<test_size;i++){
        stack.push(i);
        assert(stack.top() == i);
        assert(stack.size() == 1);
    }

    for (int i=test_size-1;i>=0;i--){
        stack.pop();
        assert(stack.size() == i);
    }
}