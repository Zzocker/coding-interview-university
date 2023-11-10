#include <string>
#include <iostream>
#include "scores.h"
#include "game_entry.h"

using std::string;
using std::cout;

Scores::Scores(int max_ent = 10) : max_entries {max_ent}, num_entries {0} {
    entries = new GameEntry[max_entries];
}

Scores::~Scores(){
    delete [] entries;
}

void Scores::add(const GameEntry& e){
    if (num_entries == max_entries){
        if (e.get_score() <= entries[max_entries - 1].get_score())return;
    }else num_entries++;

    int position = num_entries - 1;
    while (position > 0 && e.get_score() > entries[position-1].get_score()){
        entries[position] = entries[position-1];
        position--;
    } 
    entries[position] = e;
}

GameEntry Scores::remove(int i){
    if (i >= num_entries || i < 0) throw IndexOutOfBounds("Invalid index");
    GameEntry entry = entries[i];
    while (i < num_entries-1){
        entries[i] = entries[i+1];
        i++;
    }
    num_entries--;
    return entry;
}

void Scores::print() const {
    cout << "number of entries = " << num_entries << '\n';
    for (int i=0;i<num_entries;i++){
        entries[i].print();
        cout << '\n';
    }
}