
#include "images/trump.h"
#include "images/Monster1.h"
#include "images/Monster2.h"
#include "images/Monster3.h"
#include "logic.h"
#include "gba.h"
#include <stdlib.h>

void initializeAppState(AppState* appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    Human *human = malloc(sizeof(struct Human));
    Brick *brick = malloc(sizeof (struct Brick));
    brick->isThrown = 0;
    Monster_entity *monster = malloc(sizeof(struct Monster_entity));
    Human humandata = {100,HEIGHT - TRUMP_HEIGHT,0,0,0,100,0,0, trump};
    appState->score = 0;
    *human = humandata;
    appState->gameOver = 0;
    appState->human = human;
    appState->monster = monster;
    appState->level = 0;
    appState->brick = brick;
    const u16 *lol = Monster1;
    int topOfTrump = HEIGHT - TRUMP_HEIGHT;
    for (int i = 0; i < 10; i++) {
        Monster_entity monster1;
        if (i <= 3) {
                monster1 = (Monster_entity) {0,topOfTrump,0,0,0,0,3,10, lol};
            } else if (i <= 6) {
                monster1 = (Monster_entity) {0,topOfTrump,0,0,0,0,3,25, Monster2};
            } else if (i <= 10) {
                monster1 = (Monster_entity) {0,topOfTrump,0,0,0,0,3,50, putin};
            }
            appState->MonsterList[i] = monster1;
        }
    }
    


// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);

// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that vblank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */


    AppState nextState = *currentAppState;
    Human *human = currentAppState->human;
    Brick *brick = currentAppState->brick;
    //Monster_entity *currentAppState->monster = currentAppState->monster;
    //left
    human->x += human->velx;
    human->y += human->vely;
    if (human->inContact > 20) {
        if (human->inContact % 3 == 2) {
            human->health--;
            if (nextState.level > 3) {
                human->health--;
            }
            if (nextState.level > 6) {
                human->health--;
            }
            if (nextState.level > 9) {
                human->health --;
            }
        }
    }
    if (human->y < HEIGHT - TRUMP_HEIGHT) {
        human->vely += 1;
    }
    if (human->y > HEIGHT - TRUMP_HEIGHT) {;
        human->vely = 0;
        human->y = HEIGHT - TRUMP_HEIGHT;
    }
    if (human->x <= 0) {
        human->velx = 0;
        human->x = 0;
    }
    if (human->x >= WIDTH-TRUMP_WIDTH) {
        human->velx = 0;
        human->x = WIDTH-TRUMP_WIDTH;
    }
    //human attack counter, updates each cycle
    if (human->attack > 0) {
        human->attack--;
    }

    if (human->inContact && abs(human->y-120) < 3) {
        human->y = 120;
        human->vely = 0;
    }


    if (KEY_DOWN(BUTTON_RIGHT, keysPressedNow)) {
        if (human->velx < 2 && ((human->y == HEIGHT - TRUMP_HEIGHT) || human->inContact)) {
            human->facing = 1;
            human->velx++;
            human->x++;
        }

    } else if (KEY_DOWN(BUTTON_LEFT, keysPressedNow)) {
        if (human->velx > -2 && ((human->y == HEIGHT - TRUMP_HEIGHT) || human->inContact)){
            human->facing = 0;
            human->velx--;
            human->x--;
        }
    }
    if (KEY_JUST_PRESSED(BUTTON_UP, keysPressedNow, keysPressedBefore)) {
        if ((human->vely <= 0 && human->y == HEIGHT - TRUMP_HEIGHT) 
            || (human->inContact && human->y == HEIGHT - TRUMP_HEIGHT*2)) {
            human->vely -= 10;
        }
    } else if (KEY_DOWN(BUTTON_DOWN, keysPressedNow)) {
        if (human->vely <= 0 && human->y == HEIGHT - TRUMP_HEIGHT) {
            human->velx = 0;
            human->vely = 0;
        }
    }
    //a roll
    if (KEY_JUST_PRESSED(BUTTON_A, keysPressedNow, keysPressedBefore)) {
        if (!brick->isThrown) {
            brick->x = human->x;
            brick->y = human->y + 5;
            brick->isThrown = 1;
            brick->direction = human->facing*3;
        }
    }

    

    //b attack
    if (KEY_JUST_PRESSED(BUTTON_B, keysPressedNow, keysPressedBefore)) {
        if (human->attack == 0) {
            human->attack = 100;
        }
    }

    //brick update
    if (brick->isThrown) {
        if (brick->x <= 0 || brick->x > 230) {
            brick->isThrown = 0;
        }
        brick->x += brick->direction + brick->direction  - 3;
    }
    
    //make monsters.
    if (nextState.level == 0) {
        nextState.level = 1;
        nextState.numMonsters = 1;
        *nextState.monster = nextState.MonsterList[0];
    }

    //monsters chasing
    //int diffFromHuman = 0;
    //int deltax = 0;
    nextState.numDead = 0;
    for (int i = nextState.numMonsters - 1; i < nextState.numMonsters; i++) {
        int diffFromHuman = (human->x - currentAppState->monster->x);
        //if monster is dead, go to the next one.
        if (currentAppState->monster->isDead) {
            nextState.numDead++;
            continue;
        } else if (currentAppState->monster->health <= 0) {
            nextState.score += 10;
            currentAppState->monster->isDead = 1;
            continue;
        }
        //checks if monsters in contact with sword
        if ((human->attack > 60) && abs(human->y - currentAppState->monster->y) < 3) {
            if ((human->facing == 1) && (diffFromHuman >= -20) 
                && (diffFromHuman <= 0)) {
                currentAppState->monster->health--;
            } else if ((human->facing == 0) && (diffFromHuman >= 0) 
                && (diffFromHuman <= 20)) {
                currentAppState->monster->health--;
            }
        }
        //check if monster is in contact with brick
        if (abs(brick->x - currentAppState->monster->x) <= 5 &&
            (currentAppState->monster->y - brick->y) < 0 &&
            (currentAppState->monster->y - brick->y) > -20 &&
            brick->isThrown) {
                currentAppState->monster->health -= 2;
                brick->isThrown = 0;
        }

        //checks if in contact with the block.
        int deltax = 0;
        if (abs(diffFromHuman) <= 20) {
            human->inContact += 1;
            if (human->y == currentAppState->monster->y) {
                if (diffFromHuman < 0) {
                    deltax += diffFromHuman + 20;
                } else if ((diffFromHuman) > 0) {
                    deltax += diffFromHuman - 20;
                }
            }
        //move monster if its to the right of human
        } else {
            human->inContact = 0;
            if ((diffFromHuman) > 0) {
                deltax = rand()%3;
            }
            //move monster if its to the left of human
            else if ((diffFromHuman) < 0) {
                 deltax =  -rand()%3;
            }
        }

        currentAppState->monster->x += deltax;
        if (currentAppState->monster->x <= 0) {
            currentAppState->monster->velx = 0;
            currentAppState->monster->x = 0;
        } else if (currentAppState->monster->x >= WIDTH-TRUMP_WIDTH) {
            currentAppState->monster->velx = 0;
            currentAppState->monster->x = WIDTH-TRUMP_WIDTH;
        }
    }

    //level up
    //if all monsters are dead, then level up.
    if (nextState.numDead) {
        nextState.level++;
        nextState.numMonsters = nextState.level;
        nextState.numDead = 0;
        for (int i = nextState.numMonsters - 1; i < nextState.numMonsters; i++) {
            *nextState.monster = nextState.MonsterList[i];
        }
    }
    if (nextState.level == 11) {
        nextState.gameOver = 1;
    }
    if (nextState.human->health <= 0) {
        nextState.gameOver = 1;
    }
    return nextState;
}
