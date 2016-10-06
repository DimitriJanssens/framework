#include "reactor.h"

#include <osa/osmemIntf.h>

struct ReactorChannel
{
  OsNetSocket_t * socket;
  void * userdata;
  ReactorChannelHandler_t handler;
};

Status_e reactor_channel_create(ReactorChannel_t ** channel, OsNetSocket_t * socket, ReactorChannelHandler_t handler, void * userdata)
{
  Status_e rc = STATUS_FAILURE;

  if((channel != NULL) && (socket != NULL) && (handler != NULL))
  {
    const OsMemIntf_t * const memi = getOsMemIntf();
    *channel = (struct ReactorChannel *) memi->malloc(sizeof(struct ReactorChannel));
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

Status_e reactor_channel_handle(ReactorChannelState_e state, const ReactorChannel_t * const channel)
{
  Status_e rc = STATUS_FAILURE;

  if(channel != NULL)
  {
    channel->handler(state, channel);
    rc = STATUS_SUCCESS;
  }

  return rc;
}

const OsNetSocket_t * reactor_channel_get_socket(const ReactorChannel_t * const channel)
{
  OsNetSocket_t * rc = NULL;

  if(channel != NULL)
  {
    rc = channel->socket;
  }

  return rc;
}

void * reactor_channel_get_userdata(const ReactorChannel_t * const channel)
{
  void * rc = NULL;

  if(channel != NULL)
  {
    rc = channel->userdata;
  }

  return rc;
}

Status_e reactor_channel_destroy(ReactorChannel_t * channel)
{
  Status_e rc = STATUS_FAILURE;

  if(channel != NULL)
  {
    (void) reactor_channel_handle(REACTORCHANNELSTATE_CLOSE, channel);
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
