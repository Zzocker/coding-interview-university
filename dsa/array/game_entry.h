#ifndef GAME_ENTRY_H
#define GAME_ENTRY_H

#include <string>
using std::string;

class GameEntry{
    public:
        GameEntry(const string& n = "", int s = 0);
        string get_name() const;
        int get_score() const;
        void print() const;
    private:
        string name;
        int score;
};

#endif // GAME_ENTRY_H