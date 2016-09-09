#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>

#define INFO(args...)       { printf("INFO: %s:%d: ", __FILE__, __LINE__); printf(args); }
#define ERROR(args...)      { printf("ERROR: %s:%d: ", __FILE__, __LINE__); printf(args); }
#ifndef UNITTESTS
#define TRACE(args...)      
#else
#define TRACE(args...)      { printf("TRACE: %s:%d: ", __FILE__, __LINE__); printf(args); }
#endif
#endif