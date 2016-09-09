#ifndef OSREACTOR_H
#define OSREACTOR_H

#include <osa/osreactorIntf.h>

Status_e osreactor_reactor_create(OsReactor_t ** reactor);
Status_e osreactor_reactor_channel_register(OsReactor_t * reactor, OsReactorChannel_t * channel);
Status_e osreactor_reactor_channel_unregister(OsReactor_t * reactor, OsReactorChannel_t * channel);
Status_e osreactor_reactor_destroy(OsReactor_t * reactor);

Status_e osreactor_channel_create(OsReactorChannel_t ** channel, OsNetSocket_t * socket, OsReactorChannelHandler_t handler, void * userdata);
Status_e osreactor_channel_handle(OsReactorChannelState_e state, const OsReactorChannel_t * const channel);
const OsNetSocket_t * osreactor_channel_get_socket(const OsReactorChannel_t * const channel);
void * osreactor_channel_get_userdata(const OsReactorChannel_t * const channel);
Status_e osreactor_channel_destroy(OsReactorChannel_t * channel);

#endif