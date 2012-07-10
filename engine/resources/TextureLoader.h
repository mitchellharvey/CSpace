// File:        resources/TextureLoader.h
// Author:      Mitchell Harvey
// Date:        1/24/2012
// 

#ifndef ENGINE_RESOURCES_TEXTURELOADER_H_
#define ENGINE_RESOURCES_TEXTURELOADER_H_

namespace engine {
namespace resources {

    // Take a look at model loader, this is a Base Texture loader so make sure that
    // it provides an interface to information required by either opengl/directx (opengl first)
    //
class TextureLoader
{
public:
    TextureLoader();
    virtual ~TextureLoader();

    virtual bool LoadTexture(const char *filename);

protected:
    
};
} // resources
} // engine
#endif // ENGINE_RESOURCES_TEXTURELOADER_H_
