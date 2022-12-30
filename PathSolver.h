#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include <iostream>

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver(Env env, int ENV_DIM_COL_COUNT, int ENV_DIM_ROW_COUNT);
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath();

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */


    
private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    int NODE_LIST_ARRAY_MAX_SIZE;
    int ENV_DIM_COL_COUNT;
    int ENV_DIM_ROW_COUNT;
    
    NodeList* nodesOpen;
    Node* startNode;
    Node* goalNode;

    std::pair<int, int> getStartingCoordinates(Env env);
    std::pair<int, int> getGoalCoordinates(Env env);
    bool addValidSurroundingNodes(Env env, Node* node);
    bool validNode(Env env, int col, int row);
    void clearUnusedPath();
    void validNextNodeInPath(Node* current, NodeList* validNodes, NodeList* nextNodes);
    void printMe(NodeList* NodeList);
    void removeNodeFromPath(NodeList* validPath, Node* node);
};




#endif //COSC_ASSIGN_ONE_PATHSOLVER