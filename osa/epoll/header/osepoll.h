#ifndef OSEPOLL_H
#define OSEPOLL_H

#include <osa/osepollIntf.h>

Status_e osepoll_create(int32_t * epollfd);
Status_e osepoll_register(int32_t epollfd, int32_t fd, const OsEpollEvent_t * const event);
Status_e osepoll_wait(int32_t epollfd, OsEpollEvent_t * const event);
Status_e osepoll_unregister(int32_t epollfd, int32_t fd);
Status_e osepoll_close(int32_t epollfd);

int32_t osepoll_events_to_os(int32_t events);
int32_t osepoll_events_from_os(int32_t events);

#endif
