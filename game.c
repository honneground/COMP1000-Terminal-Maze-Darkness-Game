#include <stdio.h>

/* Receives the user's input from the main function and determines whether the player's movement is valid or not. 
Then updates the game map and state accordingly. */
int playerMove(int **mapData, int rows, int cols,int* CrtCoord, int viewRange, char playerFront){
    /* Store the target coordinates of the player's movement. */
    int tarX, tarY;
    /* Player move result message code.*/
    int mesCode;

    /* Provide the destination coordinates.*/
    if (playerFront == 'w'){
        tarY = CrtCoord[0]-1;
        tarX = CrtCoord[1];
    }else if (playerFront =='s'){
        tarY = CrtCoord[0]+1;
        tarX = CrtCoord[1];
    }else if (playerFront =='a'){
        tarY = CrtCoord[0];
        tarX = CrtCoord[1]-1;
    }else if (playerFront =='d'){
        tarY = CrtCoord[0];
        tarX = CrtCoord[1]+1;
    }

    /* Scenario 1: The destination coordinates are empty. 
    The movement is valid and the player can move to the that location.*/
    if (mapData[tarY][tarX] == 0){
        mapData[tarY][tarX] = -1;
        mapData[CrtCoord[0]][CrtCoord[1]] = 0;
        CrtCoord[0] = tarY;
        CrtCoord[1] = tarX;
    /* Scenario 2: The destination coordinates contain a key. 
    The movement is valid and the player can move to the that location. 
    The game state will be  updated to indicate that the player has picked up the key.*/
    }else if (mapData[tarY][tarX] == 3){
        mapData[tarY][tarX] = -1;
        mapData[CrtCoord[0]][CrtCoord[1]] = 0;
        CrtCoord[0] = tarY;
        CrtCoord[1] = tarX;
        /*Indicating that player has the key. */
        CrtCoord[2] = 1;
        mesCode = 2;
    }
    /* Scenario 3: The destination coordinates are the goal. 
    The movement is valid only if the player has already picked up the key.
    If the player has the key, the movement is valid and the player wins the game. 
    Otherwise, the movement is invalid and the player cannot move to the specified location. */
    else if (mapData[tarY][tarX] == 1){
        if (CrtCoord[2] == 1){
            mapData[tarY][tarX] = 9;
            mapData[CrtCoord[0]][CrtCoord[1]] = 0;
            CrtCoord[0] = tarY;
            CrtCoord[1] = tarX;
            /*Indicating that player won. */
            CrtCoord[2] = -1;
    /* Returns a message code to the main function after a player move, which will then passed to the moveMessenger function to print a status message to the console. */
            mesCode = -1;
        }
        else{
            mesCode = -2;
        }
    }
    else{  
        mesCode= 1;
    } 
    return mesCode;
}

/* Taking a message code as input and prints the corresponding text message to the console.
The text message provides feedback to the player move. */
void moveMessenger(int mesCode){
    if (mesCode == -2) printf("\nYou don't have the key to enter the goal.\n\n\n\n%c", 7);
    else if (mesCode == 1) printf("\nYou just hit the wall!\n\n\n\n%c", 7);
    else if (mesCode == 2) printf("\nYou got the key!\n\n\n\n");
    else if (mesCode == -1) printf("\nCongratulations on reaching the goal(X).\n You won!\n\n\n");
    else printf("\n\n\n\n\n");
}
