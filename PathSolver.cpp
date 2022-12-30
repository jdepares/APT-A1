#include "PathSolver.h"
#include <iostream>
#include "Types.h"

PathSolver::PathSolver(Env env, int ENV_DIM_COL_COUNT, int ENV_DIM_ROW_COUNT):
    ENV_DIM_COL_COUNT(ENV_DIM_COL_COUNT),
    ENV_DIM_ROW_COUNT(ENV_DIM_ROW_COUNT)
{
    NODE_LIST_ARRAY_MAX_SIZE = (4*(ENV_DIM_COL_COUNT  * ENV_DIM_ROW_COUNT));
    // Create starting and goal nodes
    std::pair<int, int>  startCo = getStartingCoordinates(env);
    std::pair<int, int>  goalCo = getGoalCoordinates(env);
 
    this->startNode = new Node(startCo.first, startCo.second, 0);
    this->goalNode = new Node(goalCo.first, goalCo.second, 0);

    // Create Nodes List
    this->nodesOpen = new NodeList(NODE_LIST_ARRAY_MAX_SIZE);
    this->nodesExplored = new NodeList(NODE_LIST_ARRAY_MAX_SIZE);
}

PathSolver::~PathSolver(){
    delete this->startNode;
    delete this->goalNode;
    delete this->nodesOpen;
    delete this->nodesExplored;

    this->startNode = nullptr;
    this->goalNode = nullptr;
    this->nodesOpen = nullptr;
    this->nodesExplored = nullptr;
}

void PathSolver::forwardSearch(Env env){

    this->nodesOpen->addElement(this->startNode);

    int currentNode = 0;
    while(currentNode < NODE_LIST_ARRAY_MAX_SIZE) {
        // Add surounding nodes
        bool hasValid = addValidSurroundingNodes(env,this->nodesOpen->getNode(currentNode));
        
        //Disable current node from next search
        if(!hasValid) {
            this->nodesOpen->getNode(currentNode)->setValidPosition(false);
            this->nodesExplored->addElement(this->nodesOpen->getNode(currentNode));
        }

        // Mark the position as checked
        this->nodesOpen->getNode(currentNode)->setPositionChecked(true);
        
        // Sort all the new nodes based on the toal distance
        this->nodesOpen->sortByManhattanDistance(this->goalNode);
        
        // Get the next node to check 
        currentNode = this->nodesOpen->getFirstValid();
        
        // Check if new current node is the goal
        if(env[this->nodesOpen->getNode(currentNode)->getCol()][this->nodesOpen->getNode(currentNode)->getRow()] == SYMBOL_GOAL){
            this->nodesOpen->getNode(currentNode)->setIsGoal(true);
            this->goalNode = this->nodesOpen->getNode(currentNode);
            currentNode = NODE_LIST_ARRAY_MAX_SIZE + 1;
        }
    }
}


NodeList* PathSolver::getNodesExplored(){
    NodeList* nodesExploredCopy = new NodeList(*this->nodesExplored);
    return nodesExploredCopy ;
}

NodeList* PathSolver::getPath(){
    // Create tmp nodelist of only the ValidNodes to make the back tracking easier. 
    // We do not want a deep copy here when creating the nodes, simple a pointer to the existing node. 
    NodeList* validNodes = new NodeList(NODE_LIST_ARRAY_MAX_SIZE);   
    bool goalPassed = false; 

    for (int x= 1; x < this->nodesOpen->getLength() ; x++) {
        if(!goalPassed && this->nodesOpen->getNode(x)->getValidPosition()
            &&  this->nodesOpen->getNode(x)->getDistanceTraveled() < this->goalNode->getDistanceTraveled()) {
            validNodes->addElement(this->nodesOpen->getNode(x));   
         }

         if(this->nodesOpen->getNode(x)->getIsGoal() ) {
            validNodes->addElement(this->nodesOpen->getNode(x));  
         }
    }

    validNodes->sortByDistanceTraveled();

    for (int x = validNodes->getLength() - 1; x > 0; x--){
        // remove steps outside the shortest path
        // Dont need to peform the check on the goal
        
        NodeList* nodesToCompare = new NodeList(NODE_LIST_ARRAY_MAX_SIZE);
        // Pass the next nodes to compare if they are one less distance then the current node
        for (int y = 1; y < validNodes->getLength(); y++){
            if(x - y >= 0 && (validNodes->getNode(x)->getDistanceTraveled() - validNodes->getNode(x - y)->getDistanceTraveled()) == 1) {
               
                nodesToCompare->addElement(validNodes->getNode(x - y));   
            }
        }
        validNextNodeInPath(validNodes->getNode(x), validNodes, nodesToCompare);
        delete nodesToCompare;
        nodesToCompare = nullptr;

    }


    // Create deep copy and return 
    NodeList* validPath = new NodeList(*validNodes);      
    delete validNodes;
    return validPath;
}

