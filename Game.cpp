//
//  Game.cpp
//  MazeSweeperFINAL3
//
//  Created by Abby petersen on 11/30/19.
//  Copyright © 2019 Abby petersen. All rights reserved.
//

#include "Game.h"
#include <iostream>
#include <fstream>

using namespace std;

Game::Game(){
    lives = 5;
    posX = 0;
    posY = 0;
    score = 0;
    tileScore = 0;
    positionStatus = false;
    currentTile.getCoordinate().setXCoordinate(0);
    currentTile.getCoordinate().setYCoordinate(0);
    grid = {};
}


// Game constructor will create the maze
void Game::playGame() {
    
    //input file to read path from previously written file (according to user specified maze size)
    string filename;
    ifstream infile;
    int size = 0;
    int num;
    Graph* g;
    
    //menu that reads chars for trap positioning from the file of the user specified size
    do{
        cout << "Enter the size of the maze (enter 1 for 10x10, 2 for 15x15, 3 for 20x20, or 4 for 25x25): ";
        cin >> num;
        switch (num){
            case 1:
                filename = "/Users/abbypetersen/Desktop/MazeSweeperFINAL3/MazeSweeperFINAL3/ten.txt";
                size = 10;
                break;
            case 2:
                filename = "/Users/abbypetersen/Desktop/MazeSweeperFINAL3/MazeSweeperFINAL3/fifteen.txt";
                size = 15;
                break;
            case 3:
                filename = "/Users/abbypetersen/Desktop/MazeSweeperFINAL3/MazeSweeperFINAL3/twenty.txt";
                size = 20;
                break;
            case 4:
                filename = "/Users/abbypetersen/Desktop/MazeSweeperFINAL3/MazeSweeperFINAL3/twentyFive.txt";
                size = 25;
                break;
        }
    } while (num <= 0 || num > 4);
    
    //initialize graph with user specified size and file with appropriate name
    g = new Graph(size);
    infile.open(filename);
    
    //the file will have 'T' and 'F' for if it is a trap or not and I just remembered that we also need a 'S' for start and 'E' for finish in the file,
    // so we have to read and assign those accordingly, can one of ya'll do that part? I included a sammple maze file of what it could possibly look like
    char val;
    // loop through the file using the sizeXsize the user entered
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            infile >> val;
            //add tiles without traps for the starting and ending tiles, actually not sure how to handle the start and finish cases?
            if( val == 'S'){
                Tile t(i, j, size, val, false);
                g->addVertex(t);
                g->setStartTile(t);
            }
            else if(val == 'T') {
                Tile t(i, j, size, val, false);
                g->addVertex(t);
            }
            else if(val == 'F') {
                Tile t(i, j, size, val, true);
                g->addVertex(t);
            }
            else if( val == 'E'){
                Tile t(i, j, size, val, false);
                g->addVertex(t);
                g->setEndTile(t);
            }
        }
    }
    
    
    infile.close();
    
    // Coordinate pointer for the Coordinate array
    Coordinate *cPtr = new Coordinate();
    int xCor;
    int yCor;

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            g->getTile(i, j).setWeight(g->getEndTile().getCoordinate());
            //using the current tile, set it's adjacent coordinates
            g->getTile(i, j).setAdjacentCoordinates(size);
            // get the current tiles array of adjacent coordinates that was set in the line above
            cPtr = g->getTile(i, j).getAdjacentCoordinates();
            // loop through the adjacent coordinate array to check if any of them contain traps
            for(int k = 0; k < 8; k++) {
                // variable for the x and y coordinate of the tile that came from the adjacent coordinates array above.
                // We need these to get the actual coordinates of the tile in the graph inorder to access that tile and see
                // if it has a trap or not
                xCor = (cPtr+k)->getXCoordinate();
                yCor = (cPtr+k)->getYCoordinate();
                // check if the x coordinate doesn't = -2, if it does, it means that the specific adjacent tile we are looking for
                // isn't actually adjacent to the current one (more detailed explanation in the function in the tile class)
                // and check if it contains a trap, if it does, increment the number of adjacent traps for the original tile
                // and add a weight of 1 to the edge of the tile who has the trap
                if(xCor != -2 && g->getTile(xCor, yCor).getIsTrap() == true) {
                    g->getTile(i, j).setNumberOfAdjacentTraps();
                }
            }
        }
    }
    
    //call start game function
    startGameLoop(g,size);
    
}

void Game::startGameLoop(Graph* g, int size){
    //construct starting grid of 'O's and print it with user position (X) in starting position
    int count = 0;
    
    grid = new char* [size];
    for(int i = 0; i < size; i++) {
        grid[i] = new char[size];
    }
    
    GameLoop(size,count,grid,positionStatus,g);
}

