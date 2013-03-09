#include <windows.h>
#include <stdlib.h>

#define IDC_LIST_BOX            100
#define IDC_NEW_ITEM            101

#define IDC_ADD_BUTTON          102
#define IDC_REMOVE_BUTTON       103
#define IDC_CLEAR_BUTTON        104
#define IDC_DAY_BUTTON          105
#define IDC_NIGHT_BUTTON        106

#define IDC_FILE_EXIT           107
#define IDC_VIEW_DAY            108
#define IDC_VIEW_NIGHT          109
#define IDC_HELP_ABOUT          110

#define IDC_BACKGROUND_SCROLL   111
#define IDC_HEIGHT_SCROLL       112
#define IDC_WIDTH_SCROLL        113

#define IDC_LABEL1              114
#define IDC_LABEL2              115
#define IDC_LABEL3              116
#define IDC_LABEL4              117
#define IDC_LABEL5              118

int iMinWindowHeight = 610;
int iMinWindowWidth  = 420;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

char szClassName[ ] = "Lab2Class";
HINSTANCE hProgramInstance;

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_EXCLAMATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_EXCLAMATION);
    wincl.hCursor = LoadCursor (NULL, IDC_HAND);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

    if(!RegisterClassEx(&wincl)) return 0;

    hwnd = CreateWindowEx (
        0,
        szClassName,
        "Laboratory Work #2",
        WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
        CW_USEDEFAULT, CW_USEDEFAULT,
        iMinWindowWidth, iMinWindowHeight,
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

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // Child windows' handles
    static HWND hwndListBox;
    static HWND hwndNewItem;
    static HWND hwndAddButton;
    static HWND hwndRemoveButton;
    static HWND hwndClearButton;
    static HWND hwndDayButton;
    static HWND hwndNightButton;
    static HWND hwndBackgroundScroll;
    static HWND hwndHeightScroll;
    static HWND hwndWidthScroll;
    static HWND hwndLabel1;
    static HWND hwndLabel2;
    static HWND hwndLabel3;
    static HWND hwndLabel4;
    static HWND hwndLabel5;

    LONG id;

    // Size and position variables
    int iSysWidth;
    int iSysHeight;
    int iWinWidth;
    int iWinHeight;

    int iWidth  = 60;   // Button width
    int iHeight = 30;   // Button height
    int x;
    int y;

    int i;

    // ListBox size and initial position
    int xListBox       = 10;
    int yListBox       = 10;
    int iListBoxWidth  = 300;
    int iListBoxHeight = 360;

    // Menu & menu items
    HMENU hMenu;
    HMENU hSubMenu;

    // Text size
    int cxChar;
    int cyChar;

    // String
    char* szText;
    int iTextLength;

    // Paint and size structs
    PWINDOWINFO pwi;
    PAINTSTRUCT ps;
    TEXTMETRIC tm;
    SCROLLINFO si;
    HBRUSH brush;
    RECT rect;
    int color;
    HDC hdc;


    hdc = GetDC(hwnd);
    GetTextMetrics(hdc, &tm);
    cxChar = tm.tmAveCharWidth;
    cyChar = tm.tmHeight;// + tm.tmExternalLeading;
    ReleaseDC(hwnd, hdc);

    switch(message) {

        case WM_CREATE:
            hwndListBox = CreateWindowEx(
                (DWORD)NULL,
                TEXT("ListBox"),
                NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_WANTKEYBOARDINPUT,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_LIST_BOX,
                hProgramInstance,
                NULL);

            hwndNewItem = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Edit"),
                TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_NEW_ITEM,
                hProgramInstance,
                NULL);


            hwndLabel1 = CreateWindowEx(
                (DWORD)NULL,
                TEXT("static"),
                TEXT("Window Background Color"),
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_LABEL1,
                hProgramInstance,
                NULL);

            hwndLabel2 = CreateWindowEx(
                (DWORD)NULL,
                TEXT("static"),
                TEXT("Window Width"),
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_LABEL2,
                hProgramInstance,
                NULL);

            hwndLabel3 = CreateWindowEx(
                (DWORD)NULL,
                TEXT("static"),
                TEXT("Window Height"),
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                0, 0, 0, 0,
                hwnd,
                (HMENU)IDC_LABEL3,
                hProgramInstance,
                NULL);

            hwndLabel4 = CreateWindowEx(
                (DWORD)NULL,
                TEXT("static"),
                TEXT("List"),
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                0, 0, 0, 0,
                hwnd,
                (HMENU)IDC_LABEL4,
                hProgramInstance,
                NULL);

            hwndLabel5 = CreateWindowEx(
                (DWORD)NULL,
                TEXT("static"),
                TEXT("Mode"),
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                0, 0, 0, 0,
                hwnd,
                (HMENU)IDC_LABEL5,
                hProgramInstance,
                NULL);

            hwndBackgroundScroll = CreateWindow(
                "Scrollbar", 
                NULL,
                WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
                0, 0, iListBoxWidth, 0,
                hwnd,
                (HMENU)IDC_BACKGROUND_SCROLL,
                hProgramInstance,
                NULL);
            SetScrollRange(hwndBackgroundScroll, SB_CTL, 0, 255, TRUE);
            SetScrollPos(hwndBackgroundScroll, SB_CTL, 255, TRUE);

            hwndWidthScroll = CreateWindow(
                "Scrollbar", 
                NULL,
                WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_WIDTH_SCROLL,
                hProgramInstance,
                NULL);
            SetScrollRange(hwndWidthScroll, SB_CTL, 0, 100, TRUE);

            hwndHeightScroll = CreateWindow(
                "Scrollbar", 
                NULL,
                WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_BOTTOMALIGN,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_HEIGHT_SCROLL,
                hProgramInstance,
                NULL);
            SetScrollRange(hwndHeightScroll, SB_CTL, 0, 100, TRUE);

            hwndAddButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Add"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_ADD_BUTTON,
                hProgramInstance,
                NULL);

            hwndRemoveButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Remove"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_REMOVE_BUTTON,
                hProgramInstance,
                NULL);

            hwndClearButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Clear"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_CLEAR_BUTTON,
                hProgramInstance,
                NULL);

            hwndDayButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Day"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_DAY_BUTTON,
                hProgramInstance,
                NULL);

            hwndNightButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Night"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 0, 0, hwnd,
                (HMENU)IDC_NIGHT_BUTTON,
                hProgramInstance,
                NULL);

            // Create menu
            hMenu = CreateMenu();

            // Add "File" menu, with "Exit" submenu
            hSubMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");
            AppendMenu(hSubMenu, MF_STRING, IDC_FILE_EXIT, "&Exit");

            // Add "View" menu, with "Day" and "Night" submenus
            hSubMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&View");
            AppendMenu(hSubMenu, MF_STRING, IDC_VIEW_DAY, "&Day\tCtrl+D");
            AppendMenu(hSubMenu, MF_STRING, IDC_VIEW_NIGHT, "&Night\tCtrl+N");

            // Add "Help" menu, with "About" submenu
            hSubMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Help");
            AppendMenu(hSubMenu, MF_STRING, IDC_HELP_ABOUT, "&About");

            // Set the menu
            SetMenu(hwnd, hMenu);
            break;

        case WM_SIZE:
            iWidth  = LOWORD(lParam);
            iHeight = HIWORD(lParam);

            // Set vertical scroll bar range and page size
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ((iMinWindowHeight - 70) / cyChar);
            si.nPage = iHeight / cyChar;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

            // Set horizontal scroll bar range and page size
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ((iMinWindowWidth - 20) / cxChar);
            si.nPage = iWidth / cxChar;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

            // CHILD WINDOWS REPOSITION BEGIN
            x = xListBox;
            y = yListBox;
            iWidth = 60;
            iHeight = 30;
            MoveWindow(hwndListBox, x, y, iListBoxWidth, iListBoxHeight, TRUE);
            y = yListBox + iListBoxHeight + 5;
            MoveWindow(hwndNewItem, x, y, (iListBoxWidth - iWidth - 5), iHeight, TRUE);
            y = y + iHeight + 10;
            MoveWindow(hwndLabel1, x, y, iListBoxWidth, 20, TRUE);
            y = y + 20;
            MoveWindow(hwndBackgroundScroll, x, y, iListBoxWidth, 10, TRUE);
            y = y + 10 + 10;
            MoveWindow(hwndLabel2, x, y, iListBoxWidth, 20, TRUE);
            y = y + 20;
            MoveWindow(hwndWidthScroll, x, y, iListBoxWidth, 10, TRUE);
            y = y + 10 + 10;
            MoveWindow(hwndLabel3, x, y, iListBoxWidth, 20, TRUE);
            y = y + 20;
            MoveWindow(hwndHeightScroll, x, y, iListBoxWidth, 10, TRUE);
            x = xListBox + iListBoxWidth - iWidth;
            y = yListBox + iListBoxHeight + 5;
            MoveWindow(hwndAddButton, x, y, iWidth, iHeight, TRUE);
            x = xListBox + iListBoxWidth + 10;
            y = yListBox;
            MoveWindow(hwndLabel4, x, y, iWidth, 20, TRUE);
            y = y + 25;
            MoveWindow(hwndRemoveButton, x, y, iWidth, iHeight, TRUE);
            y = y + iHeight + 5;
            MoveWindow(hwndClearButton, x, y, iWidth, iHeight, TRUE);
            y = y + (iHeight + 35);
            MoveWindow(hwndLabel5, x, y, iWidth, 20, TRUE);
            y = y + 25;
            MoveWindow(hwndDayButton, x, y, iWidth, iHeight, TRUE);
            y = y + iHeight + 5;
            MoveWindow(hwndNightButton, x, y, iWidth, iHeight, TRUE);
            // CHILD WINDOWS REPOSITION END

            GetWindowRect(hwnd, &rect);
            iWinWidth = rect.right - rect.left;
            iWinHeight = rect.bottom - rect.top;
            iSysWidth = GetSystemMetrics(SM_CXSCREEN);
            iSysHeight = GetSystemMetrics(SM_CYSCREEN);

            // Set width scrollbar position
            SetScrollPos(hwndWidthScroll, SB_CTL, (iWinWidth * 100 / iSysWidth), TRUE);

            // Set height scrollbar position
            SetScrollPos(hwndHeightScroll, SB_CTL, (iWinHeight * 100 / iSysHeight), TRUE);
            break;

        case WM_VSCROLL:
            // Get all the vertical scroll bar information
            si.cbSize = sizeof(si);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_VERT, &si);

            // Save the position for later comparison
            y = si.nPos;

            switch(LOWORD(wParam)) {
                case SB_TOP:
                    si.nPos = si.nMin;
                    break;

                case SB_BOTTOM:
                    si.nPos = si.nMax;
                    break;

                case SB_LINEUP:
                    si.nPos -= 1;
                    break;

                case SB_LINEDOWN:
                    si.nPos += 1;
                    break;

                case SB_PAGEUP:
                    si.nPos -= si.nPage;
                    break;

                case SB_PAGEDOWN:
                    si.nPos += si.nPage;
                    break;

                case SB_THUMBTRACK:
                    si.nPos = si.nTrackPos;
                    break;

                default:
                    break;
            }

            // Set the position and then retrieve it
            si.fMask = SIF_POS;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
            GetScrollInfo(hwnd, SB_VERT, &si);

            // If the position has changed, scroll the window and update it
            if(si.nPos != y) {
                ScrollWindow(hwnd, 0, cyChar * (y - si.nPos), NULL, NULL);
                UpdateWindow(hwnd);
            }
            break;

        case WM_HSCROLL:
            GetWindowRect(hwnd, &rect);
            iWinWidth = rect.right - rect.left;
            iWinHeight = rect.bottom - rect.top;
            iSysWidth = GetSystemMetrics(SM_CXSCREEN);
            iSysHeight = GetSystemMetrics(SM_CYSCREEN);
            if(GetWindowLong((HWND)lParam, GWL_ID) == IDC_BACKGROUND_SCROLL) {
                si.cbSize = sizeof(si);
                si.fMask = SIF_ALL;
                GetScrollInfo(hwndBackgroundScroll, SB_CTL, &si);
                x = si.nPos;
                switch(LOWORD(wParam)) {
                    case SB_LINELEFT:
                        si.nPos -= 1;
                        break;
                    case SB_LINERIGHT:
                        si.nPos += 1;
                        break;
                    case SB_THUMBPOSITION:
                        si.nPos = si.nTrackPos;
                        break;
                    default:
                        break;
                }
                si.fMask = SIF_POS;
                color = si.nPos;
                SetScrollInfo(hwndBackgroundScroll, SB_CTL, &si, TRUE);
                GetScrollInfo(hwndBackgroundScroll, SB_CTL, &si);
                if(si.nPos != x) {
                    SetScrollPos(hwndBackgroundScroll, SB_CTL, si.nPos, TRUE);
                }
                // Set background color
                brush = CreateSolidBrush(RGB(color, color, color));
                SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
                SendMessage(hwnd, WM_SIZE, NULL, NULL);
                break;
            }

            if(GetWindowLong((HWND)lParam, GWL_ID) == IDC_WIDTH_SCROLL) {
                si.cbSize = sizeof(si);
                si.fMask = SIF_ALL;
                GetScrollInfo(hwndWidthScroll, SB_CTL, &si);
                x = si.nPos;
                switch(LOWORD(wParam)) {
                    case SB_LINELEFT:
                        si.nPos -= 1;
                        break;
                    case SB_LINERIGHT:
                        si.nPos += 1;
                        break;
                    case SB_THUMBPOSITION:
                        si.nPos = si.nTrackPos;
                        break;
                    default:
                        break;
                }
                si.fMask = SIF_POS;
                SetScrollInfo(hwndWidthScroll, SB_CTL, &si, TRUE);
                GetScrollInfo(hwndWidthScroll, SB_CTL, &si);
                if(si.nPos != x) {
                    SetScrollPos(hwndWidthScroll, SB_CTL, si.nPos, TRUE);
                }
                // Set window width
                MoveWindow(hwnd, rect.left, rect.top, (si.nPos * iSysWidth / 100), iWinHeight, TRUE);
                break;
            }

            if(GetWindowLong((HWND)lParam, GWL_ID) == IDC_HEIGHT_SCROLL) {
                si.cbSize = sizeof(si);
                si.fMask = SIF_ALL;
                GetScrollInfo(hwndHeightScroll, SB_CTL, &si);
                x = si.nPos;
                switch(LOWORD(wParam)) {
                    case SB_LINELEFT:
                        si.nPos -= 1;
                        break;
                    case SB_LINERIGHT:
                        si.nPos += 1;
                        break;
                    case SB_THUMBPOSITION:
                        si.nPos = si.nTrackPos;
                        break;
                    default:
                        break;
                }
                si.fMask = SIF_POS;
                SetScrollInfo(hwndHeightScroll, SB_CTL, &si, TRUE);
                GetScrollInfo(hwndHeightScroll, SB_CTL, &si);
                if(si.nPos != x) {
                    SetScrollPos(hwndHeightScroll, SB_CTL, si.nPos, TRUE);
                }
                // Set window height
                MoveWindow(hwnd, rect.left, rect.top, iWinWidth, (si.nPos * iSysHeight / 100), TRUE);
                break;
            }

            // Get all the vertical scroll bar information
            si.cbSize = sizeof(si);
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_HORZ, &si);
            // Save the position for later comparison
            x = si.nPos;
            switch(LOWORD(wParam)) {
                case SB_LINELEFT:
                    si.nPos -= 1;
                    break;

                case SB_LINERIGHT:
                    si.nPos += 1;
                    break;

                case SB_PAGELEFT:
                    si.nPos -= si.nPage;
                    break;

                case SB_PAGERIGHT:
                    si.nPos += si.nPage;
                    break;

                case SB_THUMBPOSITION:
                    si.nPos = si.nTrackPos;
                    break;

                default:
                    break;
            }
            // Set the position and then retrieve it
            si.fMask = SIF_POS;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
            GetScrollInfo(hwnd, SB_HORZ, &si);

            // If the position has changed, scroll the window and update it
            if(si.nPos != x) {
                ScrollWindow(hwnd, cxChar * (x - si.nPos), NULL, NULL, 0);
                UpdateWindow(hwnd);
            }
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDC_LIST_BOX:
                    switch (HIWORD(wParam)) {
                        case LBN_DBLCLK:
                            MessageBox(NULL, TEXT("ListBox  Double-Clicked!"), TEXT("Double-Click!"), MB_OK);
                            break;
                    }
                    break;

                case IDC_ADD_BUTTON:
                    iTextLength = SendMessage(hwndNewItem, WM_GETTEXTLENGTH, 0, 0);
                    szText = (char*)malloc(iTextLength+1);
                    SendMessage(hwndNewItem, WM_GETTEXT, iTextLength+1, (LPARAM)szText);
                    SendMessage(hwndListBox, LB_ADDSTRING, 0, (LPARAM)szText);
                    SendMessage(hwndNewItem, WM_SETTEXT, 0, (LPARAM)"");
                    free(szText);
                    break;

                case IDC_REMOVE_BUTTON:
                    i = SendMessage(hwndListBox, LB_GETCURSEL, 0, 0);
                    if(i != LB_ERR) {
                        SendMessage(hwndListBox, LB_DELETESTRING, i, 0);
                    }
                    break;

                case IDC_CLEAR_BUTTON:
                    SendMessage(hwndListBox, LB_RESETCONTENT, 0, 0);
                    break;

                case IDC_DAY_BUTTON:
                    // Set background color
                    brush = CreateSolidBrush(RGB(255, 255, 255));
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
                    si.cbSize = sizeof(si);
                    si.fMask = SIF_POS;
                    GetScrollInfo(hwndBackgroundScroll, SB_CTL, &si);
                    si.nPos = 255;
                    SetScrollInfo(hwndBackgroundScroll, SB_CTL, &si, TRUE);
                    SendMessage(hwnd, WM_SIZE, NULL, NULL);
                    break;

                case IDC_NIGHT_BUTTON:
                    // Set background color
                    brush = CreateSolidBrush(RGB(0, 0, 0));
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
                    si.cbSize = sizeof(si);
                    si.fMask = SIF_POS;
                    GetScrollInfo(hwndBackgroundScroll, SB_CTL, &si);
                    si.nPos = 0;
                    SetScrollInfo(hwndBackgroundScroll, SB_CTL, &si, TRUE);
                    SendMessage(hwnd, WM_SIZE, NULL, NULL);
                    break;

                case IDC_FILE_EXIT:
                    SendMessage(hwnd, WM_DESTROY, NULL, NULL);
                    break;

                case IDC_VIEW_DAY:
                    SendMessage(hwnd, WM_COMMAND, IDC_DAY_BUTTON, lParam);
                    break;

                case IDC_VIEW_NIGHT:
                    SendMessage(hwnd, WM_COMMAND, IDC_NIGHT_BUTTON, lParam);
                    break;

                case IDC_HELP_ABOUT:
                    break;

                default:
                    DefWindowProc(hwnd, WM_COMMAND, wParam, lParam);
                    break;
            }
            break;

        case WM_KEYDOWN:
            GetWindowRect(hwnd, &rect);
            iWinWidth = rect.right - rect.left;
            iWinHeight = rect.bottom - rect.top;
            iSysWidth = GetSystemMetrics(SM_CXSCREEN);
            iSysHeight = GetSystemMetrics(SM_CYSCREEN);

            // Move window right on Shift + Arrow Right
            if((wParam == VK_RIGHT)&&(HIBYTE(GetKeyState(VK_SHIFT)) > 1)) {
                if(rect.left >= iSysWidth - iWinWidth) {
                    MoveWindow(hwnd, iSysWidth - iWinWidth, rect.top, iWinWidth, iWinHeight, TRUE);
                }
                else {
                    MoveWindow(hwnd, rect.left + 5, rect.top, iWinWidth, iWinHeight, TRUE);
                }
                break;
            }
            // Move window left on Shift + Arrow Left
            if((wParam == VK_LEFT)&&(HIBYTE(GetKeyState(VK_SHIFT)) > 1)) {
                if(rect.left <= 0) {
                    MoveWindow(hwnd, 0, rect.top, iWinWidth, iWinHeight, TRUE);
                }
                else {
                    MoveWindow(hwnd, rect.left - 5, rect.top, iWinWidth, iWinHeight, TRUE);
                }
                break;
            }
            // Move window down on Shift + Arrow Down
            if((wParam == VK_DOWN)&&(HIBYTE(GetKeyState(VK_SHIFT)) > 1)) {
                if(rect.top >= iSysHeight - iWinHeight) {
                    MoveWindow(hwnd, rect.left, iSysHeight - iWinHeight, iWinWidth, iWinHeight, TRUE);
                }
                else {
                    MoveWindow(hwnd, rect.left, rect.top + 5, iWinWidth, iWinHeight, TRUE);
                }
                break;
            }
            // Move window up on Shift + Arrow Up
            if((wParam == VK_UP)&&(HIBYTE(GetKeyState(VK_SHIFT)) > 1)) {
                if(rect.top <= 0) {
                    MoveWindow(hwnd, rect.left, 0, iWinWidth, iWinHeight, TRUE);
                }
                else {
                    MoveWindow(hwnd, rect.left, rect.top - 5, iWinWidth, iWinHeight, TRUE);
                }
                break;
            }
            return DefWindowProc (hwnd, WM_PAINT, wParam, lParam);

        case WM_PAINT:
            return DefWindowProc (hwnd, WM_PAINT, wParam, lParam);
            break;

        case WM_DESTROY:
            PostQuitMessage (0);
            break;

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

