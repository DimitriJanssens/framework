#include "ossignal.h"

#include <signal.h>
#include <errno.h>
#include <string.h>

#include <logging/logging.h>
#include <osa/osmemIntf.h>

OsSignalHandler_t m_handler = NULL;

Status_e signal_handler_register(OsSignalHandler_t handler)
{
  Status_e rc = STATUS_FAILURE;

  if(handler != NULL)
  {
    m_handler = handler;
    rc = STATUS_SUCCESS;
  }

  return rc;
}

static int32_t localSignalEnumToInt(OsSignal_e signal)
{
  int32_t rc = -1; 

  switch(signal)
  {
  case OSSIGNAL_SIGHUP:
    rc = SIGHUP;
    break;
  case OSSIGNAL_SIGINT:
    rc = SIGINT;
    break;
  case OSSIGNAL_SIGPIPE:
    rc = SIGPIPE;
    break;
  case OSSIGNAL_SIGALRM:
    rc = SIGALRM;
    break;
  case OSSIGNAL_SIGTERM:
    rc = SIGTERM;
    break;
  case OSSIGNAL_SIGUSR1:
    rc = SIGUSR1;
    break;
  case OSSIGNAL_SIGUSR2:
    rc = SIGUSR2;
    break;

  default:
    break;
  }

  return rc;
}

static OsSignal_e localSignalIntToEnum(int32_t signal)
{
  OsSignal_e rc = OSSIGNAL_UNKNOWN; 

  switch(signal)
  {
  case SIGHUP:
    rc = OSSIGNAL_SIGHUP;
    break;
  case SIGINT:
    rc = OSSIGNAL_SIGINT;
    break;
  case SIGPIPE:
    rc = OSSIGNAL_SIGPIPE;
    break;
  case SIGALRM:
    rc = OSSIGNAL_SIGALRM;
    break;
  case SIGTERM:
    rc = OSSIGNAL_SIGTERM;
    break;
  case SIGUSR1:
    rc = OSSIGNAL_SIGUSR1;
    break;
  case SIGUSR2:
    rc = OSSIGNAL_SIGUSR2;
    break;
  }

  return rc;
}

static void localSignalHandler(int32_t signal)
{
  if(m_handler != NULL)
  {
    m_handler(localSignalIntToEnum(signal));
  }
}

Status_e signal_signal_register(OsSignal_e signal)
{
  Status_e rc = STATUS_FAILURE;

  if(signal != OSSIGNAL_UNKNOWN)
  {
    struct sigaction sact;
    getOsMemIntf()->memset(&sact, 0, sizeof(sact));
    sact.sa_handler = localSignalHandler;
    if(sigaction(localSignalEnumToInt(signal), &sact, NULL) == 0)
    {
      rc = STATUS_SUCCESS;
    }
    else
    {
      const char_t * error = strerror(errno);
      ERROR("Unable to register signal: %s\n", error);
    }
  }

  return rc;
}