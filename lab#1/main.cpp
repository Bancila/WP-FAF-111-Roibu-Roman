#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define IDC_UPDATE_BUTTON   100
#define IDC_CLEAR_BUTTON    101
#define IDC_QUIT_BUTTON     102
#define IDC_FONT1_BUTTON    103
#define IDC_FONT2_BUTTON    104
#define IDC_FONT3_BUTTON    105
#define IDC_INPUT_TEXT      106
#define IDC_OUTPUT_TEXT     107

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

char szClassName[ ] = "Lab1Class";
HINSTANCE hProgramInstance;

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
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
  "Laboratory Work #1",
  WS_OVERLAPPEDWINDOW,
  CW_USEDEFAULT, CW_USEDEFAULT,
  306, 340,
  HWND_DESKTOP,
  NULL,
  hThisInstance,
  NULL);

  ShowWindow (hwnd, nCmdShow);

  srand(time(NULL));

  while (GetMessage (&messages, NULL, 0, 0))
  {
    TranslateMessage(&messages);
    DispatchMessage(&messages);
  }

  return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  static HWND hwndInputText;
  static HWND hwndOutputText;
  int iScreenW;
  int iScreenH;
  PAINTSTRUCT ps;
  RECT rect;
  HDC hdc;
  HWND hwndBtn;
  int iTextLength;
  char * szText;
  HFONT hfFont;

  switch(message)
  {
    case WM_CREATE:
      iScreenW = GetSystemMetrics(SM_CXSCREEN);
      iScreenH = GetSystemMetrics(SM_CYSCREEN);

      GetWindowRect(hwnd, &rect);
      SetWindowPos(
        hwnd, 0,
        (iScreenW - rect.right)/2,
        (iScreenH - rect.bottom)/2,
        0, 0,
        SWP_NOZORDER|SWP_NOSIZE);

      CreateWindowEx(
        (DWORD)NULL,
        TEXT("button"),
        TEXT("Update"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        220, 200,
        60, 20,
        hwnd,
        (HMENU)IDC_UPDATE_BUTTON,
        hProgramInstance,
        NULL);

      CreateWindowEx(
        (DWORD)NULL,
        TEXT("button"),
        TEXT("Clear"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        220, 230,
        60, 20,
        hwnd,
        (HMENU)IDC_CLEAR_BUTTON,
        hProgramInstance,
        NULL);

      CreateWindowEx(
      (DWORD)NULL,
      TEXT("button"),
      TEXT("Quit"),
      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW,
      220, 260,
      60, 20,
      hwnd,
      (HMENU)IDC_QUIT_BUTTON,
      hProgramInstance,
      NULL);

      CreateWindowEx(
      (DWORD)NULL,
      TEXT("button"),
      TEXT("Tahoma"),
      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
      10, 260,
      60, 20,
      hwnd,
      (HMENU)IDC_FONT1_BUTTON,
      hProgramInstance,
      NULL);

      CreateWindowEx(
      (DWORD)NULL,
      TEXT("button"),
      TEXT("Courier"),
      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
      80, 260,
      60, 20,
      hwnd,
      (HMENU)IDC_FONT2_BUTTON,
      hProgramInstance,
      NULL);

      CreateWindowEx(
      (DWORD)NULL,
      TEXT("button"),
      TEXT("Comic"),
      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
      150, 260,
      60, 20,
      hwnd,
      (HMENU)IDC_FONT3_BUTTON,
      hProgramInstance,
      NULL);

      hwndOutputText = CreateWindowEx(
      (DWORD)NULL,
      TEXT("edit"),
      TEXT(""),
      WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_READONLY | ES_MULTILINE,
      10, 40,
      270, 150,
      hwnd,
      (HMENU)IDC_OUTPUT_TEXT,
      hProgramInstance,
      NULL);

      hwndInputText = CreateWindowEx(
      (DWORD)NULL,
      TEXT("edit"),
      TEXT("Your text goes here..."),
      WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE,
      10, 200,
      200, 50,
      hwnd,
      (HMENU)IDC_INPUT_TEXT,
      hProgramInstance,
      NULL);

      hfFont = CreateFont(20,0,0,0,0,0,0,0,0,0,0,0,0,TEXT("Tahoma"));
      SendMessage(hwndOutputText, WM_SETFONT, (WPARAM)hfFont, 1);
      break;

    case WM_COMMAND:
      switch(LOWORD(wParam))
      {
        case IDC_UPDATE_BUTTON:
          iTextLength = SendMessage(hwndInputText, WM_GETTEXTLENGTH, 0, 0);
          szText = (char*)malloc(iTextLength+1);
          SendMessage(hwndInputText, WM_GETTEXT, iTextLength+1, (LPARAM)szText);
          SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)szText);
          free(szText);
          break;

        case IDC_CLEAR_BUTTON:
          SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)"");
          break;

        case IDC_QUIT_BUTTON:
          if(MessageBox(NULL, TEXT("Are you sure you want to quit?"), TEXT("Quit?"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDYES) {
            SendMessage(hwnd, WM_DESTROY, 0, 0);
          };
          break;

        case IDC_FONT1_BUTTON:
          hfFont = CreateFont(20,0,0,0,0,0,0,0,0,0,0,0,0,TEXT("Tahoma"));
          SendMessage(hwndOutputText, WM_SETFONT, (WPARAM)hfFont, 1);
          break;

        case IDC_FONT2_BUTTON:
          hfFont = CreateFont(20,0,0,0,0,0,0,0,0,0,0,0,0,TEXT("Courier New"));
          SendMessage(hwndOutputText, WM_SETFONT, (WPARAM)hfFont, 1);
          break;

        case IDC_FONT3_BUTTON:
          hfFont = CreateFont(20,0,0,0,0,0,0,0,0,0,0,0,0,TEXT("Comic Sans MS"));
          SendMessage(hwndOutputText, WM_SETFONT, (WPARAM)hfFont, 1);
          break;

      }
      break;

    case WM_PAINT:
      hdc = BeginPaint(hwnd, &ps);
      GetClientRect(hwnd, &rect);
      SetBkMode(hdc, TRANSPARENT);
      SetTextColor(hdc, RGB(80, 80, 80));
      DrawText(hdc, "Windows Programming", -1, &rect, DT_CENTER | DT_TOP);
      DrawText(hdc, "\n(c) Roman Roibu, 2013", -1, &rect, DT_CENTER | DT_TOP);
      EndPaint(hwnd, &ps);
      break;

    case WM_DRAWITEM:
      if((UINT)wParam == IDC_QUIT_BUTTON) {
        LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
        SIZE size;
        char szQuitBtnText[5];

        strcpy(szQuitBtnText, "Quit");
        GetTextExtentPoint32(lpdis->hDC, szQuitBtnText, strlen(szQuitBtnText), &size);
        SetTextColor(lpdis->hDC, RGB(250, 250, 250));
        SetBkColor(lpdis->hDC, RGB(200, 50, 50));

        ExtTextOut(
          lpdis->hDC,
          ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
          ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
          ETO_OPAQUE | ETO_CLIPPED,
          &lpdis->rcItem,
          szQuitBtnText,
          strlen(szQuitBtnText),
          NULL);

        DrawEdge(
          lpdis->hDC,
          &lpdis->rcItem,
          (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
          BF_RECT);
        return TRUE;
      }
      break;

    case WM_SYSCOMMAND:
      switch(wParam) {

        case SC_MINIMIZE:
          return MessageBox(NULL, TEXT("Sorry, NO!"), TEXT("Minimize Button Clicked!"), MB_OK | MB_ICONWARNING);

        case SC_MAXIMIZE:
          return MessageBox(NULL, TEXT("Maximizing is too mainstream..."), TEXT("Maximize Button Clicked!"), MB_OK | MB_ICONASTERISK);

        case SC_CLOSE:
          iScreenW = GetSystemMetrics(SM_CXSCREEN);
          iScreenH = GetSystemMetrics(SM_CYSCREEN);

          GetWindowRect(hwnd, &rect);
          SetWindowPos(
            hwnd, 0,
            (iScreenW - rect.right) / 10 * (rand() % 11),
            (iScreenH - rect.bottom) / 10 * (rand() % 11),
            0, 0,
            SWP_NOZORDER|SWP_NOSIZE);

            return MessageBox(NULL, TEXT("Gotcha!\nTo quit safely, click Quit button."), TEXT("MUHAHA!"), MB_OK | MB_ICONASTERISK);
            
        default:
          return DefWindowProc(hwnd, message, wParam, lParam);
      }
      break;

    case WM_DESTROY:
      PostQuitMessage (0);
      break;

    default:
      return DefWindowProc (hwnd, message, wParam, lParam);
  }

  return 0;
}

