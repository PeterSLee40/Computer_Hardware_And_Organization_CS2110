#include "graphics.h"
#include "images/background.h"
#include "logic.h"
#include <stdio.h>
#include "images/trump.h"

//Author: Peter Lee Plee99

//#include "gba.h"
//#include "images/Monster1"
//d#include "animals.h"
// TA-TODO: Include any header files for images generated by nin10kit.
// Example for the provided garbage image:
//#include "images/garbage.h"

// TA-TODO: Add any draw/undraw functions for sub-elements of your app here.
// For example, for a snake game, you could have a drawSnake function
// or a drawFood function
//
// e.g.:
// static void drawSnake(Snake* snake);
// static void drawFood(Food* food);
/*
static void drawMonster1(Monster1* monster1) {

}
*/
//static void drawMonster2(Monster2* monster1);
//static void drawMonster3(Monster3* monster1);

// This function will be used to draw everything about the app
// including the background and whatnot.
char welcome[40] = "Welcome to Klaus' haunted House";
char start[40] = "Press select to begin your quest.";
char controls[40] = "Use Arrow keys to move, A & B to attack";
char instructions1[40] = "Stand too near, the monster will strike";
char instructions2[45] = "Retake Klaus with a brick & lightsabre!";


char score[8] = "Score:";
char health[8] = "Health:";
char win[40] = "CONGRATULATIONS! you somehow Won!";
char loss[40] = "OH NO! you got dead and You lose!";


char again[40] = "Press select to restart the game.";
char finalscore[30] = "Your final score was:";
char scorenumber[6];
char healthNumber[6];
char finalscorenumber[7];
void drawStartState(AppState *state) {
    fillScreenDMA(WHITE);
    drawString(5, 20, welcome, GRAY);
    drawString(5, 40, controls, GRAY);
    drawString(5, 60, instructions1, GRAY);
    drawString(5, 80, instructions2, GRAY);
    drawString(5, 100, start, GRAY);
    UNUSED(state);
}


void fullDrawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.
    drawFullScreenImageDMA(background);
    drawRectDMA(160,0,80,10,BLACK);
    drawString(160, 1, score,WHITE);
    Human *human = state->human;
    drawImageDMA(human->x,human->y,10,10,human->image);
    drawRectDMA(161,1,79,10,BLACK);
    drawString(160, 1, score,WHITE);

    drawRectDMA(161,11,79,10,BLACK);
    drawString(161, 11, health, WHITE);
}

// This function will be used to undraw (i.e. erase) things that might
// move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state) {
    sprintf(healthNumber, "%i", state->human->health);
    sprintf(scorenumber, "%i", state->score);
    drawRectDMA(200,1,40,20,BLACK);
    drawString(210, 1, scorenumber, WHITE);
    drawString(210, 11, healthNumber, WHITE);
    drawString(210, 1, scorenumber, WHITE);
    drawString(210, 11, healthNumber, WHITE);
    undrew(state->human->y - 20, state->human->x - 15, 50, 50, background);
    Monster_entity cur = *state->monster;
    undrew(cur.y, cur.x - 5, 30, 20, background);
    undrew(state->brick->y - 2, state->brick->x - 5, 20, 15, background);
}

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.
    drawString(210, 1, scorenumber, WHITE);
    drawString(210, 11, healthNumber, WHITE);
    drawString(210, 1, scorenumber, WHITE);
    drawString(210, 11, healthNumber, WHITE);

    Human *human = state->human;
    Brick *brick = state->brick;
    if (brick->isThrown) {
        drawRectDMA(brick->x, brick->y - 2,  10, 5, RED);
    }

    if (human->attack > 60) {
        if (!human->facing) {
            drawRectDMA(human->x - 14, human->y + 10, 14, 4, GREEN);
        } else {
            drawRectDMA(human->x + 20, human->y + 10, 14, 4, GREEN);
        }
    }
    for (int i = state->numMonsters - 1; i < state->numMonsters; i++) {
    	Monster_entity *cur = state->monster;
    	if (cur->health > 0) {
    		drawImageDMA(cur->x, cur->y, 20, 20, cur->image);
    	}
    }
    if (human->facing) {
        drawImageDMAflip(human->x,human->y,TRUMP_WIDTH,TRUMP_HEIGHT,human->image);
    } else {
        drawImageDMA(human->x,human->y,TRUMP_WIDTH,TRUMP_HEIGHT,human->image);
    }
}
//draws winning condition
void drawWin(AppState *state) {
    fillScreenDMA(GREEN);
    drawString(10, 40, win, BLACK);
    drawString(10, 60, again, BLACK);
    drawString(10, 80, finalscore, BLACK);
    sprintf(finalscorenumber, "%i", state->score + state->human->health);
    drawString(140, 80, finalscorenumber, BLACK);
    UNUSED(state);
}
//draws losing condition
void drawLoss(AppState *state) {
    fillScreenDMA(RED);
    drawString(10, 40, loss, BLACK);
    drawString(10, 60, again, BLACK);
    drawString(10, 80, finalscore, BLACK);
    sprintf(finalscorenumber, "%i", state->score + state->human->health);
    drawString(140, 80, finalscorenumber, BLACK);
    UNUSED(state);
}