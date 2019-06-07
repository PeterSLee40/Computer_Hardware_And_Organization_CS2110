#include "gba.h"
#include <stdio.h>
#include <time.h> 
//Author: Peter Lee Plee99
volatile unsigned short *videoBuffer = (volatile unsigned short *)0x6000000;
u32 vBlankCounter = 0;

void waitForVBlank(void) {
    // TA-TODO: IMPLEMENT
    // Write a while loop that loops until we're NOT in vBlank anymore:
    // (This prevents counting one vblank more than once if your app is too fast)
    while (*SCANLINECOUNTER < HEIGHT)
    // Write a while loop that keeps going until we're in vBlank:
    while(*SCANLINECOUNTER > HEIGHT)

    // Finally, increment the vBlank counter:
    vBlankCounter++;

}

static int __qran_seed= 42;
static int qran(void) {
    __qran_seed= 1664525*__qran_seed+1013904223;
    return (__qran_seed>>16) & 0x7FFF;
}

int randint(int min, int max) {
    return (qran()*(max-min)>>15)+min;
}

void setPixel(int x, int y, u16 color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        int index = OFFSET(y,x,WIDTH);
        videoBuffer[index] = color;
    }
}

void drawRectDMA(int x, int y, int width, int height, volatile u16 color) {
    // TA-TODO: IMPLEMENT
    for (int i = 0; i < height; i++) {
        if (x > 0 && y > 0 && x < WIDTH && y < HEIGHT) {
            DMA[3].src = &color;
            DMA[3].dst = videoBuffer + OFFSET(y+i,x,WIDTH);
            DMA[3].cnt = 0;
            DMA[3].cnt = width  | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON;
        }
    }
}
void drawRect(int x, int y, int width, int height, volatile u16 color) {
    // TA-TODO: IMPLEMENT
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            videoBuffer[OFFSET(y + i, x +j,WIDTH)] = color;
        }
    }
}

void drawFullScreenImageDMA(const u16 *image) {
    // TA-TODO: IMPLEMENT
    DMA[3].src = image;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = WIDTH*HEIGHT | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
}

void drawImageDMA(int x, int y, int width, int height, const u16 *image) {
    // TA-TODO: IMPLEMENT
    for (int i = 0; i < height; i++) {
        DMA[3].src = image + i*width;
        DMA[3].dst = (videoBuffer + OFFSET(y+i,x,WIDTH));
        DMA[3].cnt = width  | DMA_DESTINATION_INCREMENT| DMA_SOURCE_INCREMENT | DMA_ON;
    }

}
void drawImageDMAflip(int x, int y, int width, int height, const u16 *image) {
    // TA-TODO: IMPLEMENT
    for (int i = 0; i < height; i++) {
        DMA[3].src = image + (i+1)*width;
        DMA[3].dst = (videoBuffer + OFFSET(y+i,x,WIDTH));
        DMA[3].cnt = width  | DMA_DESTINATION_INCREMENT| DMA_SOURCE_DECREMENT| DMA_ON;
    }

}

void fillScreenDMA(volatile u16 color) {
    // TA-TODO: IMPLEMENT
    DMA[3].src = &color;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = 0;
    DMA[3].cnt = WIDTH*HEIGHT  | DMA_SOURCE_FIXED | DMA_ON; 
}

void drawChar(int col, int row, char ch, u16 color) {
    for(int r = 0; r<8; r++) {
        for(int c=0; c<6; c++) {
            if(fontdata_6x8[OFFSET(r, c, 6) + ch*48]) {
                setPixel(col+c, row+r, color);
            }
        }
    }
}

void drawString(int col, int row, char *str, u16 color) {
    while(*str) {
        drawChar(col, row, *str++, color);
        col += 6;
    }
}


void drawCenteredString(int x, int y, int width, int height, char *str, u16 color) {
    u32 len = 0;
    char *strCpy = str;
    while (*strCpy) {
        len++;
        strCpy++;
    }

    u32 strWidth = 6 * len;
    u32 strHeight = 8;

    int col = x + ((width - strWidth) >> 1);
    int row = y + ((height - strHeight) >> 1);
    drawString(col, row, str, color);
}

void undrew(int r, int c, int width, int height, const u16 *image) {
    for (int row = 0; row < height; ++row) {
        DMA[3].src = image + OFFSET(r + row, c, WIDTH);
        DMA[3].dst = videoBuffer + OFFSET(r + row, c, WIDTH);
        DMA[3].cnt = width | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT |
                                 DMA_ON;
    }
}