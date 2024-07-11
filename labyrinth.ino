#include <iostream>
#include <string>

class GameTile {
public:
    std::string name;
    bool hasPlayerA;
    bool hasPlayerB;
    bool hasTreasure;
    bool hasDragon;
    bool isBaseA;
    bool isBaseB;
    bool isExplored;
    bool hasWallEast;
    bool hasWallWest;
    bool hasWallNorth;
    bool hasWallSouth;

    // Constructors
    GameTile() : name(""), hasPlayerA(false), hasPlayerB(false), hasTreasure(false), hasDragon(false), isBaseA(false), isBaseB(false), isExplored(false), hasWallEast(true), hasWallWest(true), hasWallNorth(true), hasWallSouth(true) {}

    // Getters and Setters
    std::string getName() { return name; }
    void setName(const std::string& newName) { name = newName; }

};

class Player {
public:
    std::string name;
    int health;
    char currentCol;
    char currentRow;
    bool hasTreasure;
    bool isSafe;

    // Constructors
    Player() : name(""), health(0), currentCol(' '), currentRow(' '), hasTreasure(false), isSafe(true) {}

    // Getters and Setters
    std::string getName() { return name; }
    void setName(const std::string& newName) { name = newName; }

    int getHealth() { return health; }
    void setHealth(int newHealth) { health = newHealth; }

    char getCurrentCol() { return currentCol; }
    void setCurrentCol(char newCol) { currentCol = newCol; }

    char getCurrentRow() { return currentRow; }
    void setCurrentRow(char newRow) { currentRow = newRow; }

    bool getHasTreasure() { return hasTreasure; }
    void setHasTreasure(bool value) { hasTreasure = value; }

    bool getIsSafe() { return isSafe; }
    void setIsSafe(bool value) { isSafe = value; }
};

int main() {
    // Define the dimensions of the game board
    int rows = 8;
    int cols = 9;

    // Create Gameboard of GameTiles
    std::vector<std::vector<GameTile>> gameBoard(rows, std::vector<GameTile>(cols));

    // Create a Player object
    Player dragon;
    dragon.setName("Dragon");
    dragon.setHealth(8);
    dragon.setCurrentCol('B');
    dragon.setCurrentRow('9');
    dragon.setHasTreasure(false);
    dragon.setIsSafe(true);

    Player playerA;
    dragon.setName("Player A");
    dragon.setHealth(8);
    dragon.setCurrentCol('B');
    dragon.setCurrentRow('1');
    dragon.setHasTreasure(false);
    dragon.setIsSafe(true);

    Player playerB;
    dragon.setName("Player B");
    dragon.setHealth(8);
    dragon.setCurrentCol('I');
    dragon.setCurrentRow('1');
    dragon.setHasTreasure(false);
    dragon.setIsSafe(true);

    // Set gameover bool
    bool gameOver = false;

  // Run the game
    while (!gameOver) {
    }



    return 0;
}