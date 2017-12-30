#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class player{
public:
    char type;
    int score;
    bool betray;
    bool haveChild;
    player* parent;

    player(){
        haveChild = false;
        parent = NULL;
    }
    player(char type){
        haveChild = false;
        parent = NULL;
        this->type = type;
    }
};

#endif // PLAYER_H_INCLUDED
