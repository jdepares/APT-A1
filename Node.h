#ifndef COSC_ASSIGN_ONE_NODE
#define COSC_ASSIGN_ONE_NODE

#include "Types.h"

class Node{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Desctructor
    Node(int row, int col, int dist_traveled);
    ~Node();

    // get row-coodinate of the node
    int getRow();

    // get column-coodinate of the node
    int getCol();

    //getter and setter for distance traveled
    int getDistanceTraveled();
    void setDistanceTraveled(int dist_traveled);

    //getter for estimated dist to goal - need to return -> Manhatten distance + distance traveled
    int getEstimatedDistToGoal(Node* goal);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    Node(Node& other);

    bool getValidPosition();
    void setValidPosition(bool valid);
    bool getIsGoal();
    void setIsGoal(bool goal);
    bool getPositionChecked();
    void setPositionChecked(bool checked);
    int getManhattanDistance(Node* goal);


private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    int row;
    int col;
    int dist_traveled;  // distance from start node

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    bool validPosition;
    bool positionChecked;
    bool isGoal;

};

#endif //COSC_ASSIGN_ONE_NODE