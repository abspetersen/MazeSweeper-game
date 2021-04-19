//
//  main.cpp
//  MazeSweeperFINAL3
//
//  Created by Abby petersen on 11/30/19.
//  Copyright © 2019 Abby petersen. All rights reserved.
//

#include <iostream>
#include "Game.h"

using namespace std;

int display(){
    int cho;
    cout    << "1) Start New Game\n"
    << "2) Leaderboard\n"
    << "3) Quit\n\n";
    cin >> cho;
    
    return cho;
}


int main() {
    
    //create game object
    Game* mazeGame = new Game();
    
    cout <<  "\n****************************"
    <<  "\n**Welcome to Maze Sweeper!**"
    <<  "\n****************************\n\n";
    
    int ret;
    bool isRunning = true;
    
Menu:
    
    while(isRunning){
        int choice = 0;
        char quit = {};
        
        while(choice <= 0 || choice > 3){
            choice = display();
        }
        
        switch (choice)
        {
            case 1:
                //call play game function to execute game
                mazeGame->playGame();
                mazeGame->resetGame();
                break;
            case 2:
                //display leaderboard
                mazeGame->LeaderboardDisplay();
                //return to main menu
                cout << "Enter 1 to return to the menu or enter any other integer to exit the program: " << endl;
                cin >> ret;
                
                if(ret == 1){
                    goto Menu;
                }
                else{
                    isRunning = false;
                }
                
                break;
            case 3:
                cout << "Are you sure you want to quit? (Y/N)\n";
                cin >> quit;
                cout << endl;
                break;
                
            default:
                break;
        }
        
        //ends the program
        if (toupper(quit) == 'Y'){
            cout << "Thank you for playing!" << endl;
            isRunning = false;
        }
        
    }
    
    return 0;
    
}

