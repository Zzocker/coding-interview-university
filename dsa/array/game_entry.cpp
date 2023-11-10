#include <string>
#include <iostream>
#include "game_entry.h"

using std::string;
using std::cout;

GameEntry::GameEntry(const string& n, int s = 0) : name {n}, score {s} {}

string GameEntry::get_name() const {
    return name;
}

int GameEntry::get_score() const {
    return score;
}

void GameEntry::print() const {
    cout <<"Name = " << name << ", Score = " << score;
}