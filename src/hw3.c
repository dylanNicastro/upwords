#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "hw3.h" 

#define DEBUG(...) fprintf(stderr, "[          ] [ DEBUG ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, " -- %s()\n", __func__)

int push(TileStack *chars, char c) {
    if ((*chars).top == 4) {
        return 1;
    }
    (*chars).stack[++(*chars).top] = c;
    return 0;
}

// Note - does not return the popped char
int pop(TileStack *chars) {
    if ((*chars).top == -1) {
        return 1;
    }
    (*chars).top--;
    return 0;
    
}

char peek(TileStack chars) {
    if (chars.top == -1) {
        return '.';
    }
    return chars.stack[chars.top];
}

GameState currentState;

GameState* initialize_game_state(const char *filename) {
    FILE *inputfile;
    inputfile = fopen(filename, "r");
    if (inputfile == NULL) {
        fprintf(stderr, "Error: Unable to open file %s\n", filename);
        return NULL;
    }
    int currentrow = 0;
    int currentcol = 0;
    char currentchar;
    while (1) {
        currentchar = fgetc(inputfile); 
        if (feof(inputfile)) {
            break;
        }
        if (currentchar == '\n') {
            currentrow++;
            //printf("\n");
        }
        else {
            //printf("%c ",currentchar);
            currentcol++;
        }
    }
    currentState.boardHeight = currentrow;
    currentState.boardWidth = currentcol/currentrow;
    currentState.prevGameState = NULL;
    rewind(inputfile);
    // create board array
    TileStack **board = malloc(currentState.boardHeight*sizeof(TileStack*));
    for (int i = 0; i < currentState.boardHeight; i++) {
        board[i] = malloc(currentState.boardWidth*sizeof(TileStack));
        for (int j = 0; j < currentState.boardWidth; j++) {
            TileStack tile;
            tile.top = -1;
            board[i][j] = tile;
        }
    }
    // create depth array
    int **depth = malloc(currentState.boardHeight*sizeof(int*));
    for (int i = 0; i < currentState.boardHeight; i++) {
        depth[i] = malloc(currentState.boardWidth*sizeof(int));
    }

    currentrow = 0;
    currentcol = 0;

    // store data
    while (1) {
        currentchar = fgetc(inputfile); 
        if (feof(inputfile)) {
            break;
        }
        if (currentchar == '\n') {
            currentrow++;
            currentcol = 0;
            // printf("\n");
        }
        else if (currentchar != '.') {
            TileStack *currentTile = &board[currentrow][currentcol];
            push(currentTile, currentchar);
            depth[currentrow][currentcol] = 1;
            currentcol++;
            // printf("%c", currentchar);
        }
        else {
            depth[currentrow][currentcol] = 0;
            currentcol++;
            // printf("%c", currentchar);
        }
    }

    currentState.currentBoard = board;
    currentState.boardDepth = depth;
    fclose(inputfile);
    GameState *ptr = &currentState;
    return ptr;
}

GameState* place_tiles(GameState *game, int row, int col, char direction, const char *tiles, int *num_tiles_placed) {
    (void)row;
    (void)col;
    (void)direction;
    (void)tiles;
    (void)num_tiles_placed;
    return game;
}

GameState* undo_place_tiles(GameState *game) {
    return game;
}

void free_game_state(GameState *game) {
    (void)game;
}

void save_game_state(GameState *game, const char *filename) {
    FILE *outputfile;
    outputfile = fopen(filename, "w");
    // Write board array
    // printf("Height: %d, Width: %d\n", (*game).boardHeight, (*game).boardWidth);
    for (int i = 0; i < (*game).boardHeight; i++) {
        for (int j = 0; j < (*game).boardWidth; j++) {
            // printf("%c",peek((*game).currentBoard[i][j]));
            fprintf(outputfile, "%c", peek((*game).currentBoard[i][j]));
        }
        fprintf(outputfile, "\n");
    }
    for (int i = 0; i < (*game).boardHeight; i++) {
        for (int j = 0; j < (*game).boardWidth; j++) {
            // printf("%c",peek((*game).currentBoard[i][j]));
            fprintf(outputfile, "%d", (*game).boardDepth[i][j]);
        }
        fprintf(outputfile, "\n");
    }
    fclose(outputfile);
    (void)game;
}
