// File:        renderer/WGLWindow.cpp
// Author:      Mitchell Harvey
// Date:        3/23/2011
// 

#include "GL/glew.h"
#include "GL/wglew.h"

#include "renderer/WGLWindow.h"
#include "renderer/WGLRenderContext.h"

namespace engine {
namespace renderer {

Window *CreateNewWindow(void)
{

    static system::UINT32 sWindowID = 0;
    char wndClassName[256] = {0};
    _snprintf_s(wndClassName, 256, "EngineWindowClass_%d", sWindowID++);

    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASSEX wndClass;
    wndClass.cbSize         = sizeof(WNDCLASSEX);
    wndClass.style          = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc    = WGLWindowProc;
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = hInstance;
    wndClass.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wndClass.lpszMenuName   = NULL;
    wndClass.lpszClassName  = wndClassName;
    wndClass.hIconSm        = LoadIcon(wndClass.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wndClass))
    {
        // TODO: Log Error
        return NULL;
    }

    HWND hWnd = CreateWindow(wndClassName, "Untitled", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
                                NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        // TODO: Log Error
        return NULL;
    }

    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_SWAP_EXCHANGE;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cAccumBits = 32;
    pfd.cStencilBits = 32;

    HDC hDC = GetDC(hWnd);
    int pixelFormat = ChoosePixelFormat(hDC, &pfd);
    if (!pixelFormat)
    {
        // TODO: Log Error
        return NULL;
    }

    if(!SetPixelFormat(hDC, pixelFormat, &pfd))
    {
        // TODO: Log Error
        return NULL;
    }

    HGLRC hGLRC = wglCreateContext(hDC);

    if (!wglMakeCurrent(hDC, hGLRC))
    {
        // TODO: Log Error
        return NULL;
    }

    if (glewInit() != GLEW_OK)
    {
        //TODO: Log Error
        return NULL;
    }

    if (wglewIsSupported("WGL_ARB_create_context"))
    {
        int attribs[] =
    	{
    		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
    		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
    		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
    		0
    	};

        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hGLRC);

        hGLRC = wglCreateContextAttribsARB(hDC,0, attribs);
    }

    if (!hGLRC)
    {
        // TODO: Log Error
        return NULL;
    }

    if (!wglMakeCurrent(hDC, hGLRC))
    {
        // TODO: Log Error
        return NULL;
    }

    RenderContext *pRC = new WGLRenderContext(hGLRC);
    WGLWindow *pWindow = new WGLWindow(hInstance, hWnd, pRC);

    pWindow->Hide();
    pWindow->SetPosition(pWindow->GetPosition());
    pWindow->SetSize(pWindow->GetSize());

    return pWindow;
}
//------------------------------------------------------------------------------------------------------------------------
void DestroyWindow(Window *pWindow)
{
    char wndClassName[256] = {0};
    HWND hWnd = static_cast<HWND>(pWindow->GetHandle());
    GetClassName(hWnd, wndClassName, 256); 

    WGLRenderContext *pRC = (WGLRenderContext *)pWindow->GetRenderContext();
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(pRC->_hGLRC);

    ReleaseDC(hWnd, GetDC(hWnd));
    ::DestroyWindow(hWnd);
    UnregisterClass(wndClassName, GetModuleHandle(NULL));

    delete pRC;
    delete (WGLWindow *)(pWindow);
}
//------------------------------------------------------------------------------------------------------------------------
WGLWindow::WGLWindow(HINSTANCE hInstance, HWND hWnd, RenderContext *pRC) :
  _hInstance(hInstance)
 ,_hWnd(hWnd)
{
    _pRenderContext = pRC;
}
//------------------------------------------------------------------------------------------------------------------------
WGLWindow::~WGLWindow(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
void WGLWindow::EnableRenderTarget(void)
{
    _pRenderContext->Bind(GetDC(static_cast<HWND>(GetHandle())));
}
//------------------------------------------------------------------------------------------------------------------------
void WGLWindow::DisableRenderTarget(void)
{
    HDC hDC = GetDC(static_cast<HWND>(GetHandle()));
    SwapBuffers(hDC);
    _pRenderContext->Unbind(hDC);
}
//------------------------------------------------------------------------------------------------------------------------
void WGLWindow::ImplementationSetWindowTitle(const system::utf8 &title)
{
    SetWindowText(_hWnd, title.c_str());
}
//------------------------------------------------------------------------------------------------------------------------
void WGLWindow::ImplementationSetWindowVisible(bool visible)
{
    if (visible)
    {
        ShowWindow(_hWnd, SW_SHOW);
        UpdateWindow(_hWnd);
    }
    else
    {
        ShowWindow(_hWnd, SW_HIDE);
    }
}
//------------------------------------------------------------------------------------------------------------------------
void WGLWindow::ImplementationSetWindowPosition(const math::vector2 &pos)
{
    SetWindowPos(_hWnd, NULL, static_cast<int>(pos.x), static_cast<int>(pos.y), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
//------------------------------------------------------------------------------------------------------------------------
void WGLWindow::ImplementationSetWindowSize(const math::vector2 &size)
{
    SetWindowPos(_hWnd, NULL, 0, 0, static_cast<int>(size.x), static_cast<int>(size.y), SWP_NOMOVE | SWP_NOZORDER);
}
//------------------------------------------------------------------------------------------------------------------------
void *WGLWindow::ImplementationGetWindowHandle(void) const
{
    return static_cast<void *>(_hWnd);
}
//------------------------------------------------------------------------------------------------------------------------
system::UINT32 WGLWindow::ImplementationProcessWindowMessages(void)
{
    MSG msg;
    while(PeekMessage(&msg, _hWnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
//------------------------------------------------------------------------------------------------------------------------
LRESULT CALLBACK WGLWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (Window::_sCallbackMap.find(static_cast<void *>(hWnd)) != Window::_sCallbackMap.end())
    {
        Window::_sCallbackMap[static_cast<void *>(hWnd)](msg);
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
} // renderer
} // engine
