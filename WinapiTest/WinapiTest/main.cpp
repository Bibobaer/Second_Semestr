#include <Windows.h>
#include "resource.h"
#include <math.h>

#define SolarCentryX       400
#define SolarCentryY       360
#define SolarRadius        50

#define IDT_TIMER	1


LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void CreateSolar(HWND hWnd);

typedef struct Planet 
{
	int radius;
	float posX, posY;
	float angel;
	HPEN pen;
}Planet;

Planet Earth;
Planet Venus;
Planet Mercury;

void CreatePlanet(Planet* pl, int rad, float x, float y);
void UpdatePlanet();
void DrawPlanet(HDC hdc);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) 
{
	CreatePlanet(&Earth, 25, 0, 0);
	CreatePlanet(&Venus, 30, 0, 0);
	CreatePlanet(&Mercury, 15, 0, 0);

	WNDCLASS SoftWareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		L"MainWindowClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftWareMainClass)) { return -1; }

	MSG SoftWareMainMessage = { 0 };

	HWND hwnd;
	hwnd = CreateWindow(L"MainWindowClass", L"Никита лох", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 10, 10, 850,770, NULL, NULL, NULL, NULL);

	if (!hwnd)
		return -1;

	while (GetMessage(&SoftWareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftWareMainMessage);
		DispatchMessage(&SoftWareMainMessage);
	}

	return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure)
{
	WNDCLASS NWC = { 0 };
	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;
	
	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) 
{
	UINT_PTR ptr;
	ptr = SetTimer(hWnd, IDT_TIMER, 1, NULL);
	
	switch (msg){
		case WM_CREATE:
			Earth.pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
			Venus.pen = CreatePen(PS_SOLID, 2, RGB(255, 100, 50));
			Mercury.pen = CreatePen(PS_SOLID, 2, RGB(255, 50, 147));

			break;
		case WM_TIMER: {

			switch (ptr) {

			case IDT_TIMER: {
				UpdatePlanet();
				InvalidateRect(hWnd, NULL, FALSE);
				break;
				}
			}
		}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		FillRect(hdc, &ps.rcPaint, GetSysColorBrush(COLOR_BACKGROUND));
		CreateSolar(hWnd);

		DrawPlanet(hdc);
		EndPaint(hWnd, &ps);
	}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, IDT_TIMER);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void CreateSolar(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);

	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));

	SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(255, 255, 0));
	Ellipse(hdc, SolarCentryX - SolarRadius, SolarCentryY - SolarRadius,
		SolarCentryX + SolarRadius, SolarCentryY + SolarRadius);

	ReleaseDC(hWnd, hdc);
}

void CreatePlanet(Planet* pl, int rad, float x, float y) 
{
	pl->posX = x;
	pl->posY = y;
	pl->radius = rad;
	pl->angel = 0;
}

void UpdatePlanet() 
{
	Mercury.angel += 0.07;
	Mercury.posX = SolarCentryX + (Mercury.radius + 100) * cos(Mercury.angel);
	Mercury.posY = SolarCentryY + (Mercury.radius + 100) * sin(Mercury.angel);

	Venus.angel += 0.06;
	Venus.posX = SolarCentryX + (Venus.radius + 200) * cos(Venus.angel);
	Venus.posY = SolarCentryY + (Venus.radius + 200) * sin(Venus.angel);

	Earth.angel += 0.05;
	Earth.posX = SolarCentryX + (Earth.radius + 300) * cos(Earth.angel);
	Earth.posY = SolarCentryY + (Earth.radius + 300) * sin(Earth.angel);
}

void DrawPlanet(HDC hdc) 
{
	for (int i = 0; i < 100; ++i) {
		int x = rand() % 850;
		int y = rand() % 770;
		SetPixel(hdc, x, y, RGB(255, 255, 255));
	}

	SelectObject(hdc, Mercury.pen);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(255, 0, 0));
	Ellipse(hdc, Mercury.posX - Mercury.radius, Mercury.posY - Mercury.radius,
		Mercury.posX + Mercury.radius, Mercury.posY + Mercury.radius);

	SelectObject(hdc, Venus.pen);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(255, 100, 0));
	Ellipse(hdc, Venus.posX - Venus.radius, Venus.posY - Venus.radius,
		Venus.posX + Venus.radius, Venus.posY + Venus.radius);

	SelectObject(hdc, Earth.pen);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(0, 255, 0));
	Ellipse(hdc, Earth.posX - Earth.radius, Earth.posY - Earth.radius,
		Earth.posX + Earth.radius, Earth.posY + Earth.radius);
}