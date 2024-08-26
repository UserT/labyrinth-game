#include <iostream>
#include <string>
#include <Keypad.h>
#include <ESP8266TrueRandom.h>

// Define button matrix inputs
const byte ROWS = 4;  // number of rows
const byte COLS = 4;  // number of columns
char keys[ROWS][COLS] = {
  { 'a', 'b', 'c', 'd' },
  { 'e', 'f', 'g', 'h' },
  { 'i', 'j', 'k', 'l' },
  { 'm', 'n', 'o', 'p' }
};

//Full gameboard - ASCII #33-#96
//const byte ROWS = 8;  // number of rows
//const byte COLS = 8;  // number of columns
//char keys[ROWS][COLS] = {
//  { '!', '"', '#', '$', '%', '&', ''', '(' },
//  { ')', '*', '+', ',', '-', '.', '/', '0' },
//  { '1', '2', '3', '4', '5', '6', '7', '8' },
//  { '9', ':', ';', '<', '=', '>', '?', '@' },
//  { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' },
//  { 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P' },
//  { 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X' },
//  { 'Y', 'Z', '[', '\', ']', '^', '_', '`' }
//};

byte rowPins[ROWS] = { 14, 12, 13, 5 };  //, 12, 13, 15}; // row pinouts of the keypad R1 = D8, R2 = D7, R3 = D6, R4 = D5
byte colPins[COLS] = { 4, 0, 2, 16 };    //, 0, 2, 16};    // column pinouts of the keypad C1 = D4, C2 = D3, C3 = D2
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Setup speaker
const int SpeakerPin = 15;  // Change this to the pin you connected the speaker to

class GameTile {
public:
  char name;
  bool hasPlayerA;
  bool hasPlayerB;
  bool hasTreasure;
  bool hasDragon;
  bool isBaseA;
  bool isBaseB;
  bool isDen;
  bool isExplored;
  bool hasWallEast;
  bool hasWallWest;
  bool hasWallNorth;
  bool hasWallSouth;

  // Constructors
  GameTile()
    : name(' '), hasPlayerA(false), hasPlayerB(false), hasTreasure(false), hasDragon(false), isBaseA(false), isBaseB(false), isDen(false), isExplored(false), hasWallEast(true), hasWallWest(true), hasWallNorth(true), hasWallSouth(true) {}

  // Getter Methods
  char getName() const {
    return name;
  }
  bool getHasPlayerA() const {
    return hasPlayerA;
  }
  bool getHasPlayerB() const {
    return hasPlayerB;
  }
  bool getHasTreasure() const {
    return hasTreasure;
  }
  bool getHasDragon() const {
    return hasDragon;
  }
  bool getIsBaseA() const {
    return isBaseA;
  }
  bool getIsBaseB() const {
    return isBaseB;
  }
  bool getIsDen() const {
    return isDen;
  }
  bool getIsExplored() const {
    return isExplored;
  }
  bool getHasWallEast() const {
    return hasWallEast;
  }
  bool getHasWallWest() const {
    return hasWallWest;
  }
  bool getHasWallNorth() const {
    return hasWallNorth;
  }
  bool getHasWallSouth() const {
    return hasWallSouth;
  }

  // Setter Methods
  void setName(char newName) {
    name = newName;
  }
  void setHasPlayerA(bool newStatus) {
    hasPlayerA = newStatus;
  }
  void setHasPlayerB(bool newStatus) {
    hasPlayerB = newStatus;
  }
  void setHasTreasure(bool newStatus) {
    hasTreasure = newStatus;
  }
  void setHasDragon(bool newStatus) {
    hasDragon = newStatus;
  }
  void setIsBaseA(bool newStatus) {
    isBaseA = newStatus;
  }
  void setIsBaseB(bool newStatus) {
    isBaseB = newStatus;
  }
  void setIsDen(bool newStatus) {
    isDen = newStatus;
  }
  void setIsExplored(bool newStatus) {
    isExplored = newStatus;
  }
  void setHasWallEast(bool newStatus) {
    hasWallEast = newStatus;
  }
  void setHasWallWest(bool newStatus) {
    hasWallWest = newStatus;
  }
  void setHasWallNorth(bool newStatus) {
    hasWallNorth = newStatus;
  }
  void setHasWallSouth(bool newStatus) {
    hasWallSouth = newStatus;
  }
};

