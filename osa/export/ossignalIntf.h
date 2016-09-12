#ifndef OSSIGNALINTF_H
#define OSSIGNALINTF_H

#include <common/commontypes.h>

typedef enum
{
  OSSIGNAL_UNKNOWN = 0,
  OSSIGNAL_SIGHUP,
  OSSIGNAL_SIGINT,
  OSSIGNAL_SIGPIPE,
  OSSIGNAL_SIGALRM,
  OSSIGNAL_SIGTERM,
  OSSIGNAL_SIGUSR1,
  OSSIGNAL_SIGUSR2,
} OsSignal_e;

typedef void (*OsSignalHandler_t)(OsSignal_e signal);

typedef struct
{
  Status_e (*handler_register)(OsSignalHandler_t handler);
  Status_e (*signal_register)(OsSignal_e signal);
} OsSignalIntf_t;

OsSignalIntf_t * getOsSignalIntf(void);

#ifdef UNITTESTS
void setDefaultOsSignalIntfForUnittests(void);
void resetDefaultOsSignalIntfForUnittests(void);
#endif

#endif