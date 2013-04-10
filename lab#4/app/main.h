#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define IDC_LIFEFORMS   100
#define IDB_SETBTN      101
#define IDB_STARTBTN    102
#define IDB_STOPBTN     103
#define ID_TIMER        104

#define NUMLIFEFORMS ((int) (sizeof lifeforms / sizeof lifeforms[0]))

typedef struct _LFORM {
    int pixel;
    int squares;
    bool** map;
    LPSTR szLabel;
} LFORM;

LFORM lifeforms[] = {
    0, 0, NULL, "Blinker",
    0, 0, NULL, "Glider",
    0, 0, NULL, "Spaceship",
    0, 0, NULL, "Pulsar",
    0, 0, NULL, "Gosper Glider Gun",
    0, 0, NULL, "Draw Some!"
};

COLORREF colors[] = {
    RGB(255, 255, 102), RGB(49, 158, 161), RGB(255, 148, 90), RGB(209, 74, 137), RGB(158, 10, 57),
    RGB(64, 94, 0), RGB(104, 152, 100), RGB(255, 101, 1), RGB(160, 183, 218), RGB(51, 103, 153),
    RGB(255, 198, 41), RGB(139, 119, 181), RGB(255, 123, 41), RGB(0, 130, 182), RGB(255, 33, 81)
};

// In-Game settings
static bool** previousMap = NULL;
static bool** gameMap = NULL;
static int gameSquares = 0;
static int gamePixel = 0;
static int gameSpeed = 10; /* int from 10 to 100 */
static bool addColor;

