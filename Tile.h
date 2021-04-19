//
//  Tile.h
//  MazeSweeperFINAL3
//
//  Created by Abby petersen on 11/30/19.
//  Copyright © 2019 Abby petersen. All rights reserved.
//

#ifndef Tile_h
#define Tile_h

#include <stdio.h>
#include <iostream>
#include "Coordinate.h"

class Tile {
private:
    Coordinate coord;
    Coordinate* adjacentCoordinates;
    double weight;
    int numberOfAdjacentTraps;
    bool isTrap;
    char typeOfTile;
public:
    Tile();
    Tile(int, int, int, char, bool);
    ~Tile();
    void setWeight(Coordinate c);
    double getWeight() const;
    Coordinate getCoordinate() const;
    void setNumberOfAdjacentTraps();
    void setAdjacentCoordinates(int);
    int getNumberOfAdjacentTraps() const;
    char getTypeOfTyle() const;
    Coordinate* getAdjacentCoordinates();
    bool getIsTrap();
    bool isInAdjacentCoordinates(Tile t);
    
};

#endif /* Tile_h */
