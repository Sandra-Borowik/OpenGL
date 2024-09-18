#include <windows.h>		 
#include <gl\gl.h>			 
#include <gl\glu.h>			 

HDC hDC = NULL;		 
HGLRC hRC = NULL;		 
HWND hWnd = NULL;		 
HINSTANCE hInstance;		 

bool keys[256];			 
bool active = TRUE;		 
bool fullscreen = FALSE;	 

char tytul[] = "Animacje szescianow";
int mode = 1;							 
GLint liczbaSzescianowWLinii = 3;				 
GLfloat katObrotuWszystkichSzescianow = 0.0f;				 
GLfloat katObrotuSzescianu = 0.0f;			 
GLfloat odstepBiezacy = 1.4f;				 
GLfloat odstepMin = 1.2f;			 
GLfloat odstepMax = 2.0f;			 
GLfloat wielkoscSzescianu = 0.85f;					 
bool zwiekszanieOdstepu = true;				 
GLfloat czerwony[2] = { 0.0f,1.0f };	 
GLfloat zielony[2] = { 0.0f,1.0f };	 
GLfloat niebieski[2] = { 0.0f,1.0f };	 
bool czerwonyFlaga = true;							 
bool zielonyFlaga = true;
bool niebieskiFlaga = true;
GLfloat predkoscObrotuWszystkichSzescianow = -0.5f;		 
GLfloat predkoscObrotuSzescianu = -1.0f;	 
GLfloat predkoscZmianyOdstepu = 0.01f;		 
GLfloat predkoscZmianyKoloru = 0.02f;			 
GLfloat odlegloscKamery = -8;
GLfloat LightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { -10.0f, 0.0f, -10.0f, -1.0f };

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	 

void drawCube(GLfloat rozmiar, GLfloat rotation) {  
	rozmiar = rozmiar / 2;
	glPushMatrix();						 
	glRotatef(rotation, 0.0f, 1.0f, 0.0f);  
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, -1.0f);			 
	glVertex3f(-rozmiar, rozmiar, -rozmiar);		 
	glVertex3f(rozmiar, rozmiar, -rozmiar);
	glVertex3f(rozmiar, -rozmiar, -rozmiar);
	glVertex3f(-rozmiar, -rozmiar, -rozmiar);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-rozmiar, rozmiar, rozmiar);			 
	glVertex3f(-rozmiar, -rozmiar, rozmiar);
	glVertex3f(rozmiar, -rozmiar, rozmiar);
	glVertex3f(rozmiar, rozmiar, rozmiar);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-rozmiar, -rozmiar, rozmiar);		 
	glVertex3f(rozmiar, -rozmiar, rozmiar);
	glVertex3f(rozmiar, -rozmiar, -rozmiar);
	glVertex3f(-rozmiar, -rozmiar, -rozmiar);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-rozmiar, rozmiar, rozmiar);			 
	glVertex3f(-rozmiar, rozmiar, -rozmiar);
	glVertex3f(rozmiar, rozmiar, -rozmiar);
	glVertex3f(rozmiar, rozmiar, rozmiar);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-rozmiar, -rozmiar, rozmiar);	 
	glVertex3f(-rozmiar, rozmiar, rozmiar);
	glVertex3f(-rozmiar, rozmiar, -rozmiar);
	glVertex3f(-rozmiar, -rozmiar, -rozmiar);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(rozmiar, -rozmiar, rozmiar);		 
	glVertex3f(rozmiar, -rozmiar, -rozmiar);
	glVertex3f(rozmiar, rozmiar, -rozmiar);
	glVertex3f(rozmiar, rozmiar, rozmiar);

	glEnd();
	glPopMatrix();							 
	return;
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

