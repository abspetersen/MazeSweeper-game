//
//  Coordinate.cpp
//  MazeSweeperFINAL3
//
//  Created by Abby petersen on 11/30/19.
//  Copyright © 2019 Abby petersen. All rights reserved.
//
#include <iostream>
#include "Coordinate.h"

Coordinate::Coordinate() : xCoordinate(0), yCoordinate(0) {
    
}

Coordinate::Coordinate(int x, int y) : xCoordinate(x), yCoordinate(y) {
    
}

Coordinate::~Coordinate() {
    
}

void Coordinate::setXCoordinate(int x) {
    xCoordinate = x;
}

void Coordinate::setYCoordinate(int y) {
    yCoordinate = y;
}

int Coordinate::getXCoordinate() const {
    return xCoordinate;
}

int Coordinate::getYCoordinate() const {
    return yCoordinate;
}

bool Coordinate::isEqual(Coordinate c) {
    if(c.getXCoordinate() == xCoordinate && c.getYCoordinate() == yCoordinate) {
        return true;
    }
    return false;
}


