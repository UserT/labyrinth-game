#include <iostream>
#include <string>
#include <Keypad.h>

// Define button matrix inputs
#define DATA_PIN 2 // Connect to DS
#define CLOCK_PIN 3 // Connect to SHCP
#define LATCH_PIN 4 // Connect to STCP

// Setup speaker
const int SpeakerPin = 5; // Change this to the pin you connected the speaker to

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

    // Getter Methods
    std::string getName() const { return name; }
    bool getHasPlayerA() const { return hasPlayerA; }
    bool getHasPlayerB() const { return hasPlayerB; }
    bool getHasTreasure() const { return hasTreasure; }
    bool getHasDragon() const { return hasDragon; }
    bool getIsBaseA() const { return isBaseA; }
    bool getIsBaseB() const { return isBaseB; }
    bool getIsExplored() const { return isExplored; }
    bool getHasWallEast() const { return hasWallEast; }
    bool getHasWallWest() const { return hasWallWest; }
    bool getHasWallNorth() const { return hasWallNorth; }
    bool getHasWallSouth() const { return hasWallSouth; }

    // Setter Methods
    void setName(const std::string& newName) { name = newName; }
    void setHasPlayerA(bool newStatus) { hasPlayerA = newStatus; }
    void setHasPlayerB(bool newStatus) { hasPlayerB = newStatus; }
    void setHasTreasure(bool newStatus) { hasTreasure = newStatus; }
    void setHasDragon(bool newStatus) { hasDragon = newStatus; }
    void setIsBaseA(bool newStatus) { isBaseA = newStatus; }
    void setIsBaseB(bool newStatus) { isBaseB = newStatus; }
    void setIsExplored(bool newStatus) { isExplored = newStatus; }
    void setHasWallEast(bool newStatus) { hasWallEast = newStatus; }
    void setHasWallWest(bool newStatus) { hasWallWest = newStatus; }
    void setHasWallNorth(bool newStatus) { hasWallNorth = newStatus; }
    void setHasWallSouth(bool newStatus) { hasWallSouth = newStatus; }
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

void setup() {
  //Setup Button Matrix  
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  // Define the dimensions of the game board
  int rows = 8;
  int cols = 9;

  // Create Gameboard of GameTiles
  std::vector<std::vector<GameTile>> gameBoard(rows, std::vector<GameTile>(cols));

  // Create Game Entities
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
}


int loop() {

    // Sampe Code to play a sound - replace this eventually for mp3 or wav with ESP8266Audio Library
    tone(SpeakerPin, 440, 500); // Play a 440Hz tone for 500 milliseconds
    delay(500); // Wait for 500 milliseconds
    noTone(SpeakerPin); // Stop playing the tone
    delay(1000); // Wait for 1000 milliseconds before repeating

    return 0;
}