int DrawGLScene(GLvoid)									 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	 
	glLoadIdentity();									 

	glTranslatef(0.0f, 0.0f, odlegloscKamery);					 
	glRotatef(30, 0.8f, 0.0f, 0.0f);					 

	glRotatef(katObrotuWszystkichSzescianow, 0.0f, 1.0f, 0.0f);
	glTranslatef(-(liczbaSzescianowWLinii - 1) * odstepBiezacy / 2, -(liczbaSzescianowWLinii - 1) * odstepBiezacy / 2, -(liczbaSzescianowWLinii - 1) * odstepBiezacy / 2);   

	for (int x = 0; x < liczbaSzescianowWLinii; x++)
	{
		glPushMatrix();
		glTranslatef(x * odstepBiezacy, 0.0f, 0.0f);
		for (int y = 0; y < liczbaSzescianowWLinii; y++)
		{
			glPushMatrix();
			glTranslatef(0.0f, y * odstepBiezacy, 0.0f);
			for (int z = 0; z < liczbaSzescianowWLinii; z++)
			{
				glPushMatrix();
				glTranslatef(0.0f, 0.0f, z * odstepBiezacy);

				if (x == 2 && z == 0 && y == 2)
					glColor3f(czerwony[1], zielony[1], niebieski[0]);
				else if (x == 1 && z == 1 && y == 2)
					glColor3f(czerwony[1], zielony[0], niebieski[0]);
				else if (x == 0 && z == 2 && y == 2)
					glColor3f(czerwony[0], zielony[1], niebieski[0]);
				else
					glColor3f(czerwony[0], zielony[0], niebieski[1]);

				drawCube(wielkoscSzescianu, katObrotuSzescianu);
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}

	if (mode == 1)
	{
		katObrotuWszystkichSzescianow = katObrotuWszystkichSzescianow + predkoscObrotuWszystkichSzescianow;
		if (katObrotuWszystkichSzescianow > 360)
			katObrotuWszystkichSzescianow = katObrotuWszystkichSzescianow - 360;
		if (katObrotuWszystkichSzescianow < 0)
			katObrotuWszystkichSzescianow = katObrotuWszystkichSzescianow + 360;
	}
	else if (mode == 2)
	{
		katObrotuSzescianu = katObrotuSzescianu + predkoscObrotuSzescianu;
		if (katObrotuSzescianu > 360)
			katObrotuSzescianu = katObrotuSzescianu - 360;
		if (katObrotuSzescianu < 0)
			katObrotuSzescianu = katObrotuSzescianu + 360;
	}
	else if (mode == 3)
	{
		if (zwiekszanieOdstepu)
			odstepBiezacy = odstepBiezacy + predkoscZmianyOdstepu;
		else
			odstepBiezacy = odstepBiezacy - predkoscZmianyOdstepu;

		if (odstepBiezacy >= odstepMax || odstepBiezacy <= odstepMin)
			zwiekszanieOdstepu = !zwiekszanieOdstepu;
	}
	else if (mode == 4)
	{
		if (czerwonyFlaga)
		{
			czerwony[1] = czerwony[1] + predkoscZmianyKoloru;
			if (czerwony[1] > 1.0f)
			{
				czerwony[1] = 1.0f;
				czerwonyFlaga = !czerwonyFlaga;
			}
		}
		else
		{
			czerwony[1] = czerwony[1] - predkoscZmianyKoloru;
			if (czerwony[1] < 0.0f)
			{
				czerwony[1] = 0.0f;
				czerwonyFlaga = !czerwonyFlaga;
			}
		}

		if (zielonyFlaga)
		{
			zielony[1] = zielony[1] + predkoscZmianyKoloru;
			if (zielony[1] > 1.0f)
			{
				zielony[1] = 1.0f;
				zielonyFlaga = !zielonyFlaga;
			}
		}
		else
		{
			zielony[1] = zielony[1] - predkoscZmianyKoloru;
			if (zielony[1] < 0.0f)
			{
				zielony[1] = 0.0f;
				zielonyFlaga = !zielonyFlaga;
			}
		}

		if (niebieskiFlaga)
		{
			niebieski[0] = niebieski[0] + predkoscZmianyKoloru;
			if (niebieski[0] > 1.0f)
			{
				niebieski[0] = 1.0f;
				niebieskiFlaga = !niebieskiFlaga;
			}
		}
		else
		{
			niebieski[0] = niebieski[0] - predkoscZmianyKoloru;
			if (niebieski[0] < 0.0f)
			{
				niebieski[0] = 0.0f;
				niebieskiFlaga = !niebieskiFlaga;
			}
		}
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

LRESULT CALLBACK WndProc(HWND	hWnd,
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

	MessageBox(NULL, "Przelaczanie trybow - klawisze: 1, 2, 3, 4", "Sterowanie", NULL);


	if (!CreateGLWindow(tytul, 640, 480, 16, fullscreen))
	{
		return 0;
	}
	int lastTick = 0;
	while (!done)
	{

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
					}
				}
			}

			if (keys['1'])
			{
				keys['1'] = false;
				mode = 1;
			}
			if (keys['2'])
			{
				keys['2'] = false;
				mode = 2;
			}
			if (keys['3'])
			{
				keys['3'] = false;
				mode = 3;
			}
			if (keys['4'])
			{
				keys['4'] = false;
				mode = 4;
			}
		}
	}

	KillGLWindow();
	return (msg.wParam);
}