#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

HDC hDC = NULL;
HGLRC hRC = NULL;
HWND hWnd = NULL;
HINSTANCE hInstance;

bool keys[256];
bool active = TRUE;
bool fullscreen = FALSE;

char tytul[] = "Zegar wskazowkowy";
GLfloat tarczaWymiary[3] = { 10.0f, 10.0f, 0.5f };
GLfloat odlegloscKamery = -25.0f;
GLfloat katKamery[3] = { 15.0f, 10.0f, 0.0f };
GLfloat predkoscObrotu = 1.2f;
GLfloat LightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { -10.0f, 0.0f, -10.0f, -1.0f };

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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

int DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, odlegloscKamery + katKamery[0] / 3);
	glRotatef(katKamery[0], 1.0f, 0.0f, 0.0f);
	glRotatef(katKamery[1], 0.0f, 1.0f, 0.0f);

	SYSTEMTIME czasSystemowy;
	GetLocalTime(&czasSystemowy);
	int aktualnyCzas[3] = { czasSystemowy.wHour, czasSystemowy.wMinute, czasSystemowy.wSecond };

	GLfloat katH = (aktualnyCzas[0] + (aktualnyCzas[1] / 60.0f)) * 30.0f;
	GLfloat katM = (aktualnyCzas[1] + (aktualnyCzas[2] / 60.0f)) * 6.0f;
	GLfloat katS = aktualnyCzas[2] * 6.0f;

	glPushMatrix();
	glRotatef(45, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	auxSolidBox(tarczaWymiary[0], tarczaWymiary[1], tarczaWymiary[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.5f);
	glColor3f(0.5f, 0.5f, 1.0f);
	auxSolidCube(0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.35f);
	glRotatef(katH, 0.0f, 0.0f, -1.0f);
	glTranslatef(0.0f, 1.5f, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	auxSolidBox(0.3f, 3.0f, 0.1f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.5f);
	glRotatef(katM, 0.0f, 0.0f, -1.0f);
	glTranslatef(0.0f, 1.75f, 0.0);
	glColor3f(0.5f, 0.5f, 0.5f);
	auxSolidBox(0.15f, 3.5f, 0.1f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.65f);
	glRotatef(katS, 0.0f, 0.0f, -1.0f);
	glTranslatef(0.0f, 2.0f, 0.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	auxSolidBox(0.08f, 4.0f, 0.1f);
	glPopMatrix();
	for (int i = 0; i < 12; i++)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.3f);
		glRotatef(i * 30, 0.0f, 0.0f, -1.0f);
		glTranslatef(0.0f, 4.5f, 0.0);
		if (i % 3 == 0)
		{
			glColor3f(0.0f, 0.0f, 0.0f);
			auxSolidBox(0.2f, 0.5f, 0.1f);
		}
		else
		{
			glColor3f(0.5f, 0.5f, 1.0f);
			auxSolidBox(0.2f, 0.2f, 0.1f);
		}
		glPopMatrix();
	}

	return TRUE;
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
	int nCmdShow)
{
	MSG	msg;
	BOOL done = FALSE;

	MessageBox(NULL, "Strzalki - obracanie kamery", "Sterowanie", NULL);
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
			}

			if (isRenderingDone)
			{
				if (keys[VK_UP])
				{
					katKamery[0] = katKamery[0] + predkoscObrotu;
					if (katKamery[0] > 45)
					{
						katKamery[0] = 45;
					}
				}
				if (keys[VK_DOWN])
				{
					katKamery[0] = katKamery[0] - predkoscObrotu;
					if (katKamery[0] < -7)
					{
						katKamery[0] = -7;
					}
				}
				if (keys[VK_LEFT])
				{
					katKamery[1] = katKamery[1] + predkoscObrotu;
					if (katKamery[1] > 360)
					{
						katKamery[1] = katKamery[1] - 360;
					}
					if (katKamery[1] < 0)
					{
						katKamery[1] = katKamery[1] + 360;
					}
				}
				if (keys[VK_RIGHT])
				{
					katKamery[1] = katKamery[1] - predkoscObrotu;
					if (katKamery[1] > 360)
					{
						katKamery[1] = katKamery[1] - 360;
					}
					if (katKamery[1] < 0)
					{
						katKamery[1] = katKamery[1] + 360;
					}
				}
			}
		}
	}
	KillGLWindow();
	return (msg.wParam);
}
