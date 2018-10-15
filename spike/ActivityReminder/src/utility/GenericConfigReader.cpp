#include "GenericConfigReader.h"

namespace utility
{
GenericConfigReader *GenericConfigReader::mGenericConfigReader = nullptr;

GenericConfigReader::GenericConfigReader()
{

}

GenericConfigReader* GenericConfigReader::getInstence()
{
    if(mGenericConfigReader == nullptr)
    {
        mGenericConfigReader = new GenericConfigReader;
    }

    return mGenericConfigReader;
}


std::list<ConfigContent> GenericConfigReader::readConfig(std::string fileName)
{
    std::list<ConfigContent> contentList;

    return contentList;
}

}
