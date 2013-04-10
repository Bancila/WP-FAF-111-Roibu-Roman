#include <windows.h>
#include <windowsx.h>
#include "main.h"

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

char szClassName[ ] = "Lab4Class";
HINSTANCE hInstance;

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = 0;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    if(!RegisterClassEx(&wincl)) return 0;

    hwnd = CreateWindowEx (
        0,
        szClassName,
        "Game of Life",
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX),
        CW_USEDEFAULT, CW_USEDEFAULT,
        705, 545,
        HWND_DESKTOP,
        NULL,
        hThisInstance,
        NULL);

    ShowWindow (hwnd, nCmdShow);

    while (GetMessage (&messages, NULL, 0, 0)) {
      TranslateMessage(&messages);
      DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hwndLifeForms;
    static HWND hwndSetBtn;
    static HWND hwndStartBtn;
    static HWND hwndStopBtn;
    static HWND hwndSpeed;

    static bool gameOn;

    int iLifeFormIndex;

    int xMouse;
    int yMouse;

    PAINTSTRUCT ps;
    HPEN hPEN;
    RECT gameArea = {11, 11, 509, 509};
    HDC hdc = GetDC(hwnd);

    switch(message) {

        case WM_CREATE:

            // Life form group box
            CreateWindowEx(0, "Button", "Life Form",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                520, 40, 170, 90,
                hwnd, 0, hInstance, NULL);

            // LIFEFORMS combobox
            hwndLifeForms = CreateWindow("ComboBox", "", 
                CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                530, 65, 150, 25,
                hwnd, (HMENU)IDC_LIFEFORMS, hInstance, NULL);

            // SET button
            hwndSetBtn = CreateWindow("Button", "Set",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                530, 95, 150, 25,
                hwnd, (HMENU)IDB_SETBTN, hInstance, NULL);

            // Animation group box
            CreateWindowEx(0, "Button", "Animation",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                520, 160, 170, 150,
                hwnd, 0, hInstance, NULL);

            // START button
            hwndStartBtn = CreateWindow("Button", "Start",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                530, 185, 150, 25,
                hwnd, (HMENU)IDB_STARTBTN, hInstance, NULL);

            // STOP button
            hwndStopBtn = CreateWindow("Button", "Start",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                530, 215, 150, 25,
                hwnd, (HMENU)IDB_STOPBTN, hInstance, NULL);

            // Speed title label
            CreateWindow("Static", "Speed:",
                WS_VISIBLE | WS_CHILD,
                530, 280, 50, 20,
                hwnd, 0, hInstance, NULL);

            // Speed value label
            hwndSpeed = CreateWindow("Static", "100%",
                WS_VISIBLE | WS_CHILD | SS_RIGHT,
                630, 280, 50, 20,
                hwnd, 0, hInstance, NULL);

            // About group box
            CreateWindowEx(0, "Button", "About",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                520, 340, 170, 170,
                hwnd, 0, hInstance, NULL);

            // About text label
            CreateWindow("Static",
                TEXT("\"Game Of Life\"\n\nWindows Programming\nLaboratory #4\n\n(c) Roman Roibu"),
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                530, 370, 150, 120,
                hwnd, 0, hInstance, NULL);

            // Add lifeforms to combo-box
            for(int i = 0; i < NUMLIFEFORMS; i++) {
                SendMessage(hwndLifeForms, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)lifeforms[i].szLabel);
            }

            // Set game boolean
            gameOn = false;

            // Init Game settings
            game_of_life_initialize();
            return 0;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDB_SETBTN:

                    // Clear drawing area
                    FillRect(hdc, &gameArea, (HBRUSH)(WHITE_BRUSH));

                    // Get selected life form index
                    iLifeFormIndex = SendMessage(hwndLifeForms, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
                    
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

                    // Pause the game, to wait for the start button
                    gameOn = false;

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
                    SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
                    if(gameMap) for(int i = 0; i < gameSquares; i++) for(int j = 0; j < gameSquares; j++) {
                        if(gameMap[i][j]) Rectangle(hdc, (10 + j * gamePixel), (10 + i * gamePixel), (10 + (j+1) * gamePixel), (10 + (i+1) * gamePixel));
                    }

                    break;
                default:
                    DefWindowProc(hwnd, WM_COMMAND, wParam, lParam);
                    break;
            }
            return 0;

        case WM_LBUTTONDOWN:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);

            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            // Draw game area
            hPEN = CreatePen(PS_SOLID, 1, RGB(0,0,0));
            SelectObject(hdc, hPEN);
            SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            Rectangle(hdc, 10, 10, 510, 510);
            DeleteObject(hPEN);
            EndPaint(hwnd, &ps);
            return 0;

        case WM_DESTROY:
            PostQuitMessage (0);
            return 0;

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
