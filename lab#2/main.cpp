#include <windows.h>
#include <stdlib.h>

#define IDC_LIST_BOX      100
#define IDC_NEW_ITEM      101

#define IDC_ADD_BUTTON    102
#define IDC_REMOVE_BUTTON 103
#define IDC_DAY_BUTTON    104
#define IDC_NIGHT_BUTTON  105

#define IDC_FILE_EXIT     106
#define IDC_VIEW_DAY      107
#define IDC_VIEW_NIGHT    108
#define IDC_HELP_ABOUT    109

int iMinWindowHeight = 500;
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
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
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
    static HWND hWndHScroll;
    static HWND hWndVScroll;

    // Size and position variables
    int iWidth  = 60;   // Button width
    int iHeight = 30;   // Button height
    int x;
    int y;

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

    // Paint and size structs
    TEXTMETRIC tm;
    SCROLLINFO si;
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
                xListBox, yListBox,
                iListBoxWidth, iListBoxHeight,
                hwnd,
                (HMENU)IDC_LIST_BOX,
                hProgramInstance,
                NULL);

            // Set "New Item" position
            x = xListBox;
            y = yListBox + iListBoxHeight + 5;

            hwndNewItem = CreateWindowEx(
                (DWORD)NULL,
                TEXT("Edit"),
                TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
                x, y, (iListBoxWidth - iWidth - 5), iHeight,
                hwnd,
                (HMENU)IDC_NEW_ITEM,
                hProgramInstance,
                NULL);
            
            // Set "Add" button position
            x = xListBox + iListBoxWidth - iWidth;
            y = yListBox + iListBoxHeight + 5;

            CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Add"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x, y, iWidth, iHeight,
                hwnd,
                (HMENU)IDC_ADD_BUTTON,
                hProgramInstance,
                NULL);

            // Set "Remove" button position
            x = xListBox + iListBoxWidth + 10;
            y = yListBox + 30;

            CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Remove"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x, y, iWidth, iHeight,
                hwnd,
                (HMENU)IDC_ADD_BUTTON,
                hProgramInstance,
                NULL);
            
            // Set "Clear" button position
            y = y + iHeight + 5;

            CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Clear"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x, y, iWidth, iHeight,
                hwnd,
                (HMENU)IDC_ADD_BUTTON,
                hProgramInstance,
                NULL);

            // Set "Day" button position
            y = y + (iHeight + 5) + 30;

            CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Day"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x, y, iWidth, iHeight,
                hwnd,
                (HMENU)IDC_DAY_BUTTON,
                hProgramInstance,
                NULL);

            // Set "Night" button position
            y = y + iHeight + 5;

            CreateWindowEx(
                (DWORD)NULL,
                TEXT("Button"),
                TEXT("Night"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x, y, iWidth, iHeight,
                hwnd,
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
            AppendMenu(hSubMenu, MF_STRING, IDC_VIEW_DAY, "&Day");
            AppendMenu(hSubMenu, MF_STRING, IDC_VIEW_NIGHT, "&Night");

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
            si.nMax = ((iMinWindowHeight - 50) / cyChar) - 1;
            si.nPage = iHeight / cyChar;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

            // Set horizontal scroll bar range and page size
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_PAGE;
            si.nMin = 0;
            si.nMax = ((iMinWindowWidth - 20) / cxChar) - 1;
            si.nPage = iWidth / cxChar;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
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
            // Get all the horizontal scroll bar information
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

        case WM_PAINT:
            // TODO: Re-position all child windows, with the reference of listbox
            return DefWindowProc(hwnd, message, wParam, lParam); // Default behaviour for now...
            break;

        case WM_DESTROY:
            PostQuitMessage (0);
            break;

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