void Game::GameLoop(int size,int count, char** grid,bool positionStatus,Graph* g){
    char move;
    if(getLives() == 0){
        AddToLeaderboard();
        cout << "You have ran out of lives!" << endl;
        cout << "Game Over!" << endl;
        return;
    }
    else if(positionStatus == true || count == 0){
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if(i == g->getEndTile().getCoordinate().getXCoordinate() && j == g->getEndTile().getCoordinate().getYCoordinate()) {
                    grid[i][j] = 'E';
                }
                else {
                    grid[i][j] = '.';
                }
            }
        }
        int startXCord = g->getStartTile().getCoordinate().getXCoordinate();
        int startYCord = g->getStartTile().getCoordinate().getYCoordinate();
        
        currentTile = g->getTile(startXCord, startYCord);
        int num = currentTile.getNumberOfAdjacentTraps();
        char c = '0' + num;
        grid[startXCord][startYCord] = c;
        
        posX = currentTile.getCoordinate().getXCoordinate();
        posY = currentTile.getCoordinate().getYCoordinate();
        
        printGrid(grid, size);
        positionStatus = false;
    }
    
    //loop for game: prompts user to enter coordinates and updates graph based on user position
    //continues game if user goes to a tile without and trap and ends it if user goes to tile with a trap
    //for(int i =0; i < lives; i++){
    if(positionStatus == false){
        bool correctTile = true;
        cout << "You have " << getLives() << " live(s) left." << endl;
        cout << "Press the direction you want to move in, or press 'h' for help." << endl;
        cin >> move;
        cout << "\n\n\n\n\n" << endl;
        switch (move) {
                // to move up
            case 'w':
                posX--;
                if(posX > size || posY > size || posX < 0 || posY < 0) {
                    correctTile = false;
                    break;
                }
                if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                    correctTile = false;
                }
                break;
                // to move left
            case 'a':
                posY--;
                if(posX > size || posY > size || posX < 0 || posY < 0) {
                    correctTile = false;
                    break;
                }
                if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                    correctTile = false;
                }
                break;
                // to move down
            case 'x':
                posX++;
                if(posX > size || posY > size || posX < 0 || posY < 0) {
                    correctTile = false;
                    break;
                }
                if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                    correctTile = false;
                }
                break;
                // to move right
            case 'd':
                posY++;
                if(posX > size || posY > size || posX < 0 || posY < 0) {
                    correctTile = false;
                    break;
                }
                if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                    correctTile = false;
                }
                break;
                // to move up and then right
            case 'e':
                posY++;
                posX--;
                if(posX > size || posY > size || posX < 0 || posY < 0) {
                    correctTile = false;
                    break;
                }
                if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                    correctTile = false;
                }
                break;
                //to move up and then left
            case 'q':
                posY--;
                posX--;
                if(posX > size || posY > size || posX < 0 || posY < 0) {
                    correctTile = false;
                    break;
                }
                if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                    correctTile = false;
                }
                break;
                // to move down and then left
            case 'z':
                posY--;
                posX++;
                if(posX > size || posY > size || posX < 0 || posY < 0) {
                    correctTile = false;
                    break;
                }
                if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                    correctTile = false;
                }
                break;
                // to move down and then right
            case 'c':
                posY++;
                posX++;
                if(posX >= size || posY >= size || posX < 0 || posY < 0) {
                    correctTile = false;
                    break;
                }
                if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                    correctTile = false;
                }
                break;
            case 'h':
                displayInstructions();
                break;
            default:
                correctTile = false;
                break;
        }
        
        while(correctTile == false) {
            posX = currentTile.getCoordinate().getXCoordinate();
            posY = currentTile.getCoordinate().getYCoordinate();
            cout << "You entered a wrong key!" << endl;
            printGrid(grid, size);
            cout << "You have " << getLives() << " lives left." << endl;
            cout << "Press the direction you want to move in, or press 'h' for help." << endl;
            cin >> move;
            cout << "\n\n\n\n\n" << endl;
            
            switch (move) {
                    // to move up
                case 'w':
                    posX--;
                    if(posX > size || posY > size || posX < 0 || posY < 0) {
                        correctTile = false;
                        break;
                    }
                    if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                        correctTile = false;
                    }
                    else {
                        correctTile = true;
                    }
                    break;
                    // to move left
                case 'a':
                    posY--;
                    if(posX > size || posY > size || posX < 0 || posY < 0) {
                        correctTile = false;
                        break;
                    }
                    if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                        correctTile = false;
                    }
                    else {
                        correctTile = true;
                    }
                    break;
                    // to move down
                case 'x':
                    posX++;
                    if(posX > size || posY > size || posX < 0 || posY < 0) {
                        correctTile = false;
                        break;
                    }
                    if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                        correctTile = false;
                    }
                    else {
                        correctTile = true;
                    }
                    break;
                    // to move right
                case 'd':
                    posY++;
                    if(posX > size || posY > size || posX < 0 || posY < 0) {
                        correctTile = false;
                        break;
                    }
                    if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                        correctTile = false;
                    }
                    else {
                        correctTile = true;
                    }
                    break;
                    // to move up and then right
                case 'e':
                    posY++;
                    posX--;
                    if(posX > size || posY > size || posX < 0 || posY < 0) {
                        correctTile = false;
                        break;
                    }
                    if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                        correctTile = false;
                    }
                    else {
                        correctTile = true;
                    }
                    break;
                    //to move up and then left
                case 'q':
                    posY--;
                    posX--;
                    if(posX > size || posY > size || posX < 0 || posY < 0) {
                        correctTile = false;
                        break;
                    }
                    if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                        correctTile = false;
                    }
                    else {
                        correctTile = true;
                    }
                    break;
                    // to move down and then left
                case 'z':
                    posY--;
                    posX++;
                    if(posX > size || posY > size || posX < 0 || posY < 0) {
                        correctTile = false;
                        break;
                    }
                    if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                        correctTile = false;
                    }
                    else {
                        correctTile = true;
                    }
                    break;
                    // to move down and then right
                case 'c':
                    posY++;
                    posX++;
                    if(posX > size || posY > size || posX < 0 || posY < 0) {
                        correctTile = false;
                        break;
                    }
                    if(!g->getTile(posX, posY).isInAdjacentCoordinates(currentTile)) {
                        correctTile = false;
                    }
                    else {
                        correctTile = true;
                    }
                    break;
                case 'h':
                    displayInstructions();
                    break;
                default:
                    correctTile = false;
                    break;
            }
        }
        
        positionStatus = g->getTile(posX, posY).getIsTrap();
        
        if(positionStatus == true) {
            Kill();
            //positionStatus = false;
            cout << "You have reached a tile with a trap and died!" << endl;
            cout << "You have " << getLives() << " lives left." << endl;
            return GameLoop(size, count, grid, positionStatus, g);
        }
        int numOfTrap = g->getTile(posX, posY).getNumberOfAdjacentTraps();
        char c = '0' + numOfTrap;
        grid[posX][posY] = c;
        setCurrentTile(posX, posY, g);
        tileScore = tileScore + currentTile.getWeight();
        printGrid(grid, size);
        IncScore();
        if(posX == g->getEndTile().getCoordinate().getXCoordinate() && posY == g->getEndTile().getCoordinate().getYCoordinate()) {
            GameSuccess();
            AddToLeaderboard();
            endGame();
            return;
        }
        count++;
        return GameLoop(size,count, grid, positionStatus, g);
    }
}

