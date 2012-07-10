// File:        resources/Resource.cpp
// Author:      Mitchell Harvey
// Date:        1/24/2012
// 

#include "resources/Resource.h"

namespace engine {
namespace resources {

Resource::Resource(const system::utf8 &resourceFile) :
 _resourceFile(resourceFile)
{
}
//------------------------------------------------------------------------------------------------------------------------
Resource::~Resource()
{
}
//------------------------------------------------------------------------------------------------------------------------
const system::utf8 &Resource::GetResourceFile() const
{
    return _resourceFile;
}

} // resources
} // engine
