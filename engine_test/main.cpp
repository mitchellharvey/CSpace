#include <iostream>
using namespace std;

#include <Windows.h>
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

#pragma comment(lib,"opengl32.lib")

ostream &operator<<(ostream &os, const vector3 &v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

bool g_quit = false;
void MyCB(system::UINT32 msg)
{
    switch(msg)
    {
    case WM_DESTROY:
    case WM_QUIT:
        g_quit = true;
    }
}

int main(char **argv, int argc)
{
    vector3 con1;
    vector3 con2(1.0f, 2.5f, 3.1f);
    vector3 con3(con1);

    cout << "con1 = " << con1 << endl;
    cout << "con2 = " << con2 << endl;
    cout << "con3 = " << con3 << endl;

    cout << endl;

    vector3 con4(con2 + vector3(1.0f, 1.0f, 1.0f));
    vector3 con5(con4 * 2.0f);
    vector3 con6(2.0f * con4);

    cout << "con4 = " << con4 << endl;
    cout << "con5 = " << con5 << endl;
    cout << "con6 = " << con6 << endl;

    cout << endl;

    bool comp1 = con5 == con6;
    bool comp2 = con5 != con2;
    vector3 con7 = con5 - con6;

    cout << "comp1 = " << comp1 << endl;
    cout << "comp2 = " << comp2 << endl;
    cout << "con7 = " << con7 << endl;

    cout << "Size of vector2 = " << sizeof(vector2) << endl;

    vector2 v[4];
    v[0].x = 123;
    v[0].y = 456;
    v[1].x = 789;
    v[1].y = 1012;
    float *f = (float *)v;

    matrix3x3 m;
    matrix3x3 m2;
    m2.m12 = 999.0f;
    bool same = m == m2;
    m2 = matrix3x3::IDENTITY;
    same = m == m2;

    float fa[] = { 1, 0, 2,
                  -1, 3, 1,
                  0, 0, 0 };

    float fb[] = { 3, 1, 0,
                   2, 1, 0,
                   1, 0, 0 };
    m.set(fa);
    m2.set(fb);

    matrix4x4 _transform;
    matrix3x3 r = m * m2;

    matrix3x3 rot;
    rot.m22 = cos(PI);
    rot.m23 = -sin(PI);
    rot.m32 = sin(PI);
    rot.m33 = cos(PI);

    matrix3x3 curRot;
    curRot = rot * curRot;
    memcpy(&_transform, &curRot, sizeof(matrix3x3));

    Scene scene;
    Camera cam;

    cam.SetTranslation(0.0f, 0.0f, 2.0f);
    cam.LookAt(0.0f, 0.0f, 0.0f);

    engine::renderer::Window *pWindow = engine::renderer::CreateNewWindow();
    pWindow->SetMessageCallback(MyCB);
    pWindow->Show();
    cam.SetWidthHeightRatio( pWindow->GetSize().x / pWindow->GetSize().y );

    // Load resources and setup a scene
    VertexShaderResource *vertShader = ResourceLoader::LoadVertexShader("..\\shaders\\glsl\\default.vert", GLSLLoader());
    FragmentShaderResource *fragShader = ResourceLoader::LoadFragmentShader("..\\shaders\\glsl\\default.frag", GLSLLoader());

    ModelResource *triangle = ResourceLoader::LoadModel("test", PrimitiveLoader(PrimitiveLoader::TRIANGLE));

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

    while (!g_quit) 
    { 
        pWindow->ProcessMessages();
        pRenderer->RenderScene(pWindow, &cam, &scene);
        if (GetAsyncKeyState(VK_RIGHT))
        {
            renderable.SetTranslation( renderable.GetTranslation() + vector3(0.01f, 0.0f, 0.0f) );
        }

        if (GetAsyncKeyState(VK_LEFT))
        {
            renderable.SetTranslation( renderable.GetTranslation() + vector3(-0.01f, 0.0f, 0.0f) );
        }

        if (GetAsyncKeyState(VK_UP))
        {
            cam.SetTranslation(cam.GetTranslation() + vector3(0.0f, 0.0f, -0.01f));
        }

        if (GetAsyncKeyState(VK_DOWN))
        {
            cam.SetTranslation(cam.GetTranslation() + vector3(0.0f, 0.0f, 0.01f));
        }
    }
    engine::renderer::DestroyWindow(pWindow);
    return 0;
}