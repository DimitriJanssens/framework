#include "ossignal.h"

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
