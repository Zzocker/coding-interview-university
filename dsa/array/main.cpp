#include "game_entry.h"
#include "scores.h"

int main(){
    Scores scores(3);
    scores.add(GameEntry("6", 6));
    scores.add(GameEntry("4", 4));
    scores.add(GameEntry("5", 5));
    scores.add(GameEntry("2", 2));
    scores.add(GameEntry("7", 7));
    scores.print();
}