class Player {
public:
  std::string name;
  int health;
  char currentTile;
  bool hasTreasure;
  bool isSafe;

  // Constructors
  Player()
    : name(""), health(0), currentTile(' '), hasTreasure(false), isSafe(true) {}

  // Getters and Setters
  std::string getName() {
    return name;
  }
  void setName(const std::string& newName) {
    name = newName;
  }

  int getHealth() {
    return health;
  }
  void setHealth(int newHealth) {
    health = newHealth;
  }

  char getCurrentTile() {
    return currentTile;
  }
  void setCurrentTile(char newTile) {
    currentTile = newTile;
  }

  bool getHasTreasure() {
    return hasTreasure;
  }
  void setHasTreasure(bool value) {
    hasTreasure = value;
  }

  bool getIsSafe() {
    return isSafe;
  }
  void setIsSafe(bool value) {
    isSafe = value;
  }
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

bool randomBool() {
  return rand() > (RAND_MAX / 2);
}

char randomDirection() {
  int numDirection = ESP8266TrueRandom.random() % 4;  // Assuming 0=West, 1=East, 2=North, 3=South
  Serial.print("Random Direction is: ");
  Serial.println(numDirection);
  char direction;
  switch (static_cast<char>(numDirection)) {
    case 0:
      direction = 'w';
      break;
    case 1:
      direction = 'e';
      break;
    case 2:
      direction = 'n';
      break;
    case 3:
      direction = 's';
      break;
  }
  return direction;
}

void dfs(std::vector<std::vector<GameTile>>& gameBoard, int x, int y, char prevDirection) {
  //Basic Algo:
  //create stack of location data
  //set passed in element to visited
  //put passed in element location data on stack
  //enter the loop: while stack not empty
  //	set current elelment to stack back location (in the vector)
  //	if current has NOT had all directons checked
  //		create bool keep checking is ture
  //		enter loop: while keep checking is true and current has NOT had all directons checked
  //			get next random direction
  //			get next element at random direction
  //			enter loop: If next element is valid and it has not been visited
  //				remove walls
  //				set next element visited to true
  //				put push next element on stack
  //				set keep checking to false
  //	else pop the element off the stack


  //stack<std::pair<int, int>> tracking;
  //tracking.push({x,y});
  if (x >= 0 && x < 4 && y >= 0 && y < 4 && !gameBoard[x][y].getIsExplored()) {
    gameBoard[x][y].setIsExplored(true);
    // Randomly choose a direction to move next
    char nextDirection = randomDirection();
    Serial.println(nextDirection);

    // Remove the wall in the opposite direction of the previous move
    switch (prevDirection) {
      case 'w':
        gameBoard[x][y].setHasWallEast(false);
        break;
      case 'e':
        gameBoard[x][y].setHasWallWest(false);
        break;
      case 'n':
        gameBoard[x][y].setHasWallSouth(false);
        break;
      case 's':
        gameBoard[x][y].setHasWallNorth(false);
        break;
    }

    // Move to the next tile in the chosen direction
    int dx, dy;
    switch (nextDirection) {
      case 'w':
        dx = -1;
        dy = 0;
        break;
      case 'e':
        dx = 1;
        dy = 0;
        break;
      case 'n':
        dx = 0;
        dy = -1;
        break;
      case 's':
        dx = 0;
        dy = 1;
        break;
    }
    dfs(gameBoard, x + dx, y + dy, nextDirection);
  }
}

void createMaze(std::vector<std::vector<GameTile>>& gameBoard) {
  //dfs(gameBoard, 0, 0, 'e'); // Start DFS from the top-left corner moving right
  //create gameboard outline and name each tile
  //char name = 'a';
  //for (int i = 0; i < gameBoard.size(); i++){
  //  for (int j = 0; j < gameBoard[i].size(); j++){
  //    //set name
  //    gameBoard[i][j].setName(name);
  //    name++;
  //    //is top of gameboard
  //    if (i == 0) {
  //      gameBoard[i][j].setHasWallNorth(true);
  //    }
  //    //is bottom of gameboard
  //    if (i == (rows-1) ){
  //      gameBoard[i][j].setHasWallSouth(true);
  //    }
  //    //is left edge of gameboard
  //    if (j == 0) {
  //      gameBoard[i][j].setHasWallWest(true);
  //    }
  //    //is right edge of gameboard
  //    if (j == (cols-1) ){
  //      gameBoard[i][j].setHasWallEast(true);
  //    }
  //  }
  //}

  //Stub in a pre-configured map - will be random eventually.
  gameBoard[0][0].setName('a');
  gameBoard[0][0].setHasWallEast(false);

  gameBoard[0][1].setName('b');
  gameBoard[0][1].setHasWallEast(false);
  gameBoard[0][1].setHasWallWest(false);
  gameBoard[0][1].setHasWallSouth(false);

  gameBoard[0][2].setName('c');
  gameBoard[0][2].setHasWallEast(false);
  gameBoard[0][2].setHasWallWest(false);
  gameBoard[0][2].setHasWallSouth(false);

  gameBoard[0][3].setName('d');
  gameBoard[0][3].setHasWallWest(false);
  gameBoard[0][3].setHasWallSouth(false);

  gameBoard[1][0].setName('e');
  gameBoard[1][0].setHasWallEast(false);
  gameBoard[1][0].setHasWallSouth(false);

  gameBoard[1][1].setName('f');
  gameBoard[1][1].setHasWallWest(false);
  gameBoard[1][1].setHasWallNorth(false);
  gameBoard[1][1].setHasWallSouth(false);

  gameBoard[1][2].setName('g');
  gameBoard[1][2].setHasWallNorth(false);

  gameBoard[1][3].setName('h');
  gameBoard[1][3].setHasWallNorth(false);
  gameBoard[1][3].setHasWallSouth(false);

  gameBoard[2][0].setName('i');
  gameBoard[2][0].setHasWallNorth(false);
  gameBoard[2][0].setHasWallSouth(false);

  gameBoard[2][1].setName('j');
  gameBoard[2][1].setHasWallEast(false);
  gameBoard[2][1].setHasWallNorth(false);
  gameBoard[2][1].setHasWallSouth(false);

  gameBoard[2][2].setName('k');
  gameBoard[2][2].setHasWallWest(false);
  gameBoard[2][2].setHasWallSouth(false);

  gameBoard[2][3].setName('l');
  gameBoard[2][3].setHasWallNorth(false);
  gameBoard[2][3].setHasWallSouth(false);

  gameBoard[3][0].setName('m');
  gameBoard[3][0].setHasWallEast(false);
  gameBoard[3][0].setHasWallNorth(false);

  gameBoard[3][1].setName('n');
  gameBoard[3][1].setHasWallWest(false);
  gameBoard[3][1].setHasWallNorth(false);

  gameBoard[3][2].setName('o');
  gameBoard[3][2].setHasWallEast(false);
  gameBoard[3][2].setHasWallNorth(false);

  gameBoard[3][3].setName('p');
  gameBoard[3][3].setHasWallWest(false);
  gameBoard[3][3].setHasWallNorth(false);
}

void printGame() {
  Serial.print("\n Game Board");
  for (int i = 0; i < gameBoard.size(); i++) {
    Serial.print('\n');
    for (int j = 0; j < gameBoard[i].size(); j++) {
      if (!gameBoard[i][j].getHasWallEast() & gameBoard[i][j].getHasWallWest() & gameBoard[i][j].getHasWallNorth() & gameBoard[i][j].getHasWallSouth()) {
        Serial.print("[¯_");
      } else if (!gameBoard[i][j].getHasWallEast() & !gameBoard[i][j].getHasWallWest() & gameBoard[i][j].getHasWallNorth() & !gameBoard[i][j].getHasWallSouth()) {
        Serial.print("¯¯¯");
      } else if (!gameBoard[i][j].getHasWallEast() & gameBoard[i][j].getHasWallWest() & gameBoard[i][j].getHasWallNorth() & !gameBoard[i][j].getHasWallSouth()) {
        Serial.print("[¯¯");
      } else if (gameBoard[i][j].getHasWallEast() & !gameBoard[i][j].getHasWallWest() & gameBoard[i][j].getHasWallNorth() & !gameBoard[i][j].getHasWallSouth()) {
        Serial.print("¯¯]");
      } else if (gameBoard[i][j].getHasWallEast() & !gameBoard[i][j].getHasWallWest() & !gameBoard[i][j].getHasWallNorth() & !gameBoard[i][j].getHasWallSouth()) {
        Serial.print("  ]");
      } else if (!gameBoard[i][j].getHasWallEast() & gameBoard[i][j].getHasWallWest() & !gameBoard[i][j].getHasWallNorth() & !gameBoard[i][j].getHasWallSouth()) {
        Serial.print("[  ");
      } else if (gameBoard[i][j].getHasWallEast() & gameBoard[i][j].getHasWallWest() & !gameBoard[i][j].getHasWallNorth() & gameBoard[i][j].getHasWallSouth()) {
        Serial.print("[_]");
      } else if (gameBoard[i][j].getHasWallEast() & gameBoard[i][j].getHasWallWest() & !gameBoard[i][j].getHasWallNorth() & !gameBoard[i][j].getHasWallSouth()) {
        Serial.print("[ ]");
      } else if (!gameBoard[i][j].getHasWallEast() & !gameBoard[i][j].getHasWallWest() & !gameBoard[i][j].getHasWallNorth() & gameBoard[i][j].getHasWallSouth()) {
        Serial.print("___");
      } else if (gameBoard[i][j].getHasWallEast() & !gameBoard[i][j].getHasWallWest() & !gameBoard[i][j].getHasWallNorth() & gameBoard[i][j].getHasWallSouth()) {
        Serial.print("__]");
      } else if (!gameBoard[i][j].getHasWallEast() & gameBoard[i][j].getHasWallWest() & !gameBoard[i][j].getHasWallNorth() & gameBoard[i][j].getHasWallSouth()) {
        Serial.print("[__");
      } else if (gameBoard[i][j].getHasWallEast() & gameBoard[i][j].getHasWallWest() & gameBoard[i][j].getHasWallNorth() & gameBoard[i][j].getHasWallSouth()) {
        Serial.print("[■]");
      } else {
        Serial.print("   ");
      }
    }
  }
  Serial.print('\n');
}

void playSound(char sound) {
  switch (sound) {
    case 'n':  //Next
      tone(SpeakerPin, 440, 100);
      delay(100);
      noTone(SpeakerPin);
      tone(SpeakerPin, 220, 100);
      break;
    case 'w':  //Wall
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
    case 't':  //Treasure
      tone(SpeakerPin, 130.8, 100);
      delay(150);
      noTone(SpeakerPin);
      tone(SpeakerPin, 146.8, 100);
      delay(150);
      noTone(SpeakerPin);
      tone(SpeakerPin, 164.8, 100);
      delay(150);
      noTone(SpeakerPin);
      tone(SpeakerPin, 174.6, 100);
      break;
    case 'i':  //Illegal Move
      tone(SpeakerPin, 440, 100);
      delay(100);
      noTone(SpeakerPin);
      tone(SpeakerPin, 523.3, 500);
      break;
    case 'm':  //Warrior Moves
      tone(SpeakerPin, 440, 100);
      break;
    case '1':  //Warrior 1
      tone(SpeakerPin, 110, 100);
      delay(150);
      noTone(SpeakerPin);
      tone(SpeakerPin, 164.8, 600);
      break;
    case '2':  //Warrior 2
      tone(SpeakerPin, 164.8, 100);
      delay(150);
      noTone(SpeakerPin);
      tone(SpeakerPin, 110, 600);
      break;
    case 'd':  //Dragon Wakes
      break;
    case 'f':  //Dragon Flying
      break;
    case 'a':  //Dragon Attacks
      break;
    case 'v':  //Winner/victory
      tone(SpeakerPin, 164.8, 100);
      delay(150);
      noTone(SpeakerPin);
      tone(SpeakerPin, 164.8, 100);
      delay(150);
      noTone(SpeakerPin);
      tone(SpeakerPin, 164.8, 100);
      delay(150);
      noTone(SpeakerPin);
      tone(SpeakerPin, 164.8, 400);
      delay(550);
      tone(SpeakerPin, 110, 100);
      delay(150);
      noTone(SpeakerPin);
      tone(SpeakerPin, 130.8, 100);
      delay(150);
      noTone(SpeakerPin);
      tone(SpeakerPin, 164.8, 100);
      delay(150);
      noTone(SpeakerPin);
      tone(SpeakerPin, 146.8, 100);
      delay(150);
      noTone(SpeakerPin);
      tone(SpeakerPin, 164.8, 500);
      delay(550);
      noTone(SpeakerPin);
      break;
    case 'g':  //Game Over/Defeat
      break;
  }
}

GameTile* getMove(char move) {
  GameTile moveTile;
  switch (move) {
    case 'a':
      return &gameBoard[0][0];
      break;
    case 'b':
      return &gameBoard[0][1];
      break;
    case 'c':
      return &gameBoard[0][2];
      break;
    case 'd':
      return &gameBoard[0][3];
      break;
    case 'e':
      return &gameBoard[1][0];
      break;
    case 'f':
      return &gameBoard[1][1];
      break;
    case 'g':
      return &gameBoard[1][2];
      break;
    case 'h':
      return &gameBoard[1][3];
      break;
    case 'i':
      return &gameBoard[2][0];
      break;
    case 'j':
      return &gameBoard[2][1];
      break;
    case 'k':
      return &gameBoard[2][2];
      break;
    case 'l':
      return &gameBoard[2][3];
      break;
    case 'm':
      return &gameBoard[3][0];
      break;
    case 'n':
      return &gameBoard[3][1];
      break;
    case 'o':
      return &gameBoard[3][2];
      break;
    case 'p':
      return &gameBoard[3][3];
      break;
  }
  return &moveTile;
}

bool moveIsValid(GameTile* previousTile, GameTile* currentTile) {
  Serial.print(previousTile->name);
  Serial.print(" to ");
  Serial.print(currentTile->name);
  Serial.print("\n");
  if (!previousTile->hasWallEast && !currentTile->hasWallWest && (currentTile->name == (previousTile->name + 1))) { return true; }  //valid space is in front
  else if (!previousTile->hasWallWest && !currentTile->hasWallEast && (currentTile->name == (previousTile->name - 1))) { return true; }  //valid space is behind
  else if (!previousTile->hasWallNorth && !currentTile->hasWallSouth && (currentTile->name == (previousTile->name - cols))) { return true; }  //valid space is above
  else if (!previousTile->hasWallSouth && !currentTile->hasWallNorth && (currentTile->name == (previousTile->name + cols))) { return true; }  //valid space is below
  else { return false; }  //space is invalid  
}

bool moveIsPossible(char previousTileName, char currentTileName) {
  if ((currentTileName == (previousTileName + 1)) || (currentTileName == (previousTileName - 1)) || (currentTileName == (previousTileName - cols)) || (currentTileName == (previousTileName + cols))) {
    return true;
  } else {
    return false;
  }
}

std::pair<int, int> findXY(char tileName) {
  for (int i = 0; i < gameBoard.size(); ++i) {
    for (int j = 0; j < gameBoard[i].size(); ++j) {
      if (gameBoard[i][j].getName() == tileName) {
        return { i, j };
      }
    }
  }
  return { -1, -1 };
}

void dragonMove(char dragonLocation, char dragonDestination) {
  std::pair<int, int> dragonLocCoords = findXY(dragonLocation);
  std::pair<int, int> dragonDestCoords = findXY(dragonDestination);

  // Check if the path is horizontal, vertical, or diagonal
  if (dragonLocCoords.first == dragonDestCoords.first) {  // Vertical path
    int y = (dragonDestCoords.second > dragonLocCoords.second) ? 1 : -1;
    dragon.setCurrentTile(gameBoard[dragonLocCoords.first][dragonLocCoords.second + y].name);
  } else if (dragonLocCoords.second == dragonDestCoords.second) {  // Horizontal path
    int x = (dragonDestCoords.first > dragonLocCoords.first) ? 1 : -1;
    dragon.setCurrentTile(gameBoard[dragonLocCoords.first + x][dragonLocCoords.second].name);
  } else {  // Diagonal path
    int dx = (dragonDestCoords.first > dragonLocCoords.first) ? 1 : -1;
    int dy = (dragonDestCoords.second > dragonLocCoords.second) ? 1 : -1;
    dragon.setCurrentTile(gameBoard[dragonLocCoords.first + dx][dragonLocCoords.second + dy].name);
  }
  Serial.print("Dragon to ");
  Serial.println(dragon.getCurrentTile());
}

//Create Game state data
int remainingMoves;
int currentPlayerId = 1;
Player* currentPlayer;
bool dragonAwake;
char denTile;

void setCurrentPlayer(int player) {
  if (player == 1) {
    currentPlayer = &playerA;
  } else if (player == 2) {
    currentPlayer = &playerB;
  } else {
    currentPlayer = &dragon;
  }
}

int distanceBetween(char location1, char location2) {
  std::pair loc1Coords = findXY(location1);
  std::pair loc2Coords = findXY(location2);
  return abs(loc2Coords.first - loc1Coords.first) + abs(loc2Coords.second - loc1Coords.second);
}

//Adding audio clip playback - removed for now to focus on mvp
//AudioGeneratorWAV         *wav = NULL;
//AudioFileSourcePROGMEM    *file_progmem = NULL;
//
//void playBootSound() {
//  file_progmem = new AudioFileSourcePROGMEM(boot_sound, sizeof(boot_sound));
//  wav = new AudioGeneratorWAV();
//  wav->begin(file_progmem, SpeakerPin);
//}

void setDragonsDen() {
  char randomTile = ESP8266TrueRandom.random(97, 113);
  if ((distanceBetween(randomTile, playerA.currentTile) > 3) && (distanceBetween(randomTile, playerB.currentTile) > 3)) {
    getMove(randomTile)->setHasTreasure(true);
    getMove(randomTile)->setHasDragon(true);
    getMove(randomTile)->setIsDen(true);
    denTile = randomTile;
    Serial.print("Dragon Den is: ");
    Serial.println(denTile);
    return;
  } else {
    setDragonsDen();
  }
}

void setup() {
  //Initialize game
  Serial.begin(921600);
  createMaze(gameBoard);
  char setupkey = keypad.getKey();
  //playBootSound();

  //Setup Player A
  while (setupkey == NO_KEY) {
    Serial.println("Waiting for Player 1...");
    setupkey = keypad.getKey();
  }
  getMove(setupkey)->setHasPlayerA(true);
  getMove(setupkey)->setIsBaseA(true);
  playerA.setName("Player A");
  playerA.setHealth(4);
  playerA.setIsSafe(true);
  playerA.setCurrentTile(setupkey);
  playSound('m');
  setupkey = NO_KEY;
  delay(1000);

  //Setup Player B
  playSound('2');
  while (setupkey == NO_KEY) {
    Serial.println("Waiting for Player 2...");
    setupkey = keypad.getKey();
    if (setupkey == playerA.getCurrentTile()) {
      playSound('i');
      Serial.println("Space is already occupied. Try again.");
      setupkey = NO_KEY;
    }
  }
  getMove(setupkey)->setHasPlayerB(true);
  getMove(setupkey)->setIsBaseB(true);
  playerB.setName("Player B");
  playerB.setHealth(4);
  playerB.setCurrentTile(setupkey);
  playerB.setIsSafe(true);
  playSound('m');
  delay(1000);
  setupkey = NO_KEY;

  //Set den location
  setDragonsDen();
  dragon.setName("Dragon");
  dragon.setHealth(1);
  dragon.setHasTreasure(false);
  dragon.setIsSafe(true);

  dragonAwake = false;
  playSound('w');
  printGame();
  Serial.println("The Game Begins!");
}

void loop() {
///////////////////////Turn Setup///////////////////////
  char key = keypad.getKey();
  setCurrentPlayer(currentPlayerId);         //set current player
  if (remainingMoves == 0) {                 //if remaining Moves is 0 then reset for the new player
    remainingMoves = currentPlayer->health;  //set max player moves based on health
  }
  GameTile* previousTileData;
  GameTile* currentTileData = getMove(currentPlayer->getCurrentTile());  //set player location for player
///////////////////////Turn///////////////////////
  if (currentPlayer->name == "Dragon" && dragonAwake) {  //Dragon Turn
    //Find the closest player
    int distanceBetweenPlayerA = distanceBetween(dragon.currentTile, playerA.currentTile);
    int distanceBetweenPlayerB = distanceBetween(dragon.currentTile, playerB.currentTile);
    Player* closestPlayer;
    if (distanceBetweenPlayerA < distanceBetweenPlayerB) {
      closestPlayer = &playerA;
    } else if (distanceBetweenPlayerA > distanceBetweenPlayerB) {
      closestPlayer = &playerB;
    } else {
      if (ESP8266TrueRandom.random() % 2 == 1) {
        closestPlayer = &playerA;
      } else {
        closestPlayer = &playerB;
      }
    }
    // Prioritize Dragons moves
    if (playerA.getIsSafe() && playerB.getIsSafe()) {               // No valid targets
      dragonMove(dragon.currentTile, denTile);                      //return to Den
      remainingMoves--;
    } else if (playerA.getHasTreasure() && !playerA.getIsSafe()) {  //Does player A have the treasure?
      dragonMove(dragon.currentTile, playerA.currentTile);          //Advance on player A
      remainingMoves--;
    } else if (playerB.getHasTreasure() && !playerB.getIsSafe()) {  //Does Player B have the treasure?
      dragonMove(dragon.currentTile, playerB.currentTile);          //Advance on player B
      remainingMoves--;
    } else if (!closestPlayer->getIsSafe()) {                       //Is closest player a valid target?
      dragonMove(dragon.currentTile, closestPlayer->currentTile);   //Advance on closest player
      remainingMoves--;
    } else {
      if (closestPlayer->name == "playerA") {
        dragonMove(dragon.currentTile, playerA.currentTile);  // Go after player A
        remainingMoves--;
      } else {
        dragonMove(dragon.currentTile, playerB.currentTile);  //Go after player B
        remainingMoves--;
      }
    }
  } else {                //Player Turn
    if (key != NO_KEY) {  //check for key press
      Serial.print("Current Player is: ");
      Serial.println(currentPlayerId);
      Serial.print("currentTileData is: ");
      Serial.println(currentPlayer->currentTile);
      Serial.print("Remaining Moves is: ");
      Serial.println(remainingMoves - 1);
      previousTileData = currentTileData;                                   //Track last move
      currentTileData = getMove(key);                                       //use key press to get current location

      if (moveIsPossible(previousTileData->name, currentTileData->name)) {  //was the wrong player moving or did someone bump a button?
        if (moveIsValid(previousTileData, currentTileData)) {               //check that move is valid
          Serial.println("Legal Move");
          currentPlayer->setCurrentTile(currentTileData->name);  //allow move by setting the move as the player location
          if (currentTileData->hasTreasure) {                    //If the Player lands on Treasure
            playSound('t');
            currentTileData->setHasTreasure(false);  //remove treasure from space
            Serial.print("Current tile Has Treasure is: ");
            Serial.println(currentTileData->hasTreasure);
            currentPlayer->setHasTreasure(true);  //give the treasure to the player
            remainingMoves = 0;                   //player turn ends
          } else {                                //otherwise treat as a normal valid move
            playSound('m');
            remainingMoves--;
          }
          //Player Enters Safe Room
          if (currentTileData->isBaseA) {  // and player is playerA
            if (currentPlayer->hasTreasure) {
              playSound('v');
              Serial.println("You Win!");
            }  //If player has treasure play victory sound
          }
        } else {               //otherwise player hit a wall and turn ends
          playSound('w');      //play wall sound
          remainingMoves = 0;  //player turn ends
          Serial.println("Hit a Wall");
        }
      } else {           //accidental button press likely
        playSound('w');  //play wall sound
        Serial.println("Ilegal Move");
      }   
    }
  }
 ///////////////////////Turn End///////////////////////
  //check on dragon
  if ((distanceBetween(currentPlayer->currentTile, dragon.getCurrentTile()) <= 3) && (currentPlayer->name != "Dragon") && !dragonAwake) {
    dragonAwake = true;
    playSound('d');
  }
  if (remainingMoves == 0) {  //check to see if turn is over
    playSound('n');
    Serial.println("Next Player!");
    if (currentPlayerId == 3) {  //check if the player is dragon (3)
      currentPlayerId = 1;       //if the current player is dragon then reset to player 1 turn
    } else {                     //otherwise move to next player
      currentPlayerId++;         //set next player
    }
  }
  delay(500);  //set a delay between moves to account for ghost presses
}