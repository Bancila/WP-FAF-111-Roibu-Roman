#include <windows.h>
#include <stdlib.h>

#define IDC_LIST_BOX      100
#define IDC_NEW_ITEM      101

#define IDC_ADD_BUTTON    102
#define IDC_REMOVE_BUTTON 103
#define IDC_DAY_BUTTON    104
#define IDC_NIGHT_BUTTON  105

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
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 500,
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

