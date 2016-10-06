#ifndef REACTORINTF_H
#define REACTORINTF_H

#include <common/commontypes.h>
#include <osa/osnetIntf.h>

typedef enum
{
  REACTORCHANNELSTATE_UNKNOWN = 0,
  REACTORCHANNELSTATE_READ,
  REACTORCHANNELSTATE_WRITE,
  REACTORCHANNELSTATE_CLOSE,
} ReactorChannelState_e;

typedef struct Reactor Reactor_t;
typedef struct ReactorChannel ReactorChannel_t;
typedef void (*ReactorChannelHandler_t)(ReactorChannelState_e state, const ReactorChannel_t * const channel);

typedef struct
{
  /*!
   * \brief Creates a reactor
   */
  Status_e (*reactor_create)(Reactor_t ** reactor);

  /*!
   * \brief Registers a channel with the reactor
   *
   * Memory management of the channel is passed to the reactor.
   */
  Status_e (*reactor_channel_register)(Reactor_t * reactor, ReactorChannel_t * channel);

  /*!
   * \brief Unregisters a channel from the reactor
   *
   * Use this function only with registered channels!
   * Unregisters and closes the channel and performs all needed memory cleanup.
   */
  Status_e (*reactor_channel_unregister)(Reactor_t * reactor, ReactorChannel_t * channel);

  /*!
   * \brief Destroys the reactor
   *
   * Destroys the reactor and all registered channels
   */
  Status_e (*reactor_destroy)(Reactor_t * reactor);

  /*!
   * \brief Creates a new channel
   *
   * Memory management of the socket is handed over to the channel.
   * Memory management of unregistered channels stays with the caller.
   */
  Status_e (*channel_create)(ReactorChannel_t ** channel, OsNetSocket_t * socket, ReactorChannelHandler_t handler, void * userdata);

  /*!
   * \brief Returns a reference to the associated socket
   */
  const OsNetSocket_t * (*channel_get_socket)(const ReactorChannel_t * const channel);

  /*!
   * \brief Returns the associated userdata
   */
  void * (*channel_get_userdata)(const ReactorChannel_t * const channel);

  /*!
   * \brief Destroys a channel
   *
   * Use this function only with unregistered channels!
   * Memory management of unregistered channels stays with the caller.
   * Memory management of registered channels is passed to the reactor.
   */
  Status_e (*channel_destroy)(ReactorChannel_t * channel);
} ReactorIntf_t;

ReactorIntf_t * getReactorIntf(void);

#ifdef UNITTESTS
void setDefaultReactorIntfForUnittests(void);
void resetDefaultReactorIntfForUnittests(void);
#endif

#endif
