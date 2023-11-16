#include "hash_table.h"
#include <cassert>

using namespace std;

int main(){
    HashTable table;
    assert(!table.exists(1));

    try {
        table.get(1);
        assert(false);
    }catch (const HashTableException& e){
        assert(e.get_message() == "key not found");
    }
    table.add(1, 2);
    assert(table.exists(1));
    assert(table.get(1) == 2);

    table.add(1, 3);
    assert(table.exists(1));
    assert(table.get(1) == 3);

    table.remove(1);
    assert(!table.exists(1));


    for (int i=0;i<100;i++) table.add(i,i+1);
    for (int i=0;i<100;i++) assert(table.get(i) == i+1);
    for (int i=0;i<100;i++) table.remove(i);
}