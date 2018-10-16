#include "ActivityReminderConfigReader.h"

namespace helper {
ActivityReminderConfigReader *ActivityReminderConfigReader::mActivityReminderConfigReader = nullptr;

ActivityReminderConfigReader::ActivityReminderConfigReader()
{
}

ActivityReminderConfigReader *ActivityReminderConfigReader::getInstence()
{
    if(mActivityReminderConfigReader == nullptr)
    {
        mActivityReminderConfigReader = new ActivityReminderConfigReader;
    }

    return mActivityReminderConfigReader;
}

std::string ActivityReminderConfigReader::getServerIP()
{
    return "127.0.0.1";
}

int ActivityReminderConfigReader::getServerUIPort()
{
    return 8000;
}

int ActivityReminderConfigReader::getServerDBPort()
{
    return 8001;
}
}
