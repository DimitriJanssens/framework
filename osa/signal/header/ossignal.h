#ifndef OSSIGNAL_H
#define OSSIGNAL_H

#include <osa/ossignalIntf.h>

Status_e signal_handler_register(OsSignalHandler_t handler);
Status_e signal_signal_register(OsSignal_e signal);

#endif