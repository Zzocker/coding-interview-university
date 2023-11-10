#ifndef SCORES_H
#define SCORES_H

#include <string>
#include "game_entry.h"

using std::string;


class Exception{
    string msg;
    public:
        Exception(const string& message) : msg {message} {};
        string& get_message() {return msg;}
};

class IndexOutOfBounds: public Exception {
    public:
        IndexOutOfBounds(const string& message): Exception(message) {}
};

class Scores{
    public:
        Scores(int maxEnt = 10);
        ~Scores();
        void add(const GameEntry& e);
        GameEntry remove(int i);
        void print() const;
    private:
        int max_entries;
        int num_entries;
        GameEntry* entries;

};

#endif