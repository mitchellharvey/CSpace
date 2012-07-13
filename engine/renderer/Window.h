// File:        renderer/Window.h
// Author:      Mitchell Harvey
// Date:        3/23/2011
// 

#ifndef ENGINE_RENDERER_WINDOW_H_
#define ENGINE_RENDERER_WINDOW_H_

#include <map>

#include "system/types.h"
#include "system/utf8.h"
#include "math/vector.h"
#include "renderer/RenderTarget.h"

using std::map;
using namespace engine::system;

namespace engine {
namespace renderer {

typedef void(*WindowMessageCB)(system::UINT32, system::UINT64, system::UINT64);

class RenderContext;

class Window : public RenderTarget
{
public:
    void *GetHandle(void) const;
    RenderContext *GetRenderContext(void) const;

    void Show(void);
    void Hide(void);
    bool IsVisible(void);

    void SetTitle(const system::utf8 &title);
    system::utf8 GetTitle(void) const;

    void SetPosition(const math::vector2 &pos);
    void SetPosition(int x, int y);
    math::vector2 GetPosition(void) const;

    void SetSize(const math::vector2 &size);
    void SetSize(int width, int height);
    math::vector2 GetSize(void) const;

    system::UINT32 ProcessMessages(void);

    void SetMessageCallback(WindowMessageCB cb);

protected:
    Window(void);
    Window(const Window &) { } // TODO: remove our callback from static map
    virtual ~Window(void);

    virtual void ImplementationSetWindowTitle(const system::utf8 &title) = 0;
    virtual void ImplementationSetWindowVisible(bool visible) = 0;
    virtual void ImplementationSetWindowPosition(const math::vector2 &pos) = 0;
    virtual void ImplementationSetWindowSize(const math::vector2 &size) = 0;
    virtual void *ImplementationGetWindowHandle(void) const = 0;
    virtual system::UINT32 ImplementationProcessWindowMessages(void) = 0;

    static map<void *, WindowMessageCB> _sCallbackMap;

    RenderContext *_pRenderContext;

private:
    system::utf8 _windowTitle;
    math::vector2 _windowPosition;
    math::vector2 _windowSize;
    bool _windowVisible;
};

Window *CreateNewWindow(void);
void DestroyWindow(Window *pWindow);

} // renderer
} // engine
#endif // ENGINE_RENDERER_WINDOW_H_
