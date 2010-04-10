#ifndef __msg_h_
#define __msg_h_

#include <iostream>

bool		initLog(const char *filename);
bool		closeLog();
void		Log(const char *format, ...);

extern		FILE *logfile;
extern		char *logfilename;

#endif
