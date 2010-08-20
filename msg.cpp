#include <fstream>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "msg.h"

FILE *logfile;

bool initLog(const char* filename) {
    if (logfile)
        if (!closeLog())
            return false;

    logfile = fopen(filename, "w");
    if (!logfile)
        return false;

    time_t tmp_time;
    time(&tmp_time);
    Log("Legendary log system initialised %s", ctime(&tmp_time));

    return true;
}

bool closeLog() {
    Log("Legendary log system shutting down.\n");
    if (!logfile)
        return true;
    if (!fclose(logfile))
        return false;
    return true;
}

void Log(const char * format, ...) {
    va_list argptr;
    va_start(argptr, format);
    char buf[255];
    int len = vsnprintf(buf, 256, format, argptr);
    va_end(argptr);
    if (!logfile)
        return;
    if (!fwrite(buf, 1, len, logfile))
        return;
    fflush(logfile);
}
