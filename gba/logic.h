#ifndef LOGIC_SEEN
#define LOGIC_SEEN
#include "gba.h"


//#define currentMonster  nextState.MonsterList[i]

typedef struct Monster_entity {
  int x;
  int y;
  int velx;
  int vely;
  int isDead;
  int attack;
  int frequency;
  int health;
  const u16 *image;
} Monster_entity;


typedef struct Human {
  int x;
  int y;
  int velx;
  int vely;
  int attack;
  int health;
  int facing;
  int inContact;
  const u16 *image;
} Human;

typedef struct Brick {
  int x;
  int y;
  int velx;
  int isThrown;
  int direction;
} Brick;

typedef struct AppState {
    // Store whether or not the game is over in this member:
    int gameOver;
    int money;
    int score;
    int level;
    struct Brick *brick;
    struct Human *human;
    int numMonsters;
    int numDead;
    struct Monster_entity MonsterList[10];
    struct Monster_entity *monster;
    /*
    * TA-TODO: Add any logical elements you need to keep track of in your app.
    *
    * For example, for a Snake game, those could be:
    *
    * Snake snake;
    * Food foods[10];
    * int points;
    *
    */

} AppState;

/*
* TA-TODO: Add any additional structs that you need for your app.
*
* For example, for a Snake game, one could be:
*
* typedef struct {
*   int heading;
*   int length;
*   int x;
*   int y;
* } Snake;
*
*/




// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

// If you have anything else you need accessible from outside the logic.c
// file, you can add them here. You likely won't.

#endif
