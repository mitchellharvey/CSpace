#include <iostream>
using namespace std;

#include <Windows.h>
#include <Windowsx.h>
#include "math/vector.h"
#include "math/matrix.h"
#include "math/util.h"
#include "renderer/Window.h"
#include "renderer/Renderer.h"
#include "resources/ResourceLoader.h"
#include "resources/GLSLLoader.h"
#include "resources/PrimitiveLoader.h"
#include "renderer/Scene.h"
#include "renderer/Camera.h"
#include "renderer/Renderable.h"

using namespace engine;
using namespace engine::math;
using namespace engine::system;
using namespace engine::renderer;
using namespace engine::resources;

ostream &operator<<(ostream &os, const vector3 &v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

static bool g_quit = false;
static vector2 g_mousePos;
static bool g_mouseLButtonDown = false;
void MyCB(system::UINT32 msg, system::UINT64 wParam, system::UINT64 lParam)
{
    switch(msg)
    {
    case WM_DESTROY:
    case WM_QUIT:
        g_quit = true;
        break;

    case WM_MOUSEMOVE:
        g_mousePos.set((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));
        g_mouseLButtonDown = (wParam & MK_RBUTTON);
        break;
    }
}

void UpdateCamera(Camera &cam, float delta)
{
    static vector2 lastMousePos = g_mousePos;

    if (g_mouseLButtonDown)
    {
        vector2 diff = (g_mousePos - lastMousePos);
        diff = Normalize(diff) * delta;

        lastMousePos = g_mousePos;
        vector3 lookAt = cam.GetZAxis();
        lookAt.x += diff.x;
        lookAt.y += diff.y;
        cam.LookAt(lookAt);
    }
    
}

int main(char **argv, int argc)
{
    Scene scene;
    Camera cam;

    cam.SetTranslation(0.0f, 0.0f, 2.0f);
    cam.LookAt(0.0f, 0.0f, 0.0f);

    engine::renderer::Window *pWindow = engine::renderer::CreateNewWindow();
    pWindow->SetMessageCallback(MyCB);
    pWindow->Show();
    cam.SetWidthHeightRatio( pWindow->GetSize().x / pWindow->GetSize().y );

    // Load resources and setup a scene
    VertexShaderResource *vertShader = ResourceLoader::LoadVertexShader("default.vert", GLSLLoader());
    FragmentShaderResource *fragShader = ResourceLoader::LoadFragmentShader("default.frag", GLSLLoader());

    ModelResource *triangle = ResourceLoader::LoadModel("test", PrimitiveLoader(PrimitiveLoader::CUBE));

    Renderable renderable;
    renderable.SetTranslation(0.0f, 0.0f, 0.0f);
    renderable.SetModelResource(triangle);

    Material &mat = renderable.GetMaterial();
    mat.SetProjectionMatrixShaderVar("projMatrix");
    mat.SetModelViewMatrixShaderVar("modelViewMatrix");
    mat.SetVertexShader(vertShader);
    mat.SetFragmentShader(fragShader);

    scene.AddRenderable(&renderable);

    engine::renderer::Renderer *pRenderer = engine::renderer::CreateNewRenderer();
    pRenderer->Initialize();
    pRenderer->UpdateViewPort(0, 0, pWindow->GetSize().x, pWindow->GetSize().y);
    float delta = 0.0001f;
    while (!g_quit) 
    { 
        pWindow->ProcessMessages();
        pRenderer->RenderScene(pWindow, &cam, &scene);

        UpdateCamera(cam, delta);

    }
    engine::renderer::DestroyWindow(pWindow);
    return 0;
}