// WinAPILecture.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinAPILecture.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
/*wchar_t를 재정의한 것이다.*/
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다. 문자열 선언
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다. 문자열 선언

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_/*변수의 용도 SAL 주석 언어이다. Docs Microsoft 데이터가 입력된다.*/ HINSTANCE hInstance
                        /*실행 된 프로세스의 시작 주소. 현재는 같은 프로그램을 키면 같은 시작 주소값을 갖는다
                        가상 메모리 덕분에 이런것이 가능하다. 동일한 주소지만, 가상 메모리에서 지칭 위치기 때문에
                        실제로 같은 주소는 아니다.*/,
                     _In_opt_/*부과적인 데이터 필요없는 데이터이다.*/ HINSTANCE hPrevInstance,
                        /*이전에 실행된 프로세스의 시작 주소*/
                     _In_ LPWSTR/*문자열 포인터*/    lpCmdLine/*CMD로 프로그램을 실행시킬 때 문자를 받는 곳이다.*/,
                     _In_ int       nCmdShow)   
{// 아래 2둘은 필요없다.
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPILECTURE, szWindowClass, MAX_LOADSTRING);
    // 프로젝트 이름으로 원도우 창 초기화 정보 등록
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    // 윈도우 생성 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPILECTURE));

    // 꺼낸 메시지
    MSG msg;

    // 기본 메시지 루프입니다: 메세지는 자료구조 큐이다.
    // 포커싱된 윈도우 창이다. 메세지를 꺼낸다 와일문을 돌면서
    // 메시지를 채워준다.

    // GetMessage
    // 메세지 큐에서 메시지 확인할 때까지 대기 메시지가 없다면 종료하지 않는다.
    // True or false 메시지의 종류에 따라 결정이 된다.
    // msg.message == WM_QUIT 인 경우 false를 반환 -> 프로그램 종료 -> 이제 종료해도 된다.

    msg.hwnd;
    // 이 메시지가 발생한 윈도우
    // 각자 윈도우는 각자 처리를 하는데 이를 프로시져 함수라고한다.

    while (GetMessage(&msg, nullptr, 0, 0))
    {

        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg); 
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//  윈도우의 정보를 등록한다.

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPILECTURE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPILECTURE);
    wcex.lpszClassName  = szWindowClass; // 프로젝트의 키 값 이를 토대로 만든다.
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   // 프로젝트의 키 값을 첫 인자로 받아온다.

   HWND hWnd = CreateWindowW(szWindowClass, L"MyGame"/*윈도우 창을 만들때 들어갈 이름*/, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            // 윈도우 핸들
            // 윈도우 좌표
            // 작업 영역 좌상단 0,0 단위가 무언인가? 1씩 증가가 어느정도일까? 단위는 픽셀이다.
            // Pixel 해상도와 관련이 되어있다. Resolution
            // 화소이다.

            // HDC?

            Rectangle(hdc,10,10,110,110);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
