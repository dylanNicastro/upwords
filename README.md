# Upwords
This file contains the functions required to implement the board game Upwords. A full description of the game can be found [here](https://winning-moves.com/images/UPWORDS_rulesv2.pdf).

> [!WARNING]
> These are only helper functions, so nothing will happen if you compile and run this file by itself!

## words.txt:
This file contains all valid words that the game will accept. If you want to add or remove a word, simply edit this file.

## Functions
### `GameState* initialize_game_state(const char *filename)`
This function initializes the file into a dynamically allocated 2D array to prepare for the start of the game.

- `const char *filename`: A `.txt` file that indicates the current state of the game. Example shown below.

**Return value**: A pointer to the GameState struct that represents the initial state of the game.

> [!NOTE]
> All stacks of tiles in the `.txt` file are assumed to be 1 tile high, and the game state in the file is assumed to be valid.

Example `.txt` file:
```
..........
..........
...T.P....
..HOME....
...P.T....
...M.A....
...A.L....
...N......
```

---

### `GameState* place_tiles(GameState *game, int row, int col, char direction, const char *tiles, int *num_tiles_placed)`
Places tiles on the board to form new valid words.

- `GameState *game`: The struct representating the current state of the game, defined in `include/definitions.h`
- `int row`: The row to start placing tiles in
- `int col`: The column to start placing tiles in
- `char direction`: The direction to place tiles. Should be either `'V'` (vertical) or `'H'` (horizontal)
- `const char *tiles`: The tiles to place, given as a string (e.g. `"HELLO WORLD"`).
    - It must form valid words only when placed on the board.
    - If any invalid words are formed, whether directly or indirectly (e.g. it overlaps other tiles on the board and creates a nonexistent word), the function will return an error.
    - If there are spaces in the string, the function will skip the corresponding tile stack when placing the tiles.
- `int *num_tiles_placed`: A pointer to an `int` variable that will be updated by this function to indicate the amount of tiles placed.

**Return value**: A pointer to the GameState struct that represents the new state of the game.

> [!IMPORTANT]
> If the tiles go out of the board, the board will be dynamically reallocated to expand and fit the tiles!

---

### `GameState* undo_place_tiles(GameState *game)`
Undos the most recent tile placement.

- `GameState *game`: The GameState struct representing the current state of the game

**Return value**:
- If `*game` represents the initial state of the game (e.g. `place_tiles()` has not been called yet), returns `*game`.
- Otherwise, returns a GameState struct representing the state of the game before the most recent call to `place_tiles()`.

> [!NOTE]
> This function can be called multiple times consecutively, as the list of changes are stored in a stack.

---

### `void free_game_state(GameState *game)`
Deallocates all memory associated with the game, including all dynamically allocated data structures.

- `GameState *game`: The GameState struct representing the current state of the game

> [!CAUTION]
> This function should only be called at the end of the game, as it effectively deletes the board!

---

### `void save_game_state(GameState *game, const char *filename)`
The current state of the game is saved as a `.txt` file, which can then be opened by `initialize_game_state()` in a new instance of the program.

- `GameState *game`: The GameState struct representing the current state of the game
- `const char *filename`: The path to save the state of the game to.

> [!TIP]
> This function does not end the game, and so it is fine to be called at any point in the game.