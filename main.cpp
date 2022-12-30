#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

Env make_env(const int rows, const int cols);
void delete_env(Env env, int rows, int cols);

// Read a environment from standard input.
Env readEnvStdin();

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);
char directionOfMove(Node* previousNode, Node* currentNOde);

int ENV_DIM_COL_COUNT = 1;
int ENV_DIM_ROW_COUNT = 1;

int main(int argc, char** argv){

    // Load Environment 
    Env env = readEnvStdin();

    // Create path solve class
    PathSolver* pathSolver = new PathSolver(env, ENV_DIM_COL_COUNT, ENV_DIM_ROW_COUNT);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    pathSolver->forwardSearch(env);
    NodeList* exploredPositions = pathSolver->getNodesExplored();
    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath();
    printEnvStdout(env, solution);
    
    delete solution;
    delete pathSolver;
    delete exploredPositions;
    return EXIT_SUCCESS;
}

// Env functions
Env readEnvStdin() {
    Env env = make_env(1,1);

    char c; 
    int colCount = 1;
    int rowCount = 1;
    int col = 0;
    int row = 0;
    std::string environment = "";

    while(std::cin.get(c)) {
        
        // Count the size of our rectangle
        if(row == 0 && c != '\n' && col != 0) {
            ++ colCount;
        } else if( c == '\n') {
            ++rowCount;
            
        } 
        
        // Add values to the string
        if(c == '\n') {
            ++row;
            col = 0;
        } else {
            environment += c;       
            ++ col;
        }
    }

    env = make_env(colCount, rowCount);


    int x = 0;
     for (row = 0; row < rowCount; row++) {
        for (col = 0; col < colCount; col++) {
            
            env[col][row] = environment.at(x);
            ++x;
        }
    }

        // Redefine variables
    ENV_DIM_COL_COUNT = colCount;
    ENV_DIM_ROW_COUNT = rowCount;

    return env;
}

void printEnvStdout(Env env, NodeList* solution) {   
     for (int row = 0; row < ENV_DIM_ROW_COUNT ; row++) {
        for (int col = 0; col < ENV_DIM_COL_COUNT ; col++) {
            
            bool onPath = false;
            // Print out direction if on path
            for(int x = 0; x < solution->getLength() - 1; x++) {
                if(solution->getNode(x)->getCol() == col
                    && solution->getNode(x)->getRow() == row
                    && env[col][row] != SYMBOL_GOAL && env[col][row] != SYMBOL_START){
                        std::cout << directionOfMove(solution->getNode(x), solution->getNode(x + 1));
                        onPath = true;
                    }
                }  
        
            if(!onPath){
                std::cout << env[col][row] ;
            }                    
        }
         std::cout << "\n" ;
    }
}

char directionOfMove(Node* previousNode, Node* currentNode){
    // Determine direction of nect move 
    // Right
    if(previousNode->getCol() < currentNode->getCol()){
        return '>';
    }
    
    // Left
    if(previousNode->getCol() > currentNode->getCol()){
        return '<';
    }

    // UP
    if(previousNode->getRow() > currentNode->getRow()){
        return '^';
    }

    // Down
    if(previousNode->getRow() < currentNode->getRow()){
        return 'V';
    }

    // Invalid Move

    return 'N';

}
 
/*
 * This function is to help you dynamically allocate
 *  memory for a generic 2D Environemnt.
 */
Env make_env(const int rows, const int cols) {
   Env env = nullptr;

   if (rows >= 0 && cols >= 0) {
      env = new char*[rows];
      for (int i = 0; i != rows; ++i) {
         env[i] = new char[cols];
      }
   }

   return env;
}

/*
 * This function is to help you delete a 
 * dynamically allocated 2D Environment.
 */
void delete_env(Env env, int rows, int cols) {
   if (rows >= 0 && cols >= 0) {
      for (int i = 0; i != rows; ++i) {
         delete env[i];
      }
      delete env;
   }

   return;
}