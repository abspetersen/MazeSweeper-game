//
//  Coordinate.h
//  MazeSweeperFINAL3
//
//  Created by Abby petersen on 11/30/19.
//  Copyright © 2019 Abby petersen. All rights reserved.
//

#ifndef Coordinate_h
#define Coordinate_h

#include <stdio.h>
#include <iostream>

class Coordinate {
private:
    int xCoordinate;
    int yCoordinate;
public:
    Coordinate();
    Coordinate(int, int);
    ~Coordinate();
    void setXCoordinate(int);
    void setYCoordinate(int);
    int getXCoordinate() const;
    int getYCoordinate() const;
    bool isEqual(Coordinate);
};
#endif /* Coordinate_h */
