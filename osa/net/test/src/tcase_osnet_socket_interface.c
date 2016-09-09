#include "test_osnet_tcases.h"

#include <logging/logging.h>

#include "test_osnet_helper.h"

START_TEST(test_osnet_socket_interface_NULL)
  const OsNetIntf_t * const neti = getOsNetIntf();
  OsNetSocket_t * socket = (OsNetSocket_t *) 0x12345;
  const char_t * const ifname = "ifname";
  int32_t ifindex;
  ck_assert(neti->socket_index_for_interface(NULL, NULL, NULL) == STATUS_FAILURE);
  ck_assert(neti->socket_index_for_interface(socket, NULL, NULL) == STATUS_FAILURE);
  ck_assert(neti->socket_index_for_interface(NULL, ifname, NULL) == STATUS_FAILURE);
  ck_assert(neti->socket_index_for_interface(NULL, NULL, &ifindex) == STATUS_FAILURE);
  ck_assert(neti->socket_index_for_interface(socket, ifname, NULL) == STATUS_FAILURE);
  ck_assert(neti->socket_index_for_interface(socket, NULL, &ifindex) == STATUS_FAILURE);
  ck_assert(neti->socket_index_for_interface(NULL, ifname, &ifindex) == STATUS_FAILURE);
END_TEST

START_TEST(test_osnet_socket_interface_index)
  const OsNetIntf_t * const neti = getOsNetIntf();
  OsNetSocket_t * socket;
  const char_t * const ifname = "lo";
  int32_t ifindex;
  ck_assert(neti->socket_create(OSNETSOCKETTYPE_CAN, &socket) == STATUS_SUCCESS);
  ck_assert(neti->socket_index_for_interface(socket, ifname, &ifindex) == STATUS_SUCCESS);
  INFO("index for %s = %d\n", ifname, ifindex);
  ck_assert(neti->socket_destroy(socket) == STATUS_SUCCESS);
END_TEST

START_TEST(test_osnet_socket_interface_index_unkown)
  const OsNetIntf_t * const neti = getOsNetIntf();
  OsNetSocket_t * socket;
  const char_t * const ifname = "eth99";
  int32_t ifindex;
  ck_assert(neti->socket_create(OSNETSOCKETTYPE_CAN, &socket) == STATUS_SUCCESS);
  ck_assert(neti->socket_index_for_interface(socket, ifname, &ifindex) == STATUS_FAILURE);
  ck_assert(neti->socket_destroy(socket) == STATUS_SUCCESS);
END_TEST

TCase *tcase_osnet_socket_interface(void)
{
  TCase *tc = tcase_create("TestCase OsNetIntf Socket Interface");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_osnet_setup, test_osnet_teardown);

  tcase_add_test(tc, test_osnet_socket_interface_NULL);
  tcase_add_test(tc, test_osnet_socket_interface_index);
  tcase_add_test(tc, test_osnet_socket_interface_index_unkown);

  return tc;
}