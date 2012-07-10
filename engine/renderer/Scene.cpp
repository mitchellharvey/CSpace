// File:        renderer/Scene.cpp
// Author:      Mitchell Harvey
// Date:        4/8/2011
// 
#include <vector>
#include "renderer/Scene.h"

namespace engine {
namespace renderer {

Scene::Scene(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
Scene::~Scene(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
void Scene::AddRenderable(Renderable *renderable)
{
    if (renderable)
    {
        _renderables.push_back(renderable);
    }
}
//------------------------------------------------------------------------------------------------------------------------
void Scene::RemoveRenderable(Renderable *renderable)
{
    std::vector<Renderable *>::iterator it = _renderables.begin();
    for(; it != _renderables.end(); ++it)
    {
        if (*it == renderable)
        {
            _renderables.erase(it);
            break;
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------
void Scene::GetSortedRenderables(std::vector<Renderable> &sorted) const
{
    // TODO: Actually sort these for the smalles amount of state changes
    // based on the material properties

    sorted.clear();
    std::vector<Renderable *>::const_iterator it = _renderables.cbegin();
    std::vector<Renderable *>::const_iterator end = _renderables.cend();
    for(; it != end; ++it)
    {
        sorted.push_back(*(*it));
    }
}
//------------------------------------------------------------------------------------------------------------------------
void Scene::ClearRenderables(void)
{
    _renderables.clear();
}
} // renderer
} // engine
