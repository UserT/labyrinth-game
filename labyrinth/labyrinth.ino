#include <iostream>
#include <string>
#include <Keypad.h>

// Define button matrix inputs
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
    char name;
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
    GameTile() : name(' '), hasPlayerA(false), hasPlayerB(false), hasTreasure(false), hasDragon(false), isBaseA(false), isBaseB(false), isExplored(false), hasWallEast(false), hasWallWest(false), hasWallNorth(false), hasWallSouth(false) {}

    // Getter Methods
    char getName() const { return name; }
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
    void setName(char newName) { name = newName; }
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

// Define the dimensions of the game board
const int rows = 4;
const int cols = 4;
// Create Gameboard of GameTiles
std::vector<std::vector<GameTile>> gameBoard(rows, std::vector<GameTile>(cols));
// Create Game Entities
Player playerA;
Player playerB;
Player dragon; 

void createMaze (std::vector<std::vector<GameTile>>& gameBoard) {
  //Stub in a pre-configured map - will be random eventually.
  gameBoard[0][0].setName('a');
  gameBoard[0][0].setHasPlayerA(true);
  gameBoard[0][0].setIsBaseA(true);
  gameBoard[0][0].setHasWallWest(true);
  gameBoard[0][0].setHasWallNorth(true);
  gameBoard[0][0].setHasWallSouth(true);

  gameBoard[0][1].setName('b');
  gameBoard[0][1].setHasWallNorth(true);
  
  gameBoard[0][2].setName('c');
  gameBoard[0][2].setHasWallNorth(true);

  gameBoard[0][3].setName('d');
  gameBoard[0][3].setHasWallEast(true);
  gameBoard[0][3].setHasWallNorth(true);

  gameBoard[1][0].setName('e');
  gameBoard[1][0].setHasPlayerB(true);
  gameBoard[1][0].setIsBaseB(true);
  gameBoard[1][0].setIsExplored(true);
  gameBoard[1][0].setHasWallWest(true);
  gameBoard[1][0].setHasWallNorth(true);

  gameBoard[1][1].setName('f');
  gameBoard[1][1].setHasWallEast(true);

  gameBoard[1][2].setName('g');
  gameBoard[1][2].setHasWallEast(true);
  gameBoard[1][2].setHasWallWest(true);
  gameBoard[1][2].setHasWallSouth(true);

  gameBoard[1][3].setName('h');
  gameBoard[1][3].setHasWallEast(true);
  gameBoard[1][3].setHasWallWest(true);
  
  gameBoard[2][0].setName('i');
  gameBoard[2][0].setHasWallEast(true);
  gameBoard[2][0].setHasWallWest(true);
  
  gameBoard[2][1].setName('j');
  gameBoard[2][1].setHasWallWest(true);
  
  gameBoard[2][2].setName('k');
  gameBoard[2][2].setHasWallEast(true);
  gameBoard[2][2].setHasWallNorth(true);
  
  gameBoard[2][3].setName('l');
  gameBoard[2][3].setHasWallEast(true);
  gameBoard[2][3].setHasWallWest(true);
  
  gameBoard[3][0].setName('m');
  gameBoard[3][0].setHasWallWest(true);
  gameBoard[3][0].setHasWallSouth(true);
  
  gameBoard[3][1].setName('n');
  gameBoard[3][1].setHasWallEast(true);
  gameBoard[3][1].setHasWallSouth(true);

  gameBoard[3][2].setName('o');
  gameBoard[3][2].setHasWallWest(true);
  gameBoard[3][2].setHasWallSouth(true);

  gameBoard[3][3].setName('p');
  gameBoard[3][3].setHasTreasure(true);
  gameBoard[3][3].setHasDragon(true);
  gameBoard[3][3].setHasWallEast(true);
  gameBoard[3][3].setHasWallSouth(true);

  //Print Game Board
  Serial.print("\n Game Board");
  for (int i = 0; i < gameBoard.size(); i++)
  {
      Serial.print('\n');
    for (int j = 0; j < gameBoard[i].size(); j++)
    {
      if (!gameBoard[i][j].getHasWallEast() & gameBoard[i][j].getHasWallWest() & gameBoard[i][j].getHasWallNorth() & gameBoard[i][j].getHasWallSouth()){ Serial.print("[¯_");
      }else if (!gameBoard[i][j].getHasWallEast() & !gameBoard[i][j].getHasWallWest() & gameBoard[i][j].getHasWallNorth() & !gameBoard[i][j].getHasWallSouth()){ Serial.print("¯¯¯");
      }else if (!gameBoard[i][j].getHasWallEast() & gameBoard[i][j].getHasWallWest() & gameBoard[i][j].getHasWallNorth() & !gameBoard[i][j].getHasWallSouth()){ Serial.print("[¯¯");
      }else if (gameBoard[i][j].getHasWallEast() & !gameBoard[i][j].getHasWallWest() & gameBoard[i][j].getHasWallNorth() & !gameBoard[i][j].getHasWallSouth()){ Serial.print("¯¯]");
      }else if (gameBoard[i][j].getHasWallEast() & !gameBoard[i][j].getHasWallWest() & !gameBoard[i][j].getHasWallNorth() & !gameBoard[i][j].getHasWallSouth()){ Serial.print("  ]");
      }else if (!gameBoard[i][j].getHasWallEast() & gameBoard[i][j].getHasWallWest() & !gameBoard[i][j].getHasWallNorth() & !gameBoard[i][j].getHasWallSouth()){ Serial.print("[  ");
      }else if (gameBoard[i][j].getHasWallEast() & gameBoard[i][j].getHasWallWest() & !gameBoard[i][j].getHasWallNorth() & gameBoard[i][j].getHasWallSouth()){ Serial.print("[_]");
      }else if (gameBoard[i][j].getHasWallEast() & gameBoard[i][j].getHasWallWest() & !gameBoard[i][j].getHasWallNorth() & !gameBoard[i][j].getHasWallSouth()){ Serial.print("[ ]");
      }else if (gameBoard[i][j].getHasWallEast() & !gameBoard[i][j].getHasWallWest() & !gameBoard[i][j].getHasWallNorth() & gameBoard[i][j].getHasWallSouth()){ Serial.print("__]");
      }else if (!gameBoard[i][j].getHasWallEast() & gameBoard[i][j].getHasWallWest() & !gameBoard[i][j].getHasWallNorth() & gameBoard[i][j].getHasWallSouth()){ Serial.print("[__");
      }else {Serial.print("   ");}
    }
  } Serial.print('\n'); 
}

