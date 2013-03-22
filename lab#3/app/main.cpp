#include <windows.h>
#include <windowsx.h>

#define IDW_DRAWING_AREA    100

#define IDB_PEN_TOOL        110
#define IDB_LINE_TOOL       111
#define IDB_POLYGON_TOOL    112
#define IDB_ELLIPSE_TOOL    113
#define IDB_BEZIER_TOOL     114
#define IDB_ERASER_TOOL     115

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void updateColorPreview(HDC, COLORREF, int, int);
int getWeight(HWND);
POINT adjustDrawLimits(int, int, RECT, int);

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
        778, 445,
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
    // static HWND hwndDrawArea;
    static HWND hwndPenTool;
    static HWND hwndLineTool;
    static HWND hwndPolygonTool;
    static HWND hwndEllipseTool;
    static HWND hwndBezierTool;
    static HWND hwndEraserTool;
    static HWND hwndFillCheck;

    // Drawing area rect
    static RECT drawingArea = {160, 17, 760, 410};

    // Drawing states
    static BOOL drawingLineNow;
    static POINT newLine;

    static BOOL drawingPolygonNow;
    static RECT newPolygon;

    static BOOL drawingEllipseNow;
    static RECT newEllipse;

    static BOOL drawingBezierFirst;
    static BOOL drawingBezierSecond;
    static BOOL drawingBezierThird;
    static POINT bezierPoints[4];

    // Mouse variables
    int xMouse, yMouse;

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
    RECT rectRED     = {25, 342, 133, 353};
    RECT rectGREEN   = {25, 362, 133, 373};
    RECT rectBLUE    = {25, 382, 133, 393};
    RECT rectTemp;

    // Painting stuff
    HDC hdc = GetDC(hwnd);
    COLORREF strokeRGB;
    int stroke_weight;
    COLORREF fillRGB;
    HBRUSH fillBrush;
    PAINTSTRUCT ps;
    HPEN strokePen;
    POINT point;
    RECT rect;

    switch(message) {

        case WM_CREATE:
            // Tools group box
            CreateWindowEx(0, "Button", "Tools",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                5, 10, 145, 160,
                hwnd, 0, hInstance, NULL);

            // Pen tool
            hwndPenTool = CreateWindowEx(0, "Button", "Pen",
                WS_VISIBLE | WS_CHILD | WS_GROUP | BS_AUTORADIOBUTTON,
                10, 30, 80, 20,
                hwnd, (HMENU)IDB_PEN_TOOL, hInstance, NULL);
            Button_SetCheck(hwndPenTool, BST_CHECKED);

            // Line tool
            hwndLineTool = CreateWindowEx(0, "Button", "Line",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 50, 80, 20,
                hwnd, (HMENU)IDB_LINE_TOOL, hInstance, NULL);

            // Polygon tool
            hwndPolygonTool = CreateWindowEx(0, "Button", "Polygon",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 70, 80, 20,
                hwnd, (HMENU)IDB_POLYGON_TOOL, hInstance, NULL);

            // Ellipse tool
            hwndEllipseTool = CreateWindowEx(0, "Button", "Ellipse",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 90, 80, 20,
                hwnd, (HMENU)IDB_ELLIPSE_TOOL, hInstance, NULL);

            // Bezier tool
            hwndBezierTool = CreateWindowEx(0, "Button", "Bezier",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 110, 80, 20,
                hwnd, (HMENU)IDB_BEZIER_TOOL, hInstance, NULL);

            // Eraser tool
            hwndEraserTool = CreateWindowEx(0, "Button", "Eraser",
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
            hwndFillCheck = CreateWindowEx(0, "Button", "Fill",
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
            return 0;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                default:
                    DefWindowProc(hwnd, WM_COMMAND, wParam, lParam);
                    break;
            }
            return 0;

        case WM_LBUTTONDOWN:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);

            // Check if colopikers clicked, set stroke colors
            if((xMouse > rectRED.left)&&(xMouse <= rectRED.right)) {
                strokeRGB = GetPixel(hdc, xStrokePreview + 20, yStrokePreview + 20);

                // If RED colorpicker
                if((yMouse > rectRED.top)&&(yMouse <= rectRED.bottom)) {
                    strokeRED = (xMouse - rectRED.left) * 255 / (rectRED.right - rectRED.left);
                    strokeGREEN = GetGValue(strokeRGB);
                    strokeBLUE = GetBValue(strokeRGB);
                    updateColorPreview(hdc, RGB(strokeRED, strokeGREEN, strokeBLUE), xStrokePreview, yStrokePreview);
                }
                // If GREEN colorpicker
                else if((yMouse > rectGREEN.top)&&(yMouse <= rectGREEN.bottom)) {
                    strokeRED = GetRValue(strokeRGB);
                    strokeGREEN = (xMouse - rectGREEN.left) * 255 / (rectGREEN.right - rectGREEN.left);
                    strokeBLUE = GetBValue(strokeRGB);
                    updateColorPreview(hdc, RGB(strokeRED, strokeGREEN, strokeBLUE), xStrokePreview, yStrokePreview);
                }
                // If BLUE colorpicker
                else if((yMouse > rectBLUE.top)&&(yMouse <= rectBLUE.bottom)) {
                    strokeRED = GetRValue(strokeRGB);
                    strokeGREEN = GetGValue(strokeRGB);
                    strokeBLUE = (xMouse - rectBLUE.left) * 255 / (rectBLUE.right - rectBLUE.left);
                    updateColorPreview(hdc, RGB(strokeRED, strokeGREEN, strokeBLUE), xStrokePreview, yStrokePreview);
                }
                return 0;
            }

            // Check if on the drawing area
            if((xMouse > drawingArea.left)&&(xMouse < drawingArea.right)&&(yMouse > drawingArea.top)&&(yMouse < drawingArea.bottom)) {
                stroke_weight = getWeight(hwndStrokeWeight);
                point = adjustDrawLimits(xMouse, yMouse, drawingArea, stroke_weight);
                xMouse = point.x;
                yMouse = point.y;
                // If Line tool is selected
                if((wParam == MK_LBUTTON)&&(Button_GetCheck(hwndLineTool) == BST_CHECKED)) {
                    newLine.x = xMouse;
                    newLine.y = yMouse;
                    drawingLineNow = true;
                }
                // If Polygon tool is selected
                if((wParam == MK_LBUTTON)&&(Button_GetCheck(hwndPolygonTool) == BST_CHECKED)) {
                    newPolygon.left = xMouse;
                    newPolygon.top = yMouse;
                    drawingPolygonNow = true;
                }
                // If Ellipse tool is selected
                if((wParam == MK_LBUTTON)&&(Button_GetCheck(hwndEllipseTool) == BST_CHECKED)) {
                    newEllipse.left = xMouse;
                    newEllipse.top = yMouse;
                    drawingEllipseNow = true;
                }
                // If Bezier tool is selected
                if((wParam == MK_LBUTTON)&&(Button_GetCheck(hwndBezierTool) == BST_CHECKED)) {
                    bezierPoints[0] = point;
                    drawingBezierFirst  = true;
                    drawingBezierSecond = false;
                    drawingBezierThird  = false;
                }
            }
            return 0;

        case WM_LBUTTONUP:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);
            strokeRGB = GetPixel(hdc, xStrokePreview + 20, yStrokePreview + 20);
            fillRGB = GetPixel(hdc, xFillPreview + 20, yFillPreview + 20);
            stroke_weight = getWeight(hwndStrokeWeight);
            
            if(drawingLineNow) {
                point = adjustDrawLimits(xMouse, yMouse, drawingArea, stroke_weight);
                xMouse = point.x;
                yMouse = point.y;

                strokePen = CreatePen(PS_SOLID, stroke_weight, strokeRGB);
                SelectObject(hdc, strokePen);
                MoveToEx(hdc, xMouse, yMouse, NULL);
                LineTo(hdc, newLine.x, newLine.y);
                DeleteObject(strokePen);

                drawingLineNow = false;
            }

            if(drawingPolygonNow) {
                point = adjustDrawLimits(xMouse, yMouse, drawingArea, stroke_weight);
                newPolygon.right = point.x;
                newPolygon.bottom = point.y;

                strokePen = CreatePen(PS_SOLID, stroke_weight, strokeRGB);
                fillBrush = (Button_GetCheck(hwndFillCheck) == BST_CHECKED)? CreateSolidBrush(fillRGB) : (HBRUSH)GetStockObject(NULL_BRUSH);
                SelectObject(hdc, strokePen);
                SelectObject(hdc, fillBrush);
                Rectangle(hdc, newPolygon.left, newPolygon.top, newPolygon.right, newPolygon.bottom);
                DeleteObject(strokePen);
                DeleteObject(fillBrush);

                drawingPolygonNow = false;
            }

            if(drawingEllipseNow) {
                point = adjustDrawLimits(xMouse, yMouse, drawingArea, stroke_weight);
                newEllipse.right = point.x;
                newEllipse.bottom = point.y;

                strokePen = CreatePen(PS_SOLID, stroke_weight, strokeRGB);
                fillBrush = (Button_GetCheck(hwndFillCheck) == BST_CHECKED)? CreateSolidBrush(fillRGB) : (HBRUSH)GetStockObject(NULL_BRUSH);
                SelectObject(hdc, strokePen);
                SelectObject(hdc, fillBrush);
                Ellipse(hdc, newEllipse.left, newEllipse.top, newEllipse.right, newEllipse.bottom);
                DeleteObject(strokePen);
                DeleteObject(fillBrush);

                drawingEllipseNow = false;
            }

            if(drawingBezierFirst) {
                point = adjustDrawLimits(xMouse, yMouse, drawingArea, stroke_weight);
                bezierPoints[1] = point;
                drawingBezierFirst  = false;
                drawingBezierSecond = true;
                drawingBezierThird  = false;
            }
            return 0;

        case WM_RBUTTONDOWN:
            xMouse = GET_X_LPARAM(lParam); 
            yMouse = GET_Y_LPARAM(lParam);

            // Check if colopikers clicked, set fill colors
            if((xMouse > rectRED.left)&&(xMouse <= rectRED.right)) {
                fillRGB = GetPixel(hdc, xFillPreview + 20, yFillPreview + 20);

                // If RED colorpicker
                if((yMouse > rectRED.top)&&(yMouse <= rectRED.bottom)) {
                    fillRED = (xMouse - rectRED.left) * 255 / (rectRED.right - rectRED.left);
                    fillGREEN = GetGValue(fillRGB);
                    fillBLUE = GetBValue(fillRGB);
                    updateColorPreview(hdc, RGB(fillRED, fillGREEN, fillBLUE), xFillPreview, yFillPreview);
                }
                // If GREEN colorpicker
                else if((yMouse > rectGREEN.top)&&(yMouse <= rectGREEN.bottom)) {
                    fillRED = GetRValue(fillRGB);
                    fillGREEN = (xMouse - rectGREEN.left) * 255 / (rectGREEN.right - rectGREEN.left);
                    fillBLUE = GetBValue(fillRGB);
                    updateColorPreview(hdc, RGB(fillRED, fillGREEN, fillBLUE), xFillPreview, yFillPreview);
                }
                // If BLUE colorpicker
                else if((yMouse > rectBLUE.top)&&(yMouse <= rectBLUE.bottom)) {
                    fillRED = GetRValue(fillRGB);
                    fillGREEN = GetGValue(fillRGB);
                    fillBLUE = (xMouse - rectBLUE.left) * 255 / (rectBLUE.right - rectBLUE.left);
                    updateColorPreview(hdc, RGB(fillRED, fillGREEN, fillBLUE), xFillPreview, yFillPreview);
                }
                return 0;
            }

            if((xMouse > drawingArea.left)&&(xMouse < drawingArea.right)&&(yMouse > drawingArea.top)&&(yMouse < drawingArea.bottom)) {
                stroke_weight = getWeight(hwndStrokeWeight);
                point = adjustDrawLimits(xMouse, yMouse, drawingArea, stroke_weight);
                xMouse = point.x;
                yMouse = point.y;

                // If Bezier tool is selected & first half is selected
                if((wParam == MK_RBUTTON)&&(Button_GetCheck(hwndBezierTool) == BST_CHECKED)&&(drawingBezierSecond)) {
                    bezierPoints[2] = point;
                    drawingBezierFirst  = false;
                    drawingBezierSecond = false;
                    drawingBezierThird  = true;
                }
            }
            return 0;

        case WM_RBUTTONUP:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);
            strokeRGB = GetPixel(hdc, xStrokePreview + 20, yStrokePreview + 20);
            fillRGB = GetPixel(hdc, xFillPreview + 20, yFillPreview + 20);
            stroke_weight = getWeight(hwndStrokeWeight);
            point = adjustDrawLimits(xMouse, yMouse, drawingArea, stroke_weight);
            xMouse = point.x;
            yMouse = point.y;

            if(drawingBezierThird) {
                bezierPoints[3] = point;
                strokePen = CreatePen(PS_SOLID, stroke_weight, strokeRGB);
                SelectObject(hdc, strokePen);
                PolyBezier(hdc, bezierPoints, 4);
                DeleteObject(strokePen);
                drawingBezierFirst  = false;
                drawingBezierSecond = false;
                drawingBezierThird  = false;
            }
            return 0;

        case WM_MOUSEMOVE:
            xMouse = GET_X_LPARAM(lParam); 
            yMouse = GET_Y_LPARAM(lParam);

            // Check if on the drawing area
            if((xMouse > drawingArea.left)&&(xMouse < drawingArea.right)
                &&(yMouse > drawingArea.top)&&(yMouse < drawingArea.bottom)) {
                strokeRGB = GetPixel(hdc, xStrokePreview + 20, yStrokePreview + 20);
                fillRGB   = GetPixel(hdc, xStrokePreview + 20, yStrokePreview + 20);

                // If Pen tool is selected
                if((wParam == MK_LBUTTON)&&(Button_GetCheck(hwndPenTool) == BST_CHECKED)) {
                    SetPixel(hdc, xMouse, yMouse, strokeRGB);
                }
                break;
            }
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            // Fill color preview rectangle
            updateColorPreview(hdc, RGB(255, 255, 255), xFillPreview, yFillPreview);

            // Stroke color preview rectangle
            updateColorPreview(hdc, RGB(0, 0, 0), xStrokePreview, yStrokePreview);

            // RED color picker
            rectTemp.top    = rectRED.top;
            rectTemp.bottom = rectRED.bottom;
            for(int i = 0; i < (rectRED.right - rectRED.left); i++) { 
                int r;
                r = i * 255 / (rectRED.right - rectRED.left);
                rectTemp.left  = rectRED.left  + i;
                rectTemp.right = rectRED.left + i + 1;
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
                rectTemp.right = rectGREEN.left + i + 1;
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
                rectTemp.right = rectBLUE.left + i + 1;
                hBrush = CreateSolidBrush(RGB(0, 0, b));
                FillRect(hdc, &rectTemp, hBrush);
                DeleteObject(hBrush);
            }

            // Blank draw area
            SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0,0,0)));
            SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            Rectangle(hdc, drawingArea.left, drawingArea.top, drawingArea.right, drawingArea.bottom);

            EndPaint(hwnd, &ps); // End main window DC paint
            return 0;

        case WM_DESTROY:
            PostQuitMessage (0);
            return 0;

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

