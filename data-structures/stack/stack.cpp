#include "stack.h"
#include <vector>

using std::vector;
using std::string;

Stack::Stack(): bucket{vector<int> ()} {}

void Stack::push(int elem) {
    bucket.push_back(elem);
}

int Stack::top() const {
    if (is_empty()) throw(StackException("empty stack"));
    return bucket.back();
}

void Stack::pop() {
    if (is_empty()) throw(StackException("empty stack"));
    bucket.pop_back();
}

bool Stack::is_empty() const {
    return bucket.empty();
}

int Stack::size() const {
    return bucket.size();
}