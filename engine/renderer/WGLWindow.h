// File:        renderer/WGLWindow.h
// Author:      Mitchell Harvey
// Date:        3/23/2011
// 

#ifndef ENGINE_RENDERER_WGLWINDOW_H_
#define ENGINE_RENDERER_WGLWINDOW_H_

#include <Windows.h>

#include "renderer/Window.h"

namespace engine {
namespace renderer {

LRESULT CALLBACK WGLWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class WGLWindow : public Window
{
friend LRESULT CALLBACK WGLWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
friend Window *CreateNewWindow(void);
friend void DestroyWindow(Window *pWindow);
protected:
    void EnableRenderTarget(void);
    void DisableRenderTarget(void);
private:
    WGLWindow(HINSTANCE hInstance, HWND hWnd, RenderContext *pRC);
    WGLWindow(const WGLWindow &) { }
    ~WGLWindow(void);
    
    void ImplementationSetWindowTitle(const system::utf8 &title);
    void ImplementationSetWindowVisible(bool visible);
    void ImplementationSetWindowPosition(const math::vector2 &pos);
    void ImplementationSetWindowSize(const math::vector2 &size);
    void *ImplementationGetWindowHandle(void) const;
    system::UINT32 ImplementationProcessWindowMessages(void);

    HINSTANCE _hInstance;
    HWND _hWnd;

};
} // renderer
} // engine
#endif // ENGINE_RENDERER_WGLWINDOW_H_
