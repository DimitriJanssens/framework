#include "test_reactor_tcases.h"

#include <netinet/in.h>

#include <logging/logging.h>
#include <osa/osmemIntf.h>

#include "test_reactor_helper.h"

START_TEST(test_reactor_NULL)
  const ReactorIntf_t * const ri = getReactorIntf();
  Reactor_t * reactor = (Reactor_t *) 0x12345;
  ReactorChannel_t * channel = (ReactorChannel_t *) 0x12345;

  ck_assert(ri->reactor_create(NULL) == STATUS_FAILURE);

  ck_assert(ri->reactor_channel_register(NULL, NULL) == STATUS_FAILURE);
  ck_assert(ri->reactor_channel_register(reactor, NULL) == STATUS_FAILURE);
  ck_assert(ri->reactor_channel_register(NULL, channel) == STATUS_FAILURE);

  ck_assert(ri->reactor_channel_unregister(NULL, NULL) == STATUS_FAILURE);
  ck_assert(ri->reactor_channel_unregister(reactor, NULL) == STATUS_FAILURE);
  ck_assert(ri->reactor_channel_unregister(NULL, channel) == STATUS_FAILURE);

  ck_assert(ri->reactor_destroy(NULL) == STATUS_FAILURE);
END_TEST

static Reactor_t * localCreateReactor(void)
{
  Reactor_t * rc = NULL;

  const ReactorIntf_t * const ri = getReactorIntf();
  ck_assert(ri->reactor_create(&rc) == STATUS_SUCCESS);

  ck_assert(rc != NULL);
  return rc;
}

static void localDestroyReactor(Reactor_t * reactor)
{
  ck_assert(reactor != NULL);
  const ReactorIntf_t * const ri = getReactorIntf();
  ck_assert(ri->reactor_destroy(reactor) == STATUS_SUCCESS);
}

START_TEST(test_reactor_create_destroy)
  localDestroyReactor(localCreateReactor());
END_TEST

#define BUFFERSIZE  (1024 * 50)
static void localUdpChannelHandler(ReactorChannelState_e state, const ReactorChannel_t * const channel)
{
  ck_assert(state != REACTORCHANNELSTATE_UNKNOWN);
  ck_assert(channel != NULL);

  const ReactorIntf_t * const ri = getReactorIntf();
  const OsNetSocket_t * socket = ri->channel_get_socket(channel);
  void * data = ri->channel_get_userdata(channel);

  if(state == REACTORCHANNELSTATE_READ)
  {
    INFO("Socket is ready for reading\n");
    char_t * recv_buffer = (char_t*) data;
    size_t recv_buffer_size = BUFFERSIZE;
    ck_assert(getOsNetIntf()->socket_recv(socket, recv_buffer, &recv_buffer_size, 0) == STATUS_SUCCESS);
    ck_assert(recv_buffer_size == BUFFERSIZE);
  }
  else if(state == REACTORCHANNELSTATE_WRITE)
  {
    INFO("Socket is ready for writing\n");
  }
  else if(state == REACTORCHANNELSTATE_CLOSE)
  {
    INFO("Socket is getting closed\n");
  }
  else
  {
    ck_abort();
  }

}

static ReactorChannel_t * localCreateUdpChannel(void * userdata, size_t count)
{
  ReactorChannel_t * rc = NULL;
  OsNetSocket_t * socket;

  const OsNetIntf_t * const neti = getOsNetIntf();
  (void) neti->socket_create(OSNETSOCKETTYPE_UDP, &socket);

  struct sockaddr_in si_me;
  si_me.sin_family = AF_INET;
  si_me.sin_port = neti->htons(8888 + count);
  si_me.sin_addr.s_addr = neti->htonl(INADDR_ANY);

  ck_assert(neti->socket_bind(socket, &si_me, sizeof(si_me)) == STATUS_SUCCESS);

  const ReactorIntf_t * const ri = getReactorIntf();
  ck_assert(ri->channel_create(&rc, socket, localUdpChannelHandler, userdata) == STATUS_SUCCESS);

  ck_assert(rc != NULL);
  return rc;
}

