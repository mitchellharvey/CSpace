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
        if (MagnitudeSquared(diff) != 0.0f)
        {
            diff = Normalize(diff) * delta;

            cam.RotateOnY(diff.x);
        }
    }
    lastMousePos = g_mousePos;
    
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

    ModelResource *cubeModel = ResourceLoader::LoadModel("cube", PrimitiveLoader(PrimitiveLoader::CUBE));
    ModelResource *triangleModel = ResourceLoader::LoadModel("triangle", PrimitiveLoader(PrimitiveLoader::TRIANGLE));


    Renderable cube, triangle;
    cube.SetTranslation(0.0f, 0.0f, -1.0f);
    cube.SetModelResource(cubeModel);

    triangle.SetTranslation(-1.0f, -1.0f, -1.0f);
    triangle.SetModelResource(triangleModel);
     
    Material *mat[] = { &(cube.GetMaterial()), &(triangle.GetMaterial()) };
    for (unsigned int i = 0; i < (sizeof(mat) / sizeof(Material*)); ++i)
    {
        mat[i]->SetProjectionMatrixShaderVar("projMatrix");
        mat[i]->SetModelViewMatrixShaderVar("modelViewMatrix");
        mat[i]->SetVertexShader(vertShader);
        mat[i]->SetFragmentShader(fragShader);
    }

    scene.AddRenderable(&cube);
    scene.AddRenderable(&triangle);

    engine::renderer::Renderer *pRenderer = engine::renderer::CreateNewRenderer();
    pRenderer->Initialize();
    pRenderer->UpdateViewPort(0, 0, pWindow->GetSize().x, pWindow->GetSize().y);
    float delta = 0.01f;
    float moveSpeed = 0.01f;
    while (!g_quit) 
    { 
        pWindow->ProcessMessages();
        pRenderer->RenderScene(pWindow, &cam, &scene);

        UpdateCamera(cam, delta);

        if (GetAsyncKeyState(VK_UP))
        {
            triangle.SetTranslation(triangle.GetTranslation() + vector3(1.0f * delta, 0.0f, 0.0f));
        }

        vector3 pos = cube.GetTranslation();
        cube.SetTranslation(pos.x + moveSpeed, pos.y, pos.z);

        if (pos.x > 1.0f )
        {
            moveSpeed *= -1.0f;
            cube.SetTranslation(1.0f, pos.y, pos.z);
        }
        else if (pos.x < -1.0f )
        {
            moveSpeed *= -1.0f;
            cube.SetTranslation(-1.0f, pos.y, pos.z);
        }


    }
    engine::renderer::DestroyWindow(pWindow);
    return 0;
}