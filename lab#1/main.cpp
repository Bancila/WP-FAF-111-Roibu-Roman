#include <windows.h>

#define IDC_UPDATE_BUTTON   100
#define IDC_TEXT_OUTPUT     101


HINSTANCE hIns;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "Lab1Class";

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use wite color for background */
    wincl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl)) return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Laboratory Work #1",/* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndUpdateButton;
    //static
    //HWND hwndTextOutput;
    int screenW;
    int screenH;
    RECT rect ;

    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            screenW = GetSystemMetrics(SM_CXSCREEN);
            screenH = GetSystemMetrics(SM_CYSCREEN);
            GetWindowRect(hwnd, &rect);
            SetWindowPos(hwnd, 0, (screenW - rect.right)/2, (screenH - rect.bottom)/2, 0, 0, SWP_NOZORDER|SWP_NOSIZE);

            /*hwndTextOutput = CreateWindowEx(
                                            (DWORD)NULL,
                                            TEXT("output"),
                                            TEXT(""),
                                            WS_CHILD|WS_VISIBLE|WS_BORDER|WS_VSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_READONLY,
                                            5, 20,                                                          // the left and top co-ordinates
                                            382, 140,                                                       // width and height
                                            hwnd,                                                           // parent window handle
                                            (HMENU)IDC_TEXT_OUTPUT,                                           // the ID of your editbox
                                            hIns,                                                          // the instance of your application
                                            NULL);*/


            hwndUpdateButton = CreateWindowEx(
                (DWORD)NULL,
                TEXT("updatebtn"),                                                 // The class name required is button
                TEXT("Update"),                                   // the caption of the button
                WS_CHILD |WS_VISIBLE | BS_PUSHBUTTON,                           // the styles
                257, 170,                                                       // the left and top co-ordinates
                130, 20,                                                        // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_UPDATE_BUTTON,                                          // the ID of your button
                hIns,                                                          // the instance of your application
                NULL);
        break;

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
