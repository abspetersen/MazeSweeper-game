//
//  Game.h
//  MazeSweeperFINAL3
//
//  Created by Abby petersen on 11/30/19.
//  Copyright © 2019 Abby petersen. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <stdio.h>
#include <iostream>
#include "Graph.h"
#include <vector>

using namespace std;

class Game {
private:
    //game and grid members
    char **grid;
    bool positionStatus;
    int posX;
    int posY;
    int lives;
    Tile currentTile;
    
    //leaderboard members
    int score;
    int tileScore;
    vector<int> leaderBoardVector;
public:
    //game and grid construction functions
    Game();
    void playGame();
    void startGameLoop(Graph*, int);
    Tile getCurrentTile() const;
    int getPosX() const;
    int getLives() const;
    int getPosY() const;
    void printGrid(char**, int);
    void GameLoop(int,int,char**,bool,Graph*);
    void setCurrentTile(int, int, Graph*);
    void setPosX(int newPosX);
    void setPosY(int newPosY);
    void displayInstructions();
    void Kill();
    void endGame();
    void resetGame();
    
    //leaderboard functions
    void IncScore();
    void AddToLeaderboard();
    void LeaderboardDisplay();
    void GameSuccess();
    ~Game();
};
#endif /* Game_h */

