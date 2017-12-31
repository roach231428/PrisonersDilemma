#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player{
public:
    char type;
    int score;
    bool betray;
    bool haveChild;
    Player* parent;

    Player(){
        haveChild = false;
        parent = NULL;
    }
    Player(char type){
        haveChild = false;
        parent = NULL;
        this->type = type;
    }

};

#endif // PLAYER_H_INCLUDED