//-----------------------------

//solve functions
std::pair<int, int> PathSolver::getStartingCoordinates(Env env)
{
    for (int row = 0; row < ENV_DIM_ROW_COUNT ; row++) {
        for (int col = 0; col < ENV_DIM_COL_COUNT ; col++) {
            if( env[col][row] == SYMBOL_START){
                return std::make_pair(row, col);   
            }
        }
    } 

    return std::make_pair(0, 0);               
}

std::pair<int, int> PathSolver::getGoalCoordinates(Env env)
{
    for (int row = 0; row < ENV_DIM_ROW_COUNT ; row++) {
        for (int col = 0; col < ENV_DIM_COL_COUNT ; col++) {
            if( env[col][row] == SYMBOL_GOAL){
                return std::make_pair(row, col);   
            }
        }
    } 

    return std::make_pair(0, 0);              
}
  
bool PathSolver::addValidSurroundingNodes(Env env, Node* node) {

    bool hasValid = false;

    int col;
    int row;
  
    // Add valid nodes that dont already exist

    // Above
    col = node->getCol();
    row = node->getRow() - 1;  
    if(PathSolver::validNode(env, col, row ) && !this->nodesOpen->checkIfNodeExistInList(col, row)) {
        this->nodesOpen->addElement(new Node(row,col,node->getDistanceTraveled() + 1));
        hasValid = true;
    }

    // right
    col = node->getCol() + 1;
    row = node->getRow();  
    if(PathSolver::validNode(env, col, row ) && !this->nodesOpen->checkIfNodeExistInList(col, row)) {
        this->nodesOpen->addElement(new Node(row,col,node->getDistanceTraveled() + 1));
        hasValid = true;
    }

    // bellow
    col = node->getCol();
    row = node->getRow() + 1;  
    if(PathSolver::validNode(env, col, row ) && !this->nodesOpen->checkIfNodeExistInList(col, row)) {
        this->nodesOpen->addElement(new Node(row,col,node->getDistanceTraveled() + 1));
        hasValid = true;
    }

    // left
    col = node->getCol() - 1;
    row = node->getRow();   
    if(PathSolver::validNode(env, col, row ) && !this->nodesOpen->checkIfNodeExistInList(col, row)) {
        this->nodesOpen->addElement(new Node(row,col,node->getDistanceTraveled() + 1));
        hasValid = true;
    }

    return hasValid;
}

bool PathSolver::validNode(Env env, int col, int row) {
    // Check out of bounds
    if(col < 0 || col > ENV_DIM_COL_COUNT - 1){
        return false;
    }
      
    if(row< 0 || row > ENV_DIM_ROW_COUNT - 1){
        return false;
    }

    if((env[col][row] == SYMBOL_EMPTY  || env[col][row]  == SYMBOL_GOAL )){
        return true;
    }  else {
        return false;
    }
}

void PathSolver::validNextNodeInPath(Node* previous, NodeList* validNodes, NodeList* nodesToCompare) {
    for (int x = 0; x < nodesToCompare->getLength(); x++){   

        // Check if the delta is > 1 for col
        if((((previous->getCol() - nodesToCompare->getNode(x)->getCol()) * -1) > 1) || (previous->getCol() - nodesToCompare->getNode(x)->getCol()) > 1){
            PathSolver::removeNodeFromPath(validNodes, nodesToCompare->getNode(x));
        }

        // Check if the delta is > 1 for col
        else if((((previous->getRow() - nodesToCompare->getNode(x)->getRow()) * -1) > 1) || (previous->getRow() - nodesToCompare->getNode(x)->getRow()) > 1){
            PathSolver::removeNodeFromPath(validNodes, nodesToCompare->getNode(x));
        }
    }

    //Deal with multiple valid nodes
    int multipleValidNodes = false;
    for (int x = 0; x < nodesToCompare->getLength(); x++){   
        
        if(nodesToCompare->getNode(x)->getValidPosition() && !multipleValidNodes){
            multipleValidNodes = true;
        }else if(nodesToCompare->getNode(x)->getValidPosition() && multipleValidNodes){
             PathSolver::removeNodeFromPath(validNodes, nodesToCompare->getNode(x));
            }
    }
}

void PathSolver::removeNodeFromPath(NodeList* validPath, Node* node) {
    node->setValidPosition(false);     
    this->nodesExplored->addElement(node);   
    validPath->removeNode(node);

}

//DELETE

void PathSolver:: printMe(NodeList* nodeList) {

     std::cout <<"|-----------------------|\n";
    for(int x = 0; x < nodeList->getLength() ; x++) {
    std::cout << nodeList->getNode(x)->getCol() << " | "
            << nodeList->getNode(x)->getRow() << " | "
            << nodeList->getNode(x)->getDistanceTraveled()  << " | "
            << nodeList->getNode(x)->getValidPosition()  << " | "
            << nodeList->getNode(x) << "\n";
            }
}