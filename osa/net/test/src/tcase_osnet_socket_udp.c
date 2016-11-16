#include "test_osnet_tcases.h"

#include <netinet/in.h>

#include <osa/osmemIntf.h>
#include <logging/logging.h>

#include "test_osnet_helper.h"

START_TEST(test_osnet_NULL)
  const OsNetIntf_t * const neti = getOsNetIntf();
  OsNetSocket_t * socket;
  ck_assert(neti->socket_create(OSNETSOCKETTYPE_UNKNOWN, NULL) == STATUS_FAILURE);
  ck_assert(neti->socket_create(OSNETSOCKETTYPE_UDP, NULL) == STATUS_FAILURE);
  ck_assert(neti->socket_create(OSNETSOCKETTYPE_UNKNOWN, &socket) == STATUS_FAILURE);

END_TEST

static OsNetSocket_t * localUdpSocketCreate(void)
{
  const OsNetIntf_t * const neti = getOsNetIntf();

  OsNetSocket_t * socket = NULL;
  ck_assert(neti->socket_create(OSNETSOCKETTYPE_UDP, &socket) == STATUS_SUCCESS);
  ck_assert(socket != NULL);
  return socket;
}

static void localUdpSocketDestroy(OsNetSocket_t * socket)
{
  const OsNetIntf_t * const neti = getOsNetIntf();

  ck_assert(socket != NULL);
  ck_assert(neti->socket_destroy(socket) == STATUS_SUCCESS);
}

START_TEST(test_osnet_socket_udp_create_destroy)
  localUdpSocketDestroy(localUdpSocketCreate());
END_TEST

START_TEST(test_osnet_socket_udp_send_recv)
  const OsNetIntf_t * const neti = getOsNetIntf();

  OsNetSocket_t * socket = localUdpSocketCreate();

  struct sockaddr_in si_me;
  si_me.sin_family = AF_INET;
  si_me.sin_port = neti->host_to_network_short(8888);
  si_me.sin_addr.s_addr = neti->host_to_network_long(INADDR_ANY);

  char_t send_buffer[] = { "DEADBEEF" };
  size_t send_buffer_size = ARRAY_SIZE(send_buffer);
  char_t recv_buffer[] = { "00000000" };
  size_t recv_buffer_size = ARRAY_SIZE(recv_buffer);

  ck_assert(neti->socket_bind(socket, &si_me, sizeof(si_me)) == STATUS_SUCCESS);

  INFO("BEFORE: send buffer <%s> vs recv buffer <%s>\n", send_buffer, recv_buffer);

  ck_assert(neti->socket_sendto(socket, &send_buffer, &send_buffer_size, 0, &si_me, sizeof(si_me)) == STATUS_SUCCESS);
  ck_assert(send_buffer_size == ARRAY_SIZE(send_buffer));

  ck_assert(neti->socket_recv(socket, &recv_buffer, &recv_buffer_size, 0) == STATUS_SUCCESS);
  ck_assert(recv_buffer_size == ARRAY_SIZE(recv_buffer));

  INFO("AFTER: send buffer <%s> vs recv buffer <%s>\n", send_buffer, recv_buffer);

  ck_assert(getOsMemIntf()->memcmp(send_buffer, recv_buffer, ARRAY_SIZE(send_buffer)) == STATUS_SUCCESS);

  localUdpSocketDestroy(socket);
END_TEST

TCase *tcase_osnet_socket_udp(void)
{
  TCase *tc = tcase_create("TestCase OsNetIntf Socket UDP");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_osnet_setup, test_osnet_teardown);

  tcase_add_test(tc, test_osnet_NULL);
  tcase_add_test(tc, test_osnet_socket_udp_create_destroy);
  tcase_add_test(tc, test_osnet_socket_udp_send_recv);

  return tc;
}