void updateColorPreview(HDC hdc, COLORREF rgb, int xLeft, int yTop) {
    HBRUSH hBrush = CreateSolidBrush(rgb);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, xLeft, yTop, xLeft + 45, yTop + 45);
    DeleteObject(hBrush);
}

int getWeight(HWND input) {
    int result;
    int iLength = SendMessage(input, WM_GETTEXTLENGTH, 0, 0);
    char* szText = (char*)malloc(iLength+1);
    SendMessage(input, WM_GETTEXT, iLength+1, (LPARAM)szText);
    result = atoi(szText);
    _itoa(result, szText, 10);
    SendMessage(input, WM_SETTEXT, 0, (LPARAM)szText);
    free(szText);
    return result;
}

POINT adjustDrawLimits(int xMouse, int yMouse, RECT limit, int stroke) {
    POINT result;
    stroke = stroke / 2 + 1;

    if(xMouse - stroke < limit.left) {
        result.x = limit.left + stroke;
    } else if(xMouse + stroke > limit.right) {
        result.x = limit.right - stroke;
    } else result.x = xMouse;

    if(yMouse - stroke < limit.top) {
        result.y = limit.top + stroke;
    } else if(yMouse + stroke > limit.bottom) {
        result.y = limit.bottom - stroke;
    } else result.y = yMouse;

    return result;
}



