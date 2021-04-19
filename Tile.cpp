//
//  Tile.cpp
//  MazeSweeperFINAL3
//
//  Created by Abby petersen on 11/30/19.
//  Copyright © 2019 Abby petersen. All rights reserved.
//

#include "Tile.h"
#include <iostream>
#include <cmath>

using namespace std;

Tile::Tile() {
    // set the x and y coordinates of the tile
    coord.setXCoordinate(1);
    coord.setYCoordinate(1);
    isTrap = false;
    numberOfAdjacentTraps = 0;
    weight = 0.0;
    
    // initialize the array of coordinates that will be used to find the adjacent tiles from the graph
    adjacentCoordinates = new Coordinate[8];
    
    // okay so idk if there's a more efficient way of doing this but yaaaaa
    // set the values of the adjacent coordinate array to the generic coordinates of:
    // (1,0), (1,1), (1,-1), (0,1), (0,-1), (-1,-1), (-1,0), (-1,1)
    // we do this because this allows us to get all the possible adjacent tiles we can move to
    // from our current tile. There are 8 possiblilites, if the current tile is in the  middle of the
    // maze, hence the 8 different coordinates we will add the the current tile to
    // get the tiles we can move to. I think theres a std::pair shit or something, maybe look into that?
    adjacentCoordinates[0].setXCoordinate(1);
    adjacentCoordinates[0].setYCoordinate(0);
    
    adjacentCoordinates[1].setXCoordinate(1);
    adjacentCoordinates[1].setYCoordinate(1);
    
    adjacentCoordinates[2].setXCoordinate(1);
    adjacentCoordinates[2].setYCoordinate(-1);
    
    adjacentCoordinates[3].setXCoordinate(0);
    adjacentCoordinates[3].setYCoordinate(1);
    
    adjacentCoordinates[4].setXCoordinate(0);
    adjacentCoordinates[4].setYCoordinate(-1);
    
    adjacentCoordinates[5].setXCoordinate(-1);
    adjacentCoordinates[5].setYCoordinate(-1);
    
    adjacentCoordinates[6].setXCoordinate(-1);
    adjacentCoordinates[6].setYCoordinate(0);
    
    adjacentCoordinates[7].setXCoordinate(-1);
    adjacentCoordinates[7].setYCoordinate(1);
}

Tile::Tile(int x, int y, int size, char type, bool trap) {
    // set the x and y coordinates of the tile
    coord.setXCoordinate(x);
    coord.setYCoordinate(y);
    isTrap = trap;
    numberOfAdjacentTraps = 0;
    typeOfTile = type;
    weight = 0.0;
    
    // initialize the array of coordinates that will be used to find the adjacent tiles from the graph
    adjacentCoordinates = new Coordinate[8];
    
    // okay so idk if there's a more efficient way of doing this but yaaaaa
    // set the values of the adjacent coordinate array to the generic coordinates of:
    // (1,0), (1,1), (1,-1), (0,1), (0,-1), (-1,-1), (-1,0), (-1,1)
    // we do this because this allows us to get all the possible adjacent tiles we can move to
    // from our current tile. There are 8 possiblilites, if the current tile is in the  middle of the
    // maze, hence the 8 different coordinates we will add the the current tile to
    // get the tiles we can move to. I think theres a std::pair shit or something, maybe look into that?
    adjacentCoordinates[0].setXCoordinate(1);
    adjacentCoordinates[0].setYCoordinate(0);
    
    adjacentCoordinates[1].setXCoordinate(1);
    adjacentCoordinates[1].setYCoordinate(1);
    
    adjacentCoordinates[2].setXCoordinate(1);
    adjacentCoordinates[2].setYCoordinate(-1);
    
    adjacentCoordinates[3].setXCoordinate(0);
    adjacentCoordinates[3].setYCoordinate(1);
    
    adjacentCoordinates[4].setXCoordinate(0);
    adjacentCoordinates[4].setYCoordinate(-1);
    
    adjacentCoordinates[5].setXCoordinate(-1);
    adjacentCoordinates[5].setYCoordinate(-1);
    
    adjacentCoordinates[6].setXCoordinate(-1);
    adjacentCoordinates[6].setYCoordinate(0);
    
    adjacentCoordinates[7].setXCoordinate(-1);
    adjacentCoordinates[7].setYCoordinate(1);
}

Tile::~Tile() {
    //delete [] adjacentCoordinates;
    //delete [] neighboringCoordinatesWeights;
}

void Tile::setWeight(Coordinate c) {
    int x = coord.getXCoordinate();
    int y = coord.getYCoordinate();
    
    int xDif = c.getXCoordinate() - x;
    int yDif = c.getYCoordinate() - y;
    
    weight = sqrt((pow(xDif, 2)) + (pow(yDif, 2)));
    
}

double Tile::getWeight() const {
    return weight;
}

Coordinate Tile::getCoordinate() const {
    return coord;
}

void Tile::setNumberOfAdjacentTraps() {
    numberOfAdjacentTraps++;
}

int Tile::getNumberOfAdjacentTraps() const {
    return numberOfAdjacentTraps;
}

char Tile::getTypeOfTyle() const {
    return typeOfTile;
}

// sets the adjacent coordinate array with all the coordiantes that are adjacent, ie that we can move to
void Tile::setAdjacentCoordinates(int size) {
    // get the current tiles coordinates
    int currentX = coord.getXCoordinate();
    int currentY = coord.getYCoordinate();
    
    // pointer for the adjacent coordinate array
    Coordinate *ptr = new Coordinate();
    
    ptr = getAdjacentCoordinates();
    
    int x;
    
    // loop through the array
    for(int i = 0; i < 8; i++) {
        x  = (ptr + i)->getXCoordinate();
        // now we have top add the current tiles coordiantes we got from above to the coordinates that were already in the array.
        // this will give us the exact coordinates of the tile in the graph that we can move to
        (ptr + i)->setXCoordinate(currentX + x);
        (ptr + i)->setYCoordinate(currentY + (ptr + i)->getYCoordinate());
        // if at any point after adding the coordinates, one of them goes out of bounds, ie greater than the size of the maze or less than 0,
        // it means that the current tile is probably a corner tile ( ie (0,0) or (9,9)) and only has 3 tiles to move to instead of 8. In a case
        // like this, I just reset the corodinates to -2 meaning that index of the array is not to be considered as one of the adjacent coordinates
        if((ptr + i)->getXCoordinate() < 0 || (ptr + i)->getXCoordinate() > (size - 1) || (ptr + i)->getYCoordinate() < 0 || (ptr + i)->getXCoordinate() > (size - 1)) {
            (ptr + i)->setYCoordinate(-2);
            (ptr + i)->setXCoordinate(-2);
        }
    }
}

Coordinate* Tile::getAdjacentCoordinates() {
    return adjacentCoordinates;
}

bool Tile::getIsTrap() {
    return isTrap;
}
// checks to see if the current tile from the graph is in the original tiles adjacent coordinates, this allows us
// to see if we can move to this tile or not
bool Tile::isInAdjacentCoordinates(Tile t) {
    Coordinate *ptr = getAdjacentCoordinates();
    for(int i = 0; i < 8; i++) {
        if((ptr + i)->isEqual(t.getCoordinate())) {
            return true;
        }
    }
    return false;
}
