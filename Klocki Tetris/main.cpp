#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <random>

HDC hDC = NULL;
HGLRC hRC = NULL;
HWND hWnd = NULL;
HINSTANCE hInstance;

bool keys[256];
bool active = TRUE;
bool fullscreen = FALSE;

char tytul[] = "Tetris";
GLfloat odlegloscKamery = -15.0f;
GLfloat katKamery[3] = { 10.0f, -15.0f, 0.0f };
GLfloat predkoscObrotu = 1.2f;
int rodzajKlocka = 1;
GLfloat obecnaWysokoscKlocka = 0.0f;
GLfloat katKlocka = 0.0f;
bool obrotZgodny = false;
bool obrotPrzeciwny = false;
GLfloat LightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { -10.0f, 0.0f, -10.0f, -1.0f };

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void drawOblock()
{
	glPushMatrix();
	glTranslatef(-0.5f, 0.5f, -0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, 0.5f, -0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, -0.5f, -0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, -0.5f, -0.0f);
	glColor3f(0.5f, 0.5f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();
}

void drawIblock()
{
	glPushMatrix();
	glTranslatef(-0.25f, 1.5f, -0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25f, 0.5f, -0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25f, -0.5f, -0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25f, -1.5f, -0.0f);
	glColor3f(0.5f, 0.5f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();
}

void drawJblock()
{
	glPushMatrix();
	glTranslatef(0.5f, 0.5f, -0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, -0.5f, -0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, -1.5f, -0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, -1.5f, -0.0f);
	glColor3f(0.5f, 0.5f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();
}

void drawLblock()
{
	glPushMatrix();
	glTranslatef(-0.5f, 0.5f, -0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, -0.5f, -0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, -1.5f, -0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, -1.5f, -0.0f);
	glColor3f(0.5f, 0.5f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();
}

void drawSblock()
{
	glPushMatrix();
	glTranslatef(0.5f, 0.5f, -0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, 0.5f, -0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, -0.5f, -0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, -0.5f, -0.0f);
	glColor3f(0.5f, 0.5f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();
}

void drawZblock()
{
	glPushMatrix();
	glTranslatef(-1.5f, 0.5f, -0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, 0.5f, -0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, -0.5f, -0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, -0.5f, -0.0f);
	glColor3f(0.5f, 0.5f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();
}

void drawTblock()
{
	glPushMatrix();
	glTranslatef(0.5f, -0.5f, -0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, 0.5f, -0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, -0.5f, -0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, -0.5f, -0.0f);
	glColor3f(0.5f, 0.5f, 0.0f);
	auxSolidBox(1.0f, 1.0f, 0.5f);
	glPopMatrix();
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0)
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	return TRUE;
}

void DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 1.0f, odlegloscKamery + katKamery[0] / 3);
	glRotatef(katKamery[0], 1.0f, 0.0f, 0.0f);
	glRotatef(katKamery[1], 0.0f, 1.0f, 0.0f);

	if (obecnaWysokoscKlocka < 7.0f)
	{
		glTranslatef(0.0f, 2.0f - obecnaWysokoscKlocka, -0.0f);

		glRotatef(katKlocka, 0.0f, 0.0f, 1.0f);
		if (obrotZgodny == true)
		{
			katKlocka = katKlocka + 90;
			obrotZgodny = false;
		}
		if (obrotPrzeciwny == true)
		{
			katKlocka = katKlocka - 90;
			obrotPrzeciwny = false;
		}

		switch (rodzajKlocka)
		{
		case 0:
			drawOblock();
			break;

		case 1:
			drawIblock();
			break;

		case 2:
			drawJblock();
			break;

		case 3:
			drawLblock();
			break;

		case 4:
			drawSblock();
			break;

		case 5:
			drawZblock();
			break;

		case 6:
			drawTblock();
			break;
		}
	}
	else
	{
		obecnaWysokoscKlocka = 0.0f;
		rodzajKlocka = rand() % 7;
	}

	obecnaWysokoscKlocka = obecnaWysokoscKlocka + 0.06f;
}

GLvoid KillGLWindow(GLvoid)
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (hRC)
	{
		if (!wglMakeCurrent(NULL, NULL))
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;
	}

	if (hDC && !ReleaseDC(hWnd, hDC))
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}

	if (hWnd && !DestroyWindow(hWnd))
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}

	if (!UnregisterClass("OpenGL", hInstance))
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint PixelFormat;
	WNDCLASS wc;
	DWORD dwExStyle;
	DWORD dwStyle;
	RECT WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;

	fullscreen = fullscreenflag;

	hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "OpenGL";

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;
			}
			else
			{
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);
	if (!(hWnd = CreateWindowEx(dwExStyle,
		"OpenGL",
		title,
		dwStyle |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN,
		0, 0,
		WindowRect.right - WindowRect.left,
		WindowRect.bottom - WindowRect.top,
		NULL,
		NULL,
		hInstance,
		NULL)))
	{
		KillGLWindow();
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		bits,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	if (!(hDC = GetDC(hWnd)))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(hRC = wglCreateContext(hDC)))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!wglMakeCurrent(hDC, hRC))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ReSizeGLScene(width, height);

	if (!InitGL())
	{
		KillGLWindow();
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_ACTIVATE:
		{
			if (!HIWORD(wParam))
			{
				active = TRUE;
			}
			else
			{
				active = FALSE;
			}

			return 0;
		}

		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
			case SC_SCREENSAVE:
			case SC_MONITORPOWER:
				return 0;
			}
			break;
		}

		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		case WM_KEYDOWN:
		{
			keys[wParam] = TRUE;
			return 0;
		}

		case WM_KEYUP:
		{
			keys[wParam] = FALSE;
			return 0;
		}

		case WM_SIZE:
		{
			ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));
			return 0;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, 
	int nShowCmd)
{
	MSG	msg;
	BOOL done = FALSE;

	MessageBox(NULL, "Strzalki w lewo/prawo - obracanie klockow \nStrzalki w gore/dol - zmiana predkosci opadania klocka", "Sterowanie", NULL);
	if (!CreateGLWindow(tytul, 640, 480, 16, fullscreen))
	{
		return 0;
	}

	int lastTick = 0;
	while (!done)
	{

		bool isRenderingDone = false;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (active)
			{
				if (keys[VK_ESCAPE])
				{
					done = TRUE;
				}
				else
				{
					int tick = GetTickCount();
					if (tick - lastTick >= 20)
					{
						DrawGLScene();
						SwapBuffers(hDC);
						lastTick = tick;
						isRenderingDone = true;
					}
				}

				if (isRenderingDone)
				{
					if (keys[VK_UP])
					{
						obecnaWysokoscKlocka = obecnaWysokoscKlocka - 0.03f;
					}
					if (keys[VK_DOWN])
					{
						obecnaWysokoscKlocka = obecnaWysokoscKlocka + 0.3f;
					}
					if (keys[VK_LEFT])
					{
						obrotZgodny = true;
					}
					if (keys[VK_RIGHT])
					{
						obrotPrzeciwny = true;
					}
				}
			}
		}
	}
	KillGLWindow();
	return (msg.wParam);
}