void game_of_life_initialize() {
    int i, j;

    // Blinker Init
    lifeforms[0].pixel = 25;
    lifeforms[0].squares = 20;
    lifeforms[0].map = (bool**)malloc(sizeof(bool*) * lifeforms[0].squares);
    for(i=0;i<lifeforms[0].squares;i++) lifeforms[0].map[i] = (bool*)malloc(sizeof(bool) * lifeforms[0].squares);
    // Init with 0
    for(i=0;i<lifeforms[0].squares;i++) for(j=0;j<lifeforms[0].squares;j++) lifeforms[0].map[i][j] = 0;
    for(i=0;i<3;i++) {
        lifeforms[0].map[9][5+i]  = 1;
        lifeforms[0].map[9][11+i] = 1;
        lifeforms[0].map[5+i][9]  = 1;
        lifeforms[0].map[11+i][9] = 1;
    }

    // Glider Init
    lifeforms[1].pixel = 25;
    lifeforms[1].squares = 20;
    lifeforms[1].map = (bool**)malloc(sizeof(bool*) * lifeforms[1].squares);
    for(i=0;i<lifeforms[1].squares;i++) lifeforms[1].map[i] = (bool*)malloc(sizeof(bool) * lifeforms[1].squares);
    // Init with 0
    for(i=0;i<lifeforms[1].squares;i++) for(j=0;j<lifeforms[1].squares;j++) lifeforms[1].map[i][j] = 0;
    lifeforms[1].map[1][2] = 1;
    lifeforms[1].map[2][3] = 1;
    lifeforms[1].map[3][1] = 1;
    lifeforms[1].map[3][2] = 1;
    lifeforms[1].map[3][3] = 1;

    // SpaceShip Init
    lifeforms[2].pixel = 20;
    lifeforms[2].squares = 25;
    lifeforms[2].map = (bool**)malloc(sizeof(bool*) * lifeforms[2].squares);
    for(i=0;i<lifeforms[2].squares;i++) lifeforms[2].map[i] = (bool*)malloc(sizeof(bool) * lifeforms[2].squares);
    // Init with 0
    for(i=0;i<lifeforms[2].squares;i++) for(j=0;j<lifeforms[2].squares;j++) lifeforms[2].map[i][j] = 0;
    lifeforms[2].map[10][5] = 1;
    lifeforms[2].map[10][8] = 1;
    lifeforms[2].map[12][5] = 1;
    for(i=0;i<3;i++) {
        lifeforms[2].map[11+i][9] = 1;
        lifeforms[2].map[13][6+i] = 1;
    }

    // Pulsar Init
    lifeforms[3].pixel = 25;
    lifeforms[3].squares = 20;
    lifeforms[3].map = (bool**)malloc(sizeof(bool*) * lifeforms[3].squares);
    for(i=0;i<lifeforms[3].squares;i++) lifeforms[3].map[i] = (bool*)malloc(sizeof(bool) * lifeforms[3].squares);
    // Init with 0
    for(i=0;i<lifeforms[3].squares;i++) for(j=0;j<lifeforms[3].squares;j++) lifeforms[3].map[i][j] = 0;
    for(i=0;i<3;i++) {
        // horizontal segments
        lifeforms[3].map[3][5+i]   = 1;
        lifeforms[3].map[3][11+i]  = 1;
        lifeforms[3].map[8][5+i]   = 1;
        lifeforms[3].map[8][11+i]  = 1;
        lifeforms[3].map[10][5+i]  = 1;
        lifeforms[3].map[10][11+i] = 1;
        lifeforms[3].map[15][5+i]  = 1;
        lifeforms[3].map[15][11+i] = 1;
        // vertical segments
        lifeforms[3].map[5+i][3]   = 1;
        lifeforms[3].map[11+i][3]  = 1;
        lifeforms[3].map[5+i][8]   = 1;
        lifeforms[3].map[11+i][8]  = 1;
        lifeforms[3].map[5+i][10]  = 1;
        lifeforms[3].map[11+i][10] = 1;
        lifeforms[3].map[5+i][15]  = 1;
        lifeforms[3].map[11+i][15] = 1;
    }

    // Gosper Gun Init
    lifeforms[4].pixel = 10;
    lifeforms[4].squares = 50;
    lifeforms[4].map = (bool**)malloc(sizeof(bool*) * lifeforms[4].squares);
    for(i=0;i<lifeforms[4].squares;i++) lifeforms[4].map[i] = (bool*)malloc(sizeof(bool) * lifeforms[4].squares);
    // Init with 0
    for(i=0;i<lifeforms[4].squares;i++) for(j=0;j<lifeforms[4].squares;j++) lifeforms[4].map[i][j] = 0;
    // left square
    lifeforms[4].map[11][8]  = 1;
    lifeforms[4].map[11][9]  = 1;
    lifeforms[4].map[12][8]  = 1;
    lifeforms[4].map[12][9]  = 1;
    // right square
    lifeforms[4].map[9][42]  = 1;
    lifeforms[4].map[9][43]  = 1;
    lifeforms[4].map[10][42] = 1;
    lifeforms[4].map[10][43] = 1;
    // left ship
    lifeforms[4].map[9][20]  = 1;
    lifeforms[4].map[9][21]  = 1;
    lifeforms[4].map[10][19] = 1;
    lifeforms[4].map[10][23] = 1;
    lifeforms[4].map[11][18] = 1;
    lifeforms[4].map[11][24] = 1;
    lifeforms[4].map[12][18] = 1;
    lifeforms[4].map[12][22] = 1;
    lifeforms[4].map[12][24] = 1;
    lifeforms[4].map[12][25] = 1;
    lifeforms[4].map[13][18] = 1;
    lifeforms[4].map[13][24] = 1;
    lifeforms[4].map[14][19] = 1;
    lifeforms[4].map[14][23] = 1;
    lifeforms[4].map[15][20] = 1;
    lifeforms[4].map[15][21] = 1;
    // right ship
    lifeforms[4].map[7][32]  = 1;
    lifeforms[4].map[8][30]  = 1;
    lifeforms[4].map[8][32]  = 1;
    lifeforms[4].map[9][28]  = 1;
    lifeforms[4].map[9][29]  = 1;
    lifeforms[4].map[10][28] = 1;
    lifeforms[4].map[10][29] = 1;
    lifeforms[4].map[11][28] = 1;
    lifeforms[4].map[11][29] = 1;
    lifeforms[4].map[12][30] = 1;
    lifeforms[4].map[12][32] = 1;
    lifeforms[4].map[13][32] = 1;

    // Draw Some! Init
    lifeforms[5].pixel = 10;
    lifeforms[5].squares = 50;
    lifeforms[5].map = (bool**)malloc(sizeof(bool*) * lifeforms[5].squares);
    for(i=0;i<lifeforms[5].squares;i++) {
        lifeforms[5].map[i] = (bool*)malloc(sizeof(bool) * lifeforms[5].squares);
        for(j=0;j<lifeforms[5].squares;j++) lifeforms[5].map[i][j] = 0;
    }
}

