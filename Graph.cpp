//
//  Graph.cpp
//  MazeSweeperFINAL3
//
//  Created by Abby petersen on 11/30/19.
//  Copyright © 2019 Abby petersen. All rights reserved.
//

#include "Graph.h"
#include <iostream>

using namespace std;

Graph::Graph() {
    
}
// initialize the 2D array
Graph::Graph(int size) {
    arr = new Tile* [size];
    for(int i = 0; i < size; i++) {
        arr[i] = new Tile[size];
    }
    
}

Graph::~Graph() {
    for(int i = 0; i < (sizeof(arr)/sizeof(*arr)); i++) {
        delete [] arr[i];
    }
    delete [] arr;
}
// add the tile to the graphs 2D array
void Graph::addVertex(Tile t) {
    arr[t.getCoordinate().getXCoordinate()][t.getCoordinate().getYCoordinate()] = t;
}
// get the current Tile using the coordinates
Tile& Graph::getTile(int x, int y) const {
    return arr[x][y];
}

void Graph::setStartTile(Tile t) {
    startTile = t;
}

Tile Graph::getStartTile() const {
    return startTile;
}

void Graph::setEndTile(Tile t) {
    endTile = t;
}

Tile Graph:: getEndTile() const {
    return endTile;
}
