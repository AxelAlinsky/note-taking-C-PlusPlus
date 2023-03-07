#include <Windows.h>
#include <cstdio>

const int ID_EDIT_BOX = 1;
const int ID_SAVE_BUTTON = 2;
const int MAX_TEXT_LENGTH = 1000;

void OnSaveButtonClicked(HWND hEditBox) {
    char note[MAX_TEXT_LENGTH];
    GetWindowText(hEditBox, note, MAX_TEXT_LENGTH);
    FILE* fp = fopen("note.txt", "w");
    if (fp) {
        fprintf(fp, "%s", note);
        fclose(fp);
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_SAVE_BUTTON) {
                HWND hEditBox = GetDlgItem(hwnd, ID_EDIT_BOX);
                OnSaveButtonClicked(hEditBox);
            }
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "NoteTakingAppClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Note Taking App",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    HWND hEditBox = CreateWindowEx(
        0,
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
        10, 10, 380, 200,
        hwnd,
        (HMENU) ID_EDIT_BOX,
        hInstance,
        NULL
    );

    HWND hButton = CreateWindowEx(
        0,
        "BUTTON",
        "Save",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        160, 220, 80, 25,
        hwnd,
        (HMENU) ID_SAVE_BUTTON,
        hInstance,
        NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
