#include <windows.h>

#define IDW_DRAWING_AREA    100

#define IDB_PEN_TOOL        101
#define IDB_LINE_TOOL       102
#define IDB_POLYGON_TOOL    103
#define IDB_ELLIPSE_TOOL    104
#define IDB_BEZIER_TOOL     105
#define IDB_ERASER_TOOL     106

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

char szClassName[ ] = "Lab3Class";
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
        "Laboratory Work #3",
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX),
        CW_USEDEFAULT, CW_USEDEFAULT,
        760, 445,
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
    // Child windows' handles
    static HWND hwndEraserWeight;
    static HWND hwndStrokeWeight;
    static HWND hwndDrawArea;

    // Color variabes
    UINT fillRED      = 255;
    UINT fillGREEN    = 255;
    UINT fillBLUE     = 255;
    UINT strokeRED    = 0;
    UINT strokeGREEN  = 0;
    UINT strokeBLUE   = 0;

    // Color preview rectangles
    HBRUSH hBrush;
    int xFillPreview   = 25;
    int yFillPreview   = 277;
    int xStrokePreview = 88;
    int yStrokePreview = 277;

    // Color picker rectangles
    RECT rectRED     = {25, 342, 79, 353};
    RECT rectGREEN   = {25, 362, 79, 373};
    RECT rectBLUE    = {25, 382, 79, 393};
    RECT rectTemp;

    // Painting stuff
    PAINTSTRUCT ps;
    RECT rect;
    HDC hdc;

    switch(message) {

        case WM_CREATE:
            // Tools group box
            CreateWindowEx(0, "Button", "Tools",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                5, 10, 145, 160,
                hwnd, 0, hInstance, NULL);

            // Pen tool
            CreateWindowEx(0, "Button", "Pen",
                WS_VISIBLE | WS_CHILD | WS_GROUP | BS_AUTORADIOBUTTON,
                10, 30, 80, 20,
                hwnd, (HMENU)IDB_PEN_TOOL, hInstance, NULL);

            // Line tool
            CreateWindowEx(0, "Button", "Line",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 50, 80, 20,
                hwnd, (HMENU)IDB_LINE_TOOL, hInstance, NULL);

            // Polygon tool
            CreateWindowEx(0, "Button", "Polygon",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 70, 80, 20,
                hwnd, (HMENU)IDB_POLYGON_TOOL, hInstance, NULL);

            // Ellipse tool
            CreateWindowEx(0, "Button", "Ellipse",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 90, 80, 20,
                hwnd, (HMENU)IDB_ELLIPSE_TOOL, hInstance, NULL);

            // Bezier tool
            CreateWindowEx(0, "Button", "Bezier",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 110, 80, 20,
                hwnd, (HMENU)IDB_BEZIER_TOOL, hInstance, NULL);

            // Eraser tool
            CreateWindowEx(0, "Button", "Eraser",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 140, 80, 20,
                hwnd, (HMENU)IDB_ERASER_TOOL, hInstance, NULL);

            // Eraser weight input
            hwndEraserWeight = CreateWindowEx(0, "Edit", "5",
                WS_VISIBLE | WS_CHILD | WS_BORDER,
                120, 140, 20, 18,
                hwnd, (HMENU)0, hInstance, NULL);

            // Style group box
            CreateWindowEx(0, "Button", "Style",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                5, 180, 145, 50,
                hwnd, 0, hInstance, NULL);

            // Fill checkbox
            CreateWindowEx(0, "Button", "Fill",
                WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                10, 200, 50, 20,
                hwnd, (HMENU)0, hInstance, NULL);

            // Stroke label
            CreateWindowEx(0, "Static", "Stroke",
                WS_VISIBLE | WS_CHILD,
                70, 202, 40, 20,
                hwnd, (HMENU)0, hInstance, NULL);

            // Stroke weight input
            hwndStrokeWeight = CreateWindowEx(0, "Edit", "1",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                120, 200, 20, 18,
                hwnd, (HMENU)0, hInstance, NULL);

            // Color group box
            CreateWindowEx(0, "Button", "Color",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                5, 240, 145, 170,
                hwnd, 0, hInstance, NULL);

            // Fill color label
            CreateWindowEx(0, "Static", "Fill",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                30, 260, 30, 17,
                hwnd, (HMENU)0, hInstance, NULL);

            // Stroke color label
            CreateWindowEx(0, "Static", "Stroke",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                90, 260, 40, 17,
                hwnd, (HMENU)0, hInstance, NULL);

            // RED color label
            CreateWindowEx(0, "Static", "R",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                10, 340, 10, 20,
                hwnd, (HMENU)0, hInstance, NULL);
            
            // GREEN color label
            CreateWindowEx(0, "Static", "G",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                10, 360, 10, 20,
                hwnd, (HMENU)0, hInstance, NULL);

            // BLUE color label
            CreateWindowEx(0, "Static", "B",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                10, 380, 10, 20,
                hwnd, (HMENU)0, hInstance, NULL);

            // Drawing area
            hwndDrawArea = CreateWindowEx(0,
                "Static", "",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_WHITERECT, 
                160, 17, 585, 393,
                hwnd, (HMENU)IDW_DRAWING_AREA, hInstance, NULL);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {

                default:
                    DefWindowProc(hwnd, WM_COMMAND, wParam, lParam);
                    break;
            }
            break;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            // Fill color preview rectangle
            hBrush = CreateSolidBrush(RGB(fillRED, fillGREEN, fillBLUE));
            SelectObject(hdc, hBrush);
            Rectangle(hdc, xFillPreview, yFillPreview, xFillPreview+45, yFillPreview+45);
            DeleteObject(hBrush);


            // Stroke color preview rectangle
            hBrush = CreateSolidBrush(RGB(strokeRED, strokeGREEN, strokeBLUE));
            SelectObject(hdc, hBrush);
            Rectangle(hdc, xStrokePreview, yStrokePreview, xStrokePreview+45, yStrokePreview+45);
            DeleteObject(hBrush);

            // RED color picker
            rectTemp.top    = rectRED.top;
            rectTemp.bottom = rectRED.bottom;
            for(int i = 0; i < (rectRED.right - rectRED.left); i++) { 
                int r;
                r = i * 255 / (rectRED.right - rectRED.left);
                rectTemp.left  = rectRED.left  + i;
                rectTemp.right = rectRED.right + i + 1;
                hBrush = CreateSolidBrush(RGB(r, 0, 0));
                FillRect(hdc, &rectTemp, hBrush);
                DeleteObject(hBrush);
            }

            // GREEN color picker
            rectTemp.top    = rectGREEN.top;
            rectTemp.bottom = rectGREEN.bottom;
            for(int i = 0; i < (rectGREEN.right - rectGREEN.left); i++) { 
                int g;
                g = i * 255 / (rectGREEN.right - rectGREEN.left);
                rectTemp.left  = rectGREEN.left  + i;
                rectTemp.right = rectGREEN.right + i + 1;
                hBrush = CreateSolidBrush(RGB(0, g, 0));
                FillRect(hdc, &rectTemp, hBrush);
                DeleteObject(hBrush);
            }

            // BLUE color picker
            rectTemp.top    = rectBLUE.top;
            rectTemp.bottom = rectBLUE.bottom;
            for(int i = 0; i < (rectBLUE.right - rectBLUE.left); i++) { 
                int b;
                b = i * 255 / (rectBLUE.right - rectBLUE.left);
                rectTemp.left  = rectBLUE.left  + i;
                rectTemp.right = rectBLUE.right + i + 1;
                hBrush = CreateSolidBrush(RGB(0, 0, b));
                FillRect(hdc, &rectTemp, hBrush);
                DeleteObject(hBrush);
            }

            EndPaint(hwnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage (0);
            break;

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
