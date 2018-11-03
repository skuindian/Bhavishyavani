#ifndef GENERICREADCONFIG_H
#define GENERICREADCONFIG_H

#include <string>
#include <list>

namespace utility
{

typedef struct
{
    std::string key;
    std::string value;
} ConfigContent;

class GenericConfigReader
{
private:
    GenericConfigReader();

    static GenericConfigReader *mGenericConfigReader;

public:
    static GenericConfigReader *getInstence();

    std::list<ConfigContent> loadConfig(std::string fileName);
};

}

#endif // GENERICREADCONFIG_H
