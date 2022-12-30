#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled):
    row(row),
    col(col),
    dist_traveled(dist_traveled),
    validPosition(true),
    positionChecked(false),
    isGoal(false)
{  }

Node::Node(Node& other):
    row(other.row),
    col(other.col),
    dist_traveled(other.dist_traveled),
    validPosition(other.validPosition),
    positionChecked(other.positionChecked),
    isGoal(other.isGoal)
{  }


Node::~Node(){   
}

int Node::getRow(){
    return this->row;
}

int Node::getCol(){
    return this->col;
}

int Node::getDistanceTraveled(){
    return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled){
    this->dist_traveled = dist_traveled;
}

bool Node::getValidPosition(){
    return this->validPosition;
}

void Node::setValidPosition(bool valid) {
    this->validPosition = valid;
}
bool Node::getIsGoal(){
    return this->isGoal;
}

void Node::setIsGoal(bool goal) {
    this->isGoal= goal;
}

bool Node::getPositionChecked(){
    return this->positionChecked;
}

void Node::setPositionChecked(bool checked) {
    this->positionChecked = checked;
}

int Node::getEstimatedDistToGoal(Node* goal){   
    int dist = (this->col - goal->getCol()) + (this->row - goal->getRow());
    return dist < 0 ? dist * -1 : dist;
}

int Node::getManhattanDistance(Node* goal){
    return this->getDistanceTraveled() + this->getEstimatedDistToGoal(goal);
}
    
//--------------------------------                             