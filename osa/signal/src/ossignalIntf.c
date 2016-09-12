#include <osa/ossignalIntf.h>

#include "ossignal.h"

static OsSignalIntf_t intf =
{
  #ifndef UNITTESTS
  .handler_register = signal_handler_register,
  .signal_register = signal_signal_register,
  #else
  .handler_register = NULL,
  .signal_register = NULL,  
  #endif
};

OsSignalIntf_t * getOsSignalIntf(void)
{
  return &intf;
}

#ifdef UNITTESTS
void setDefaultOsSignalIntfForUnittests(void)
{
  OsSignalIntf_t * intf = getOsSignalIntf();

  intf->handler_register = signal_handler_register;
  intf->signal_register = signal_signal_register;
}

void resetDefaultOsSignalIntfForUnittests(void)
{
  OsSignalIntf_t * intf = getOsSignalIntf();

  intf->handler_register = NULL;
  intf->signal_register = NULL;  
}
#endif