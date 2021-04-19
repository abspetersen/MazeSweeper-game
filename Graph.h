//
//  Graph.h
//  MazeSweeperFINAL3
//
//  Created by Abby petersen on 11/30/19.
//  Copyright © 2019 Abby petersen. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include <iostream>
#include "Tile.h"

class Graph {
private:
    Tile **arr;
    Tile startTile;
    Tile endTile;
public:
    Graph();
    Graph(int);
    ~Graph();
    void addVertex(Tile);
    Tile& getTile(int, int) const;
    void setStartTile(Tile t);
    Tile getStartTile() const;
    void setEndTile(Tile t);
    Tile getEndTile() const;
    // more functions to add
};
#endif /* Graph_h */
