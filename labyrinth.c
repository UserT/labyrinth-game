#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the gameTile struct
typedef struct {
    char* name;
    bool has_player_A;
    bool has_player_B;
    bool has_treasure;
    bool has_dragon;
    bool is_base_A;
    bool is_base_B;
    bool is_explored;
    bool has_wall_east;
    bool has_wall_west;
    bool has_wall_north;
    bool has_wall_south;
} gameTile;

// Function prototypes for gameTile getters and setters
char* get_name(gameTile* tile);
void set_name(gameTile* tile, const char* new_name);

bool get_has_player_A(gameTile* tile);
void set_has_player_A(gameTile* tile, bool value);

bool get_has_player_B(gameTile* tile);
void set_has_player_B(gameTile* tile, bool value);

bool get_has_treasure(gameTile* tile);
void set_has_treasure(gameTile* tile, bool value);

bool get_has_dragon(gameTile* tile);
void set_has_dragon(gameTile* tile, bool value);

bool get_is_base_A(gameTile* tile);
void set_is_base_A(gameTile* tile, bool value);

bool get_is_base_B(gameTile* tile);
void set_is_base_B(gameTile* tile, bool value);

bool get_is_explored(gameTile* tile);
void set_is_explored(gameTile* tile, bool value);

bool get_has_wall_east(gameTile* tile);
void set_has_wall_east(gameTile* tile, bool value);

bool get_has_wall_west(gameTile* tile);
void set_has_wall_west(gameTile* tile, bool value);

bool get_has_wall_north(gameTile* tile);
void set_has_wall_north(gameTile* tile, bool value);

bool get_has_wall_south(gameTile* tile);
void set_has_wall_south(gameTile* tile, bool value);


// Define the player struct
typedef struct {
    char* name;
    int health;
    char current_col;
    char current_row;
    bool has_treasure;
    bool is_safe;
} player;

// Function prototypes for player getters and setters
char* get_name(player* p);
void set_name(player* p, const char* new_name);

int get_health(player* p);
void set_health(player* p, int new_health);

char get_current_col(player* p);
void set_current_col(player* p, char new_col);

char get_current_row(player* p);
void set_current_row(player* p, char new_row);

bool get_has_treasure(player* p);
void set_has_treasure(player* p, bool value);

bool get_is_safe(player* p);
void set_is_safe(player* p, bool value);


// Function prototype for createGameBoard
gameTile*** createGameBoard(int rows, int cols);


//main
int main() {
    // Define the dimensions of the game board
    int rows = 8;
    int cols = 9;

    // Call createGameBoard to allocate and initialize the game board
    gameTile*** gameBoard = createGameBoard(rows, cols);

   // Allocate memory for the Dragon player
    player* Dragon = malloc(sizeof(player));

    // Initialize the properties of the Dragon player
    set_name(Dragon, "Dragon");
    set_health(Dragon, 5);
    set_current_col(Dragon, 'A');
    set_current_row(Dragon, '1');
    set_has_treasure(Dragon, false);
    set_is_safe(Dragon, true);

    // Free the allocated memory
        free(Dragon);

    for(int i = 0; i < rows; ++i) {
        free(gameBoard[i]);
    }
    free(gameBoard);

    return 0;
}

// Implementation of createGameBoard
gameTile*** createGameBoard(int rows, int cols) {
    // Allocate memory for the 2D array of gameTile pointers
    gameTile*** gameBoard = malloc(rows * sizeof(gameTile**));
    for(int i = 0; i < rows; ++i) {
        gameBoard[i] = malloc(cols * sizeof(gameTile*));
    }

    // Initialize each gameTile in the array
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            // Initialize properties of each gameTile
            gameBoard[i][j] = malloc(sizeof(gameTile));
            gameBoard[i][j]->name = "Uninitialized";
            gameBoard[i][j]->has_player_A = false;
            gameBoard[i][j]->has_player_B = false;
            gameBoard[i][j]->has_treasure = false;
            gameBoard[i][j]->has_dragon = false;
            gameBoard[i][j]->is_base_A = false;
            gameBoard[i][j]->is_base_B = false;
            gameBoard[i][j]->is_explored = false;
            gameBoard[i][j]->has_wall_east = true; // Example initialization
            gameBoard[i][j]->has_wall_west = true; // Example initialization
            gameBoard[i][j]->has_wall_north = true; // Example initialization
            gameBoard[i][j]->has_wall_south = true; // Example initialization
        }
    }

    // Return the pointer to the 2D array of gameTile structs
    return gameBoard;
}



// Getter and Setter implementations for gameTile
char* get_name(gameTile* tile) {
    return tile->name;
}

void set_name(gameTile* tile, const char* new_name) {
    if (tile->name != NULL) {
        free(tile->name); // Free the old memory if it exists
    }
    tile->name = strdup(new_name); // Allocate new memory for the new name
}

bool get_has_player_A(gameTile* tile) {
    return tile->has_player_A;
}

void set_has_player_A(gameTile* tile, bool value) {
    tile->has_player_A = value;
}


// Getter and Setter for player implementations
char* get_name(player* p) {
    return p->name;
}

void set_name(player* p, const char* new_name) {
    if (p->name != NULL) {
        free(p->name); // Free the old memory if it exists
    }
    p->name = strdup(new_name); // Allocate new memory for the new name
}

int get_health(player* p) {
    return p->health;
}

void set_health(player* p, int new_health) {
    p->health = new_health;
}

char get_current_col(player* p) {
    return p->current_col;
}

void set_current_col(player* p, char new_col) {
    p->current_col = new_col;
}

char get_current_row(player* p) {
    return p->current_row;
}

void set_current_row(player* p, char new_row) {
    p->current_row = new_row;
}

bool get_has_treasure(player* p) {
    return p->has_treasure;
}

void set_has_treasure(player* p, bool value) {
    p->has_treasure = value;
}

bool get_is_safe(player* p) {
    return p->is_safe;
}

void set_is_safe(player* p, bool value) {
    p->is_safe = value;
}