#include "GenericConfigReader.h"

#include <QSettings>

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


std::list<ConfigContent> GenericConfigReader::loadConfig(std::string fileName)
{
    std::list<ConfigContent> contentList;

    QSettings settings(fileName.c_str(), QSettings::NativeFormat);

    return contentList;
}

}
