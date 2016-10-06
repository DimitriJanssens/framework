#include "test_reactor_tcases.h"

#include "test_reactor_helper.h"

START_TEST(test_channel_NULL)
  const ReactorIntf_t * const ri = getReactorIntf();
  ReactorChannel_t * channel = (ReactorChannel_t *) 0x12345;
  ReactorChannelHandler_t handler = (ReactorChannelHandler_t) 0x12345;

  const OsNetIntf_t * const neti = getOsNetIntf();
  OsNetSocket_t * socket;

  ck_assert(ri->channel_create(NULL, NULL, NULL, NULL) == STATUS_FAILURE);
  ck_assert(ri->channel_create(&channel, NULL, NULL, NULL) == STATUS_FAILURE);

  (void) neti->socket_create(OSNETSOCKETTYPE_UDP, &socket);
  ck_assert(ri->channel_create(NULL, socket, NULL, NULL) == STATUS_FAILURE);

  ck_assert(ri->channel_create(NULL, NULL, handler, NULL) == STATUS_FAILURE);
  ck_assert(ri->channel_create(&channel, NULL, handler, NULL) == STATUS_FAILURE);

  (void) neti->socket_create(OSNETSOCKETTYPE_UDP, &socket);
  ck_assert(ri->channel_create(&channel, socket, NULL, NULL) == STATUS_FAILURE);

  (void) neti->socket_create(OSNETSOCKETTYPE_UDP, &socket);
  ck_assert(ri->channel_create(NULL, socket, handler, NULL) == STATUS_FAILURE);

  ck_assert(ri->channel_get_socket(NULL) == NULL);
  ck_assert(ri->channel_get_userdata(NULL) == NULL);

  ck_assert(ri->channel_destroy(NULL) == STATUS_FAILURE);
END_TEST

static void localUdpChannelHandler(ReactorChannelState_e state, const ReactorChannel_t * const channel)
{
  ck_assert(state == REACTORCHANNELSTATE_CLOSE);
  ck_assert(channel != NULL);
  const ReactorIntf_t * const ri = getReactorIntf();
  ck_assert(ri->channel_get_socket(channel) != NULL);
  ck_assert(ri->channel_get_userdata(channel) != NULL);
  (*((uint8_t *) ri->channel_get_userdata(channel)))++;
}

static ReactorChannel_t * localCreateUdpChannel(void * userdata)
{
  ReactorChannel_t * rc = NULL;
  OsNetSocket_t * socket;

  const OsNetIntf_t * const neti = getOsNetIntf();
  (void) neti->socket_create(OSNETSOCKETTYPE_UDP, &socket);

  const ReactorIntf_t * const ri = getReactorIntf();
  ck_assert(ri->channel_create(&rc, socket, localUdpChannelHandler, userdata) == STATUS_SUCCESS);

  ck_assert(rc != NULL);
  return rc;
}

static void localDestroyChannel(ReactorChannel_t * channel)
{
  ck_assert(channel != NULL);
  const ReactorIntf_t * const ri = getReactorIntf();
  ck_assert(ri->channel_destroy(channel) == STATUS_SUCCESS);
}

START_TEST(test_channel_create_destroy)
  uint8_t data = 0;
  localDestroyChannel(localCreateUdpChannel(&data));
  ck_assert(data == 1);
END_TEST

TCase * tcase_reactor_channel(void)
{
  TCase *tc = tcase_create("TestCase ReactorIntf Channel");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_reactor_setup, test_reactor_teardown);

  tcase_add_test(tc, test_channel_NULL);
  tcase_add_test(tc, test_channel_create_destroy);

  return tc;
}
