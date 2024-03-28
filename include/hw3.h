#include <stdlib.h>

typedef struct TileStack
{
    char stack[5];
    int top;
} TileStack;

typedef struct GameState
{
    int boardHeight;
    int boardWidth;
    TileStack** currentBoard;
    int** boardDepth;
} GameState;

typedef struct Change
{
    int oldHeight;
    int oldWidth;
    int amountOfTiles;
    int** tile_positions;
} Change;

typedef struct ChangeStack
{
    Change* stack;
    int top;
} ChangeStack;

GameState* initialize_game_state(const char *filename);
GameState* place_tiles(GameState *game, int row, int col, char direction, const char *tiles, int *num_tiles_placed);
GameState* undo_place_tiles(GameState *game);
void free_game_state(GameState *game);
void save_game_state(GameState *game, const char *filename);
