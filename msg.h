#ifndef __msg_h_
#define __msg_h_

#define LOG(text) std::cout << __PRETTY_FUNCTION__ << " (" << __FILE__ << ":" << __LINE__ << "): " << text << std::endl;

#include <iostream>

bool		initLog(const char *filename);
bool		closeLog();
void		Log(const char *format, ...);

extern		FILE *logfile;
extern		char *logfilename;


#define printf BRUK_LOG_DIN_KUKFAEN

#endif