void playSound (char sound){
  switch (sound){
    case 'n': //Next
    break;
    case 'w': //Wall
      tone(SpeakerPin, 523.3, 100);
      delay(150);
      noTone(SpeakerPin);
      tone(SpeakerPin, 523.3, 150);
      delay(100);
      noTone(SpeakerPin);
      tone(SpeakerPin, 523.3, 150);
      delay(100);
      noTone(SpeakerPin);
      tone(SpeakerPin, 523.3, 150);
    break;
    case 't': //Treasure
    break;
    case 'i': //Illegal Move
      tone(SpeakerPin, 440, 100);
      delay(100);
      noTone(SpeakerPin);
      tone(SpeakerPin, 523.3, 500);  
      break;
    case 'm': //Warrior Moves
      tone(SpeakerPin, 440, 100);
    break;
    case '1': //Warrior 1
    break;
    case '2': //Warrior 2
    break;
    case 'd': //Dragon Wakes
    break;
    case 'f': //Dragon Flying
    break;
    case 'a': //Dragon Attacks
    break;
    case 'v': //Winner/victory
    break;
    case 'g': //Game Over/Defeat
    break;
  }
}

GameTile& getMove (char move){
  GameTile moveTile;
  switch (move) {
      case 'a':
      return gameBoard[0][0];
      break;
      case 'b':
      return gameBoard[0][1];
      break;
      case 'c':
      return gameBoard[0][2];
      break;
      case 'd':
      return gameBoard[0][3];
      break;
      case 'e':
      return gameBoard[1][0];
      break;
      case 'f':
      return gameBoard[1][1];
      break;
      case 'g':
      return gameBoard[1][2];
      break;
      case 'h':
      return gameBoard[1][3];
      break;
      case 'i':
      return gameBoard[2][0];
      break;
      case 'j':
      return gameBoard[2][1];
      break;
      case 'k':
      return gameBoard[2][2];
      break;
      case 'l':
      return gameBoard[2][3];
      break;
      case 'm':
      return gameBoard[3][0];
      break;
      case 'n':
      return gameBoard[3][1];
      break;
      case 'o':
      return gameBoard[3][2];
      break;
      case 'p':
      return gameBoard[3][3];
      break;
    }
    return moveTile;
}

bool moveIsValid (GameTile& previousTile, GameTile& currentTile){
  Serial.print(previousTile.name);
  Serial.print(" to ");
  Serial.print(currentTile.name);
  Serial.print("\n");
  //valid space is in front
  if (!previousTile.hasWallEast && !currentTile.hasWallWest && (currentTile.name == (previousTile.name+1))){return true;}
  //valid space is behind
  else if (!previousTile.hasWallWest && !currentTile.hasWallEast && (currentTile.name == (previousTile.name-1))) {return true;}
  //valid space is above
  else if (!previousTile.hasWallNorth && !currentTile.hasWallSouth && (currentTile.name == (previousTile.name-cols))) {return true;}
  //valid space is below
  else if (!previousTile.hasWallSouth && !currentTile.hasWallNorth && (currentTile.name == (previousTile.name+cols))) {return true;}
  //space is invalid
  else {return false;} 
}

void setup() {
  Serial.begin(921600);

  createMaze(gameBoard);
  
  // Stub in Game Entities
  playerA.setName("Player A");
  playerA.setHealth(4);
  playerA.setHasTreasure(false);
  playerA.setIsSafe(true);
  playerB.setName("Player B");
  playerB.setHealth(8);
  playerB.setHasTreasure(false);
  playerB.setIsSafe(true);
  dragon.setName("Dragon");
  dragon.setHealth(1);
  dragon.setHasTreasure(false);
  dragon.setIsSafe(true);
  playerA.setCurrentTile('a');
  playerB.setCurrentTile('e');
  dragon.setCurrentTile('p'); 
}

void loop() {
  //Player Turn
  Player& currentPlayer = playerA;
  int playerMoves = currentPlayer.getHealth();
  GameTile previousTileData;
  GameTile currentTileData = getMove(playerA.getCurrentTile());
    char key = keypad.getKey();
    if (key != NO_KEY) {
      Serial.print("Key is ");
      Serial.println(key);
      previousTileData = currentTileData;
      currentTileData = getMove(key);
      Serial.print("Current location is ");
      Serial.print(currentTileData.name);
      Serial.print("\n");
      Serial.print("Previous location is ");
      Serial.print(previousTileData.name);
      Serial.print("\n");
      if (moveIsValid(previousTileData, currentTileData)) {
        playSound('m');
        Serial.println("Legal Move");
        currentPlayer.setCurrentTile(currentTileData.name);
        playerMoves--;
      } else {
        playSound('w');
        Serial.println("Ilegal Move");
        playerMoves = 0;
      }
    }
    delay(100);  
}