#include "NodeList.h"
#include <iostream>



NodeList::NodeList(int size){
    this->nodes = new Node *[this->arraySize];
    //this->nodes = new Node *[size];
}

NodeList::~NodeList(){
    // /delete this->nodes;
}

NodeList::NodeList(NodeList& other){
   
    for(int x = 0; x < other.getLength(); x++) {
        this->nodes[this->length] = new Node(*other.getNode(x));
        this->length = this->length + 1;
    }
}

int NodeList::getLength(){
    return this->length;
}

void NodeList::addElement(Node* newPos){
    // Expand the array 
    if(this->length < this->arraySize - 1){
        expandArray(this->arraySize+ 10);

    }    
    this->nodes[this->length] = newPos;
    this->length = this->length + 1;
}

Node* NodeList::getNode(int i){
    return this->nodes[i];
}

void NodeList::sortByManhattanDistance(Node* goal) {
    
    for(int x = 1; x < this->length -1; x++) {
        
        int lengthPositionZero = this->getNode(x - 1)->getManhattanDistance(goal);
        int lengthPositionOne = this->getNode(x)->getManhattanDistance(goal);

        if(lengthPositionOne < lengthPositionZero) {
            Node* tmpZero = this->getNode(x - 1);
            Node* tmpOne = this->getNode(x);
            this->nodes[x - 1] = tmpOne;
            this->nodes[x] = tmpZero;
            x = 1;
        }
    }    
}

void NodeList::sortByDistanceTraveled() {
    
    for(int x = 1; x < this->length -1; x++) {
        
        int lengthPositionZero = this->getNode(x - 1)->getDistanceTraveled();
        int lengthPositionOne = this->getNode(x)->getDistanceTraveled();

        if(lengthPositionOne < lengthPositionZero) {
            Node* tmpZero = this->getNode(x - 1);
            Node* tmpOne = this->getNode(x);
            this->nodes[x - 1] = tmpOne;
            this->nodes[x] = tmpZero;
            x = 1;
        }
    }   
}


bool NodeList::checkIfNodeExistInList(int col, int row) {
     for(int x = 0; x < this->length - 1; x++) {
        Node* node = this->getNode(x);
        if(node->getCol() == col && node->getRow() == row) {
            return true;
        }
     }

     return false;
}

int NodeList::getFirstValid(){
    for(int x = 0; x < this->length; x++) {
        if(!nodes[x]->getPositionChecked()) {
            return x;
        }
    }

    // No valid nodes left
    return 0;
}

void NodeList::removeNode(Node* nodeToRemove) {
    
    bool nodeFound = false;
    for (int x = 0; x < this->length - 1; x++){
        if(this->nodes[x] == nodeToRemove || nodeFound) {
            this->nodes[x] = this->nodes[x + 1];
            nodeFound = true;
            
        }
    }
    --this->length;
}

void NodeList::expandArray(int newlength)
{   
    Node** newArray = new Node *[newlength]; //Creates new array with expanded length
    for (int i = 0; i < this->length; i++)   //Copies from existing array to ne array.
    {
        newArray[i] = nodes[i];
    }

    //Deletes existing array and assigns the new array as a member variable.
    delete nodes;
 
    this->nodes = newArray;
    this->arraySize = this->arraySize + 10;
}
