#ifndef REACTOR_H
#define REACTOR_H

#include <reactor/reactorIntf.h>

Status_e reactor_reactor_create(Reactor_t ** reactor);
Status_e reactor_reactor_channel_register(Reactor_t * reactor, ReactorChannel_t * channel);
Status_e reactor_reactor_channel_unregister(Reactor_t * reactor, ReactorChannel_t * channel);
Status_e reactor_reactor_destroy(Reactor_t * reactor);

Status_e reactor_channel_create(ReactorChannel_t ** channel, OsNetSocket_t * socket, ReactorChannelHandler_t handler, void * userdata);
Status_e reactor_channel_handle(ReactorChannelState_e state, const ReactorChannel_t * const channel);
const OsNetSocket_t * reactor_channel_get_socket(const ReactorChannel_t * const channel);
void * reactor_channel_get_userdata(const ReactorChannel_t * const channel);
Status_e reactor_channel_destroy(ReactorChannel_t * channel);

#endif
