#include "test_osreactor_tcases.h"

#include "test_osreactor_helper.h"

START_TEST(test_channel_NULL)
  const OsReactorIntf_t * const ri = getOsReactorIntf();
  OsReactorChannel_t * channel = (OsReactorChannel_t *) 0x12345;
  OsReactorChannelHandler_t handler = (OsReactorChannelHandler_t) 0x12345;

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

static void localUdpChannelHandler(OsReactorChannelState_e state, const OsReactorChannel_t * const channel)
{
  ck_assert(state == OSREACTORCHANNELSTATE_CLOSE);
  ck_assert(channel != NULL);
  const OsReactorIntf_t * const ri = getOsReactorIntf();
  ck_assert(ri->channel_get_socket(channel) != NULL);
  ck_assert(ri->channel_get_userdata(channel) != NULL);
  (*((uint8_t *) ri->channel_get_userdata(channel)))++;
}

static OsReactorChannel_t * localCreateUdpChannel(void * userdata)
{
  OsReactorChannel_t * rc = NULL;
  OsNetSocket_t * socket;

  const OsNetIntf_t * const neti = getOsNetIntf();
  (void) neti->socket_create(OSNETSOCKETTYPE_UDP, &socket);

  const OsReactorIntf_t * const ri = getOsReactorIntf();
  ck_assert(ri->channel_create(&rc, socket, localUdpChannelHandler, userdata) == STATUS_SUCCESS);

  ck_assert(rc != NULL);
  return rc;
}

static void localDestroyChannel(OsReactorChannel_t * channel)
{
  ck_assert(channel != NULL);
  const OsReactorIntf_t * const ri = getOsReactorIntf();
  ck_assert(ri->channel_destroy(channel) == STATUS_SUCCESS);
}

START_TEST(test_channel_create_destroy)
  uint8_t data = 0;
  localDestroyChannel(localCreateUdpChannel(&data));
  ck_assert(data == 1);
END_TEST

TCase * tcase_osreactor_channel(void)
{
  TCase *tc = tcase_create("TestCase OsReactorIntf Channel");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_osreactor_setup, test_osreactor_teardown);

  tcase_add_test(tc, test_channel_NULL);
  tcase_add_test(tc, test_channel_create_destroy);

  return tc;
}