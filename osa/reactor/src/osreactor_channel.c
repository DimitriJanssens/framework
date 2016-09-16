#include "osreactor.h"

#include <osa/osmemIntf.h>

struct OsReactorChannel
{
  OsNetSocket_t * socket;
  void * userdata;
  OsReactorChannelHandler_t handler;
};

Status_e osreactor_channel_create(OsReactorChannel_t ** channel, OsNetSocket_t * socket, OsReactorChannelHandler_t handler, void * userdata)
{
  Status_e rc = STATUS_FAILURE;

  if((channel != NULL) && (socket != NULL) && (handler != NULL))
  {
    const OsMemIntf_t * const memi = getOsMemIntf();
    *channel = (struct OsReactorChannel *) memi->malloc(sizeof(struct OsReactorChannel));
    if(*channel != NULL)
    {
      (*channel)->socket = socket;
      (*channel)->userdata = userdata;
      (*channel)->handler = handler;

      rc = STATUS_SUCCESS;
    }
  }

  if((rc != STATUS_SUCCESS) && (socket != NULL))
  {
    (void) getOsNetIntf()->socket_destroy(socket);
  }

  return rc;
}

Status_e osreactor_channel_handle(OsReactorChannelState_e state, const OsReactorChannel_t * const channel)
{
  Status_e rc = STATUS_FAILURE;

  if(channel != NULL)
  {
    channel->handler(state, channel);
    rc = STATUS_SUCCESS;
  }

  return rc;
}

const OsNetSocket_t * osreactor_channel_get_socket(const OsReactorChannel_t * const channel)
{
  OsNetSocket_t * rc = NULL;

  if(channel != NULL)
  {
    rc = channel->socket;
  }

  return rc;
}

void * osreactor_channel_get_userdata(const OsReactorChannel_t * const channel)
{
  void * rc = NULL;

  if(channel != NULL)
  {
    rc = channel->userdata;
  }

  return rc;
}

Status_e osreactor_channel_destroy(OsReactorChannel_t * channel)
{
  Status_e rc = STATUS_FAILURE;

  if(channel != NULL)
  {
    (void) osreactor_channel_handle(OSREACTORCHANNELSTATE_CLOSE, channel);
    channel->handler = NULL;
    channel->userdata = NULL;

    const OsNetIntf_t * const neti = getOsNetIntf();
    (void) neti->socket_destroy(channel->socket);
    channel->socket = NULL;

    const OsMemIntf_t * const memi = getOsMemIntf();
    memi->free(channel);

    rc = STATUS_SUCCESS;
  }

  return rc;
}