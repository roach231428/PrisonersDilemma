#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "Config.h"
#include <time.h>
#include <stdio.h>
#include <vector>
#include <algorithm>    // std::sort

int indexof(std::vector<Player*>* players, Player* A, const int tolPlayer){
    for(int i = 0 ;i < tolPlayer; i++){
        if (A == players->at(i))
            return i;
    }
    return -1;
}

int pickComponent(std::vector<Player*>* players, int a,const int tolPlayer){
    int opponent = a;
    gameSetting config;

    // Calculate size of the pool
    int poolnum = tolPlayer;
    int parentConst = tolPlayer * config.relative_const;
    Player* trace = players->at(a);
    while(trace->parent != NULL){
        poolnum += parentConst;
        parentConst = parentConst / 2;
        trace = trace->parent;
    }

    // Build the pickup pool
    int pool[poolnum];
    parentConst = tolPlayer * config.relative_const;
    trace = players->at(a);
    int n = 0;
    for (; n < tolPlayer; n++) pool[n] = n;
    while(trace->parent){
        for (int i = 0; i < parentConst; i++){
            pool[n] = indexof(players, trace->parent, tolPlayer);
            n++;
        }
        trace = trace->parent;
        if (parentConst < 2)    break;
        parentConst = parentConst / 2;
    }

    while(opponent == a){
        int temp = rand()%poolnum;
        opponent = pool[temp];
    }

    return opponent;
}

bool cmpPlayers(Player* A, Player* B){
    return A->score > B->score;
}

void game(Player* A, Player* B, int rounds){
    scoreRule rule;
    for (int i = 0; i < rounds; i++){
        if (A->betray == true && B->betray == true){
            A->score += rule.doubleBetray;
            B->score += rule.doubleBetray;
        }
        else if (A->betray == false && B->betray == true){
            A->score += rule.beBetrayed;
            B->score += rule.betray;
        }
        else if (A->betray == false && B->betray == false){
            A->score += rule.winwin;
            B->score += rule.winwin;
        }
        else if (A->betray == true && B->betray == false){
            A->score += rule.betray;
            B->score += rule.beBetrayed;
        }

        if (A->type == 'C')  A->betray = B->betray;
        if (B->type == 'C')  B->betray = A->betray;
    }
}

void resetPlayers(std::vector<Player*>* players, int tolPlayer){
    for (int i = 0; i < tolPlayer; i++){
        players->at(i)->score = 0;
        if (players->at(i)->type == 'C')
            players->at(i)->betray = false;
        else if (players->at(i)->type == 'B')
            players->at(i)->betray = true;
    }
}

void clearPlayers(std::vector<Player*>* players){
    int numSize = players->size();
    for (int i = 0; i < numSize; i++)
        delete(players->at(i));
    players->clear();
}

void naturalSelection(std::vector<Player*>* players, int numReplace, int tolPlayer){
    std::sort(players->begin(), players->end(), cmpPlayers);
    //std::cout << "After sorting: " << std::endl;
    //for (int i = 0; i < players->size(); i++) std::cout << "Player " << i << ": " << players->at(i) << " " << players->at(i)->score << " " << players->at(i)->parent << " " << players->at(i)->haveChild << std::endl;

    // Replicate
    for (int i = 0; i < numReplace; i++){
        Player* delPlayer = players->at(players->size()-1);
        // Delete the parent link
        for(int j = 0; j < players->size()- 1; j++){
            if (players->at(j)->parent == delPlayer)
                players->at(j)->parent = NULL;
        }

        delete(delPlayer);
        players->pop_back();
    }

    for (int i = 0; i < numReplace; i++){
        //players[i] = players[players->size()-numReplace-menopause+i];
        Player *temp = new Player;
        *temp = *players->at(i);
        players->push_back(temp);
        players->at(players->size()- 1)->parent = players->at(i);
        players->at(i)->haveChild = true;
    }
    //std::cout << "After selection: " << std::endl;
    //for (int i = 0; i < players->size(); i++) std::cout << "Player " << i << ": " << players->at(i) << " " << players->at(i)->score << " " << players->at(i)->parent << " " << players->at(i)->haveChild << std::endl;

}


#endif // FUNCTIONS_H_INCLUDED
