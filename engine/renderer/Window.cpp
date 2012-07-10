// File:        renderer/Window.cpp
// Author:      Mitchell Harvey
// Date:        3/23/2011
// 

#include "renderer/Window.h"
#include "renderer/RenderContext.h"

namespace engine {
namespace renderer {

map<void *, WindowMessageCB> Window::_sCallbackMap = map<void *, WindowMessageCB>();

Window::Window(void) :
 _windowTitle("Engine Window")
,_windowPosition(0.0f, 0.0f)
,_windowSize(1024, 768)
,_windowVisible(false)
,_pRenderContext(0)
{
}
//------------------------------------------------------------------------------------------------------------------------
Window::~Window(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
void *Window::GetHandle(void) const
{
    return ImplementationGetWindowHandle();
}
//------------------------------------------------------------------------------------------------------------------------
RenderContext *Window::GetRenderContext(void) const
{
    return _pRenderContext;
}
//------------------------------------------------------------------------------------------------------------------------
void Window::Show(void)
{
    _windowVisible = true;
    ImplementationSetWindowVisible(_windowVisible);
}
//------------------------------------------------------------------------------------------------------------------------
void Window::Hide(void)
{
    _windowVisible = false;
    ImplementationSetWindowVisible(_windowVisible);
}
//------------------------------------------------------------------------------------------------------------------------
bool Window::IsVisible(void)
{
    return _windowVisible;
}
//------------------------------------------------------------------------------------------------------------------------
void Window::SetTitle(const system::utf8 &title)
{
    _windowTitle = title;
    ImplementationSetWindowTitle(_windowTitle);
}
//------------------------------------------------------------------------------------------------------------------------
system::utf8 Window::GetTitle(void) const
{
    return _windowTitle;
}
//------------------------------------------------------------------------------------------------------------------------
void Window::SetPosition(const math::vector2 &pos)
{
    _windowPosition = pos;
    ImplementationSetWindowPosition(_windowPosition);
}
//------------------------------------------------------------------------------------------------------------------------
void Window::SetPosition(int x, int y)
{
    SetPosition(math::vector2(static_cast<float>(x), static_cast<float>(y)));
}
//------------------------------------------------------------------------------------------------------------------------
math::vector2 Window::GetPosition(void) const
{
    return _windowPosition;
}
//------------------------------------------------------------------------------------------------------------------------
void Window::SetSize(const math::vector2 &size)
{
    _windowSize = size;
    ImplementationSetWindowSize(_windowSize);
}
//------------------------------------------------------------------------------------------------------------------------
void Window::SetSize(int width, int height)
{
    SetSize(math::vector2(static_cast<float>(width), static_cast<float>(height)));
}
//------------------------------------------------------------------------------------------------------------------------
math::vector2 Window::GetSize(void) const
{
    return _windowSize;
}
//------------------------------------------------------------------------------------------------------------------------
system::UINT32 Window::ProcessMessages(void)
{
    return ImplementationProcessWindowMessages();
}
//------------------------------------------------------------------------------------------------------------------------
void Window::SetMessageCallback(WindowMessageCB cb)
{
    _sCallbackMap[GetHandle()] = cb;
}
} // renderer
} // engine