Tile Game::getCurrentTile() const {
    return currentTile;
}

int Game::getPosX() const{
    return posX;
}

int Game::getPosY() const{
    return posY;
}

void Game::setCurrentTile(int x, int y, Graph* g) {
    currentTile = g->getTile(x, y);
}

void Game::setPosX(int newPosX){
    posX = newPosX;
}
void Game::setPosY(int newPosY){
    posY = newPosY;
}

void Game::displayInstructions() {
    cout << "Instructions: " << endl;
    cout << "1. The number shown on the maze is where your current position is, and tells you how many traps are around you." << endl;
    cout << "2. Moving:\n\tup = w\n\tdown = x\n\tleft = a\n\tright = d\n\tup and right = e\n\tup and left = q\n\tdown and right = c\n\tdown and left = z" << endl;
    cout << "\n\n\n\n\n" << endl;
}

int Game::getLives() const{
    return lives;
}

void Game::Kill(){
    lives--;
}


void Game::endGame() {
    cout << "YOU HAVE SUCCESSFULLY FINISHED THE MAZE!\nTHANKS FOR PLAYING!\n" << endl;
}

void Game::printGrid(char ** g, int size) {
    cout << "\n";
    
    for(int i = 0; i < size; i++) {
        cout << "\t";
        for(int j = 0; j < size; j++) {
            cout << g[i][j];
            cout << " ";
        }
        cout << endl;
    }
    cout << "\n";
}

void Game::IncScore(){
    score++;
}

void Game::AddToLeaderboard(){
    int temp = score;
    leaderBoardVector.push_back(temp);
}

void Game::GameSuccess(){
    score = score + getLives();
    score = score + tileScore;
}

void Game::LeaderboardDisplay(){
    cout <<  "\n************************************************************" << endl;
    cout << "Leaderboard of all rounds played!\n";
    cout <<  "\n************************************************************" << endl;
    cout << "If you ran out of lives before reaching the end of the maze,\n";
    cout << "you're given a score that is equal to the number of times you landed on a tile without a trap.\n";
    cout << "If you reached the end of the maze, your number of remaining lives is given as your score and the round is recorded as a success.\n";
    cout << "** You have completed 1 round after using up 5 lives or reaching the end of the maze! **\n";
    cout <<  "\n************************************************************\n\n";
    
    for(int i : leaderBoardVector) {
        cout << "Score: " << i << endl;
    }
    /*for(int i = 0; i < num_scores; i++){
        cout << "- Round " << (i+1) << "): " << scores[i] << '\n';
    }
    
    cout <<  "\n************************************************************" << endl;
    cout << "The maze was successfully completed during the following rounds: \n";
    for(int i = 0; i < num_complete; i++){
        cout << "- Round " << completes[i] << '\n';
    }*/
}

void Game::resetGame() {
    lives = 5;
    posX = 0;
    posY = 0;
    score = 0;
    tileScore = 0;
    positionStatus = false;
    currentTile.getCoordinate().setXCoordinate(0);
    currentTile.getCoordinate().setYCoordinate(0);
    grid = {};
}

Game::~Game(){
    
}
