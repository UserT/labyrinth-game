#include <iostream>
#include <string>
#include <Keypad.h>

// Define button matrix inputs
//#define DATA_PIN 2 // Connect to DS
//#define CLOCK_PIN 3 // Connect to SHCP
//#define LATCH_PIN 4 // Connect to STCP
const byte ROWS = 4; // number of rows
const byte COLS = 4; // number of columns
char keys[ROWS][COLS] = {
{'a','b','c','d'},
{'e','f','g','h'},
{'i','j','k','l'},
{'m','n','o','p'}

};

byte rowPins[ROWS] = {14, 12, 13, 5}; //, 12, 13, 15}; // row pinouts of the keypad R1 = D8, R2 = D7, R3 = D6, R4 = D5
byte colPins[COLS] = {4, 0, 2, 16}; //, 0, 2, 16};    // column pinouts of the keypad C1 = D4, C2 = D3, C3 = D2
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Setup speaker
const int SpeakerPin = 15; // Change this to the pin you connected the speaker to

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
    char currentTile;
    bool hasTreasure;
    bool isSafe;

    // Constructors
    Player() : name(""), health(0), currentTile(' '), hasTreasure(false), isSafe(true) {}

    // Getters and Setters
    std::string getName() { return name; }
    void setName(const std::string& newName) { name = newName; }

    int getHealth() { return health; }
    void setHealth(int newHealth) { health = newHealth; }

    char getCurrentTile() { return currentTile; }
    void setCurrentTile(char newTile) { currentTile = newTile; }

    bool getHasTreasure() { return hasTreasure; }
    void setHasTreasure(bool value) { hasTreasure = value; }

    bool getIsSafe() { return isSafe; }
    void setIsSafe(bool value) { isSafe = value; }
};

void createMaze (std::vector<std::vector<GameTile>>& gameBoard) {
}

void setup() {
  //Setup Button Matrix  
  //pinMode(DATA_PIN, OUTPUT);
  //pinMode(CLOCK_PIN, OUTPUT);
  //pinMode(LATCH_PIN, OUTPUT);

  // Define the dimensions of the game board
  int rows = 4;
  int cols = 4;

  // Create Gameboard of GameTiles
  std::vector<std::vector<GameTile>> gameBoard(rows, std::vector<GameTile>(cols));

  // Create Game Entities
  Player playerA;
  playerA.setName("Player A");
  playerA.setHealth(8);
  playerA.setCurrentTile('1');
  playerA.setHasTreasure(false);
  playerA.setIsSafe(true);

  Player playerB;
  playerB.setName("Player B");
  playerB.setHealth(8);
  playerB.setCurrentTile('5');
  playerB.setHasTreasure(false);
  playerB.setIsSafe(true);

  createMaze(gameBoard);

  Player dragon;
  dragon.setName("Dragon");
  dragon.setHealth(1);
  dragon.setCurrentTile('f');
  dragon.setHasTreasure(false);
  dragon.setIsSafe(true);

  Serial.begin(921600);
}


void loop() {

    // Sampe Code to play a sound - replace this eventually for mp3 or wav with ESP8266Audio Library
    char key = keypad.getKey(); 
  if (key != NO_KEY) {
    Serial.println(key);
    switch (key) {
      case 'a':
        tone(SpeakerPin, 440, 500);
        break;
      case 'b':
        tone(SpeakerPin, 493.9, 500);
        break;
      case 'c':
        tone(SpeakerPin, 523.3, 500);
        break;
      case 'd':
        tone(SpeakerPin, 587.4, 500);
        break;
      case 'e':
        tone(SpeakerPin, 659.4, 500);
        break;
      case 'f':
        tone(SpeakerPin, 698.7, 500);
        break;
      case 'g':
        tone(SpeakerPin, 784.3, 500);
        break;
      case 'h':
        tone(SpeakerPin, 164.8, 500);
        break;
        case 'i':
        tone(SpeakerPin, 174.6, 500);
        break;
        case 'j':
        tone(SpeakerPin, 196, 500);
        break;
        case 'k':
        tone(SpeakerPin, 220, 500);
        break;
        case 'l':
        tone(SpeakerPin, 247, 500);
        break;
        case 'm':
        tone(SpeakerPin, 261.6, 500);
        break;
        case 'n':
        tone(SpeakerPin, 293.7, 500);
        break;
        case 'o':
        tone(SpeakerPin, 329.6, 500);
        break;
        case 'p':
        tone(SpeakerPin, 392, 500);
        break;
    }
  }
}