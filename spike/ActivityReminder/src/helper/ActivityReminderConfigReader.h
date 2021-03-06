#ifndef ACTIVITYREMINDERCONFIGREADER_H
#define ACTIVITYREMINDERCONFIGREADER_H

#include <QSettings>

#include <string>

namespace helper {
class ActivityReminderConfigReader
{
private:
    ActivityReminderConfigReader();
    static ActivityReminderConfigReader *mActivityReminderConfigReader;
    QSettings mConfigSetting;

public:
    static ActivityReminderConfigReader *getInstence();

    //All interfaces related to project specific configuration
    std::string getServerIP();
    int getServerUIPort();
    int getServerDBPort();
};
}

#endif // ACTIVITYREMINDERCONFIGREADER_H
