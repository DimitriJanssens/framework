#ifndef OSREACTORINTF_H
#define OSREACTORINTF_H

#include <common/commontypes.h>
#include <osa/osnetIntf.h>

typedef enum
{
  OSREACTORCHANNELSTATE_UNKNOWN = 0,
  OSREACTORCHANNELSTATE_READ,
  OSREACTORCHANNELSTATE_WRITE,
  OSREACTORCHANNELSTATE_CLOSE,
} OsReactorChannelState_e;

typedef struct OsReactor OsReactor_t;
typedef struct OsReactorChannel OsReactorChannel_t;
typedef void (*OsReactorChannelHandler_t)(OsReactorChannelState_e state, const OsReactorChannel_t * const channel);

typedef struct
{
  /*!
   * \brief Creates a reactor
   */
  Status_e (*reactor_create)(OsReactor_t ** reactor);

  /*!
   * \brief Registers a channel with the reactor
   *
   * Memory management of the channel is passed to the reactor.
   */
  Status_e (*reactor_channel_register)(OsReactor_t * reactor, OsReactorChannel_t * channel);

  /*!
   * \brief Unregisters a channel from the reactor
   *
   * Use this function only with registered channels!
   * Unregisters and closes the channel and performs all needed memory cleanup.
   */
  Status_e (*reactor_channel_unregister)(OsReactor_t * reactor, OsReactorChannel_t * channel);

  /*!
   * \brief Destroys the reactor
   *
   * Destroys the reactor and all registered channels
   */
  Status_e (*reactor_destroy)(OsReactor_t * reactor);

  /*!
   * \brief Creates a new channel
   *
   * Memory management of the socket is handed over to the channel.
   * Memory management of unregistered channels stays with the caller.
   */
  Status_e (*channel_create)(OsReactorChannel_t ** channel, OsNetSocket_t * socket, OsReactorChannelHandler_t handler, void * userdata);

  /*!
   * \brief Returns a reference to the associated socket
   */
  const OsNetSocket_t * (*channel_get_socket)(const OsReactorChannel_t * const channel);

  /*!
   * \brief Returns the associated userdata
   */
  void * (*channel_get_userdata)(const OsReactorChannel_t * const channel);

  /*!
   * \brief Destroys a channel
   *
   * Use this function only with unregistered channels!
   * Memory management of unregistered channels stays with the caller.
   * Memory management of registered channels is passed to the reactor.
   */
  Status_e (*channel_destroy)(OsReactorChannel_t * channel);
} OsReactorIntf_t;

OsReactorIntf_t * getOsReactorIntf(void);

#ifdef UNITTESTS
void setDefaultOsReactorIntfForUnittests(void);
void resetDefaultOsReactorIntfForUnittests(void);
#endif

#endif