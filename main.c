#include <stdio.h>
#include <stdlib.h>
#include "world.h"
#include "map.h"
#include "game.h"
#include "terminal.h"

/* The "main" function which initializes the game and passes data between various components of the program. */
int main(int argc, char* argv[]) {
    /* An integer variable to store the total number of rows in the world data array. aka. numbers of element in the map.*/
    int worldDataAmount;
    /* An integer variable to store the number of rows in the maze map */
    int worldRow;
     /* An integer variable to store the number of cols in the maze map */
    int worldCol;
    /* A pointer to a pointer of integers to store the address of the dynamically allocated 2D array that will hold the locations of elements in the map.*/
    int** worldData;
    /* A pointer to a pointer of integers to store the address of the dynamically allocated 2D array that will hold the world data.*/
    int** mapData;
    /* Two integer variable to serve as loop counter variables in the subsequent code.*/
    int i, j;
    /* Maximum distance at which an element can be seen by the player. 
    By default, it is initialised to a value of 0 and can be overwritten with another value if needed.*/    
    int visibilityDistance = 0;
    /*  Store the input from the user to move the player which expected to be in the form of the keys "w", "a", "s", and "d" as directional keys in games.*/
    char charIn;
    /* An integer array to indicate the player's position[playerValsArr[0] for rows, playerValsArr[1] for cols] and game status. 
    This provide a quick reference to the player's position without having to search the entire game map element by element.

    playerValsArr[2] is being used to store the game status. Specifically:
    0 indicates that the player does not have the key and the game is still in progress.
    1 indicates that the player has the key.
    -1 indicates that the player has won the game and the game is over.*/
    int playerValsArr[3]={0,0,0};
    /* The warningFlag variable is used to prevent duplicate warning messages from being printed to the terminal.
    If a warning message has already been printed and not cleared, a beep will also be played to alert the user instead.*/
    int warningFlag = 1;
    /* Player move result message code.*/
    int mesCode;
    /* These variables are intermediate variables used to fill the mapData from the worldData in the for loop."*/
    int objCode;
    int row;
    int col;


    /* Conditional Compilation (to enable/disable the visibility feature.)*/
    
    /* The following code is only included if the DARK macro is defined.*/
    /* In the case DARK in defined, we use the DARK macro to enable a visibility feature by overwriting the visibilityDistance with the argv integer.*/

    #ifdef DARK
    /*retrieving command-line arguments*/
    if (argc > 2) {
        printf("Error: Error: Too many arguments.\nUsage: %s [<visibility distance>]\n", argv[0]);
        return 1; /* Return an error code.*/
    }
    if (argc > 1) {
        int result = sscanf(argv[1], "%d", &visibilityDistance);/* Convert the input to an integer.*/
        /* Check if visibilityDistance is a integer by using sscanf function, which returns 0 when the string cannot be converted to an integer, 
        and the subsequent check ensures that it is greater than 0.*/
        if (result !=1 || visibilityDistance < 0) {
            printf("Error: The visibility distance must be a non-negative integer.\nUsage: %s [<visibility distance>]\n", argv[0]);
            return 1; /* Return an error code.*/
        }
    }
    #endif
    /* This code calls the "disableBuffer" function from "terminal.c" to enable continuous input without requiring the user to press "Enter". */
    disableBuffer();

    /* Welcome Page */
    /* This section of code displays the welcome page, which provides instructions of the program.*/

    system("clear");
    printf("\n___  ___                    _____");
    printf("\n|  \\/  |                   |  __ \\");
    printf("\n| .  . |  __ _  ____  ___  | |  \\/  __ _  _ __ ___    ___");
    printf("\n| |\\/| | / _` ||_  / / _ \\ | | __  / _` || '_ ` _ \\  / _ \\");
    printf("\n| |  | || (_| | / / |  __/ | |_\\ \\| (_| || | | | | ||  __/ ");
    printf("\n\\_|  |_/ \\__,_|/___| \\___|  \\____/ \\__,_||_| |_| |_| \\___|");
    printf("\n__________________________________________________________________");
    printf("\n\nWelcome to the Maze Game!\n\n");
    printf("Your objective is to find the key (k) and then reach the goal (x).\n");
    printf("Use WASD keys to move around the maze.\n");
    printf("Press Q to quit the game at any time.\n\n");
    printf("Please ensure that CapsLock is turned off.\n");
    printf("\nPress any key to continue...\n");
    getchar();
    system("clear");


    /* Map Initialization (Although it may appear lengthy due to the comments, there is actually not a significant amount of codes.)*/

    /* Our map initialization code is relatively simple and # ONLY USED IN ONE PLASE #. I choose the approach that avoids introducing additional files and complexity. 
    If the map initialization code is not placed in the main, and instead is redundantly defined and called wordData and mapData in multiple files, 
    it would lead to code redundancy and increased memory usage, which can affect the performance and stability of the application. 
    Therefore, it's not a great approach in this scenario to place the map initialization code in a separate function or file. 
    Remaining initialization in the main function can help avoid redundant calls and improve code reusability and maintainability. */
    
    /* Request the fundamental information and distribution of elements on the map.*/
    worldData = getWorldData(&worldDataAmount, &worldRow, &worldCol);
    /* Conditional compilation statements that are used for debugging purposes. */
    #ifdef DEBUBG1
    for (i=0; i<worldDataAmount;i++){
        printf("%d,%d %d\n",worldData[i][0],worldData[i][1],worldData[i][2]);
    }
    #endif

    /* Create a dynamically allocated 2D array ready to be filled up with map data, using calloc() to avoid the need for initialization.*/
    mapData = (int**)calloc(worldRow, sizeof(int*)); 
    for (i = 0; i < worldRow; i++) {
        mapData[i] = (int*)calloc(worldCol, sizeof(int));
    }

    /* Populate the map data according to worldData, but redefining the player's position as -1 instead of the 0 given in worldData.*/
    for (i = 0; i < worldDataAmount; i++) {
        row = worldData[i][0] ; 
        col = worldData[i][1] ; 
        objCode = worldData[i][2];
        if (objCode == 0){
            /* record the player's position */
            playerValsArr[0] = row; 
            playerValsArr[1] = col;
            objCode = -1;/* For zero values, replace with 1.*/
        }
        mapData[row][col] = objCode;
    }

    /*After adding elements to the map, free the memory used for the table of the location of each element.*/
    for(i = 0; i < worldDataAmount; i++) {/* Free the memory for each array pointed to by the pointers */
        free(worldData[i]);
        worldData[i] = NULL;
    }
    free(worldData);/* Free the memory for the pointer array */
    worldData = NULL;

    /* Setting up borders by filling the first and last columns and rows with the object code for the wall*/
    for (j = 0; j < worldCol; j++) {/* set the top and bottom rows to 2*/
        mapData[0][j] = 2; /* top row */
        mapData[worldRow - 1][j] = 2; /* bottom row */
    }
    for (i = 0; i < worldRow; i++) {/* set the left and right columns to 2 */
        mapData[i][0] = 2; /* left column */
        mapData[i][worldCol - 1] = 2; /* right column */
    }

    /* Prints the initial state of the game map. */
    printMap(mapData, worldRow, worldCol, playerValsArr, visibilityDistance, 'w');


    /* Checks whether the game is over by checking if the user has pressed 'q' to quit or has won the game. 
    If either condition is true, the while loop is terminated, and the game is ended. */
    while (charIn !='q'&& playerValsArr[2]!=-1){
        /* Scenario 1: If the user inputs 'q', the game loop will then be ended.*/
        charIn = getchar();
        if (charIn == 'q'){
            system("clear");
            printMap(mapData, worldRow, worldCol, playerValsArr, visibilityDistance, charIn);
        printf("\nThe game has been exited. Thank you for playing!\n");

        }
        /*Scenario 2: If the user inputs a valid character ('w', 'a', 's', 'd'), 
        the character will be passed as an argument to the playerMove() function, which updates the game state based on the player's movement.*/
        else if(charIn == 'a' || charIn == 's' || charIn == 'd' || charIn == 'w'){
            warningFlag = 1;
            
            mesCode = playerMove(mapData, worldRow, worldCol, playerValsArr, visibilityDistance, charIn);
            system("clear");/* Clean the terminal for Linux system.*/
            printMap(mapData, worldRow, worldCol, playerValsArr, visibilityDistance, charIn);
            moveMessenger(mesCode);
        }
        /*Scenario 3: If the user inputs an invalid character.The user will then be prompted to try again.*/ 
        else if(warningFlag == 1){
            printf("\n#Warning: Invalid input!#\n%c",7);
            printf("Use WASD keys to move around.\n");
            printf("Press Q to quit the game\n\n");
            printf("Ensure that CapsLock is turned off.\n");
            
        /* The warningFlag variable is used to prevent duplicate warning messages from being printed to the terminal.
        If a warning message has already been printed and not cleared, a beep will also be played to alert the user instead.*/
            warningFlag = 0;
        }
        else printf("%c",7);/*Beep*/
    }
    /*After adding maze is end, free the memory used for the maze.*/
    for(i = 0; i < worldRow; i++) {/* Free the memory for each array pointed to by the pointers */
        free(mapData[i]);
        mapData[i] = NULL;
    }
    free(mapData);/* Free the memory for the pointer array */
    mapData = NULL;

    

    enableBuffer();
    return 0;
}