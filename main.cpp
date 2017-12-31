#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Player.h"
#include "Functions.h"
#include "Config.h"

int main()
{
    int numCat = 4;
    int numBlack = 296;

    unsigned seed = (unsigned)time(NULL);
    srand(seed);
    int tolPlayer = numCat + numBlack;
    gameSetting config;
    std::vector<Player*> players;

    for(int i = 0; i < numCat; i++)
        players.push_back(new Player('C'));
    for(int i = numCat; i < tolPlayer; i++)
        players.push_back(new Player('B'));
    //for (int i = 0; i < players.size(); i++)    std::cout << &players[i] <<std::endl;

    for (int i = 1; i <= config.generation; i++){
        std::cout << "In generation " << i << " : " << std::endl;
        std::cout << "\tNumber of copycat is: " << numCat << std::endl;
        std::cout << "\tNumber of black heart is: " << numBlack << std::endl;
        resetPlayers(&players, tolPlayer);
        for (int j = 0; j < tolPlayer; j++){
            for (int k = 0; k < config.contact; k++){
                int opponent;
                opponent = pickComponent(&players, j, tolPlayer);
                //std::cout << "\tPlayer " << j << " vs " << "Player " << opponent << std::endl;
                game(players[j], players[opponent], config.rounds);
            }
            //std::cout << "\t\tPlayer " << j << "(" << players[j].type << ")" << "'s score = " << players[j].score << std::endl;
        }

        naturalSelection(&players, config.Replace, tolPlayer);

        numBlack = 0;
        numCat = 0;
        for (int j = 0; j < tolPlayer; j ++){
            if (players[j]->type == 'C')    numCat++;
            else if (players[j]->type == 'B')    numBlack++;
        }
        std::cout << "\n\n";
        //system("pause");
    }
    clearPlayers(&players);
    system("pause");
    return 0;
}