START_TEST(test_reactor_udpchannel)
  const ReactorIntf_t * const ri = getReactorIntf();

  Reactor_t * reactor = localCreateReactor();

  const OsMemIntf_t * const memi = getOsMemIntf();
  char_t send_buffer[BUFFERSIZE];
  memi->memset(send_buffer, 'A', BUFFERSIZE);
  char_t recv_buffer[BUFFERSIZE];
  memi->memset(recv_buffer, 'B', BUFFERSIZE);

  ReactorChannel_t * channel = localCreateUdpChannel(recv_buffer, 0);

  ck_assert(ri->reactor_channel_register(reactor, channel) == STATUS_SUCCESS);

  const OsNetIntf_t * const neti = getOsNetIntf();
  struct sockaddr_in si_me;
  si_me.sin_family = AF_INET;
  si_me.sin_port = neti->htons(8888);
  si_me.sin_addr.s_addr = neti->htonl(INADDR_ANY);

  size_t send_buffer_size= BUFFERSIZE;
  ck_assert(neti->socket_sendto(ri->channel_get_socket(channel), send_buffer, &send_buffer_size, 0, &si_me, sizeof(si_me)) == STATUS_SUCCESS);
  ck_assert(send_buffer_size == BUFFERSIZE);

  while(memi->memcmp(send_buffer, recv_buffer, BUFFERSIZE) != STATUS_SUCCESS);

  localDestroyReactor(reactor);
END_TEST

#define CHANNELCOUNT  10

START_TEST(test_reactor_udpchannels)
  const ReactorIntf_t * const ri = getReactorIntf();

  Reactor_t * reactor = localCreateReactor();

  ReactorChannel_t * channels[CHANNELCOUNT];

  const OsMemIntf_t * const memi = getOsMemIntf();
  char_t send_buffer[CHANNELCOUNT][BUFFERSIZE];
  char_t recv_buffer[CHANNELCOUNT][BUFFERSIZE];

  for(size_t i = 0; i < CHANNELCOUNT; i++)
  {
    memi->memset(send_buffer[i], 'A', BUFFERSIZE);
    memi->memset(recv_buffer[i], 'B', BUFFERSIZE);
    channels[i] = localCreateUdpChannel(recv_buffer[i], i);
    ck_assert(ri->reactor_channel_register(reactor, channels[i]) == STATUS_SUCCESS);
  }

  const OsNetIntf_t * const neti = getOsNetIntf();

  for(size_t i = 0; i < CHANNELCOUNT; i++)
  {
    struct sockaddr_in si_me;
    si_me.sin_family = AF_INET;
    si_me.sin_port = neti->htons(8888 + i);
    si_me.sin_addr.s_addr = neti->htonl(INADDR_ANY);

    size_t send_buffer_size = BUFFERSIZE;
    ck_assert(neti->socket_sendto(ri->channel_get_socket(channels[i]), send_buffer[i], &send_buffer_size, 0, &si_me, sizeof(si_me)) == STATUS_SUCCESS);
    ck_assert(send_buffer_size == BUFFERSIZE);
  }

  while(memi->memcmp(send_buffer, recv_buffer, CHANNELCOUNT * BUFFERSIZE) != STATUS_SUCCESS);

  localDestroyReactor(reactor);
END_TEST

TCase * tcase_reactor_reactor(void)
{
  TCase *tc = tcase_create("TestCase ReactorIntf Reactor");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_reactor_setup, test_reactor_teardown);

  tcase_add_test(tc, test_reactor_NULL);
  tcase_add_test(tc, test_reactor_create_destroy);
  tcase_add_test(tc, test_reactor_udpchannel);
  tcase_add_test(tc, test_reactor_udpchannels);

  return tc;
}
