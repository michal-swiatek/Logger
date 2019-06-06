#include "Logger.h"

int main()
{
    LOG_Init(LOG_INIT_EVERYTHING);

    logger->log(LOG_MSG_GENERAL, "Testing logger");
    logger->log(LOG_MSG_ERROR, "This is an error message number ", 1, "!");

    LOG_DisableSubsytemMessages(LOG_SUBSYSTEM_FILE_LOGGER, LOG_MSG_ERROR);

    logger->log(LOG_MSG_ERROR, "This error should be saved in log history, but not in logErrors.txt");

    LOG_SaveHistoryToFile("history.txt");

    LOG_Quit();

    return 0;
}