bool dead_or_alive(int i, int j) {
    int neighbours = 0;

    if ((i > 0)             && (previousMap[i-1][j])) neighbours++; // N
    if ((j > 0)             && (previousMap[i][j-1])) neighbours++; // W
    if ((i < gameSquares-1) && (previousMap[i+1][j])) neighbours++; // S
    if ((j < gameSquares-1) && (previousMap[i][j+1])) neighbours++; // E

    if ((i > 0)             && (j > 0)             && (previousMap[i-1][j-1])) neighbours++; // NW
    if ((i > 0)             && (j < gameSquares-1) && (previousMap[i-1][j+1])) neighbours++; // NE
    if ((i < gameSquares-1) && (j > 0)             && (previousMap[i+1][j-1])) neighbours++; // SW
    if ((i < gameSquares-1) && (j < gameSquares-1) && (previousMap[i+1][j+1])) neighbours++; // SE

    // 1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
    // 2. Any live cell with two or three live neighbours lives on to the next generation.
    // 3. Any live cell with more than three live neighbours dies, as if by overcrowding.
    // 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
    if(neighbours == 3) return true; // rule #2 & #4
    else if(neighbours == 2) return previousMap[i][j]; // rule #2
    else return false;
}

void set_game_map(int iLifeFormIndex) {
    // Free last maps
    if(gameMap)     for(int i=0; i<gameSquares; i++) free(gameMap[i]);     free(gameMap);
    if(previousMap) for(int i=0; i<gameSquares; i++) free(previousMap[i]); free(previousMap);

    // Set new params
    gameSquares = lifeforms[iLifeFormIndex].squares;
    gamePixel = lifeforms[iLifeFormIndex].pixel;

    // Allocate memory for maps
    gameMap     = (bool**)malloc(sizeof(bool*) * gameSquares);
    previousMap = (bool**)malloc(sizeof(bool*) * gameSquares);
    for(int i=0; i<gameSquares; i++) gameMap[i]     = (bool*)malloc(sizeof(bool) * gameSquares);
    for(int i=0; i<gameSquares; i++) previousMap[i] = (bool*)malloc(sizeof(bool) * gameSquares);

    // Copy game map from lifeform's map
    for(int i=0; i<gameSquares; i++) for(int j=0; j<gameSquares; j++) gameMap[i][j] = lifeforms[iLifeFormIndex].map[i][j];
}

bool update_game_map() {
    // Returns true if gameMap is different than previousMap
    // If they are the same, the game should stop

    for(int i=0; i<gameSquares; i++) for(int j=0; j<gameSquares; j++) previousMap[i][j] = gameMap[i][j];
    for(int i=0; i<gameSquares; i++) for(int j=0; j<gameSquares; j++) gameMap[i][j] = dead_or_alive(i, j);
    
    // If at least 1 difference, return true
    for(int i=0; i<gameSquares; i++) for(int j=0; j<gameSquares; j++)
        if(gameMap[i][j] != previousMap[i][j]) return true;

    // If no difference found, return false
    return false;
}

void draw_game_pixel(HWND hwnd, RECT gameArea, int i, int j) {
    HDC hdc = GetDC(hwnd);
    HBRUSH hBrush;
    srand(time(NULL));
    int r = rand() % 15;
    if(addColor) hBrush = CreateSolidBrush(colors[r]);
    else hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, (10 + j * gamePixel), (10 + i * gamePixel), (10 + (j+1) * gamePixel), (10 + (i+1) * gamePixel));
    DeleteObject(hBrush);
    ReleaseDC(hwnd, hdc);
}

void draw_game_map(HWND hwnd, RECT gameArea) {
    HDC hdc = GetDC(hwnd);

    // Clear drawing area
    FillRect(hdc, &gameArea, (HBRUSH)(WHITE_BRUSH));

    // Draw grid
    for(int x=10; x<gamePixel*gameSquares + 10; x+=gamePixel) {
        // vertical lines
        MoveToEx(hdc, x, 10, NULL);
        LineTo(hdc, x, gamePixel*gameSquares+10);
        // horizontal lines
        MoveToEx(hdc, 10, x, NULL);
        LineTo(hdc, gamePixel*gameSquares+10, x);
    }

    // Draw lifeforms
    if(gameMap) for(int i = 0; i < gameSquares; i++) for(int j = 0; j < gameSquares; j++) {
        if(gameMap[i][j]) draw_game_pixel(hwnd, gameArea, i, j);
    }

    ReleaseDC(hwnd, hdc);
}

