#ifndef ACTIVITYREMINDERCONST_H
#define ACTIVITYREMINDERCONST_H

namespace gActivityReminderConst {

typedef enum
{
    SUCCESS = 1,
    PROCESS_CORE_NOT_STARTED = 2,
    PROCESS_DB_NOT_STARTED = 3,
    SERVER_NOT_STARTED = 4,
    SERVER_NOT_CONNECTED = 5,
    CLIENT_NOT_CONNECTED = 6,
    UNKNOWN_ERROR = 50
}ConnectionStatus;
}

#endif // ACTIVITYREMINDERCONST_H
