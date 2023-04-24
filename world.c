#include<stdlib.h>
#include"world.h"

/*  This file and the corresponding header file (world.c and world.h) contains a
    single function you can use to get some Worlddata that you need to create
    the 2D world array in the main function. 

    DO NOT add any new function here. We will test it with our own world.c
    when we mark it. DO NOT change the name of the function and the filename
    (getWorlddata function,  world.c and world.h)
    
    If you want to make your own Worlddata for the world (e.g adding wall),
    you can modify the Worlddata table here. Once again, keep in mind that
    we will test your assignment with our own Worlddata. */

int** getWorldData(int * worldDataAmount, int * worldRow, int * worldCol)
{
    int i;
    int ** table;

    *worldDataAmount = 18;   /* amount of the objects in the playable area */
    *worldRow = 8;            /* The world row size you will create later */
    *worldCol = 10;           /* The world column size you will create later */

    /* Remember, the playable area would be only (worldRow-2) x (worldCol-2)
       due to world border at the edge */

    /* Now it is the time to malloc 2D Worlddata array */
    table = (int **) malloc(sizeof(int *) * (*worldDataAmount));

    for(i = 0 ; i < (*worldDataAmount) ; i++)
    {
        table[i] = (int *) malloc(sizeof(int) * 3);
    }
        /*  every WorlddataTable row always has 3 integers. These 3 numbers are:
            <worldRow_index> <worldCol_index> <object_code>

            This is the list of the object_code:
            0 -> Player (will always start facing up with char '^')
            1 -> Goal (char 'x')
            2 -> Wall (char 'o')
            3 -> Key (char 'k')

            For simplicity, you can assume the first two entries are
            always the player and the goal position.

            You can assume there is only 1 player and 1 goal.
        */
    
    /*  Normally we put a newline after semicolon,
        but this is just to make it easier to read the table entry.
        All indexing is based on the 0-based index (starts from 0) */
    table[0][0] = 6; table[0][1] = 3; table[0][2] = 0;
    table[1][0] = 1; table[1][1] = 8; table[1][2] = 1;
    table[2][0] = 1; table[2][1] = 7; table[2][2] = 2;
    table[3][0] = 2; table[3][1] = 1; table[3][2] = 2;
    table[4][0] = 2; table[4][1] = 3; table[4][2] = 2;
    table[5][0] = 2; table[5][1] = 7; table[5][2] = 2;
    table[6][0] = 3; table[6][1] = 3; table[6][2] = 2;
    table[7][0] = 3; table[7][1] = 7; table[7][2] = 2;
    table[8][0] = 4; table[8][1] = 2; table[8][2] = 2;
    table[9][0] = 4; table[9][1] = 3; table[9][2] = 2;
    table[10][0] = 4; table[10][1] = 4; table[10][2] = 2;
    table[11][0] = 4; table[11][1] = 5; table[11][2] = 2;
    table[12][0] = 4; table[12][1] = 7; table[12][2] = 2;
    table[13][0] = 5; table[13][1] = 4; table[13][2] = 2;
    table[14][0] = 5; table[14][1] = 7; table[14][2] = 2;
    table[15][0] = 6; table[15][1] = 2; table[15][2] = 2;
    table[16][0] = 6; table[16][1] = 4; table[16][2] = 2;   
    table[17][0] = 1; table[17][1] = 1; table[17][2] = 3;   
    
    
    return table; /* return the array */

    /* remember, you need to free this 2D table at some point once you finish
       extracting its information to create your own 2D world array in
       the main function. */
}