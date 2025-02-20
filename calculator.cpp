#include <windows.h>
#include <stdio.h>

#define ID_EDIT1 1
#define ID_EDIT2 2
#define ID_BUTTON_ADD 3
#define ID_BUTTON_SUB 4
#define ID_BUTTON_MUL 5
#define ID_BUTTON_DIV 6

HWND hEdit1, hEdit2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("STATIC", "Please input two numbers",
                         WS_VISIBLE | WS_CHILD,
                         20, 10, 200, 20,
                         hwnd, NULL, NULL, NULL);

			hEdit1 = CreateWindow("EDIT", "",
							WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
							50, 40, 150, 20,  // เปลี่ยน x เป็น 50
							hwnd, (HMENU)ID_EDIT1, NULL, NULL);
	  
	        hEdit2 = CreateWindow("EDIT", "",
							WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
							50, 70, 150, 20,  // เปลี่ยน x เป็น 50
							hwnd, (HMENU)ID_EDIT2, NULL, NULL);
	  
            CreateWindow("BUTTON", "+",
                         WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                         25, 100, 30, 30,
                         hwnd, (HMENU)ID_BUTTON_ADD, NULL, NULL);

            CreateWindow("BUTTON", "-",
                         WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                         75, 100, 30, 30,
                         hwnd, (HMENU)ID_BUTTON_SUB, NULL, NULL);

            CreateWindow("BUTTON", "*",
                         WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                         125, 100, 30, 30,
                         hwnd, (HMENU)ID_BUTTON_MUL, NULL, NULL);

            CreateWindow("BUTTON", "/",
                         WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                         175, 100, 30, 30,
                         hwnd, (HMENU)ID_BUTTON_DIV, NULL, NULL);
            break;

        case WM_COMMAND: {
            if (LOWORD(wParam) >= ID_BUTTON_ADD && LOWORD(wParam) <= ID_BUTTON_DIV) {
                char text1[20], text2[20];
                GetWindowText(hEdit1, text1, sizeof(text1));
                GetWindowText(hEdit2, text2, sizeof(text2));

                double num1 = atof(text1);
                double num2 = atof(text2);
                double result = 0.0;
                char output[50];

                switch (LOWORD(wParam)) {
                    case ID_BUTTON_ADD: result = num1 + num2; break;
                    case ID_BUTTON_SUB: result = num1 - num2; break;
                    case ID_BUTTON_MUL: result = num1 * num2; break;
                    case ID_BUTTON_DIV: 
                        if (num2 == 0) {
                            MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                            return 0;
                        }
                        result = num1 / num2; 
                        break;
                }

                sprintf(output, "%f", result);
                MessageBox(hwnd, output, "Result", MB_OK | MB_ICONINFORMATION);
            }
            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "CalculatorClass";
    wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 0)); 
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("CalculatorClass", "My Calculator",
		    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, // ไม่มี WS_THICKFRAME หรือ WS_MAXIMIZEBOX
		    CW_USEDEFAULT, CW_USEDEFAULT, 250, 200,
		    NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
