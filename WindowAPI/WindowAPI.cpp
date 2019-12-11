// WindowAPI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WindowAPI.h"
#include "string"
#include "iostream"
//using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWAPI));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWAPI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWAPI);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, widthz, height, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
CString GetSex(HWND hWnd) {
	if (IsDlgButtonChecked(hWnd, radioMale)) return _T("\nSex: Male");
	else if (IsDlgButtonChecked(hWnd, radioFaMale)) return _T("\nSex: FaMale");
	else 
	{
		MessageBox(hWnd, _T("Select sex???"), _T("Warning"), MB_OK);
		return _T("\nSex: ");
	}
}


CString GetName(HWND hWnd) {
	CString s = _T("\nName: ");
	char a[100];
	GetDlgItemTextW(hWnd, comboboxName, (LPUWSTR)a, 98);
	for (size_t i = 0; i < 98; i += 2)
	{
		if (a[i] == '\0') break;
		s += a[i];
	}
	return s;
}
CString GetLanguage(HWND hWnd){
	CString language = _T("\nLanguage: ");
	//IsDlgButtonChecked(hWnd, id)
	if (IsDlgButtonChecked(hWnd, checkboxEnglish)) language += _T("English\t");
	if (IsDlgButtonChecked(hWnd, checkboxFrance)) language += _T("France\t");
	if (IsDlgButtonChecked(hWnd, checkboxChina)) language += _T("China\t");
	if(language.GetLength()<15) MessageBox(hWnd, _T("Select language???"), _T("Warning"), MB_OK);
	return language;
}
CString GetAddress(HWND hWnd) {
	CString s = _T("\nAddress: ");
	char a[100];
	GetDlgItemTextW(hWnd, txtAddress, (LPUWSTR)a, 98);
	for (size_t i = 0; i < 98; i += 2)
	{
		if (a[i] == '\0') break;
		s += a[i];
	}
	return s;
}
void bntOK_click(HWND hWnd) {
	//string s = GetValues(hWnd);
	CString name = GetName(hWnd);
	CString sex = GetSex(hWnd);
	CString language = GetLanguage(hWnd);
	CString address = GetAddress(hWnd);
	/*TCHAR * p = _T(a);
	CString s = p;*/
	int msgboxID = MessageBox(hWnd, name + sex + language + address , _T("Imformation"), MB_YESNO);
	switch (msgboxID)
	{
	case IDYES:
		DestroyWindow(hWnd);
		break;
	case IDNO:
		break;
	default:
		break;
	}
}

int  Radio_sex_Click(HWND hWnd, int id, int x) {
	if (CheckDlgButton(hWnd, id, x)) return 0;
	return 1;
}
void CheckBox_Language_Click(HWND hWnd, int id) {
	bool checked = IsDlgButtonChecked(hWnd, id);
	if (checked) CheckDlgButton(hWnd, id, BST_UNCHECKED);
	else CheckDlgButton(hWnd, id, BST_CHECKED);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE: {
		//name
		CreateWindow(_T("static"), _T("Name: "), WS_VISIBLE | WS_CHILD, 50, 50, 50, 25, hWnd, NULL, NULL, NULL, NULL);
		CreateWindowExW(WS_EX_STATICEDGE, _T("COMBOBOX"), _T("comboboxName"), CBS_DROPDOWN | WS_CHILD | WS_VISIBLE, 150, 50, 250, 50, hWnd, (HMENU)comboboxName, NULL, NULL); // 100 = ID of this control
		//sex
		CreateWindowW(_T("static"), _T("Sex: "), WS_VISIBLE | WS_CHILD, 50, 125, 50, 25, hWnd, NULL, NULL, NULL, NULL);
		CreateWindow(TEXT("BUTTON"), TEXT("Male"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 175, 125, 50, 25, hWnd, (HMENU)radioMale, NULL, NULL);
		CreateWindow(TEXT("BUTTON"), TEXT("FaMale"), WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 275, 125, 75, 25, hWnd, (HMENU)radioFaMale, NULL, NULL);
		//language
		CreateWindowW(_T("static"), _T("Language: "), WS_VISIBLE | WS_CHILD, 50, 200, 75, 25, hWnd, NULL, NULL, NULL, NULL);
		CreateWindow(TEXT("button"), TEXT("English"), WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 150, 200, 75, 25, hWnd, (HMENU)checkboxEnglish, NULL, NULL);
		CreateWindow(TEXT("button"), TEXT("France"), WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 230, 200, 75, 25, hWnd, (HMENU)checkboxFrance, NULL, NULL);
		CreateWindow(TEXT("button"), TEXT("China"), WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 310, 200, 75, 25, hWnd, (HMENU)checkboxChina, NULL, NULL);
		//address
		CreateWindowW(_T("static"), _T("Address: "), WS_VISIBLE | WS_CHILD, 50, 275, 75, 25, hWnd, NULL, NULL, NULL, NULL);
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE, 150, 275, 250, 25, hWnd, (HMENU)txtAddress, NULL, NULL);
		//button ok
		CreateWindowW(_T("button"), _T("ok"), WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 200, 350, 50, 50, hWnd, (HMENU)btnOK, 0, NULL);
		break;
	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case comboboxName:
		{
			break;
		}
		case btnOK:
		{
			bntOK_click(hWnd);
			break;
		}
		case radioMale:
		{
			Radio_sex_Click(hWnd, radioFaMale, Radio_sex_Click(hWnd, radioMale, 1));
			break;
		}
		case radioFaMale: {
			Radio_sex_Click(hWnd, radioMale, Radio_sex_Click(hWnd, radioFaMale, 1));
			break;
		}
		case IDM_ABOUT:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		}
		case checkboxChina:
		{
			CheckBox_Language_Click(hWnd, checkboxChina);
			break;
		}
		case checkboxEnglish:
		{
			CheckBox_Language_Click(hWnd, checkboxEnglish);
			break;
		}
		case checkboxFrance:
		{
			CheckBox_Language_Click(hWnd, checkboxFrance);
			break;
		}
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
		// TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
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
